%error-verbose
%{

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "symboltable.h"

#define INSTR_BUFFER_SIZE 1000
#define KEEPER_ADDR 200
int tempAddr = 100;
int success = 1; 
int voidOrIntMain=0;//void by def
int hasAreturn=0;

char * type;
FILE* file;
int yylex(void);
int yyerror(const char *s);

char* last_var;
float declaration_a_virg_last_type;
//NB: les var sont passées à l'assembleur par valeur, on à presque une interprétation du C par le parser qui peut de fait optimiser l'ASM (pas fait pour garder ttes les ope affichées
// juste les var intermediaires ne font plus sens #keeper le même pour tous du coup )
//NB: divide and conquer sur les operations : X +Y => on réalise toujours l'opération atomique => 1 seul resultat à retenir 
//+passage par valeur => last operation =all (on pourrait se passer des autres resultats intermédiaires #opti aggressive)
//AFC, COP par exemple
void AutreOperation(const char * operation, int addr1,float value) {
	printf("[YACC %s %d %f ]", operation, addr1, value);
	fprintf(file, "%s %d %f \n",operation, addr1, value);
}
//operation arithmetique
void operation(const char * operation, int addr1, int addr2) {
	printf("[YACC %s %d %d %d ]", operation,KEEPER_ADDR, addr1, addr2);
	fprintf(file, "%s %d %d %d \n",operation,KEEPER_ADDR, addr1, addr2);
}
//operation string
void StrOperation(const char * operation, int addr1, char* str) {
	printf("[YACC %s %d %s ]", operation, addr1, str);
	fprintf(file, "%s %d %s \n",operation, addr1,str);
}
void PrintfOperation(char *name, char* value){
	printf(" [YACC PRINTF : la variable est : %s et vaut %s ]",name,value);
	fprintf(file, "PRINTF %s %s \n",name,value);
}
void ReturnOperation(int value){
	printf(" [YACC RETURN value: %d ]",value);
	fprintf(file, "RETURN %d \n",value);
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
  	tINT tMAIN { voidOrIntMain=1;}tOP tCP Body {if(hasAreturn ==0){printf("\033[01;33m Warning no return in a non-void function ! \033[0m");}}
	| tVOID tMAIN tOP tCP Body	{if(hasAreturn == 1){printf("\033[01;33m Warning return in a void function ! \033[0m");}}
    ;
Type :
     tINT {$<INT>$ =INT_TYPE;}
    |tFLOAT {$<INT>$ = FLOAT_TYPE;}
    |tVOID {$<INT>$ = VOID_TYPE;}
    |tCHAR {$<INT>$ =CHAR_TYPE;}
    ;



Body :
      tOB Instruction tCB 
    ;

//que entre même type
Expression:
    tINT_VAL      { $<FLOAT>$ = (float)$<INT>1;
		//printf("[YACC AFF addr: %d value:%f ]", tempAddr, $<FLOAT>$);
		AutreOperation("AFC",tempAddr, $<FLOAT>$);
		tempAddr++;}
  | tFLOAT_VAL { $<FLOAT>$ = $<FLOAT>1;
		//printf("[YACC AFF addr: %d value:%f ]", tempAddr, $<FLOAT>$);
		AutreOperation("AFC",tempAddr, $<FLOAT>$);
		tempAddr++;}
  | tCHAR_VAL{ $<STR>$ = $<STR>1;
		//printf("[YACC AFF addr: %d value:%s ]", tempAddr, $<STR>$);
		AutreOperation("AFC",tempAddr, $<FLOAT>$);
		tempAddr++;}
  | Expression tPLUS Expression  { $<FLOAT>$=$<FLOAT>1+$<FLOAT>3;operation("ADD", $<FLOAT>1, $<FLOAT>3);}
  | Expression tMOINS Expression { $<FLOAT>$=$<FLOAT>1-$<FLOAT>3;operation("SOU", $<FLOAT>1, $<FLOAT>3);}
  | Expression tFOIS Expression  { $<FLOAT>$=$<FLOAT>1*$<FLOAT>3; operation("MUL", $<FLOAT>1, $<FLOAT>3);}
  | Expression tDIVISE Expression  { $<FLOAT>$=$<FLOAT>1/$<FLOAT>3; operation("DIV", $<FLOAT>1, $<FLOAT>3);}
  | tMOINS Expression {
		$<FLOAT>$ = -$<FLOAT>2;
		//printf("[YACC COP %d 0 ]", tempAddr);
		//printf("[YACC SOU %d %d %f ]", tempAddr, tempAddr, $<FLOAT>2);
		//AutreOperation("COP",tempAddr, 0);
		operation("SOU",0,$<FLOAT>2);
		tempAddr++;
	}        %prec tNEG  
  | tOP Expression tCP  { $<FLOAT>$=$<FLOAT>2; }
  | tVAR	{/*^$$= value_of_variable_tVar */
  		$<FLOAT>$ = atof(getValeurToPrint($<STR>1));
		int varAddr = getAdresse($<STR>1);
		if(!varEstIni(varAddr)) {
			printf(" \033[01;31m FATAL ERROR :unitialized variable \033[0m");
			exit(-1);
		}
		//printf("[YACC COP %f %d ]", $<FLOAT>$, varAddr);
		AutreOperation("COP",varAddr, $<FLOAT>$);
		tempAddr++; }
  ;
Liste :
	tVAR tCOMMA  {
		if(alreadyDeclaredVar($<STR>1)) {
				printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
				exit(-1);
		}
		ajouter($<STR>1, declaration_a_virg_last_type, false, false);
  	} Liste
      | tVAR tVIRG  {
      		if(alreadyDeclaredVar($<STR>1)) {
					printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
					exit(-1);
		}
		ajouter($<STR>1, declaration_a_virg_last_type, false, false);
 	} Instruction
      ;

Instruction:
  tVAR tPLUS tPLUS tVIRG{
		int varAddr = getAdresse($1);		
		if(isSymbolConst(varAddr)) {
			printf("\033[01;31m FATAL ERROR : const variable cannot reaffect value \033[0m");
			exit(-1);
		}
		if(!varEstIni(varAddr)) {
			printf("\033[01;31m This variable is not initialized  \033[0m");
			exit(-1);
		}
		int type=getType($1);
		if(type==FLOAT_TYPE || type==INT_TYPE){
			float value=atof(getValeurToPrint($1));
			setValeurFloat($1,value+1);
			AutreOperation("COP",varAddr, value+1);
		}
		else {
			printf("\033[01;31m This type doesn't permit quick increment  \033[0m");
			exit(-1);
		}
   } Instruction
 | tVAR tMOINS tMOINS tVIRG{
   		int varAddr = getAdresse($1);		
		if(isSymbolConst(varAddr)) {
			printf("\033[01;31m FATAL ERROR : const variable cannot reaffect value \033[0m");
			exit(-1);
		}
		if(!varEstIni(varAddr)) {
			printf("\033[01;31m This variable is not initialized  \033[0m");
			exit(-1);
		}
		int type=getType($1);
		if(type==FLOAT_TYPE || type==INT_TYPE){
			float value=atof(getValeurToPrint($1));
			setValeurFloat($1,value-1);
			AutreOperation("COP",varAddr, value-1);
		}
		else {
			printf("\033[01;31m This type doesn't permit quick increment  \033[0m");
			exit(-1);
		}
   } Instruction
  |Type tVAR tEGAL Expression tVIRG {
		if(alreadyDeclaredVar($<STR>2)) {
			printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
			exit(-1);
		}
		int varAddr =ajouter($<STR>2, $<INT>1, true,false);
		if(!varEstIni(varAddr)) {
			iniVar(varAddr);
		}
  		int type=$<INT>1;
		if(type==FLOAT_TYPE || type==INT_TYPE){
			setValeurFloat($<STR>2,(float)$<FLOAT>4);
			//printf("[YACC COP %d : %f ]", varAddr , (float)$<FLOAT>4);
			AutreOperation("COP",varAddr, (float)$<FLOAT>4);
		}
		else if(type==CHAR_TYPE){
			setValeurStr($2,$<STR>4);
			printf("[YACC COP %d : %s]", varAddr , $<STR>4);
			StrOperation("COP",varAddr, $<STR>4);
		}
  } Instruction
| Type tCONST tVAR tEGAL Expression tVIRG {
		if(alreadyDeclaredVar($<STR>3)) {
			printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
			exit(-1);
		}
  		int varAddr = ajouter($3, $<INT>1, true,true);//cst
		int type=$<INT>1;
		if(type==FLOAT_TYPE || type==INT_TYPE){
			setValeurFloat($3,(float)$<FLOAT>5);
			//printf("[YACC COP %d : %f ]", varAddr , (float)$<FLOAT>5);
			AutreOperation("COP",varAddr, (float)$<FLOAT>5);
		}
		else if(type==CHAR_TYPE){
			setValeurStr($3,$<STR>5);
			//printf("[YACC COP %d : %s]", varAddr , $<STR>5);
			StrOperation("COP",varAddr,$<STR>5);
		}
  } Instruction
 | tCONST Type tVAR tEGAL Expression tVIRG {
 		if(alreadyDeclaredVar($<STR>3)) {
					printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
					exit(-1);
		}
    		int varAddr = ajouter($3, $<INT>2, true,true);
  		int type=$<INT>2;
  		if(type==FLOAT_TYPE || type==INT_TYPE){
  			setValeurFloat($3,(float)$<FLOAT>5);
  			//printf("[YACC COP %d : %f ]", varAddr , (float)$<FLOAT>5);
  			AutreOperation("COP",varAddr, (float)$<FLOAT>5);
  		}
  		else if(type==CHAR_TYPE){
  			setValeurStr($3,$<STR>5);
  			//printf("[YACC COP %d : %s]", varAddr , $<STR>5);
  			StrOperation("COP",varAddr,$<STR>5);
  		}
  } Instruction
| Type tVAR tVIRG {
		if(alreadyDeclaredVar($<STR>2)) {
					printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
					exit(-1);
		}
		ajouter($2, $<INT>1, false, false);
  } Instruction
| Type tVAR tCOMMA {
	if(alreadyDeclaredVar($<STR>2)) {
				printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
				exit(-1);
	}
	declaration_a_virg_last_type= $<INT>1;
	ajouter($2, $<INT>1, false, false);
  } Liste
| tVAR tEGAL Expression tVIRG {
	//printf("[YACC %s ]",$1);
	int varAddr = getAdresse($1);		
			if(isSymbolConst(varAddr)) {
				printf("\033[01;31m FATAL ERROR : const variable cannot reaffect value \033[0m");
				exit(-1);
			}
			if(!varEstIni(varAddr)) {
				iniVar(varAddr);
			}
		int type=getType($1);
		if(type==FLOAT_TYPE || type==INT_TYPE){
			setValeurFloat($1,$<FLOAT>3);
			//printf("[YACC COP %d %f ]", varAddr, $<FLOAT>3);
			AutreOperation("COP",varAddr, $<FLOAT>3);
		}
		else if(type==CHAR_TYPE){
			setValeurStr($1,$<STR>3);
			//printf("[YACC COP %d %s ]", varAddr, $<STR>3);
			StrOperation("COP",varAddr, $<STR>3);
		}
	
  }Instruction
| tPRINTF tOP tVAR { PrintfOperation($3, getValeurToPrint($3));}tCP tVIRG Instruction 
| tRETURN tVAR tVIRG {
			int varAddr = getAdresse($2);
			if(voidOrIntMain==0){
				printf("\033[01;31m FATAL ERROR : void function cannot return a value, switch to int main() \033[0m");
				exit(-1);
			}
			if(!varEstIni(varAddr)) {
				printf("\033[01;33m Warning return unaffected value \033[0m");
			}
			if(hasAreturn==1){
						printf("\033[01;33m Warning dead code! more than one return without conditionnal \033[0m");
					}else
			hasAreturn =1;
			$<INT>$ =atoi(getValeurToPrint($2));
			ReturnOperation($<INT>$);}
| tRETURN tINT_VAL tVIRG {
		if(voidOrIntMain==0){
						printf("\033[01;31m FATAL ERROR : void function cannot return a value, switch to int main() \033[0m");
						exit(-1);
			}
		if(hasAreturn==1){
			printf("\033[01;33m Warning dead code! more than one return without conditionnal \033[0m");
		}else
		hasAreturn =1;
	         $<INT>$ = $<INT>2;
		  ReturnOperation($<INT>$);
		}
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
//nettoie
    file = fopen("output.asm","a+");    
    yyparse();
    fclose(file);
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

