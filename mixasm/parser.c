/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "parser.y"

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




/* Line 268 of yacc.c  */
#line 108 "parser.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     SYMBOL = 258,
     LOCALH = 259,
     LOCALB = 260,
     LOCALF = 261,
     INSTR = 262,
     NUMBER = 263,
     EQU = 264,
     ORIG = 265,
     CON = 266,
     END = 267,
     ALF = 268,
     STRING = 269,
     _NEXTLOC = 270,
     MOD = 271,
     _ALF_ERROR = 272
   };
#endif
/* Tokens.  */
#define SYMBOL 258
#define LOCALH 259
#define LOCALB 260
#define LOCALF 261
#define INSTR 262
#define NUMBER 263
#define EQU 264
#define ORIG 265
#define CON 266
#define END 267
#define ALF 268
#define STRING 269
#define _NEXTLOC 270
#define MOD 271
#define _ALF_ERROR 272




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 38 "parser.y"

    char*       t_string;
    mix_word_t  t_mix_word;
    long        t_long;
    mix_byte_t  t_mix_byte;



/* Line 293 of yacc.c  */
#line 187 "parser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 199 "parser.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   126

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  28
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  16
/* YYNRULES -- Number of rules.  */
#define YYNRULES  59
/* YYNRULES -- Number of states.  */
#define YYNSTATES  97

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   272

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      23,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      25,    26,    20,    18,    27,    19,     2,    21,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    22,     2,
       2,    24,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     7,     9,    12,    15,    18,    21,
      24,    27,    30,    32,    36,    38,    42,    44,    47,    51,
      54,    57,    60,    62,    64,    66,    68,    70,    72,    75,
      78,    82,    86,    90,    94,    98,   102,   106,   110,   114,
     118,   122,   126,   130,   134,   138,   142,   146,   150,   155,
     156,   158,   160,   164,   165,   169,   170,   173,   176,   181
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      29,     0,    -1,    -1,    29,    30,    -1,    23,    -1,    31,
      23,    -1,    32,    23,    -1,    33,    23,    -1,    34,    23,
      -1,    38,    23,    -1,    43,    23,    -1,    15,    23,    -1,
       1,    -1,     3,     9,    37,    -1,     3,    -1,     4,     9,
      37,    -1,     4,    -1,    10,    37,    -1,     3,    10,    37,
      -1,    11,    42,    -1,    13,    14,    -1,    13,    17,    -1,
       8,    -1,     3,    -1,     5,    -1,    20,    -1,     6,    -1,
      35,    -1,    18,    35,    -1,    19,    35,    -1,    37,    18,
      35,    -1,    37,    19,    35,    -1,    37,    20,    35,    -1,
      37,    21,    35,    -1,    37,    16,    35,    -1,    37,    22,
      35,    -1,    36,    18,    37,    -1,    36,    19,    37,    -1,
      36,    20,    37,    -1,    36,    21,    37,    -1,    36,    16,
      37,    -1,    36,    22,    37,    -1,    37,    18,    36,    -1,
      37,    19,    36,    -1,    37,    20,    36,    -1,    37,    21,
      36,    -1,    37,    16,    36,    -1,    37,    22,    36,    -1,
       7,    39,    41,    40,    -1,    -1,    37,    -1,     6,    -1,
      24,    42,    24,    -1,    -1,    25,    37,    26,    -1,    -1,
      27,    37,    -1,    37,    40,    -1,    42,    27,    37,    40,
      -1,    12,    42,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    82,    82,    83,    87,    88,    89,    90,    91,    92,
      96,    97,    98,   102,   117,   133,   152,   175,   181,   193,
     201,   212,   220,   221,   230,   243,   248,   252,   254,   256,
     258,   260,   262,   269,   282,   289,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   311,   339,
     340,   341,   354,   375,   376,   380,   381,   385,   395,   408
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SYMBOL", "LOCALH", "LOCALB", "LOCALF",
  "INSTR", "NUMBER", "EQU", "ORIG", "CON", "END", "ALF", "STRING",
  "_NEXTLOC", "MOD", "_ALF_ERROR", "'+'", "'-'", "'*'", "'/'", "':'",
  "'\\n'", "'='", "'('", "')'", "','", "$accept", "input", "line", "equ",
  "orig", "con", "alf", "atom", "eatom", "expr", "instr", "a_part",
  "f_part", "index", "w_val", "end", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,    43,    45,
      42,    47,    58,    10,    61,    40,    41,    44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    28,    29,    29,    30,    30,    30,    30,    30,    30,
      30,    30,    30,    31,    31,    31,    31,    32,    32,    33,
      34,    34,    35,    35,    35,    35,    36,    37,    37,    37,
      37,    37,    37,    37,    37,    37,    37,    37,    37,    37,
      37,    37,    37,    37,    37,    37,    37,    37,    38,    39,
      39,    39,    39,    40,    40,    41,    41,    42,    42,    43
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     2,     2,     2,     2,     2,
       2,     2,     1,     3,     1,     3,     1,     2,     3,     2,
       2,     2,     1,     1,     1,     1,     1,     1,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     4,     0,
       1,     1,     3,     0,     3,     0,     2,     2,     4,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,    12,    14,    16,    49,     0,     0,     0,
       0,     0,     4,     3,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    23,    24,    26,    22,     0,     0,    25,
       0,    27,     0,    50,    55,    26,    17,    53,    19,    59,
      20,    21,    11,     5,     6,     7,     8,     9,    10,    13,
      18,    15,    28,    29,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    53,     0,
      57,     0,    52,    40,    36,    37,    38,    39,    41,    34,
      46,    30,    42,    31,    43,    32,    44,    33,    45,    35,
      47,    56,    48,     0,    53,    54,    58
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,    13,    14,    15,    16,    17,    31,    32,    37,
      18,    34,    70,    68,    38,    19
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -65
static const yytype_int8 yypact[] =
{
     -65,    66,   -65,   -65,     8,     3,     2,    26,    26,    26,
      11,    -4,   -65,   -65,     0,     1,    10,    12,    19,    20,
      26,    26,    26,   -65,   -65,   -14,   -65,    77,    77,   -65,
      26,   -65,    91,    98,    21,   -65,    98,    83,    35,    35,
     -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,    98,
      98,    98,   -65,   -65,    32,    26,    26,    26,    26,    26,
      26,    52,    52,    52,    52,    52,    52,    26,    22,    26,
     -65,    26,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,
     -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,
     -65,    98,   -65,    72,    83,   -65,   -65
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -65,   -65,   -65,   -65,   -65,   -65,   -65,   -25,    60,    -6,
     -65,   -65,   -64,   -65,    -3,   -65
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -52
static const yytype_int8 yytable[] =
{
      33,    36,    52,    53,    92,    23,    39,    24,    25,   -51,
      26,   -51,    22,   -51,    49,    50,    51,    20,    21,    42,
      27,    28,    29,    43,    44,    40,    30,    54,    41,    23,
      96,    24,    35,    45,    26,    46,    79,    81,    83,    85,
      87,    89,    47,    48,    27,    28,    29,    69,    67,    73,
      74,    75,    76,    77,    78,    23,    72,    24,    35,    71,
      26,    91,    71,    93,     0,    94,     2,     3,     0,     4,
       5,     0,    29,     6,     0,     0,     7,     8,     9,    10,
      23,    11,    24,     0,     0,    26,     0,     0,    61,    12,
      62,    63,    64,    65,    66,     0,     0,    29,    95,    61,
       0,    62,    63,    64,    65,    66,     0,    55,    69,    56,
      57,    58,    59,    60,    61,     0,    62,    63,    64,    65,
      66,    80,    82,    84,    86,    88,    90
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-65))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
       6,     7,    27,    28,    68,     3,     9,     5,     6,    23,
       8,    25,     9,    27,    20,    21,    22,     9,    10,    23,
      18,    19,    20,    23,    23,    14,    24,    30,    17,     3,
      94,     5,     6,    23,     8,    23,    61,    62,    63,    64,
      65,    66,    23,    23,    18,    19,    20,    25,    27,    55,
      56,    57,    58,    59,    60,     3,    24,     5,     6,    27,
       8,    67,    27,    69,    -1,    71,     0,     1,    -1,     3,
       4,    -1,    20,     7,    -1,    -1,    10,    11,    12,    13,
       3,    15,     5,    -1,    -1,     8,    -1,    -1,    16,    23,
      18,    19,    20,    21,    22,    -1,    -1,    20,    26,    16,
      -1,    18,    19,    20,    21,    22,    -1,    16,    25,    18,
      19,    20,    21,    22,    16,    -1,    18,    19,    20,    21,
      22,    61,    62,    63,    64,    65,    66
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    29,     0,     1,     3,     4,     7,    10,    11,    12,
      13,    15,    23,    30,    31,    32,    33,    34,    38,    43,
       9,    10,     9,     3,     5,     6,     8,    18,    19,    20,
      24,    35,    36,    37,    39,     6,    37,    37,    42,    42,
      14,    17,    23,    23,    23,    23,    23,    23,    23,    37,
      37,    37,    35,    35,    42,    16,    18,    19,    20,    21,
      22,    16,    18,    19,    20,    21,    22,    27,    41,    25,
      40,    27,    24,    37,    37,    37,    37,    37,    37,    35,
      36,    35,    36,    35,    36,    35,    36,    35,    36,    35,
      36,    37,    40,    37,    37,    26,    40
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:

