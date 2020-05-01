
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

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

/* Line 189 of yacc.c  */
#line 2 "parser.y"


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "symboltable.h"
#define output "interpreter/output.asm"
#define MAX_INSTRUCTIONS 1000
#define SIZE_INSTRUCTION 30
#define MAX_INSIDE_IF 10
#define MAX_INSIDE_LOOP 10
int OPTI;
int user_want_opti;

int tempAddr = 100;
int success = 1; 
int voidOrIntMain=0;//void by def
int hasAreturn=0;
char instruction[MAX_INSTRUCTIONS][SIZE_INSTRUCTION];
int cp=0;
int depth=0;
int old_depth[MAX_INSIDE_IF];
int jumpToPatch[MAX_INSIDE_IF];
int activeIf[MAX_INSIDE_IF];
int old_depthW[MAX_INSIDE_LOOP];
int jumpToPatchW[MAX_INSIDE_LOOP];
int lastJumpW=-1;
int lastJump=-1;


int activeInstruction=1;
int wasInActifState=1;
int wasInActifStateIf=1;

char * type;
FILE* file;
int yylex(void);
int yyerror(const char *s);

char* last_var;
float declaration_a_virg_last_type;

//NB: les var sont passées à l'assembleur par valeur, on à presque une interprétation du C par le parser qui peut de fait optimiser l'ASM (pas fait pour garder ttes les ope affichées
// juste les var intermediaires ne font plus sens (conservées pour respecter le sujet))

//NB: AFC = on affecte une cte 
// COP on copie la valeur d'une addresse dans une autre
//value ou addr2
//AFC ou COP
void AutreOperation(const char * operation, int addr1,float value) {
if(activeInstruction){
	//l'ASM ne gère pas les float => écris à la int
	printf("[YACC %s %d %f ]", operation, addr1, value);
	//fprintf(file, "%s %d %.0f \n",operation, addr1, value);
	snprintf(instruction[cp],30,"%s %d %.0f \n",operation, addr1, value);
	cp++;
	}
}
//operation arithmetique
void operation(const char * operation,int addresse_result, int addr1, int addr2) {
if(activeInstruction){
	printf("[YACC %s %d %d %d ]", operation,addresse_result, addr1, addr2);
	snprintf(instruction[cp],30,"%s %d %d %d \n",operation,addresse_result, addr1, addr2);
	cp++;
	}
}

void PrintfOperation(char *name, char* value, int addr){
if(activeInstruction){
	printf(" [YACC PRINTF : la variable est : %s et vaut %s ]",name,value);
	//fprintf(file, "PRI %d \n",addr);
	snprintf(instruction[cp],30,"PRI %d \n",addr);
	cp++;
	free(value);
	}
}
void ReturnOperation(int addr, int value){
if(activeInstruction){
	printf(" [YACC RETURN value: %d ]",value);
	//fprintf(file, "RET %d \n",addr);
	snprintf(instruction[cp],30,"RET %d \n",addr);
	cp++;
	}
}
//rq if else <=> if if (avec deuxième if true auto (rq: syntax mod like true ASM jmf fait référence à l'instruction precedente pour check la cond #interpretation part)
//rq: start line =0
void IfOperation(void){
if(activeInstruction){
	lastJump++;
	old_depth[lastJump]=depth;
	jumpToPatch[lastJump]=cp;
	depth+=MAX_INSIDE_IF;
	cp++;
	}
}
void ElseOperation(void){
if(activeInstruction){
	//car if seul différent de if else
	//lastJump+1 car repatchage d'un if déjà patché (le if gère comme un if normal) 
	printf("\n [YACC REPATCH IF false goto line: %d]",cp+1);
	snprintf(instruction[jumpToPatch[lastJump+1]],30,"JMF %d \n",cp+1);
	lastJump++;
	depth++;
	jumpToPatch[lastJump]=cp;
	cp++;
	}
}

void IfPatchOperation(int addr){
if(activeInstruction){
	printf("\n [YACC PATCH IF addr false goto line: %d]",cp);
	snprintf(instruction[jumpToPatch[lastJump]],30,"JMF %d \n",addr);//if else addr=cp+1, sinon cp
	depth=old_depth[lastJump];
	lastJump--;
	}
}
void ElsePatchOperation(void){
if(activeInstruction){
	printf("\n [YACC PATCH ELSE false goto line: %d]",cp);
	snprintf(instruction[jumpToPatch[lastJump]],30,"JMP %d \n",cp);
	lastJump--;
	depth--;
	}
}

void loopStart(void){
if(activeInstruction){
	lastJumpW++;
	old_depthW[lastJumpW]=depth;
	jumpToPatchW[lastJumpW]=cp;
	depth+=MAX_INSIDE_LOOP;
	}

}
void loopEnd(void){
if(activeInstruction){
	printf("\n [YACC PATCH DO WHILE addr goto line: %d]",cp);
	snprintf(instruction[cp],30,"JMT %d \n",jumpToPatchW[lastJumpW]);
	depth=old_depthW[lastJumpW];
	lastJumpW--;
	cp++;
	}
}



