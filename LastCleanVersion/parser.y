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
	int INT;
	float FLOAT;
	char* STR;
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


//%type<FLOAT> Expression
/*%type<reel> Val
%type<reel> Type*/
%type<STR> tVAR


%start Program
%%

Program :
  	tINT tMAIN tOP tCP Body
	| tVOID tMAIN tOP tCP Body
    ;
Type :
     tINT {$<INT>$ =INT_TYPE;}
    |tFLOAT {$<INT>$ = FLOAT_TYPE;}
    |tVOID {$<INT>$ = VOID_TYPE;}
    |tCHAR {$<INT>$ =CHAR_TYPE;}
    ;

//conv en float
Val:
  tINT_VAL {$<FLOAT>$ =(float)$<INT>1}
| tFLOAT_VAL {$<FLOAT>$ =$<FLOAT>1}
| tCHAR_VAL {$<STR>$ =$<STR>1}
;


Body :
      tOB Instruction tCB 
    ;

//que entre même type
Expression:
    tINT_VAL      { $<FLOAT>$ = (float)$<INT>1;
		printf("[YACC AFF addr: %d value:%f ]", tempAddr, $<FLOAT>$);
		tempAddr++;}
  | tFLOAT_VAL { $<FLOAT>$ = $<FLOAT>1;
		printf("[YACC AFF addr: %d value:%f ]", tempAddr, $<FLOAT>1);
		tempAddr++;}
  | tCHAR_VAL{ $<STR>$ = $<STR>1;
		printf("[YACC AFF addr: %d value:%s ]", tempAddr, $<STR>1);
		tempAddr++;}
  | Expression tPLUS Expression  { $<FLOAT>$=$<FLOAT>1+$<FLOAT>3;operation("ADD", $<FLOAT>1, $<FLOAT>3);}
  | Expression tMOINS Expression { $<FLOAT>$=$<FLOAT>1-$<FLOAT>3;operation("SOU", $<FLOAT>1, $<FLOAT>3);}
  | Expression tFOIS Expression  { $<FLOAT>$=$<FLOAT>1*$<FLOAT>3; operation("MUL", $<FLOAT>1, $<FLOAT>3);}
  | Expression tDIVISE Expression  { $<FLOAT>$=$<FLOAT>1/$<FLOAT>3; operation("DIV", $<FLOAT>1, $<FLOAT>3);}
  | tMOINS Expression {
		$<FLOAT>$ = -$<FLOAT>2;
		printf("[YACC COP %d 0 ]", tempAddr);
		printf("[YACC SOU %d %d %f ]", tempAddr, tempAddr, $<FLOAT>2);
		tempAddr++;
	}        %prec tNEG  
  | tOP Expression tCP  { $<FLOAT>$=$<FLOAT>2; }
  | tVAR	{/*^$$= value_of_variable_tVar */
  		$<FLOAT>$ = atof(getValeurToPrint($<STR>1));
		int varAddr = getAdresse($<STR>1);
		if(!varEstIni(varAddr)) {
			printf("FATAL ERROR :unitialized variable");
			exit(-1);
		}
		printf("[YACC COP %f %d ]", $<FLOAT>$, varAddr);
		tempAddr++; }
  ;
Liste :
	tVAR tCOMMA  {
		ajouter($<STR>1, declaration_a_virg_last_type, false, false);
  	} Liste
      | tVAR tVIRG  {
		ajouter($<STR>1, declaration_a_virg_last_type, false, false);
 	} Instruction
      ;

Instruction:
  Type tVAR tEGAL Expression tVIRG {
  		int varAddr =ajouter($<STR>2, $<INT>1, true,false);
		if(isSymbolConst(varAddr)) {
			printf("FATAL ERROR : const variable");
			exit(-1);
		}
		if(!varEstIni(varAddr)) {
			iniVar(varAddr);
		}
  		int type=$<INT>1;
		if(type==FLOAT_TYPE || type==INT_TYPE){
			setValeurFloat($<STR>2,(float)$<FLOAT>4);
			printf("[YACC COP %d : %f ]", varAddr , (float)$<FLOAT>4);
		}
		else if(type==CHAR_TYPE){
			setValeurStr($2,$<STR>4);
			printf("[YACC COP %d : %s]", varAddr , $<STR>4);
		}
  } Instruction
| Type tCONST tVAR tEGAL Expression tVIRG {
  		int varAddr = ajouter($3, $<INT>1, true,false);
		int type=$<INT>1;
		if(type==FLOAT_TYPE || type==INT_TYPE){
			setValeurFloat($3,(float)$<FLOAT>5);
			printf("[YACC COP %d : %f ]", varAddr , (float)$<FLOAT>5);
		}
		else if(type==CHAR_TYPE){
			setValeurStr($3,$<STR>5);
			printf("[YACC COP %d : %s]", varAddr , $<STR>5);
		}
  } Instruction
| Type tVAR tVIRG {
		ajouter($2, $<INT>1, false, false);
  } Instruction
| Type tVAR tCOMMA {
	declaration_a_virg_last_type= $<INT>1;
	ajouter($2, $<INT>1, false, false);
  } Liste
| tVAR tEGAL Expression tVIRG {
	//printf("[YACC %s ]",$1);
	int varAddr = getAdresse($1);		
			if(isSymbolConst(varAddr)) {
				printf("FATAL ERROR : const variable");
				exit(-1);
			}
			if(!varEstIni(varAddr)) {
				iniVar(varAddr);
			}
		int type=getType($1);
		if(type==FLOAT_TYPE || type==INT_TYPE){
			setValeurFloat($1,$<FLOAT>3);
			printf("[YACC COP %d %f ]", varAddr, $<FLOAT>3);
		}
		else if(type==CHAR_TYPE){
			setValeurStr($1,$<STR>3);
			printf("[YACC COP %d %f ]", varAddr, $<FLOAT>3);
		}
	
  }Instruction
| tPRINTF tOP tVAR { printf(" [YACC la variable est : %s et vaut %s ]",$3, getValeurToPrint($3)); }tCP tVIRG Instruction 
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

