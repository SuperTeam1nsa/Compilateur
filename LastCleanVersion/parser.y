%error-verbose
%{

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "symboltable.h"

char * type;
int yylex(void);
int yyerror(const char *s);
int success = 1;

%}

%union {
int nb;
float reel;
char* str;
}

%token  tPLUS  tMOINS tFOIS  tDIVISE 
%token  tCOMMA
%token  tOP tCP
%token  tOB tCB
%token  tVAR 
%token  tCOMPARAISON tEGAL tINFSTRICT tSUPSTRICT
%token  tSUPEGAL tINFEGAL tDIFF tNOT 
%token  tINT tVOID tCHAR tFLOAT tVIRG tMAIN tCONST
%token  tINT_VAL tFLOAT_VAL tCHAR_VAL
%token  tRETURN
%token  tPRINTF

%left tPLUS  tMOINS
%left tFOIS  tDIVISE
%left tNEG
%left tCOMPARAISON tEGAL tINFSTRICT tSUPSTRICT
%left tSUPEGAL tINFEGAL tDIFF

%right tNOT

%type<nb> Expression Val
%type<str> tVAR

%start Program
%%

Program :
     Type tMAIN tOP tCP Body 
    ;
Type :
     tINT
    |tFLOAT
    |tVOID
    |tCHAR
    ;
Val:
  tINT_VAL
| tFLOAT_VAL
| tCHAR_VAL
;

Body :
      tOB Instruction tCB 
    ;

Expression:
    Val      { $$=$1; }
  | Expression tPLUS Expression  { $$=$1+$3; }
  | Expression tMOINS Expression { $$=$1-$3; }
  | Expression tFOIS Expression  { $$=$1*$3; }
  | Expression tDIVISE Expression  { $$=$1/$3; }
  | tMOINS Expression %prec tNEG  { $$=-$2; }
  | tOP Expression tCP  { $$=$2; }
  | tVAR
  ;
Liste :
	tVAR tCOMMA Liste
      | tVAR tVIRG Instruction
      ;

Instruction:
  Type tVAR tEGAL Expression tVIRG Instruction
| Type tVAR tVIRG Instruction
| Type tVAR tCOMMA Liste
| tVAR tEGAL Expression tVIRG Instruction
| tPRINTF tOP tVAR tCP tVIRG Instruction
| tRETURN tVAR tVIRG
| tRETURN Val tVIRG
| tRETURN tOP tVAR tCP tVIRG
| tRETURN tOP Val tCP tVIRG
| /* epsilon */
;



%%
//rappel: printf g�re seulement une variable
//  | Expression tPUISSANCE Expression { $$=pow($1,$3); }
int yywrap(void)
{
   return 1;
}
int main()
{
    yyparse();
    if(success)
    	printf("Parsing Successful\n");
    return 0;
}

int yyerror(const char *msg)
{
	//extern int yylineno;
	printf("Parsing Failed\n %s\n",msg);
	success = 0;
	return 0;
}

