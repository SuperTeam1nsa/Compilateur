/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 2 "parser.y" /* yacc.c:339  */


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


#line 214 "parser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
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
#line 150 "parser.y" /* yacc.c:355  */

//on déclare une struct plutôt que directement $<INT>$ pour pouvoir renvoyer plusieurs valeurs 
//#ADDR pour l'interpreteur assembleur et FLOAT pour l'analyse par valeur du C dans le parser
	struct s{
	int INT;
	float FLOAT;
	char* STR;
	int ADDR;
	} s;

#line 339 "parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 356 "parser.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   229

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  149

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
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

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "tCOMMA", "tIF", "tELSE", "tDO",
  "tWHILE", "tOP", "tCP", "tOB", "tCB", "tVAR", "tINT", "tVOID", "tCHAR",
  "tFLOAT", "tVIRG", "tMAIN", "tCONST", "tINT_VAL", "tFLOAT_VAL",
  "tCHAR_VAL", "tRETURN", "tPRINTF", "tPLUS", "tMOINS", "tFOIS", "tDIVISE",
  "tNEG", "tCOMPARAISON", "tINFSTRICT", "tSUPSTRICT", "tSUPEGAL",
  "tINFEGAL", "tDIFF", "tNOT", "tEGAL", "$accept", "Program", "$@1",
  "Type", "Body", "Expression", "Liste", "$@2", "$@3", "If", "$@4", "$@5",
  "Else", "$@6", "Instruction", "$@7", "$@8", "$@9", "$@10", "$@11",
  "$@12", "$@13", "$@14", "$@15", "$@16", "$@17", "$@18", "$@19", "$@20",
  "$@21", "$@22", "$@23", "@24", "@25", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292
};
# endif

#define YYPACT_NINF -33

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-33)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -3,    -5,    -2,     6,   -33,    16,   -33,    40,    41,    55,
      53,    53,   160,   -33,   -33,    69,   -33,   -18,   -33,   -33,
     -33,   -33,    14,   -11,    70,    -7,   146,    68,   -33,    53,
      56,    58,   -33,    73,    65,    71,    75,     0,    77,   -33,
     160,   -33,   -33,    54,    79,    86,    96,    54,    59,   -33,
     -33,   -33,   -33,   -33,   -33,    78,    53,   -33,    54,   -33,
     -33,   -33,   -33,    54,    54,    74,    83,   -33,   -33,     8,
     -33,   160,   160,   107,    80,   160,    54,   -33,   -33,   103,
      37,   -33,   -33,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,   -33,   -33,   -33,    54,   -33,   -33,
     100,     1,   -33,   -33,   161,    54,   -33,    53,   194,   194,
      37,    37,   -12,   -12,   -12,   -33,   -33,   -33,   114,   160,
     160,   160,   173,   160,   -33,   -33,   -33,   185,   -33,   -33,
     -33,   -33,   -33,   -33,   -33,    80,   160,   160,   -33,   104,
     160,   -33,   -33,   -33,   160,   160,   -33,   -33,   -33
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     2,     0,     1,     0,     0,     0,
       0,     0,    69,     4,     3,     0,    60,     0,     5,     7,
       8,     6,     0,     0,     0,     0,    69,     0,    31,     0,
       0,     0,    55,     0,     0,     0,     0,     0,     0,    34,
      69,    59,     9,     0,     0,     0,     0,     0,     0,    65,
      67,    63,    53,    51,    42,     0,     0,    58,     0,    26,
      10,    11,    12,     0,     0,     0,     0,    36,    39,     0,
      48,    69,    69,     0,     0,    69,     0,    45,    35,     0,
      24,    23,    32,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    37,    40,    56,     0,    66,    68,
       0,     0,    54,    52,     0,     0,    25,     0,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,     0,    69,
      69,    69,     0,    69,    27,    29,    43,     0,    33,    61,
      38,    41,    57,    49,    64,     0,    69,    69,    46,     0,
      69,    28,    30,    44,    69,    69,    50,    47,    62
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -33,   -33,   -33,    98,    -9,   -32,   -13,   -33,   -33,   -33,
     -33,   -33,   -33,   -33,   -26,   -33,   -33,   -33,   -33,   -33,
     -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,
     -33,   -33,   -33,   -33
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     7,    25,    13,    65,   102,   135,   136,    26,
      43,   107,    40,    56,    27,    94,   119,    95,   120,    76,
     137,   105,   144,    97,   140,    75,    74,    47,   121,    29,
     139,    73,    71,    72
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      41,    34,    14,    52,   124,    37,     6,    30,    31,    35,
       1,     2,    38,     4,    57,    69,     5,    53,   125,    32,
      44,    90,    91,    92,     8,    96,    79,    18,    19,    20,
      21,    80,    81,    83,    84,    85,    86,    54,    87,    88,
      89,    90,    91,    92,   104,    98,    99,    78,     9,   103,
      10,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,    58,    12,    11,   122,    59,    87,    88,    89,
      90,    91,    92,   127,    60,    61,    62,    28,    36,    42,
      63,    45,    49,    82,    46,    48,    66,    51,    50,    55,
      64,    93,   101,   130,   131,   132,    70,   134,   128,    83,
      84,    85,    86,    67,    87,    88,    89,    90,    91,    92,
     142,   143,   106,    68,   146,    77,   100,   123,   147,   148,
      33,   145,   141,   129,     0,     0,     0,     0,    83,    84,
      85,    86,     0,    87,    88,    89,    90,    91,    92,    83,
      84,    85,    86,     0,    87,    88,    89,    90,    91,    92,
      15,    39,    16,     0,     0,     0,     0,     0,    17,    18,
      19,    20,    21,     0,    15,    22,    16,     0,     0,    23,
      24,     0,    17,    18,    19,    20,    21,     0,   126,    22,
       0,     0,     0,    23,    24,     0,    83,    84,    85,    86,
     133,    87,    88,    89,    90,    91,    92,     0,    83,    84,
      85,    86,   138,    87,    88,    89,    90,    91,    92,     0,
      83,    84,    85,    86,     0,    87,    88,    89,    90,    91,
      92,    85,    86,     0,    87,    88,    89,    90,    91,    92
};

