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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    tNOMBRE = 258,
    tPLUS = 259,
    tMOINS = 260,
    tFOIS = 261,
    tDIVISE = 262,
    tPUISSANCE = 263,
    tOP = 264,
    tCP = 265,
    tOB = 266,
    tCB = 267,
    tIF = 268,
    tELSE = 269,
    tVAR = 270,
    tCOMPARAISON = 271,
    tEGAL = 272,
    tINFSTRICT = 273,
    tSUPSTRICT = 274,
    tSUPEGAL = 275,
    tINFEGAL = 276,
    tDIFF = 277,
    tNOT = 278,
    tINT = 279,
    tVOID = 280,
    tCHAR = 281,
    tVIRG = 282,
    tMAIN = 283,
    tCONST = 284,
    tNEG = 285
  };
#endif
/* Tokens.  */
#define tNOMBRE 258
#define tPLUS 259
#define tMOINS 260
#define tFOIS 261
#define tDIVISE 262
#define tPUISSANCE 263
#define tOP 264
#define tCP 265
#define tOB 266
#define tCB 267
#define tIF 268
#define tELSE 269
#define tVAR 270
#define tCOMPARAISON 271
#define tEGAL 272
#define tINFSTRICT 273
#define tSUPSTRICT 274
#define tSUPEGAL 275
#define tINFEGAL 276
#define tDIFF 277
#define tNOT 278
#define tINT 279
#define tVOID 280
#define tCHAR 281
#define tVIRG 282
#define tMAIN 283
#define tCONST 284
#define tNEG 285

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
