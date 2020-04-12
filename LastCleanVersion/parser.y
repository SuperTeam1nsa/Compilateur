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

int tempAddr = 100;
char* last_var;
float declaration_a_virg_last_type;
void operation(const char * operation, int addr1, int addr2) {
	printf("[YACC OP %s %d %d %d ]", operation, addr1, addr1, addr2);
}

%}

%union {
	int nb;
	float reel;
	char* str;
}
 
%token  tCOMMA
%token  tOP tCP
%token  tOB tCB
%token  tVAR 
%token  tINT tVOID tCHAR tFLOAT tVIRG tMAIN tCONST
%token  tINT_VAL tFLOAT_VAL tCHAR_VAL
%token  tRETURN
%token  tPRINTF

%left tPLUS  tMOINS
%left tFOIS  tDIVISE
%left tNEG
%left tCOMPARAISON tINFSTRICT tSUPSTRICT
%left tSUPEGAL tINFEGAL tDIFF

%right tNOT tEGAL

%type<reel> Expression
%type<reel> Val
%type<reel> Type
%type<str> tVAR

%start Program
%%

Program :
  	tINT tMAIN tOP tCP Body
	| tVOID tMAIN tOP tCP Body
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
    Val      { $$ = tempAddr;
		printf("AFECTATION addr: %d value:%d ", tempAddr, $1);
		tempAddr++;}
  | Expression tPLUS Expression  { $$=$1+$3; operation("ADD", $1, $3);}
  | Expression tMOINS Expression { $$=$1-$3; operation("SOU", $1, $3);}
  | Expression tFOIS Expression  { $$=$1*$3; operation("MUL", $1, $3);}
  | Expression tDIVISE Expression  { $$=$1/$3; operation("DIV", $1, $3);}
  | tMOINS Expression {
		$$ = tempAddr;
		printf("COP %d 0", tempAddr);
		printf("SOU %d %d %d", $$, tempAddr, $2);
		tempAddr++;
	}        %prec tNEG  
  | tOP Expression tCP  { $$=$2; }
  | tVAR	{/*^$$= value_of_variable_tVar */
  		$$ = tempAddr;
		int varAddr = getAdresse($1);
		if(!varEstIni(varAddr)) {
			printf("FATAL ERROR :unitialized variable");
			exit(-1);
		}
		printf("COP %d %d", $$, varAddr);
		tempAddr++; }
  ;
Liste :
	tVAR tCOMMA  {
		ajouter($1, declaration_a_virg_last_type, false, false);
  	} Liste
      | tVAR tVIRG  {
		ajouter($1, declaration_a_virg_last_type, false, false);
 	} Instruction
      ;

Instruction:
  Type tVAR tEGAL Expression tVIRG {
  		int varAddr =ajouter($2, $1, true,false);
		printf("[YACC COP %d : %d ]", varAddr , $4);
  } Instruction
| Type tCONST tVAR tEGAL Expression tVIRG {
  		int varAddr = ajouter($3, $1, true,false);
		printf("[YACC COP %d : %d ]", varAddr , $5);
  } Instruction
| Type tVAR tVIRG {
		ajouter($2, $1, false, false);
  } Instruction
| Type tVAR tCOMMA {
	declaration_a_virg_last_type= $1;
	ajouter($2, $1, false, false);
  } Liste
| tVAR tEGAL Expression tVIRG {
	//printf("[YACC %s ]",$1);
	int varAddr = getAdresse($1);
	//$1.str  error: request for member 'str' in something not a structure or union
	//$1 seul =>  Erreur fatale : pas de symbole "i =3;" dans la table		
			if(isSymbolConst(varAddr)) {
				printf("FATAL ERROR : const variable");
				exit(-1);
			}
			if(!varEstIni(varAddr)) {
				iniVar(varAddr);
			}
	printf("COP %d %d", varAddr, $3);
  }Instruction
| tPRINTF tOP tVAR { printf(" [YACC la variable est : %s ]",$3); }tCP tVIRG Instruction 
| tRETURN tVAR tVIRG
| tRETURN Val tVIRG
| tRETURN tOP tVAR tCP tVIRG
| tRETURN tOP Val tCP tVIRG
| /* epsilon */
;



%%
//rappel: printf gère seulement une variable
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

