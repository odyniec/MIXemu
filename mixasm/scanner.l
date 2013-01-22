%{
#include <string.h>

#include "mix.h"
#include "parser.h"

#include "mixasm.h"

/* EOF flag */
int end_of_file = 0;

int newline = 1;

int pass = 1;

%}

%option noyywrap
%option stack

SPACE   [ \t]+
DIGIT   [0-9]
LETTER  [A-Z]
CHAR    [.,()+*/=$<>@;:']|"-"

STRCHR  (" "|{DIGIT}|{LETTER}|{CHAR})

NUMBER  {DIGIT}{1,10}

SYMBOL  {DIGIT}*{LETTER}+({DIGIT}|{LETTER})*
LOCALH  {DIGIT}H
LOCALB  {DIGIT}B
LOCALF  {DIGIT}F

INSTR   {LETTER}+({DIGIT}|{LETTER})*


%x FIRST
%x SECOND

%x NEWLINE

%x symbol
%x op
%x symdef
%x addr
%x end
%x equ
%x orig
%x con
%x alf

%x ignore

%%

<FIRST,SECOND>{
    \n  return '\n';

    ^{SPACE}?(\*|#) { yy_push_state(ignore); }
}

<FIRST>{
    ^{LOCALH}   {
        yytext[1] = '\0';
        yylval.t_long = atol(yytext);
        yy_push_state(symdef);
        return LOCALH;
    }

    ^{SYMBOL}   {
        yy_push_state(symdef);
        yylval.t_string = strdup(yytext);
        return SYMBOL;
    }

    ORIG    {
        yy_push_state(orig);
        return ORIG;
    }

    {INSTR} {
        yy_push_state(ignore);
        return _NEXTLOC;
    }

    .
}

<symdef>{
    EQU {
        yy_push_state(equ); 
        return EQU; 
    }

    \n  {
        yy_pop_state();
        yyless(0);
    }

    .
}

<SECOND>{
    /* Ignore symbol name */
    ^{SYMBOL}   yy_push_state(op);


    ^{SPACE}    yy_push_state(op);

    EQU /* Do nothing */

    /* FIXME: Is this necessary? probably not */
    {SYMBOL}    {
        yylval.t_string = strdup(yytext);
        return SYMBOL;
    }

    .   /* Do nothing */
}

<op>{
    EQU { yy_push_state(ignore); }

    ORIG    {
        yy_push_state(orig);
        return ORIG;
    }

    END {
        yy_push_state(end);
        return END;
    }

    CON {
        yy_push_state(con);
        return CON;
    }

    ALF {
        yy_push_state(alf);
        return ALF;
    }

    {INSTR} {
        yylval.t_string = strdup(yytext);
        yy_push_state(addr);
        return INSTR;
    }

    \n  {
        yy_pop_state();
        yyless(0);
    }
}

<addr>{
    /* Forward references are only valid in <addr> */
    {LOCALF}    {
        yytext[1] = '\0';
        yylval.t_long = atol(yytext);
        return LOCALF;
    }
    /* Memory constants as well */
    "=" return '=';
}


<end,equ,con,orig>{LOCALF}  {
    /* INVALID - for error detection */
    return LOCALF;
}


<addr,end,equ,con,orig>{
    {NUMBER}    {
        long_to_mix_word(atol(yytext), &yylval.t_mix_word);
        return NUMBER; 
    }

    {LOCALB}    {
        yytext[1] = '\0';
        yylval.t_long = atol(yytext);
        return LOCALB;
    }

    {SYMBOL}    {
        yylval.t_string = strdup(yytext);
        return SYMBOL;
    }

    "+" return '+';
    "-" return '-';
    "*" return '*';
    "/" return '/';
    "//"    return MOD;
    ":" return ':';
    "," return ',';
    "(" return '(';
    ")" return ')';

    \n  { 
        yy_pop_state();
        yyless(0);
    }
}


<alf>{
    {SPACE}+"\""{STRCHR}{5}"\"" {
        char *s;
        *(s = strrchr(yytext, '"')) = '\0';
        yylval.t_string = strdup(strchr(yytext, '"')+1);
        return STRING;
    }

    "\t"{STRCHR}{5} {
        yylval.t_string = strdup(yytext+1);
        return STRING;
    }

    "  "{STRCHR}{5} {
        yylval.t_string = strdup(yytext+2);
        return STRING;
    }

    " "({LETTER}|{DIGIT}){STRCHR}{4}    {
        yylval.t_string = strdup(yytext+1);
        return STRING;
    }

    \n  {
        yy_pop_state();
        yyless(0);
    }
    
    .*  { return _ALF_ERROR; }
}

<ignore>{
    \n  {
        yy_pop_state();
        yyless(0);
    }

    .*
}

<*>{
    {SPACE}
}


%%


void lex_first_pass()
{ 
    yyin = ifp;

    BEGIN(FIRST);
}


void lex_second_pass()
{
    BEGIN(SECOND);
}

