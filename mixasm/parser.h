/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
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

/* Line 2068 of yacc.c  */
#line 38 "parser.y"

    char*       t_string;
    mix_word_t  t_mix_word;
    long        t_long;
    mix_byte_t  t_mix_byte;



/* Line 2068 of yacc.c  */
#line 93 "parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