static const yytype_int16 yycheck[] =
{
      26,    12,    11,     3,     3,    12,     0,    25,    26,    20,
      13,    14,    19,    18,    40,    47,    18,    17,    17,    37,
      29,    33,    34,    35,     8,    17,    58,    13,    14,    15,
      16,    63,    64,    25,    26,    27,    28,    37,    30,    31,
      32,    33,    34,    35,    76,    71,    72,    56,     8,    75,
       9,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,     8,    10,     9,    97,    12,    30,    31,    32,
      33,    34,    35,   105,    20,    21,    22,     8,     8,    11,
      26,    25,    17,     9,    26,    12,     7,    12,    17,    12,
      36,     8,    12,   119,   120,   121,    37,   123,   107,    25,
      26,    27,    28,    17,    30,    31,    32,    33,    34,    35,
     136,   137,     9,    17,   140,    37,     9,    17,   144,   145,
      22,    17,   135,     9,    -1,    -1,    -1,    -1,    25,    26,
      27,    28,    -1,    30,    31,    32,    33,    34,    35,    25,
      26,    27,    28,    -1,    30,    31,    32,    33,    34,    35,
       4,     5,     6,    -1,    -1,    -1,    -1,    -1,    12,    13,
      14,    15,    16,    -1,     4,    19,     6,    -1,    -1,    23,
      24,    -1,    12,    13,    14,    15,    16,    -1,    17,    19,
      -1,    -1,    -1,    23,    24,    -1,    25,    26,    27,    28,
      17,    30,    31,    32,    33,    34,    35,    -1,    25,    26,
      27,    28,    17,    30,    31,    32,    33,    34,    35,    -1,
      25,    26,    27,    28,    -1,    30,    31,    32,    33,    34,
      35,    27,    28,    -1,    30,    31,    32,    33,    34,    35
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    13,    14,    39,    18,    18,     0,    40,     8,     8,
       9,     9,    10,    42,    42,     4,     6,    12,    13,    14,
      15,    16,    19,    23,    24,    41,    47,    52,     8,    67,
      25,    26,    37,    41,    12,    20,     8,    12,    19,     5,
      50,    52,    11,    48,    42,    25,    26,    65,    12,    17,
      17,    12,     3,    17,    37,    12,    51,    52,     8,    12,
      20,    21,    22,    26,    36,    43,     7,    17,    17,    43,
      37,    70,    71,    69,    64,    63,    57,    37,    42,    43,
      43,    43,     9,    25,    26,    27,    28,    30,    31,    32,
      33,    34,    35,     8,    53,    55,    17,    61,    52,    52,
       9,    12,    44,    52,    43,    59,     9,    49,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    54,
      56,    66,    43,    17,     3,    17,    17,    43,    42,     9,
      52,    52,    52,    17,    52,    45,    46,    58,    17,    68,
      62,    44,    52,    52,    60,    17,    52,    52,    52
};

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

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
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


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
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

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
      yychar = yylex ();
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

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
#line 191 "parser.y" /* yacc.c:1646  */
    { voidOrIntMain=1;}