/* Line 189 of yacc.c  */
#line 222 "parser.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
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
     tMOINS = 280,
     tPLUS = 281,
     tDIVISE = 282,
     tFOIS = 283,
     tNEG = 284,
     tSUPSTRICT = 285,
     tINFSTRICT = 286,
     tCOMPARAISON = 287,
     tDIFF = 288,
     tINFEGAL = 289,
     tSUPEGAL = 290,
     tEGAL = 291,
     tNOT = 292
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 150 "parser.y"

//on déclare une struct plutôt que directement $<INT>$ pour pouvoir renvoyer plusieurs valeurs 
//#ADDR pour l'interpreteur assembleur et FLOAT pour l'analyse par valeur du C dans le parser
	struct s{
	int INT;
	float FLOAT;
	char* STR;
	int ADDR;
	} s;



/* Line 214 of yacc.c  */
#line 308 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 320 "parser.tab.c"

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
# if YYENABLE_NLS
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
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

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   230

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNRULES -- Number of states.  */
#define YYNSTATES  149

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,    11,    17,    19,    21,    23,    25,
      29,    31,    33,    35,    39,    43,    47,    51,    55,    59,
      63,    67,    71,    75,    78,    81,    85,    87,    88,    93,
      94,    99,   100,   101,   109,   110,   114,   115,   116,   124,
     125,   126,   134,   135,   136,   145,   146,   147,   157,   158,
     159,   169,   170,   176,   177,   183,   184,   185,   193,   197,
     200,   201,   202,   213,   214,   222,   223,   229,   230,   236
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      39,     0,    -1,    -1,    13,    18,    40,     8,     9,    42,
      -1,    14,    18,     8,     9,    42,    -1,    13,    -1,    16,
      -1,    14,    -1,    15,    -1,    10,    52,    11,    -1,    20,
      -1,    21,    -1,    22,    -1,    43,    26,    43,    -1,    43,
      25,    43,    -1,    43,    28,    43,    -1,    43,    27,    43,
      -1,    43,    32,    43,    -1,    43,    31,    43,    -1,    43,
      30,    43,    -1,    43,    35,    43,    -1,    43,    34,    43,
      -1,    43,    33,    43,    -1,    37,    43,    -1,    25,    43,
      -1,     8,    43,     9,    -1,    12,    -1,    -1,    12,     3,
      45,    44,    -1,    -1,    12,    17,    46,    52,    -1,    -1,
      -1,     4,     8,    48,    43,     9,    49,    42,    -1,    -1,
       5,    51,    42,    -1,    -1,    -1,    12,    26,    26,    17,
      53,    54,    52,    -1,    -1,    -1,    12,    25,    25,    17,
      55,    56,    52,    -1,    -1,    -1,    41,    12,    36,    57,
      43,    17,    58,    52,    -1,    -1,    -1,    41,    19,    12,
      36,    59,    43,    17,    60,    52,    -1,    -1,    -1,    19,
      41,    12,    36,    61,    43,    17,    62,    52,    -1,    -1,
      41,    12,    17,    63,    52,    -1,    -1,    41,    12,     3,
      64,    44,    -1,    -1,    -1,    12,    36,    65,    43,    17,
      66,    52,    -1,    47,    50,    52,    -1,    47,    52,    -1,
      -1,    -1,     6,    67,    42,     7,     8,    43,     9,    68,
      17,    52,    -1,    -1,    24,     8,    12,    69,     9,    17,
      52,    -1,    -1,    23,    12,    17,    70,    52,    -1,    -1,
      23,    20,    17,    71,    52,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   191,   191,   191,   192,   195,   196,   197,   198,   204,
     209,   215,   221,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   247,   248,   269,   269,   276,
     276,   284,   288,   284,   301,   301,   304,   304,   304,   340,
     340,   340,   375,   375,   375,   401,   401,   401,   423,   423,
     423,   445,   445,   452,   452,   460,   460,   460,   486,   487,
     488,   488,   488,   489,   489,   490,   490,   508,   508,   520
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "tCOMMA", "tIF", "tELSE", "tDO",
  "tWHILE", "tOP", "tCP", "tOB", "tCB", "tVAR", "tINT", "tVOID", "tCHAR",
  "tFLOAT", "tVIRG", "tMAIN", "tCONST", "tINT_VAL", "tFLOAT_VAL",
  "tCHAR_VAL", "tRETURN", "tPRINTF", "tMOINS", "tPLUS", "tDIVISE", "tFOIS",
  "tNEG", "tSUPSTRICT", "tINFSTRICT", "tCOMPARAISON", "tDIFF", "tINFEGAL",
  "tSUPEGAL", "tEGAL", "tNOT", "$accept", "Program", "$@1", "Type", "Body",
  "Expression", "Liste", "$@2", "$@3", "If", "$@4", "$@5", "Else", "$@6",
  "Instruction", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12", "$@13",
  "$@14", "$@15", "$@16", "$@17", "$@18", "$@19", "$@20", "$@21", "$@22",
  "$@23", "@24", "@25", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    40,    39,    39,    41,    41,    41,    41,    42,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    45,    44,    46,
      44,    48,    49,    47,    51,    50,    53,    54,    52,    55,
      56,    52,    57,    58,    52,    59,    60,    52,    61,    62,
      52,    63,    52,    64,    52,    65,    66,    52,    52,    52,
      67,    68,    52,    69,    52,    70,    52,    71,    52,    52
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     6,     5,     1,     1,     1,     1,     3,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     3,     1,     0,     4,     0,
       4,     0,     0,     7,     0,     3,     0,     0,     7,     0,
       0,     7,     0,     0,     8,     0,     0,     9,     0,     0,
       9,     0,     5,     0,     5,     0,     0,     7,     3,     2,
       0,     0,    10,     0,     7,     0,     5,     0,     5,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     2,     0,     1,     0,     0,     0,
       0,     0,    69,     4,     3,     0,    60,     0,     5,     7,
       8,     6,     0,     0,     0,     0,    69,     0,    31,     0,
       0,     0,    55,     0,     0,     0,     0,     0,     0,    34,
      69,    59,     9,     0,     0,     0,     0,     0,     0,    65,
      67,    63,    53,    51,    42,     0,     0,    58,     0,    26,
      10,    11,    12,     0,     0,     0,     0,    39,    36,     0,
      48,    69,    69,     0,     0,    69,     0,    45,    35,     0,
      24,    23,    32,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    40,    37,    56,     0,    66,    68,
       0,     0,    54,    52,     0,     0,    25,     0,    14,    13,
      16,    15,    19,    18,    17,    22,    21,    20,     0,    69,
      69,    69,     0,    69,    27,    29,    43,     0,    33,    61,
      41,    38,    57,    49,    64,     0,    69,    69,    46,     0,
      69,    28,    30,    44,    69,    69,    50,    47,    62
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     7,    25,    13,    65,   102,   135,   136,    26,
      43,   107,    40,    56,    27,    95,   120,    94,   119,    76,
     137,   105,   144,    97,   140,    75,    74,    47,   121,    29,
     139,    73,    71,    72
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -33
static const yytype_int16 yypact[] =
{
      -6,     5,     9,    19,   -33,    16,   -33,    20,    21,    28,
      32,    32,   152,   -33,   -33,    35,   -33,   -20,   -33,   -33,
     -33,   -33,    -3,   -11,    40,    10,   138,    61,   -33,    32,
      49,    50,   -33,    63,    60,    65,    77,     0,    78,   -33,
     152,   -33,   -33,    13,    84,    75,    79,    13,    64,   -33,
     -33,   -33,   -33,   -33,   -33,    66,    32,   -33,    13,   -33,
     -33,   -33,   -33,    13,    13,    53,    91,   -33,   -33,   153,
     -33,   152,   152,    92,    93,   152,    13,   -33,   -33,    95,
     195,   -33,   -33,    13,    13,    13,    13,    13,    13,    13,
      13,    13,    13,    13,   -33,   -33,   -33,    13,   -33,   -33,
      86,     1,   -33,   -33,   165,    13,   -33,    32,    36,    36,
     195,   195,     6,     6,     6,   -33,   -33,   -33,   106,   152,
     152,   152,   177,   152,   -33,   -33,   -33,   189,   -33,   -33,
     -33,   -33,   -33,   -33,   -33,    93,   152,   152,   -33,    89,
     152,   -33,   -33,   -33,   152,   152,   -33,   -33,   -33
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -33,   -33,   -33,    85,    -9,   -32,   -27,   -33,   -33,   -33,
     -33,   -33,   -33,   -33,   -26,   -33,   -33,   -33,   -33,   -33,
     -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,
     -33,   -33,   -33,   -33
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      41,    34,    14,    52,   124,    30,    31,     1,     2,    35,
      18,    19,    20,    21,    57,    69,    32,    53,   125,     6,
      44,    58,    37,     4,     8,    59,    79,     5,     9,    38,
      10,    80,    81,    60,    61,    62,    54,    11,    63,    90,
      91,    92,    12,    28,   104,    98,    99,    78,    36,   103,
      64,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,    82,    85,    86,   122,    87,    88,    89,    90,
      91,    92,    42,   127,    45,    48,    46,    49,    83,    84,
      85,    86,    50,    87,    88,    89,    90,    91,    92,    51,
      55,    66,    67,   130,   131,   132,    68,   134,   128,    93,
      70,   100,    77,   123,   106,   101,   145,    33,   141,     0,
     142,   143,     0,     0,   146,   129,     0,     0,   147,   148,
      83,    84,    85,    86,     0,    87,    88,    89,    90,    91,
      92,    83,    84,    85,    86,     0,    87,    88,    89,    90,
      91,    92,    15,    39,    16,     0,     0,     0,     0,     0,
      17,    18,    19,    20,    21,     0,    15,    22,    16,     0,
       0,    23,    24,     0,    17,    18,    19,    20,    21,     0,
      96,    22,     0,     0,     0,    23,    24,     0,    83,    84,
      85,    86,   126,    87,    88,    89,    90,    91,    92,     0,
      83,    84,    85,    86,   133,    87,    88,    89,    90,    91,
      92,     0,    83,    84,    85,    86,   138,    87,    88,    89,
      90,    91,    92,     0,    83,    84,    85,    86,     0,    87,
      88,    89,    90,    91,    92,    87,    88,    89,    90,    91,
      92
};

