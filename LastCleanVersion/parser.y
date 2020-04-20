%error-verbose
%{

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "symboltable.h"
#define output "interpreter/output.asm"

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
// juste les var intermediaires ne font plus sens (conservées pour respecter le sujet))

//NB: AFC = on affecte une cte 
// COP on copie la valeur d'une addresse dans une autre
//value ou addr2
//AFC ou COP
void AutreOperation(const char * operation, int addr1,float value) {
	//l'ASM ne gère pas les float => écris à la int
	printf("[YACC %s %d %f ]", operation, addr1, value);
	fprintf(file, "%s %d %.0f \n",operation, addr1, value);
}
//operation arithmetique
void operation(const char * operation,int addresse_result, int addr1, int addr2) {
	printf("[YACC %s %d %d %d ]", operation,addresse_result, addr1, addr2);
	fprintf(file, "%s %d %d %d \n",operation,addresse_result, addr1, addr2);
}

void PrintfOperation(char *name, char* value, int addr){
	printf(" [YACC PRINTF : la variable est : %s et vaut %s ]",name,value);
	fprintf(file, "PRI %d \n",addr);
}
void ReturnOperation(int addr, int value){
	printf(" [YACC RETURN value: %d ]",value);
	fprintf(file, "RETURN %d \n",addr);
}
%}