#line 1546 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 191 "parser.y" /* yacc.c:1646  */
    {if(hasAreturn ==0){printf("\033[01;33m Warning no return in a non-void function ! \033[0m");}}
#line 1552 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 192 "parser.y" /* yacc.c:1646  */
    {if(hasAreturn == 1){printf("\033[01;33m Warning return in a void function ! \033[0m");}}
#line 1558 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 195 "parser.y" /* yacc.c:1646  */
    {(yyval.s).INT =INT_TYPE;}
#line 1564 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 196 "parser.y" /* yacc.c:1646  */
    {(yyval.s).INT = FLOAT_TYPE;}
#line 1570 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 197 "parser.y" /* yacc.c:1646  */
    {(yyval.s).INT = VOID_TYPE;}
#line 1576 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 198 "parser.y" /* yacc.c:1646  */
    {(yyval.s).INT =CHAR_TYPE;}
#line 1582 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 209 "parser.y" /* yacc.c:1646  */
    { 
    		(yyval.s).ADDR=tempAddr;
    		(yyval.s).FLOAT = (yyvsp[0].s).FLOAT;
		AutreOperation("AFC",tempAddr, (yyval.s).FLOAT);
		tempAddr++;
		}
#line 1593 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 215 "parser.y" /* yacc.c:1646  */
    { (yyval.s).FLOAT = (yyvsp[0].s).FLOAT;
  		(yyval.s).ADDR=tempAddr;
		//printf("[YACC AFF addr: %d value:%f ]", tempAddr, $<s>$.FLOAT);
		AutreOperation("AFC",tempAddr, (yyval.s).FLOAT);
		tempAddr++;
		}
#line 1604 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 221 "parser.y" /* yacc.c:1646  */
    { (yyval.s).STR = (yyvsp[0].s).STR;
  		(yyval.s).ADDR=tempAddr;
  		(yyval.s).FLOAT=(yyvsp[0].s).FLOAT;
		AutreOperation("AFC",tempAddr, (yyval.s).FLOAT);
		tempAddr++;
		}
#line 1615 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 227 "parser.y" /* yacc.c:1646  */
    { (yyval.s).FLOAT=(yyvsp[-2].s).FLOAT+(yyvsp[0].s).FLOAT;(yyval.s).ADDR=tempAddr;operation("ADD",tempAddr, (yyvsp[-2].s).ADDR, (yyvsp[0].s).ADDR);tempAddr++;}
#line 1621 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 228 "parser.y" /* yacc.c:1646  */
    { (yyval.s).FLOAT=(yyvsp[-2].s).FLOAT-(yyvsp[0].s).FLOAT;(yyval.s).ADDR=tempAddr;operation("SOU",tempAddr, (yyvsp[-2].s).ADDR, (yyvsp[0].s).ADDR);tempAddr++;}
#line 1627 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 229 "parser.y" /* yacc.c:1646  */
    { (yyval.s).FLOAT=(yyvsp[-2].s).FLOAT*(yyvsp[0].s).FLOAT;(yyval.s).ADDR=tempAddr; operation("MUL",tempAddr, (yyvsp[-2].s).ADDR, (yyvsp[0].s).ADDR);tempAddr++;}
#line 1633 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 230 "parser.y" /* yacc.c:1646  */
    { (yyval.s).FLOAT=(yyvsp[-2].s).FLOAT/(yyvsp[0].s).FLOAT;(yyval.s).ADDR=tempAddr; operation("DIV",tempAddr, (yyvsp[-2].s).ADDR, (yyvsp[0].s).ADDR);tempAddr++;}
