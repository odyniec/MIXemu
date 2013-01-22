%{
#include <stdio.h>

#include "mix_types.h"
#include "mix_chars.h"
#include "errstr.h"
#include "mixasm.h"

#define yyerror(s) 1

extern int yylex();

mix_word_t w;

int f_empty = 0;

typedef struct _memc {
  mix_word_t val;
  struct _memc *next;
} mem_const_t;

mem_const_t *memconsts = NULL;
mem_const_t *mc_last = NULL;


int error(int e)
{
  fprintf(stderr, "%s:%d: %s\n", ifname, linenum,
    errstr(e));

  return e;
}


%}


%union {
    char*       t_string;
    mix_word_t  t_mix_word;
    long        t_long;
    mix_byte_t  t_mix_byte;
}

%token  SYMBOL
%token  LOCALH
%token  LOCALB
%token  LOCALF
%token  INSTR
%token  NUMBER
%token  EQU
%token  ORIG
%token  CON
%token  END
%token  ALF
%token  STRING
%token  _NEXTLOC
%token  MOD

%token  _ALF_ERROR

%left   '+' '-' '*' '/' MOD ':'

%type <t_string>    SYMBOL
%type <t_long>      LOCALH
%type <t_long>      LOCALB
%type <t_long>      LOCALF
%type <t_string>    INSTR
%type <t_mix_word>  NUMBER
%type <t_string>    STRING
%type <t_mix_word>  atom
%type <t_mix_word>  eatom
%type <t_mix_word>  expr
%type <t_mix_word>  a_part
%type <t_mix_byte>  f_part
%type <t_mix_word>  w_val
%type <t_mix_byte>  index
%type <t_mix_word>  instr

%%

input:
    | input line    { linenum++; }
;


line:   '\n'
    | equ '\n'
    | orig '\n'
    | con '\n'
    | alf '\n'
    | instr '\n'
        {
            fprintf(ofp, "%s #%d\n", sprintf_mix_word($1), linenum); 
        }
    | end '\n'
    | _NEXTLOC '\n' { loc++; }
    | error { return error(ERR_PARSE_ERROR); }
;


equ: SYMBOL EQU expr
        {
            if (hashtbl_get(symbols, $1) == NULL) {
                if (hashtbl_get(opcodes, $1) == NULL) {
                    mix_word_t *w = (mix_word_t *)malloc(sizeof(mix_word_t));
    
                    *w = $3;
                    hashtbl_put(symbols, $1, w);
                }
                else
                    return error(ERR_SYMBOL_INVALID);
            }
            else
                return error(ERR_SYMBOL_DEFINED);
        }
    | SYMBOL
        {
            if (hashtbl_get(symbols, $1) == NULL) {
                if (hashtbl_get(opcodes, $1) == NULL) {
                    mix_word_t *w = (mix_word_t *)malloc(sizeof(mix_word_t));

                    long_to_mix_word(loc, w);
                    hashtbl_put(symbols, $1, w);
                    loc++;
                }
                else
                    return error(ERR_SYMBOL_INVALID);
            }
            else
                return error(ERR_SYMBOL_DEFINED);
        }
    | LOCALH EQU expr
        {
            locsym_t *ls = (locsym_t *)malloc(sizeof(locsym_t));
        
            ls->loc = loc;
            ls->val = $3;
            ls->next = NULL;
        
            if (locsyms[$1] == NULL)
                locsyms[$1] = ls;
            else {
                locsym_t *last = locsyms[$1];
          
                while (last->next != NULL)
                    last = last->next;
          
                last->next = ls;
            }
        }
    | LOCALH
        {
            locsym_t *ls = (locsym_t *)malloc(sizeof(locsym_t));
        
            ls->loc = loc;
            long_to_mix_word(loc, &ls->val);
            ls->next = NULL;
        
            if (locsyms[$1] == NULL)
                locsyms[$1] = ls;
            else {
                locsym_t *last = locsyms[$1];
          
                while (last->next != NULL)
                    last = last->next;
          
                last->next = ls;
            }
            loc++;
        }
;


orig:   ORIG expr
        {
            mix_word_to_long($2, (long *)&loc);
            if (output)
                fprintf(ofp, "%04d\n", loc);
        }
    | SYMBOL ORIG expr
        {
            mix_word_t *w = (mix_word_t *)malloc(sizeof(mix_word_t));

            long_to_mix_word(loc, w);
            mix_word_to_long($3, (long *)&loc);
            if (output)
                fprintf(ofp, "%04d\n", loc);
        }
;


con:    CON w_val
        { 
            fprintf(ofp, "%s\n", sprintf_mix_word($2));
            loc++; 
        }
;


alf:    ALF STRING
        {
            mix_word_t w;
            int i;

            w.s = POS;
            for (i = 0; i < 5; i++)
                w.b[i] = ASCII_TO_MIX($2[i]);
        
            fprintf(ofp, "%s\n", sprintf_mix_word(w));
        }
    | ALF _ALF_ERROR
        { 
            printf("--> \"%d\"\n", yychar); 
            return error(ERR_INVALID_ALF);
        }