%union {
//on déclare une struct plutôt que directement $<INT>$ pour pouvoir renvoyer plusieurs valeurs 
//#ADDR pour l'interpreteur assembleur et FLOAT pour l'analyse par valeur du C dans le parser
	struct s{
	int INT;
	float FLOAT;
	char* STR;
	int ADDR;
	} s;
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
%type<s.STR> tVAR


%start Program
%%

Program :
  	tINT tMAIN { voidOrIntMain=1;}tOP tCP Body {if(hasAreturn ==0){printf("\033[01;33m Warning no return in a non-void function ! \033[0m");}}
	| tVOID tMAIN tOP tCP Body	{if(hasAreturn == 1){printf("\033[01;33m Warning return in a void function ! \033[0m");}}
    ;
Type :
     tINT {$<s>$.INT =INT_TYPE;}
    |tFLOAT {$<s>$.INT = FLOAT_TYPE;}
    |tVOID {$<s>$.INT = VOID_TYPE;}
    |tCHAR {$<s>$.INT =CHAR_TYPE;}
    ;



Body :
      tOB Instruction tCB 
    ;

//que entre même type
Expression :
    tINT_VAL      { 
    		$<s>$.ADDR=tempAddr;
    		$<s>$.FLOAT = (float)$<s>1.INT;
		AutreOperation("AFC",tempAddr, $<s>$.FLOAT);
		tempAddr++;
		}
  | tFLOAT_VAL { $<s>$.FLOAT = $<s>1.FLOAT;
  		$<s>$.ADDR=tempAddr;
		//printf("[YACC AFF addr: %d value:%f ]", tempAddr, $<s>$.FLOAT);
		AutreOperation("AFC",tempAddr, $<s>$.FLOAT);
		tempAddr++;
		}
  | tCHAR_VAL{ $<s>$.STR = $<s>1.STR;
  		$<s>$.ADDR=tempAddr;
		AutreOperation("AFC",tempAddr, $<s>$.FLOAT);
		tempAddr++;
		}
  | Expression tPLUS Expression  { $<s>$.FLOAT=$<s>1.FLOAT+$<s>3.FLOAT;$<s>$.ADDR=tempAddr;operation("ADD",tempAddr, $<s>1.ADDR, $<s>3.ADDR);tempAddr++;}
  | Expression tMOINS Expression { $<s>$.FLOAT=$<s>1.FLOAT-$<s>3.FLOAT;$<s>$.ADDR=tempAddr;operation("SOU",tempAddr, $<s>1.ADDR, $<s>3.ADDR);tempAddr++;}
  | Expression tFOIS Expression  { $<s>$.FLOAT=$<s>1.FLOAT*$<s>3.FLOAT;$<s>$.ADDR=tempAddr; operation("MUL",tempAddr, $<s>1.ADDR, $<s>3.ADDR);tempAddr++;}
  | Expression tDIVISE Expression  { $<s>$.FLOAT=$<s>1.FLOAT/$<s>3.FLOAT;$<s>$.ADDR=tempAddr; operation("DIV",tempAddr, $<s>1.ADDR, $<s>3.ADDR);tempAddr++;}
  | tMOINS Expression {
		$<s>$.FLOAT = -$<s>2.FLOAT;
		$<s>$.ADDR = tempAddr;
		//printf("[YACC COP %d 0 ]", tempAddr);
		//printf("[YACC SOU %d %d %f ]", tempAddr, tempAddr, $<s>2.FLOAT);
		//AutreOperation("COP",tempAddr, 0);
		operation("SOU",tempAddr, tempAddr, $<s>2.ADDR);
		tempAddr++;
	}        %prec tNEG  
  | tOP Expression tCP  { $<s>$.FLOAT=$<s>2.FLOAT; $<s>$.ADDR=$<s>2.ADDR; }
  | tVAR	{/*^$$= value_of_variable_tVar */
  		//!\ il ne faut pas renvoyer l'adresse de la var mais une copie temp (sinon modifie définitivement la var)
  		$<s>$.FLOAT = atof(getValeurToPrint($<s>1.STR));
		$<s>$.ADDR=tempAddr;
		int varAddr = getAdresse($<s>1.STR);
		if(!varEstIni(varAddr)) {
			printf(" \033[01;31m FATAL ERROR :unitialized variable \033[0m");
			exit(-1);
		}
		AutreOperation("COP",tempAddr, varAddr);
		tempAddr++; 
		}
  ;
Liste :
	tVAR tCOMMA  {
		if(alreadyDeclaredVar($<s>1.STR)) {
				printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
				exit(-1);
		}
		ajouter($<s>1.STR, declaration_a_virg_last_type, false, false);
  	} Liste
      | tVAR tVIRG  {
      		if(alreadyDeclaredVar($<s>1.STR)) {
					printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
					exit(-1);
		}
		ajouter($<s>1.STR, declaration_a_virg_last_type, false, false);
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
			printf("\033[01;31m This variable is not initialized cannot quick increment \033[0m");
			exit(-1);
		}
		int type=getType($1);
		if(type==FLOAT_TYPE || type==INT_TYPE){
			float value=atof(getValeurToPrint($1));
			setValeurFloat($1,value+1);
			//operation("COP",varAddr, $<s>1.ADDR, $<s>3.ADDR);
			AutreOperation("AFC",tempAddr, 1);//on stocke 1 dans une adresse temp
			operation("ADD",varAddr,varAddr,tempAddr);//on stocke dans varAddr varAddr+1
			//rq: ope atomique => pas besoin d'incrementer tempAddr (on peut écraser le 1 ss probleme)
		}
		else {
			printf("\033[01;31m FATAL ERROR : This type doesn't permit quick increment  \033[0m");
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
			printf("\033[01;31m FATAL ERROR : This variable is not initialized cannot quick decrement \033[0m");
			exit(-1);
		}
		int type=getType($1);
		if(type==FLOAT_TYPE || type==INT_TYPE){
			float value=atof(getValeurToPrint($1));
			setValeurFloat($1,value-1);
			//AutreOperation("COP",varAddr, value-1);
			AutreOperation("AFC",tempAddr, 1);//on stocke 1 dans une adresse temp
			operation("SOU",varAddr,varAddr,tempAddr);//on stocke dans varAddr varAddr-1
		}
		else {
			printf("\033[01;31m FATAL ERROR : This type doesn't permit quick increment  \033[0m");
			exit(-1);
		}
   } Instruction
  |Type tVAR tEGAL Expression tVIRG {
		if(alreadyDeclaredVar($<s>2.STR)) {
			printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
			exit(-1);
		}
		int varAddr =ajouter($<s>2.STR, $<s>1.INT, true,false);
		if(!varEstIni(varAddr)) {
			iniVar(varAddr);
		}
  		int type=$<s>1.INT;
		if(type==FLOAT_TYPE || type==INT_TYPE){
			setValeurFloat($<s>2.STR,(float)$<s>4.FLOAT);
			AutreOperation("COP",varAddr, $<s>4.ADDR);
		}
		else if(type==CHAR_TYPE){
			setValeurStr($2,$<s>4.STR);
			//printf("[YACC COP %d : %s]", varAddr , $<s>4.STR);
			AutreOperation("COP",varAddr, $<s>4.ADDR);
		}
  } Instruction