#line 1639 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 231 "parser.y" /* yacc.c:1646  */
    { (yyval.s).FLOAT=(float)((yyvsp[-2].s).FLOAT==(yyvsp[0].s).FLOAT?1:0);printf("\n\n r: %f 1: %f 3: %f",(yyval.s).FLOAT,(yyvsp[-2].s).FLOAT,(yyvsp[0].s).FLOAT);(yyval.s).ADDR=tempAddr; operation("CMP",tempAddr, (yyvsp[-2].s).ADDR, (yyvsp[0].s).ADDR);tempAddr++;}
#line 1645 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 232 "parser.y" /* yacc.c:1646  */
    { (yyval.s).FLOAT=((yyvsp[-2].s).FLOAT < (yyvsp[0].s).FLOAT?1:0);(yyval.s).ADDR=tempAddr; operation("INF",tempAddr, (yyvsp[-2].s).ADDR, (yyvsp[0].s).ADDR);tempAddr++;}
#line 1651 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 233 "parser.y" /* yacc.c:1646  */
    { (yyval.s).FLOAT=((yyvsp[-2].s).FLOAT > (yyvsp[0].s).FLOAT?1:0);(yyval.s).ADDR=tempAddr; operation("SUP",tempAddr, (yyvsp[-2].s).ADDR, (yyvsp[0].s).ADDR);tempAddr++;}
#line 1657 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 234 "parser.y" /* yacc.c:1646  */
    { (yyval.s).FLOAT=((yyvsp[-2].s).FLOAT >= (yyvsp[0].s).FLOAT?1:0);(yyval.s).ADDR=tempAddr; operation("SUE",tempAddr, (yyvsp[-2].s).ADDR, (yyvsp[0].s).ADDR);tempAddr++;}
#line 1663 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 235 "parser.y" /* yacc.c:1646  */
    { (yyval.s).FLOAT=((yyvsp[-2].s).FLOAT <= (yyvsp[0].s).FLOAT?1:0);(yyval.s).ADDR=tempAddr; operation("INE",tempAddr, (yyvsp[-2].s).ADDR, (yyvsp[0].s).ADDR);tempAddr++;}
#line 1669 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 236 "parser.y" /* yacc.c:1646  */
    { (yyval.s).FLOAT=((yyvsp[-2].s).FLOAT != (yyvsp[0].s).FLOAT?1:0);(yyval.s).ADDR=tempAddr; operation("DIF",tempAddr, (yyvsp[-2].s).ADDR, (yyvsp[0].s).ADDR);tempAddr++;}
#line 1675 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 237 "parser.y" /* yacc.c:1646  */
    { (yyval.s).FLOAT=((yyvsp[-1].s).FLOAT= ((yyvsp[0].s).FLOAT==0)?1:0);(yyval.s).ADDR=tempAddr; operation("NOT",tempAddr, (yyvsp[-1].s).ADDR, (yyvsp[0].s).ADDR);tempAddr++;}
#line 1681 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 238 "parser.y" /* yacc.c:1646  */
    {
		(yyval.s).FLOAT = -(yyvsp[0].s).FLOAT;
		(yyval.s).ADDR = tempAddr;
		//printf("[YACC COP %d 0 ]", tempAddr);
		//printf("[YACC SOU %d %d %f ]", tempAddr, tempAddr, $<s>2.FLOAT);
		//AutreOperation("COP",tempAddr, 0);
		operation("SOU",tempAddr, tempAddr, (yyvsp[0].s).ADDR);
		tempAddr++;
	}
#line 1695 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 247 "parser.y" /* yacc.c:1646  */
    { (yyval.s).FLOAT=(yyvsp[-1].s).FLOAT; (yyval.s).ADDR=(yyvsp[-1].s).ADDR; }