;


atom:   NUMBER  { $$ = $1; }
    | SYMBOL
        { 
            void *ptr = hashtbl_get(symbols, $1);
        
            if (ptr != NULL)
                $$ = *(mix_word_t *)ptr;
            else
                return error(ERR_SYMBOL_UNKNOWN);
        }
    | LOCALB
        {
            locsym_t *ls = locsyms[$1];

            if (ls != NULL) {
                while (ls->next != NULL && ls->next->loc < loc)
                    ls = ls->next;

                $$ = ls->val;
            }
            else
                return error(ERR_LOCAL_UNKNOWN);
        }
    | '*'   { long_to_mix_word((long)loc, &$$); }
;


/* Erroneous atom */
eatom:  LOCALF  { return error(ERR_LOCALF_IN_EXPR); }
;


expr:   atom
        { $$ = $1; }
    | '+' atom
        { $$ = $2; }
    | '-' atom
        { $$ = $2; $$.s = ($$.s == POS ? NEG : POS); }
    | expr '+' atom
        { mix_word_add($1, $3, &$$); }
    | expr '-' atom
        { mix_word_sub($1, $3, &$$); }
    | expr '*' atom
        { 
            mix_word_t w;
          
            mix_word_mul($1, $3, &w, &$$);
            /* w != 0 indicates an overflow */
        }
    | expr '/' atom
        {
            mix_word_t z = MIX_WORD_ZERO, w;

            /* 
             * NOTE: Division overflow cannot happen here, because always
             * abs($3) >= z. 
             * $3 == z means division by zero.
             */ 

            if (mix_word_div(z, $1, $3, &$$, &w) != 0)
                return error(ERR_DIV_BY_ZERO);
        }
    | expr MOD atom
        {
            mix_word_t z = MIX_WORD_ZERO, w;

            if (mix_word_div(z, $1, $3, &w, &$$) != 0)
                return error(ERR_DIV_BY_ZERO);
        }
    | expr ':' atom
        { 
            /* Assumption: result <= 63 */
            $$ = mix_word(POS, 0, 0, 0, 0, 0);
            $$.b[4] = $1.b[4] * 8 + $3.b[4];
        }
    /* Error detection rules follow */
    | eatom '+' expr    { }
    | eatom '-' expr    { }
    | eatom '*' expr    { }
    | eatom '/' expr    { }
    | eatom MOD expr    { }
    | eatom ':' expr    { }
    | expr '+' eatom    { }
    | expr '-' eatom    { }
    | expr '*' eatom    { }
    | expr '/' eatom    { }
    | expr MOD eatom    { }
    | expr ':' eatom    { }
;


instr:  INSTR a_part index f_part
        {
            mix_word_t *w = (mix_word_t *)hashtbl_get(opcodes, $1);

            if (w != NULL) {
                $$ = *w;
    
                /* Address */
                $$.s = $2.s;
                $$.b[0] = $2.b[3];
                $$.b[1] = $2.b[4];

                /* Index */
                $$.b[2] = $3;

                /* F-part */
                if (!f_empty)
                    $$.b[3] = $4;
                f_empty = 0;

                loc++;
            }
            else
                return error(ERR_INVALID_INSTR);
        }
;


a_part: { $$ = mix_word(POS, 0, 0, 0, 0, 0); }
    | expr      { $$ = $1; }
    | LOCALF
        {
            locsym_t *ls = locsyms[$1];

            if (ls != NULL) {
                while (ls != NULL && ls->loc <= loc)
                    ls = ls->next;

                $$ = ls->val; 
            }
            else
                return error(ERR_LOCAL_UNKNOWN);
        }
    | '=' w_val '='
        {
            mem_const_t *mc = (mem_const_t *)malloc(sizeof(mem_const_t));
        
            mc->val = $2;
            mc->next = NULL;

            if (memconsts == NULL)
                memconsts = mc;
            else
                mc_last->next = mc;
          
            mc_last = mc;

            long_to_mix_word((long)last_loc, &$$);

            last_loc++;
        }
;


f_part: { /* Empty F-part */ f_empty = 1; }
    | '(' expr ')'  { $$ = $2.b[4]; }
;


index:  { $$ = 0; }
    | ',' expr  { $$ = $2.b[4]; }
;


w_val:  expr f_part
        {
            $$ = MIX_WORD_ZERO;

            if (f_empty == 0)
                frag_stored($1, $2, &$$);
            else
                frag_stored($1, 5, &$$);
            f_empty = 0;
        }
    | w_val ',' expr f_part
        {
            $$ = $1;

            if (f_empty == 0)
                frag_stored($3, $4, &$$);
            else
                frag_stored($3, 5, &$$);
            f_empty = 0;
        }
;


end:    END w_val
        {
            long l;
            mem_const_t *mc;

            /* Memory constants */
            mc = memconsts;

            while (mc != NULL) {
                fprintf(ofp, "%s\n", sprintf_mix_word(mc->val));
                mc = mc->next;
            }

            mix_word_to_long($2, &l);
            fprintf(ofp, "%04d\n", l);
        }
;


%%