| Type tCONST tVAR tEGAL Expression tVIRG {
		if(alreadyDeclaredVar($<s>3.STR)) {
			printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
			exit(-1);
		}
  		int varAddr = ajouter($3, $<s>1.INT, true,true);//cst
		int type=$<s>1.INT;
		if(type==FLOAT_TYPE || type==INT_TYPE){
			setValeurFloat($3,(float)$<s>5.FLOAT);
			//AutreOperation("COP",varAddr, (float)$<s>5.FLOAT);
			AutreOperation("COP",varAddr, $<s>5.ADDR);
		}
		else if(type==CHAR_TYPE){
			setValeurStr($3,$<s>5.STR);
			//printf("[YACC COP %d : %s]", varAddr , $<s>5.STR);(StrOperation)
			AutreOperation("COP",varAddr, $<s>5.ADDR);
		}
  } Instruction
 | tCONST Type tVAR tEGAL Expression tVIRG {
 		if(alreadyDeclaredVar($<s>3.STR)) {
					printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
					exit(-1);
		}
    		int varAddr = ajouter($3, $<s>2.INT, true,true);
  		int type=$<s>2.INT;
  		if(type==FLOAT_TYPE || type==INT_TYPE){
  			setValeurFloat($3,(float)$<s>5.FLOAT);
  			//printf("[YACC COP %d : %f ]", varAddr , (float)$<s>5.FLOAT);
  			AutreOperation("COP",varAddr, $<s>5.ADDR);
  		}
  		else if(type==CHAR_TYPE){
  			setValeurStr($3,$<s>5.STR);
  			//printf("[YACC COP %d : %s]", varAddr , $<s>5.STR);
  			AutreOperation("COP",varAddr, $<s>5.ADDR);
  		}
  } Instruction
| Type tVAR tVIRG {
		if(alreadyDeclaredVar($<s>2.STR)) {
					printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
					exit(-1);
		}
		ajouter($2, $<s>1.INT, false, false);
  } Instruction
| Type tVAR tCOMMA {
	if(alreadyDeclaredVar($<s>2.STR)) {
				printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
				exit(-1);
	}
	declaration_a_virg_last_type= $<s>1.INT;
	ajouter($2, $<s>1.INT, false, false);
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
			setValeurFloat($1,$<s>3.FLOAT);
			//printf("[YACC COP %d %f ]", varAddr, $<s>3.FLOAT);
			AutreOperation("COP",varAddr, $<s>3.ADDR);
		}
		else if(type==CHAR_TYPE){
			setValeurStr($1,$<s>3.STR);
			//printf("[YACC COP %d %s ]", varAddr, $<s>3.STR);
			AutreOperation("COP",varAddr, $<s>3.ADDR);
		}
	
  }Instruction
| tPRINTF tOP tVAR { PrintfOperation($3, getValeurToPrint($3),getAdresse($3) );}tCP tVIRG Instruction 
| tRETURN tVAR tVIRG {
			int varAddr = getAdresse($2);
			if(voidOrIntMain==0){
				printf("\033[01;31m FATAL ERROR : void function cannot return a value, switch to int main() \033[0m");
				exit(-1);
			}
			if(!varEstIni(varAddr)) {
				printf("\033[01;33m Warning return uninitialized variable \033[0m");
			}
			if(hasAreturn==1){
					printf("\033[01;33m Warning dead code! more than one return without conditionnal \033[0m");
					}else
			hasAreturn =1;
			$<s>$.INT =atoi(getValeurToPrint($2));
			$<s>$.ADDR=tempAddr;
			printf("[YACC RETURN value: %d",$<s>$.INT);
			AutreOperation("COP",tempAddr, varAddr);
			ReturnOperation($<s>$.ADDR,$<s>$.INT);
			tempAddr++;
			} Instruction
| tRETURN tINT_VAL tVIRG {
		if(voidOrIntMain==0){
						printf("\033[01;31m FATAL ERROR : void function cannot return a value, switch to int main() \033[0m");
						exit(-1);
			}
		if(hasAreturn==1){
			printf("\033[01;33m Warning dead code! more than one return without conditionnal \033[0m");
		}else
		hasAreturn =1;
	         $<s>$.INT = $<s>2.INT;
		$<s>$.ADDR=tempAddr;
		printf("[YACC RETURN value: %d",$<s>$.INT);
		AutreOperation("AFC",tempAddr, $<s>$.INT);
		ReturnOperation($<s>$.ADDR,$<s>$.INT);
		tempAddr++;
		} Instruction
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
    file = fopen(output,"a+");    
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