#line 1701 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 248 "parser.y" /* yacc.c:1646  */
    {/*^$$= value_of_variable_tVar */
  		//!\ il ne faut pas renvoyer l'adresse de la var mais une copie temp (sinon modifie définitivement la var)
  		//bad conversion (aka char)
  		char *buff=getValeurToPrint((yyvsp[0].s).STR);
  		if(getType((yyvsp[0].s).STR)==CHAR_TYPE)
  			(yyval.s).FLOAT=(float)buff[0];
  		else{
  		(yyval.s).FLOAT = atof(buff);
  		free(buff);
  		}
		(yyval.s).ADDR=tempAddr;
		int varAddr = getAdresse((yyvsp[0].s).STR,depth);
		if(!varEstIni(varAddr)) {
			printf(" \033[01;31m FATAL ERROR :unitialized variable \033[0m");
			exit(-1);
		}
		AutreOperation("COP",tempAddr, varAddr);
		tempAddr++; 
		}
#line 1725 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 269 "parser.y" /* yacc.c:1646  */
    {
		if(alreadyDeclaredVar((yyvsp[-1].s).STR)) {
				printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
				exit(-1);
		}
		ajouter((yyvsp[-1].s).STR, declaration_a_virg_last_type, false, false,depth);
  	}
#line 1737 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 276 "parser.y" /* yacc.c:1646  */
    {
      		if(alreadyDeclaredVar((yyvsp[-1].s).STR)) {
					printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
					exit(-1);
		}
		ajouter((yyvsp[-1].s).STR, declaration_a_virg_last_type, false, false,depth);
 	}
#line 1749 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 284 "parser.y" /* yacc.c:1646  */
    {if(OPTI){
		wasInActifStateIf=activeInstruction;
		activeInstruction=0;}
		}
#line 1758 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 288 "parser.y" /* yacc.c:1646  */
    {
			/*GENERER JMF */ 
			if(OPTI){
				if(wasInActifStateIf){
					activeIf[lastJump]=(yyvsp[-1].s).FLOAT; 
					activeInstruction=(yyvsp[-1].s).FLOAT;
				}
			}else{
				IfOperation();
			}
		}
#line 1774 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 298 "parser.y" /* yacc.c:1646  */
    {if(!OPTI && activeInstruction){
			IfPatchOperation(cp);
			}activeInstruction=1;}
#line 1782 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 301 "parser.y" /* yacc.c:1646  */
    { /*GENERER JMP*/activeInstruction=activeIf[lastJump]?0:1;if(!OPTI && activeInstruction){ElseOperation();}}
#line 1788 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 301 "parser.y" /* yacc.c:1646  */
    {if(!OPTI && activeInstruction){ElsePatchOperation();}activeInstruction=1;}
#line 1794 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 304 "parser.y" /* yacc.c:1646  */
    {wasInActifState=activeInstruction;if(OPTI)activeInstruction=0;}