static const yytype_int16 yycheck[] =
{
      26,    12,    11,     3,     3,    25,    26,    13,    14,    20,
      13,    14,    15,    16,    40,    47,    36,    17,    17,     0,
      29,     8,    12,    18,     8,    12,    58,    18,     8,    19,
       9,    63,    64,    20,    21,    22,    36,     9,    25,    33,
      34,    35,    10,     8,    76,    71,    72,    56,     8,    75,
      37,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,     9,    27,    28,    97,    30,    31,    32,    33,
      34,    35,    11,   105,    25,    12,    26,    17,    25,    26,
      27,    28,    17,    30,    31,    32,    33,    34,    35,    12,
      12,     7,    17,   119,   120,   121,    17,   123,   107,     8,
      36,     9,    36,    17,     9,    12,    17,    22,   135,    -1,
     136,   137,    -1,    -1,   140,     9,    -1,    -1,   144,   145,
      25,    26,    27,    28,    -1,    30,    31,    32,    33,    34,
      35,    25,    26,    27,    28,    -1,    30,    31,    32,    33,
      34,    35,     4,     5,     6,    -1,    -1,    -1,    -1,    -1,
      12,    13,    14,    15,    16,    -1,     4,    19,     6,    -1,
      -1,    23,    24,    -1,    12,    13,    14,    15,    16,    -1,
      17,    19,    -1,    -1,    -1,    23,    24,    -1,    25,    26,
      27,    28,    17,    30,    31,    32,    33,    34,    35,    -1,
      25,    26,    27,    28,    17,    30,    31,    32,    33,    34,
      35,    -1,    25,    26,    27,    28,    17,    30,    31,    32,
      33,    34,    35,    -1,    25,    26,    27,    28,    -1,    30,
      31,    32,    33,    34,    35,    30,    31,    32,    33,    34,
      35
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    13,    14,    39,    18,    18,     0,    40,     8,     8,
       9,     9,    10,    42,    42,     4,     6,    12,    13,    14,
      15,    16,    19,    23,    24,    41,    47,    52,     8,    67,
      25,    26,    36,    41,    12,    20,     8,    12,    19,     5,
      50,    52,    11,    48,    42,    25,    26,    65,    12,    17,
      17,    12,     3,    17,    36,    12,    51,    52,     8,    12,
      20,    21,    22,    25,    37,    43,     7,    17,    17,    43,
      36,    70,    71,    69,    64,    63,    57,    36,    42,    43,
      43,    43,     9,    25,    26,    27,    28,    30,    31,    32,
      33,    34,    35,     8,    55,    53,    17,    61,    52,    52,
       9,    12,    44,    52,    43,    59,     9,    49,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    56,
      54,    66,    43,    17,     3,    17,    17,    43,    42,     9,
      52,    52,    52,    17,    52,    45,    46,    58,    17,    68,
      62,    44,    52,    52,    60,    17,    52,    52,    52
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
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



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
  if (yyn == YYPACT_NINF)
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
        case 2:

/* Line 1455 of yacc.c  */
#line 191 "parser.y"
    { voidOrIntMain=1;;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 191 "parser.y"
    {if(hasAreturn ==0){printf("\033[01;33m Warning no return in a non-void function ! \033[0m");};}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 192 "parser.y"
    {if(hasAreturn == 1){printf("\033[01;33m Warning return in a void function ! \033[0m");};}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 195 "parser.y"
    {(yyval.s).INT =INT_TYPE;;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 196 "parser.y"
    {(yyval.s).INT = FLOAT_TYPE;;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 197 "parser.y"
    {(yyval.s).INT = VOID_TYPE;;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 198 "parser.y"
    {(yyval.s).INT =CHAR_TYPE;;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 209 "parser.y"
    { 
    		(yyval.s).ADDR=tempAddr;
    		(yyval.s).FLOAT = (yyvsp[(1) - (1)].s).FLOAT;
		AutreOperation("AFC",tempAddr, (yyval.s).FLOAT);
		tempAddr++;
		;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 215 "parser.y"
    { (yyval.s).FLOAT = (yyvsp[(1) - (1)].s).FLOAT;
  		(yyval.s).ADDR=tempAddr;
		//printf("[YACC AFF addr: %d value:%f ]", tempAddr, $<s>$.FLOAT);
		AutreOperation("AFC",tempAddr, (yyval.s).FLOAT);
		tempAddr++;
		;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 221 "parser.y"
    { (yyval.s).STR = (yyvsp[(1) - (1)].s).STR;
  		(yyval.s).ADDR=tempAddr;
  		(yyval.s).FLOAT=(yyvsp[(1) - (1)].s).FLOAT;
		AutreOperation("AFC",tempAddr, (yyval.s).FLOAT);
		tempAddr++;
		;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 227 "parser.y"
    { (yyval.s).FLOAT=(yyvsp[(1) - (3)].s).FLOAT+(yyvsp[(3) - (3)].s).FLOAT;(yyval.s).ADDR=tempAddr;operation("ADD",tempAddr, (yyvsp[(1) - (3)].s).ADDR, (yyvsp[(3) - (3)].s).ADDR);tempAddr++;;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 228 "parser.y"
    { (yyval.s).FLOAT=(yyvsp[(1) - (3)].s).FLOAT-(yyvsp[(3) - (3)].s).FLOAT;(yyval.s).ADDR=tempAddr;operation("SOU",tempAddr, (yyvsp[(1) - (3)].s).ADDR, (yyvsp[(3) - (3)].s).ADDR);tempAddr++;;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 229 "parser.y"
    { (yyval.s).FLOAT=(yyvsp[(1) - (3)].s).FLOAT*(yyvsp[(3) - (3)].s).FLOAT;(yyval.s).ADDR=tempAddr; operation("MUL",tempAddr, (yyvsp[(1) - (3)].s).ADDR, (yyvsp[(3) - (3)].s).ADDR);tempAddr++;;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 230 "parser.y"
    { (yyval.s).FLOAT=(yyvsp[(1) - (3)].s).FLOAT/(yyvsp[(3) - (3)].s).FLOAT;(yyval.s).ADDR=tempAddr; operation("DIV",tempAddr, (yyvsp[(1) - (3)].s).ADDR, (yyvsp[(3) - (3)].s).ADDR);tempAddr++;;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 231 "parser.y"
    { (yyval.s).FLOAT=(float)((yyvsp[(1) - (3)].s).FLOAT==(yyvsp[(3) - (3)].s).FLOAT?1:0);printf("\n\n r: %f 1: %f 3: %f",(yyval.s).FLOAT,(yyvsp[(1) - (3)].s).FLOAT,(yyvsp[(3) - (3)].s).FLOAT);(yyval.s).ADDR=tempAddr; operation("CMP",tempAddr, (yyvsp[(1) - (3)].s).ADDR, (yyvsp[(3) - (3)].s).ADDR);tempAddr++;;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 232 "parser.y"
    { (yyval.s).FLOAT=((yyvsp[(1) - (3)].s).FLOAT < (yyvsp[(3) - (3)].s).FLOAT?1:0);(yyval.s).ADDR=tempAddr; operation("INF",tempAddr, (yyvsp[(1) - (3)].s).ADDR, (yyvsp[(3) - (3)].s).ADDR);tempAddr++;;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 233 "parser.y"
    { (yyval.s).FLOAT=((yyvsp[(1) - (3)].s).FLOAT > (yyvsp[(3) - (3)].s).FLOAT?1:0);(yyval.s).ADDR=tempAddr; operation("SUP",tempAddr, (yyvsp[(1) - (3)].s).ADDR, (yyvsp[(3) - (3)].s).ADDR);tempAddr++;;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 234 "parser.y"
    { (yyval.s).FLOAT=((yyvsp[(1) - (3)].s).FLOAT >= (yyvsp[(3) - (3)].s).FLOAT?1:0);(yyval.s).ADDR=tempAddr; operation("SUE",tempAddr, (yyvsp[(1) - (3)].s).ADDR, (yyvsp[(3) - (3)].s).ADDR);tempAddr++;;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 235 "parser.y"
    { (yyval.s).FLOAT=((yyvsp[(1) - (3)].s).FLOAT <= (yyvsp[(3) - (3)].s).FLOAT?1:0);(yyval.s).ADDR=tempAddr; operation("INE",tempAddr, (yyvsp[(1) - (3)].s).ADDR, (yyvsp[(3) - (3)].s).ADDR);tempAddr++;;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 236 "parser.y"
    { (yyval.s).FLOAT=((yyvsp[(1) - (3)].s).FLOAT != (yyvsp[(3) - (3)].s).FLOAT?1:0);(yyval.s).ADDR=tempAddr; operation("DIF",tempAddr, (yyvsp[(1) - (3)].s).ADDR, (yyvsp[(3) - (3)].s).ADDR);tempAddr++;;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 237 "parser.y"
    { (yyval.s).FLOAT=((yyvsp[(1) - (2)].s).FLOAT= ((yyvsp[(2) - (2)].s).FLOAT==0)?1:0);(yyval.s).ADDR=tempAddr; operation("NOT",tempAddr, (yyvsp[(1) - (2)].s).ADDR, (yyvsp[(2) - (2)].s).ADDR);tempAddr++;;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 238 "parser.y"
    {
		(yyval.s).FLOAT = -(yyvsp[(2) - (2)].s).FLOAT;
		(yyval.s).ADDR = tempAddr;
		//printf("[YACC COP %d 0 ]", tempAddr);
		//printf("[YACC SOU %d %d %f ]", tempAddr, tempAddr, $<s>2.FLOAT);
		//AutreOperation("COP",tempAddr, 0);
		operation("SOU",tempAddr, tempAddr, (yyvsp[(2) - (2)].s).ADDR);
		tempAddr++;
	;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 247 "parser.y"
    { (yyval.s).FLOAT=(yyvsp[(2) - (3)].s).FLOAT; (yyval.s).ADDR=(yyvsp[(2) - (3)].s).ADDR; ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 248 "parser.y"
    {/*^$$= value_of_variable_tVar */
  		//!\ il ne faut pas renvoyer l'adresse de la var mais une copie temp (sinon modifie définitivement la var)
  		//bad conversion (aka char)
  		char *buff=getValeurToPrint((yyvsp[(1) - (1)].s).STR);
  		if(getType((yyvsp[(1) - (1)].s).STR)==CHAR_TYPE)
  			(yyval.s).FLOAT=(float)buff[0];
  		else{
  		(yyval.s).FLOAT = atof(buff);
  		free(buff);
  		}
		(yyval.s).ADDR=tempAddr;
		int varAddr = getAdresse((yyvsp[(1) - (1)].s).STR,depth);
		if(!varEstIni(varAddr)) {
			printf(" \033[01;31m FATAL ERROR :unitialized variable \033[0m");
			exit(-1);
		}
		AutreOperation("COP",tempAddr, varAddr);
		tempAddr++; 
		;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 269 "parser.y"
    {
		if(alreadyDeclaredVar((yyvsp[(1) - (2)].s).STR)) {
				printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
				exit(-1);
		}
		ajouter((yyvsp[(1) - (2)].s).STR, declaration_a_virg_last_type, false, false,depth);
  	;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 276 "parser.y"
    {
      		if(alreadyDeclaredVar((yyvsp[(1) - (2)].s).STR)) {
					printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
					exit(-1);
		}
		ajouter((yyvsp[(1) - (2)].s).STR, declaration_a_virg_last_type, false, false,depth);
 	;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 284 "parser.y"
    {if(OPTI){
		wasInActifStateIf=activeInstruction;
		activeInstruction=0;}
		;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 288 "parser.y"
    {
			/*GENERER JMF */ 
			if(OPTI){
				if(wasInActifStateIf){
					activeIf[lastJump]=(yyvsp[(4) - (5)].s).FLOAT; 
					activeInstruction=(yyvsp[(4) - (5)].s).FLOAT;
				}
			}else{
				IfOperation();
			}
		;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 298 "parser.y"
    {if(!OPTI && activeInstruction){
			IfPatchOperation(cp);
			}activeInstruction=1;;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 301 "parser.y"
    { /*GENERER JMP*/activeInstruction=activeIf[lastJump]?0:1;if(!OPTI && activeInstruction){ElseOperation();};}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 301 "parser.y"
    {if(!OPTI && activeInstruction){ElsePatchOperation();}activeInstruction=1;;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 304 "parser.y"
    {wasInActifState=activeInstruction;if(OPTI)activeInstruction=0;;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 304 "parser.y"
    {
  		if(wasInActifState){
		int varAddr = getAdresse((yyvsp[(1) - (5)].s.STR),depth);		
		if(isSymbolConst(varAddr)) {
			printf("\033[01;31m FATAL ERROR : const variable cannot reaffect value \033[0m");
			exit(-1);
		}
		if(!varEstIni(varAddr)) {
			printf("\033[01;31m This variable is not initialized cannot quick increment \033[0m");
			exit(-1);
		}
		int type=getType((yyvsp[(1) - (5)].s.STR));
		if(type==FLOAT_TYPE || type==INT_TYPE){
			char *buff=getValeurToPrint((yyvsp[(1) - (5)].s.STR));
			int value;
			if(getType((yyvsp[(1) - (5)].s).STR)==CHAR_TYPE)
				value=(float)buff[0];
			else{
			value = atof(buff);
			free(buff);
  			}
			setValeurFloat((yyvsp[(1) - (5)].s.STR),value+1);
			AutreOperation("AFC",tempAddr, 1);//on stocke 1 dans une adresse temp
			operation("ADD",varAddr,varAddr,tempAddr);//on stocke dans varAddr varAddr+1
			//rq: ope atomique => pas besoin d'incrementer tempAddr (on peut écraser le 1 ss probleme)
			if(OPTI){
				activeInstruction=1;
				AutreOperation("AFC",varAddr, value+1);
			}
		}
		else {
			printf("\033[01;31m FATAL ERROR : This type doesn't permit quick increment  \033[0m");
			exit(-1);
		}
		}
   ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 340 "parser.y"
    {wasInActifState=activeInstruction;if(OPTI)activeInstruction=0;;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 340 "parser.y"
    {
 		if(wasInActifState){
   		int varAddr = getAdresse((yyvsp[(1) - (5)].s.STR),depth);		
		if(isSymbolConst(varAddr)) {
			printf("\033[01;31m FATAL ERROR : const variable cannot reaffect value \033[0m");
			exit(-1);
		}
		if(!varEstIni(varAddr)) {
			printf("\033[01;31m FATAL ERROR : This variable is not initialized cannot quick decrement \033[0m");
			exit(-1);
		}
		int type=getType((yyvsp[(1) - (5)].s.STR));
		if(type==FLOAT_TYPE || type==INT_TYPE){
			int value;
			char *buff=getValeurToPrint((yyvsp[(1) - (5)].s.STR));
			if(getType((yyvsp[(1) - (5)].s).STR)==CHAR_TYPE)
				value=(float)buff[0];
			else{
				value = atof(buff);
				free(buff);
  			}
			setValeurFloat((yyvsp[(1) - (5)].s.STR),value-1);
			AutreOperation("AFC",tempAddr, 1);//on stocke 1 dans une adresse temp
			operation("SOU",varAddr,varAddr,tempAddr);//on stocke dans varAddr varAddr-1
			if(OPTI){
				activeInstruction=1;
				AutreOperation("AFC",varAddr, value-1);
			}
		}
		else {
			printf("\033[01;31m FATAL ERROR : This type doesn't permit quick increment  \033[0m");
			exit(-1);
		}
		}
   ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 375 "parser.y"
    {wasInActifState=activeInstruction;if(OPTI)activeInstruction=0;;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 375 "parser.y"
    {
		if(wasInActifState){
		if(alreadyDeclaredVar((yyvsp[(2) - (6)].s).STR)) {
			printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
			exit(-1);
		}
		int varAddr =ajouter((yyvsp[(2) - (6)].s).STR, (yyvsp[(1) - (6)].s).INT, true,false,depth)-1;
		if(!varEstIni(varAddr)) {
			iniVar(varAddr);
		}
  		int type=(yyvsp[(1) - (6)].s).INT;
		if(type==FLOAT_TYPE || type==INT_TYPE){
			setValeurFloat((yyvsp[(2) - (6)].s).STR,(float)(yyvsp[(5) - (6)].s).FLOAT);
			AutreOperation("COP",varAddr, (yyvsp[(5) - (6)].s).ADDR);
		}
		else if(type==CHAR_TYPE){
			setValeurStr((yyvsp[(2) - (6)].s.STR),(yyvsp[(5) - (6)].s).STR);
			//printf("[YACC COP %d : %s]", varAddr , $<s>5.STR);
			AutreOperation("COP",varAddr, (yyvsp[(5) - (6)].s).ADDR);
		}
		if(OPTI){
		activeInstruction=1;
		AutreOperation("AFC",varAddr, (float)(yyvsp[(5) - (6)].s).FLOAT);
		}
		}
  ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 401 "parser.y"
    {wasInActifState=activeInstruction;if(OPTI)activeInstruction=0;;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 401 "parser.y"
    {
		if(wasInActifState){
		if(alreadyDeclaredVar((yyvsp[(3) - (7)].s).STR)) {
			printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
			exit(-1);
		}
  		int varAddr = ajouter((yyvsp[(3) - (7)].s.STR), (yyvsp[(1) - (7)].s).INT, true,true,depth)-1;//cst
		int type=(yyvsp[(1) - (7)].s).INT;
		if(type==FLOAT_TYPE || type==INT_TYPE){
			setValeurFloat((yyvsp[(3) - (7)].s.STR),(float)(yyvsp[(6) - (7)].s).FLOAT);
			AutreOperation("COP",varAddr, (yyvsp[(6) - (7)].s).ADDR);
		}
		else if(type==CHAR_TYPE){
			setValeurStr((yyvsp[(3) - (7)].s.STR),(yyvsp[(6) - (7)].s).STR);
			AutreOperation("COP",varAddr, (yyvsp[(6) - (7)].s).ADDR);
		}
		if(OPTI){
			activeInstruction=1;
			AutreOperation("AFC",varAddr, (float)(yyvsp[(6) - (7)].s).FLOAT);
		}
		}
  ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 423 "parser.y"
    {wasInActifState=activeInstruction;if(OPTI)activeInstruction=0;;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 423 "parser.y"
    {
 		if(wasInActifState){
 		if(alreadyDeclaredVar((yyvsp[(3) - (7)].s).STR)) {
					printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
					exit(-1);
		}
    		int varAddr = ajouter((yyvsp[(3) - (7)].s.STR), (yyvsp[(2) - (7)].s).INT, true,true,depth)-1;
  		int type=(yyvsp[(2) - (7)].s).INT;
  		if(type==FLOAT_TYPE || type==INT_TYPE){
				setValeurFloat((yyvsp[(3) - (7)].s.STR),(float)(yyvsp[(6) - (7)].s).FLOAT);
				AutreOperation("COP",varAddr, (yyvsp[(6) - (7)].s).ADDR);
			}
		else if(type==CHAR_TYPE){
			setValeurStr((yyvsp[(3) - (7)].s.STR),(yyvsp[(6) - (7)].s).STR);
			AutreOperation("COP",varAddr, (yyvsp[(6) - (7)].s).ADDR);
		}
		if(OPTI && wasInActifState){
			activeInstruction=1;
			AutreOperation("AFC",varAddr, (float)(yyvsp[(6) - (7)].s).FLOAT);
		}
		}
  ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 445 "parser.y"
    {
		if(alreadyDeclaredVar((yyvsp[(2) - (3)].s).STR)) {
					printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
					exit(-1);
		}
		ajouter((yyvsp[(2) - (3)].s.STR), (yyvsp[(1) - (3)].s).INT, false, false,depth);
  ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 452 "parser.y"
    {
	if(alreadyDeclaredVar((yyvsp[(2) - (3)].s).STR)) {
				printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
				exit(-1);
	}
	declaration_a_virg_last_type= (yyvsp[(1) - (3)].s).INT;
	ajouter((yyvsp[(2) - (3)].s.STR), (yyvsp[(1) - (3)].s).INT, false, false,depth);
  ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 460 "parser.y"
    {wasInActifState=activeInstruction;if(OPTI)activeInstruction=0;;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 460 "parser.y"
    {
	if(wasInActifState){
	int varAddr = getAdresse((yyvsp[(1) - (5)].s.STR),depth);		
			if(isSymbolConst(varAddr)) {
				printf("\033[01;31m FATAL ERROR : const variable cannot reaffect value \033[0m");
				exit(-1);
			}
			if(!varEstIni(varAddr)) {
				iniVar(varAddr);
			}
		int type=getType((yyvsp[(1) - (5)].s.STR));
		if(type==FLOAT_TYPE || type==INT_TYPE){
			setValeurFloat((yyvsp[(1) - (5)].s.STR),(yyvsp[(4) - (5)].s).FLOAT);
			AutreOperation("COP",varAddr, (yyvsp[(4) - (5)].s).ADDR);
		}
		else if(type==CHAR_TYPE){
			setValeurStr((yyvsp[(1) - (5)].s.STR),(yyvsp[(4) - (5)].s).STR);
			AutreOperation("COP",varAddr, (yyvsp[(4) - (5)].s).ADDR);
		}
		if(OPTI){
			activeInstruction=1;
			AutreOperation("AFC",varAddr, (float)(yyvsp[(4) - (5)].s).FLOAT);
		}
		}
	
  ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 488 "parser.y"
    { loopStart();OPTI=0;/*pas d'opti de boucle*/;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 488 "parser.y"
    {loopEnd();OPTI=user_want_opti;;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 489 "parser.y"
    { if(activeInstruction){PrintfOperation((yyvsp[(3) - (3)].s.STR), getValeurToPrint((yyvsp[(3) - (3)].s.STR)),getAdresse((yyvsp[(3) - (3)].s.STR),depth) );};}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 490 "parser.y"
    {
			int varAddr = getAdresse((yyvsp[(2) - (3)].s.STR),depth);
			if(voidOrIntMain==0){
				printf("\033[01;31m FATAL ERROR : void function cannot return a value, switch to int main() \033[0m");
				exit(-1);
			}
			if(!varEstIni(varAddr)) {
				printf("\033[01;33m Warning return uninitialized variable \033[0m");
			}
			hasAreturn =1;
			char* buff=getValeurToPrint((yyvsp[(2) - (3)].s.STR));
			(yyval.s).INT =atoi(buff);
			free(buff);
			(yyval.s).ADDR=tempAddr;
			AutreOperation("COP",tempAddr, varAddr);
			ReturnOperation((yyval.s).ADDR,(yyval.s).INT);
			tempAddr++;
			;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 508 "parser.y"
    {
		if(voidOrIntMain==0){
						printf("\033[01;31m FATAL ERROR : void function cannot return a value, switch to int main() \033[0m");
						exit(-1);
			}
		hasAreturn =1;
	         (yyval.s).INT = (yyvsp[(2) - (3)].s).INT;
		(yyval.s).ADDR=tempAddr;
		AutreOperation("AFC",tempAddr, (yyval.s).INT);
		ReturnOperation((yyval.s).ADDR,(yyval.s).INT);
		tempAddr++;
		;}
    break;



/* Line 1455 of yacc.c  */
#line 2273 "parser.tab.c"
      default: break;
    }
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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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
      if (yyn != YYPACT_NINF)
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
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



/* Line 1675 of yacc.c  */
#line 525 "parser.y"

//rappel: printf gère seulement une variable
//  | Expression tPUISSANCE Expression { $$=pow($1,$3); }
int yywrap(void)
{
   return 1;
}
int main(int argc,  char** argv)
{	
    if(argc ==2)
    	user_want_opti=atoi(argv[1]);
    else
    	user_want_opti=0;
    OPTI=user_want_opti;
    setOpti(OPTI);
    file = fopen(output,"w+");    
    yyparse();
    for(int i=0; i<cp;i++)
    	fprintf(file,instruction[i]);
    fclose(file);
    /*if(hasOneIf && OPTI)
    	printf("\033[01;33m Warning use optimisation mode with if !Conditionnal statements are not yet managed in optimisation \033[0m");*/
    if(success)
    	printf("Parsing Successful\n");
    freeAll();
    return 0;
}

int yyerror(const char *msg)
{
	//extern int yylineno;
	printf("Parsing Failed\n %s\n",msg);
	success = 0;
	return 0;
}


