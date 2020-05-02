/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_SIMULATOR_TAB_H_INCLUDED
# define YY_YY_SIMULATOR_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    tADD = 258,
    tMUL = 259,
    tSOU = 260,
    tDIV = 261,
    tCOP = 262,
    tAFC = 263,
    tJMP = 264,
    tJMF = 265,
    tINF = 266,
    tSUP = 267,
    tCMP = 268,
    tSUE = 269,
    tINE = 270,
    tDIF = 271,
    tNOT = 272,
    tPRI = 273,
    tRET = 274,
    tJMT = 275,
    tNB = 276
  };
#endif
/* Tokens.  */
#define tADD 258
#define tMUL 259
#define tSOU 260
#define tDIV 261
#define tCOP 262
#define tAFC 263
#define tJMP 264
#define tJMF 265
#define tINF 266
#define tSUP 267
#define tCMP 268
#define tSUE 269
#define tINE 270
#define tDIF 271
#define tNOT 272
#define tPRI 273
#define tRET 274
#define tJMT 275
#define tNB 276

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 11 "simulator.y" /* yacc.c:1909  */

    int nb;

#line 100 "simulator.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SIMULATOR_TAB_H_INCLUDED  */