#line 1800 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 304 "parser.y" /* yacc.c:1646  */
    {
  		if(wasInActifState){
		int varAddr = getAdresse((yyvsp[-4].s.STR),depth);		
		if(isSymbolConst(varAddr)) {
			printf("\033[01;31m FATAL ERROR : const variable cannot reaffect value \033[0m");
			exit(-1);
		}
		if(!varEstIni(varAddr)) {
			printf("\033[01;31m This variable is not initialized cannot quick increment \033[0m");
			exit(-1);
		}
		int type=getType((yyvsp[-4].s.STR));
		if(type==FLOAT_TYPE || type==INT_TYPE){
			char *buff=getValeurToPrint((yyvsp[-4].s.STR));
			int value;
			if(getType((yyvsp[-4].s).STR)==CHAR_TYPE)
				value=(float)buff[0];
			else{
			value = atof(buff);
			free(buff);
  			}
			setValeurFloat((yyvsp[-4].s.STR),value+1);
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
   }
#line 1841 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 340 "parser.y" /* yacc.c:1646  */
    {wasInActifState=activeInstruction;if(OPTI)activeInstruction=0;}
#line 1847 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 340 "parser.y" /* yacc.c:1646  */
    {
 		if(wasInActifState){
   		int varAddr = getAdresse((yyvsp[-4].s.STR),depth);		
		if(isSymbolConst(varAddr)) {
			printf("\033[01;31m FATAL ERROR : const variable cannot reaffect value \033[0m");
			exit(-1);
		}
		if(!varEstIni(varAddr)) {
			printf("\033[01;31m FATAL ERROR : This variable is not initialized cannot quick decrement \033[0m");
			exit(-1);
		}
		int type=getType((yyvsp[-4].s.STR));
		if(type==FLOAT_TYPE || type==INT_TYPE){
			int value;
			char *buff=getValeurToPrint((yyvsp[-4].s.STR));
			if(getType((yyvsp[-4].s).STR)==CHAR_TYPE)
				value=(float)buff[0];
			else{
				value = atof(buff);
				free(buff);
  			}
			setValeurFloat((yyvsp[-4].s.STR),value-1);
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
   }
#line 1887 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 375 "parser.y" /* yacc.c:1646  */
    {wasInActifState=activeInstruction;if(OPTI)activeInstruction=0;}
#line 1893 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 375 "parser.y" /* yacc.c:1646  */
    {
		if(wasInActifState){
		if(alreadyDeclaredVar((yyvsp[-4].s).STR)) {
			printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
			exit(-1);
		}
		int varAddr =ajouter((yyvsp[-4].s).STR, (yyvsp[-5].s).INT, true,false,depth)-1;
		if(!varEstIni(varAddr)) {
			iniVar(varAddr);
		}
  		int type=(yyvsp[-5].s).INT;
		if(type==FLOAT_TYPE || type==INT_TYPE){
			setValeurFloat((yyvsp[-4].s).STR,(float)(yyvsp[-1].s).FLOAT);
			AutreOperation("COP",varAddr, (yyvsp[-1].s).ADDR);
		}
		else if(type==CHAR_TYPE){
			setValeurStr((yyvsp[-4].s.STR),(yyvsp[-1].s).STR);
			//printf("[YACC COP %d : %s]", varAddr , $<s>5.STR);
			AutreOperation("COP",varAddr, (yyvsp[-1].s).ADDR);
		}
		if(OPTI){
		activeInstruction=1;
		AutreOperation("AFC",varAddr, (float)(yyvsp[-1].s).FLOAT);
		}
		}
  }
#line 1924 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 401 "parser.y" /* yacc.c:1646  */
    {wasInActifState=activeInstruction;if(OPTI)activeInstruction=0;}
#line 1930 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 401 "parser.y" /* yacc.c:1646  */
    {
		if(wasInActifState){
		if(alreadyDeclaredVar((yyvsp[-4].s).STR)) {
			printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
			exit(-1);
		}
  		int varAddr = ajouter((yyvsp[-4].s.STR), (yyvsp[-6].s).INT, true,true,depth)-1;//cst
		int type=(yyvsp[-6].s).INT;
		if(type==FLOAT_TYPE || type==INT_TYPE){
			setValeurFloat((yyvsp[-4].s.STR),(float)(yyvsp[-1].s).FLOAT);
			AutreOperation("COP",varAddr, (yyvsp[-1].s).ADDR);
		}
		else if(type==CHAR_TYPE){
			setValeurStr((yyvsp[-4].s.STR),(yyvsp[-1].s).STR);
			AutreOperation("COP",varAddr, (yyvsp[-1].s).ADDR);
		}
		if(OPTI){
			activeInstruction=1;
			AutreOperation("AFC",varAddr, (float)(yyvsp[-1].s).FLOAT);
		}
		}
  }
#line 1957 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 423 "parser.y" /* yacc.c:1646  */
    {wasInActifState=activeInstruction;if(OPTI)activeInstruction=0;}
#line 1963 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 423 "parser.y" /* yacc.c:1646  */
    {
 		if(wasInActifState){
 		if(alreadyDeclaredVar((yyvsp[-4].s).STR)) {
					printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
					exit(-1);
		}
    		int varAddr = ajouter((yyvsp[-4].s.STR), (yyvsp[-5].s).INT, true,true,depth)-1;
  		int type=(yyvsp[-5].s).INT;
  		if(type==FLOAT_TYPE || type==INT_TYPE){
				setValeurFloat((yyvsp[-4].s.STR),(float)(yyvsp[-1].s).FLOAT);
				AutreOperation("COP",varAddr, (yyvsp[-1].s).ADDR);
			}
		else if(type==CHAR_TYPE){
			setValeurStr((yyvsp[-4].s.STR),(yyvsp[-1].s).STR);
			AutreOperation("COP",varAddr, (yyvsp[-1].s).ADDR);
		}
		if(OPTI && wasInActifState){
			activeInstruction=1;
			AutreOperation("AFC",varAddr, (float)(yyvsp[-1].s).FLOAT);
		}
		}
  }
#line 1990 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 445 "parser.y" /* yacc.c:1646  */
    {
		if(alreadyDeclaredVar((yyvsp[-1].s).STR)) {
					printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
					exit(-1);
		}
		ajouter((yyvsp[-1].s.STR), (yyvsp[-2].s).INT, false, false,depth);
  }
#line 2002 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 452 "parser.y" /* yacc.c:1646  */
    {
	if(alreadyDeclaredVar((yyvsp[-1].s).STR)) {
				printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
				exit(-1);
	}
	declaration_a_virg_last_type= (yyvsp[-2].s).INT;
	ajouter((yyvsp[-1].s.STR), (yyvsp[-2].s).INT, false, false,depth);
  }
#line 2015 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 460 "parser.y" /* yacc.c:1646  */
    {wasInActifState=activeInstruction;if(OPTI)activeInstruction=0;}
#line 2021 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 460 "parser.y" /* yacc.c:1646  */
    {
	if(wasInActifState){
	int varAddr = getAdresse((yyvsp[-4].s.STR),depth);		
			if(isSymbolConst(varAddr)) {
				printf("\033[01;31m FATAL ERROR : const variable cannot reaffect value \033[0m");
				exit(-1);
			}
			if(!varEstIni(varAddr)) {
				iniVar(varAddr);
			}
		int type=getType((yyvsp[-4].s.STR));
		if(type==FLOAT_TYPE || type==INT_TYPE){
			setValeurFloat((yyvsp[-4].s.STR),(yyvsp[-1].s).FLOAT);
			AutreOperation("COP",varAddr, (yyvsp[-1].s).ADDR);
		}
		else if(type==CHAR_TYPE){
			setValeurStr((yyvsp[-4].s.STR),(yyvsp[-1].s).STR);
			AutreOperation("COP",varAddr, (yyvsp[-1].s).ADDR);
		}
		if(OPTI){
			activeInstruction=1;
			AutreOperation("AFC",varAddr, (float)(yyvsp[-1].s).FLOAT);
		}
		}
	
  }
#line 2052 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 488 "parser.y" /* yacc.c:1646  */
    { loopStart();OPTI=0;/*pas d'opti de boucle*/}
#line 2058 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 488 "parser.y" /* yacc.c:1646  */
    {loopEnd();OPTI=user_want_opti;}
#line 2064 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 489 "parser.y" /* yacc.c:1646  */
    { if(activeInstruction){PrintfOperation((yyvsp[0].s.STR), getValeurToPrint((yyvsp[0].s.STR)),getAdresse((yyvsp[0].s.STR),depth) );}}
#line 2070 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 490 "parser.y" /* yacc.c:1646  */
    {
			int varAddr = getAdresse((yyvsp[-1].s.STR),depth);
			if(voidOrIntMain==0){
				printf("\033[01;31m FATAL ERROR : void function cannot return a value, switch to int main() \033[0m");
				exit(-1);
			}
			if(!varEstIni(varAddr)) {
				printf("\033[01;33m Warning return uninitialized variable \033[0m");
			}
			hasAreturn =1;
			char* buff=getValeurToPrint((yyvsp[-1].s.STR));
			(yyval.s).INT =atoi(buff);
			free(buff);
			(yyval.s).ADDR=tempAddr;
			AutreOperation("COP",tempAddr, varAddr);
			ReturnOperation((yyval.s).ADDR,(yyval.s).INT);
			tempAddr++;
			}
#line 2093 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 508 "parser.y" /* yacc.c:1646  */
    {
		if(voidOrIntMain==0){
						printf("\033[01;31m FATAL ERROR : void function cannot return a value, switch to int main() \033[0m");
						exit(-1);
			}
		hasAreturn =1;
	         (yyval.s).INT = (yyvsp[-1].s).INT;
		(yyval.s).ADDR=tempAddr;
		AutreOperation("AFC",tempAddr, (yyval.s).INT);
		ReturnOperation((yyval.s).ADDR,(yyval.s).INT);
		tempAddr++;
		}
#line 2110 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 2114 "parser.tab.c" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 525 "parser.y" /* yacc.c:1906  */

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
    	fprintf(file,"%s",instruction[i]);
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

