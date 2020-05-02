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

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
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
    tCOMMA = 258,
    tIF = 259,
    tELSE = 260,
    tDO = 261,
    tWHILE = 262,
    tOP = 263,
    tCP = 264,
    tOB = 265,
    tCB = 266,
    tVAR = 267,
    tINT = 268,
    tVOID = 269,
    tCHAR = 270,
    tFLOAT = 271,
    tVIRG = 272,
    tMAIN = 273,
    tCONST = 274,
    tINT_VAL = 275,
    tFLOAT_VAL = 276,
    tCHAR_VAL = 277,
    tRETURN = 278,
    tPRINTF = 279,
    tPLUS = 280,
    tMOINS = 281,
    tFOIS = 282,
    tDIVISE = 283,
    tNEG = 284,
    tCOMPARAISON = 285,
    tINFSTRICT = 286,
    tSUPSTRICT = 287,
    tSUPEGAL = 288,
    tINFEGAL = 289,
    tDIFF = 290,
    tNOT = 291,
    tEGAL = 292
  };
#endif
/* Tokens.  */
#define tCOMMA 258
#define tIF 259
#define tELSE 260
#define tDO 261
#define tWHILE 262
#define tOP 263
#define tCP 264
#define tOB 265
#define tCB 266
#define tVAR 267
#define tINT 268
#define tVOID 269
#define tCHAR 270
#define tFLOAT 271
#define tVIRG 272
#define tMAIN 273
#define tCONST 274
#define tINT_VAL 275
#define tFLOAT_VAL 276
#define tCHAR_VAL 277
#define tRETURN 278
#define tPRINTF 279
#define tPLUS 280
#define tMOINS 281
#define tFOIS 282
#define tDIVISE 283
#define tNEG 284
#define tCOMPARAISON 285
#define tINFSTRICT 286
#define tSUPSTRICT 287
#define tSUPEGAL 288
#define tINFEGAL 289
#define tDIFF 290
#define tNOT 291
#define tEGAL 292

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 150 "parser.y" /* yacc.c:1909  */

//on déclare une struct plutôt que directement $<INT>$ pour pouvoir renvoyer plusieurs valeurs 
//#ADDR pour l'interpreteur assembleur et FLOAT pour l'analyse par valeur du C dans le parser
	struct s{
	int INT;
	float FLOAT;
	char* STR;
	int ADDR;
	} s;

#line 139 "parser.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