/* Line 1806 of yacc.c  */
#line 83 "parser.y"
    { linenum++; }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 93 "parser.y"
    {
            fprintf(ofp, "%s #%d\n", sprintf_mix_word((yyvsp[(1) - (2)].t_mix_word)), linenum); 
        }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 97 "parser.y"
    { loc++; }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 98 "parser.y"
    { return error(ERR_PARSE_ERROR); }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 103 "parser.y"
    {
            if (hashtbl_get(symbols, (yyvsp[(1) - (3)].t_string)) == NULL) {
                if (hashtbl_get(opcodes, (yyvsp[(1) - (3)].t_string)) == NULL) {
                    mix_word_t *w = (mix_word_t *)malloc(sizeof(mix_word_t));
    
                    *w = (yyvsp[(3) - (3)].t_mix_word);
                    hashtbl_put(symbols, (yyvsp[(1) - (3)].t_string), w);
                }
                else
                    return error(ERR_SYMBOL_INVALID);
            }
            else
                return error(ERR_SYMBOL_DEFINED);
        }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 118 "parser.y"
    {
            if (hashtbl_get(symbols, (yyvsp[(1) - (1)].t_string)) == NULL) {
                if (hashtbl_get(opcodes, (yyvsp[(1) - (1)].t_string)) == NULL) {
                    mix_word_t *w = (mix_word_t *)malloc(sizeof(mix_word_t));

                    long_to_mix_word(loc, w);
                    hashtbl_put(symbols, (yyvsp[(1) - (1)].t_string), w);
                    loc++;
                }
                else
                    return error(ERR_SYMBOL_INVALID);
            }
            else
                return error(ERR_SYMBOL_DEFINED);
        }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 134 "parser.y"
    {
            locsym_t *ls = (locsym_t *)malloc(sizeof(locsym_t));
        
            ls->loc = loc;
            ls->val = (yyvsp[(3) - (3)].t_mix_word);
            ls->next = NULL;
        
            if (locsyms[(yyvsp[(1) - (3)].t_long)] == NULL)
                locsyms[(yyvsp[(1) - (3)].t_long)] = ls;
            else {
                locsym_t *last = locsyms[(yyvsp[(1) - (3)].t_long)];
          
                while (last->next != NULL)
                    last = last->next;
          
                last->next = ls;
            }
        }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 153 "parser.y"
    {
            locsym_t *ls = (locsym_t *)malloc(sizeof(locsym_t));
        
            ls->loc = loc;
            long_to_mix_word(loc, &ls->val);
            ls->next = NULL;
        
            if (locsyms[(yyvsp[(1) - (1)].t_long)] == NULL)
                locsyms[(yyvsp[(1) - (1)].t_long)] = ls;
            else {
                locsym_t *last = locsyms[(yyvsp[(1) - (1)].t_long)];
          
                while (last->next != NULL)
                    last = last->next;
          
                last->next = ls;
            }
            loc++;
        }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 176 "parser.y"
    {
            mix_word_to_long((yyvsp[(2) - (2)].t_mix_word), (long *)&loc);
            if (output)
                fprintf(ofp, "%04d\n", loc);
        }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 182 "parser.y"
    {
            mix_word_t *w = (mix_word_t *)malloc(sizeof(mix_word_t));

            long_to_mix_word(loc, w);
            mix_word_to_long((yyvsp[(3) - (3)].t_mix_word), (long *)&loc);
            if (output)
                fprintf(ofp, "%04d\n", loc);
        }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 194 "parser.y"
    { 
            fprintf(ofp, "%s\n", sprintf_mix_word((yyvsp[(2) - (2)].t_mix_word)));
            loc++; 
        }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 202 "parser.y"
    {
            mix_word_t w;
            int i;

            w.s = POS;
            for (i = 0; i < 5; i++)
                w.b[i] = ASCII_TO_MIX((yyvsp[(2) - (2)].t_string)[i]);
        
            fprintf(ofp, "%s\n", sprintf_mix_word(w));
        }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 213 "parser.y"
    { 
            printf("--> \"%d\"\n", yychar); 
            return error(ERR_INVALID_ALF);
        }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 220 "parser.y"
    { (yyval.t_mix_word) = (yyvsp[(1) - (1)].t_mix_word); }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 222 "parser.y"
    { 
            void *ptr = hashtbl_get(symbols, (yyvsp[(1) - (1)].t_string));
        
            if (ptr != NULL)
                (yyval.t_mix_word) = *(mix_word_t *)ptr;
            else
                return error(ERR_SYMBOL_UNKNOWN);
        }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 231 "parser.y"
    {
            locsym_t *ls = locsyms[(yyvsp[(1) - (1)].t_long)];

            if (ls != NULL) {
                while (ls->next != NULL && ls->next->loc < loc)
                    ls = ls->next;

                (yyval.t_mix_word) = ls->val;
            }
            else
                return error(ERR_LOCAL_UNKNOWN);
        }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 243 "parser.y"
    { long_to_mix_word((long)loc, &(yyval.t_mix_word)); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 248 "parser.y"
    { return error(ERR_LOCALF_IN_EXPR); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 253 "parser.y"
    { (yyval.t_mix_word) = (yyvsp[(1) - (1)].t_mix_word); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 255 "parser.y"
    { (yyval.t_mix_word) = (yyvsp[(2) - (2)].t_mix_word); }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 257 "parser.y"
    { (yyval.t_mix_word) = (yyvsp[(2) - (2)].t_mix_word); (yyval.t_mix_word).s = ((yyval.t_mix_word).s == POS ? NEG : POS); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 259 "parser.y"
    { mix_word_add((yyvsp[(1) - (3)].t_mix_word), (yyvsp[(3) - (3)].t_mix_word), &(yyval.t_mix_word)); }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 261 "parser.y"
    { mix_word_sub((yyvsp[(1) - (3)].t_mix_word), (yyvsp[(3) - (3)].t_mix_word), &(yyval.t_mix_word)); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 263 "parser.y"
    { 
            mix_word_t w;
          
            mix_word_mul((yyvsp[(1) - (3)].t_mix_word), (yyvsp[(3) - (3)].t_mix_word), &w, &(yyval.t_mix_word));
            /* w != 0 indicates an overflow */
        }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 270 "parser.y"
    {
            mix_word_t z = MIX_WORD_ZERO, w;

            /* 
             * NOTE: Division overflow cannot happen here, because always
             * abs($3) >= z. 
             * $3 == z means division by zero.
             */ 

            if (mix_word_div(z, (yyvsp[(1) - (3)].t_mix_word), (yyvsp[(3) - (3)].t_mix_word), &(yyval.t_mix_word), &w) != 0)
                return error(ERR_DIV_BY_ZERO);
        }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 283 "parser.y"
    {
            mix_word_t z = MIX_WORD_ZERO, w;

            if (mix_word_div(z, (yyvsp[(1) - (3)].t_mix_word), (yyvsp[(3) - (3)].t_mix_word), &w, &(yyval.t_mix_word)) != 0)
                return error(ERR_DIV_BY_ZERO);
        }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 290 "parser.y"
    { 
            /* Assumption: result <= 63 */
            (yyval.t_mix_word) = mix_word(POS, 0, 0, 0, 0, 0);
            (yyval.t_mix_word).b[4] = (yyvsp[(1) - (3)].t_mix_word).b[4] * 8 + (yyvsp[(3) - (3)].t_mix_word).b[4];
        }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 296 "parser.y"
    { }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 297 "parser.y"
    { }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 298 "parser.y"
    { }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 299 "parser.y"
    { }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 300 "parser.y"
    { }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 301 "parser.y"
    { }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 302 "parser.y"
    { }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 303 "parser.y"
    { }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 304 "parser.y"
    { }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 305 "parser.y"
    { }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 306 "parser.y"
    { }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 307 "parser.y"
    { }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 312 "parser.y"
    {
            mix_word_t *w = (mix_word_t *)hashtbl_get(opcodes, (yyvsp[(1) - (4)].t_string));

            if (w != NULL) {
                (yyval.t_mix_word) = *w;
    
                /* Address */
                (yyval.t_mix_word).s = (yyvsp[(2) - (4)].t_mix_word).s;
                (yyval.t_mix_word).b[0] = (yyvsp[(2) - (4)].t_mix_word).b[3];
                (yyval.t_mix_word).b[1] = (yyvsp[(2) - (4)].t_mix_word).b[4];

                /* Index */
                (yyval.t_mix_word).b[2] = (yyvsp[(3) - (4)].t_mix_byte);

                /* F-part */
                if (!f_empty)
                    (yyval.t_mix_word).b[3] = (yyvsp[(4) - (4)].t_mix_byte);
                f_empty = 0;

                loc++;
            }
            else
                return error(ERR_INVALID_INSTR);
        }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 339 "parser.y"
    { (yyval.t_mix_word) = mix_word(POS, 0, 0, 0, 0, 0); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 340 "parser.y"
    { (yyval.t_mix_word) = (yyvsp[(1) - (1)].t_mix_word); }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 342 "parser.y"
    {
            locsym_t *ls = locsyms[(yyvsp[(1) - (1)].t_long)];

            if (ls != NULL) {
                while (ls != NULL && ls->loc <= loc)
                    ls = ls->next;

                (yyval.t_mix_word) = ls->val; 
            }
            else
                return error(ERR_LOCAL_UNKNOWN);
        }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 355 "parser.y"
    {
            mem_const_t *mc = (mem_const_t *)malloc(sizeof(mem_const_t));
        
            mc->val = (yyvsp[(2) - (3)].t_mix_word);
            mc->next = NULL;

            if (memconsts == NULL)
                memconsts = mc;
            else
                mc_last->next = mc;
          
            mc_last = mc;

            long_to_mix_word((long)last_loc, &(yyval.t_mix_word));

            last_loc++;
        }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 375 "parser.y"
    { /* Empty F-part */ f_empty = 1; }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 376 "parser.y"
    { (yyval.t_mix_byte) = (yyvsp[(2) - (3)].t_mix_word).b[4]; }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 380 "parser.y"
    { (yyval.t_mix_byte) = 0; }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 381 "parser.y"
    { (yyval.t_mix_byte) = (yyvsp[(2) - (2)].t_mix_word).b[4]; }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 386 "parser.y"
    {
            (yyval.t_mix_word) = MIX_WORD_ZERO;

            if (f_empty == 0)
                frag_stored((yyvsp[(1) - (2)].t_mix_word), (yyvsp[(2) - (2)].t_mix_byte), &(yyval.t_mix_word));
            else
                frag_stored((yyvsp[(1) - (2)].t_mix_word), 5, &(yyval.t_mix_word));
            f_empty = 0;
        }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 396 "parser.y"
    {
            (yyval.t_mix_word) = (yyvsp[(1) - (4)].t_mix_word);

            if (f_empty == 0)
                frag_stored((yyvsp[(3) - (4)].t_mix_word), (yyvsp[(4) - (4)].t_mix_byte), &(yyval.t_mix_word));
            else
                frag_stored((yyvsp[(3) - (4)].t_mix_word), 5, &(yyval.t_mix_word));
            f_empty = 0;
        }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 409 "parser.y"
    {
            long l;
            mem_const_t *mc;

            /* Memory constants */
            mc = memconsts;

            while (mc != NULL) {
                fprintf(ofp, "%s\n", sprintf_mix_word(mc->val));
                mc = mc->next;
            }

            mix_word_to_long((yyvsp[(2) - (2)].t_mix_word), &l);
            fprintf(ofp, "%04d\n", l);
        }
    break;



/* Line 1806 of yacc.c  */
#line 2077 "parser.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 427 "parser.y"


