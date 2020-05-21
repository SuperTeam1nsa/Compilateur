%error-verbose
%{

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

int tempAddr = 0;
int success = 1; 
int voidOrIntMain=0;//void by def
int hasAreturn=0;
char instruction[MAX_INSTRUCTIONS][SIZE_INSTRUCTION];
int cp=0;
int depth=0;
//variante depth : if => depth +=MAX_INSIDE_IF, ifPatch: depth =olddepth[lastJump] else: depth++; elsepatch: depth--
int jumpToPatch[MAX_INSIDE_IF];
int lastJump=-1;

int jumpToPatchW[MAX_INSIDE_LOOP];
int lastJumpW=-1;


int activeIf[MAX_INSIDE_IF];
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
void oneOperation(const char * operation,int addresse_result, int addr1) {
if(activeInstruction){
	printf("[YACC %s %d %d ]", operation,addresse_result, addr1);
	snprintf(instruction[cp],30,"%s %d %d \n",operation,addresse_result, addr1);
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
	jumpToPatch[lastJump]=cp;
	depth++;
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
	deleteVarDepht(depth);
	depth--;
	lastJump--;
	}
}
void ElsePatchOperation(void){
if(activeInstruction){
	printf("\n [YACC PATCH ELSE false goto line: %d]",cp);
	snprintf(instruction[jumpToPatch[lastJump]],30,"JMP %d \n",cp);
	deleteVarDepht(depth);
	lastJump--;
	depth--;
	}
}

void loopStart(void){
if(activeInstruction){
	lastJumpW++;
	jumpToPatchW[lastJumpW]=cp;
	depth++;
	}

}
void loopEnd(void){
if(activeInstruction){
	printf("\n [YACC PATCH DO WHILE addr goto line: %d]",cp);
	snprintf(instruction[cp],30,"JMT %d \n",jumpToPatchW[lastJumpW]);
	depth--;
	lastJumpW--;
	cp++;
	}
}

%}

%union {
//on déclare une struct plutôt que directement $<INT>$ pour pouvoir renvoyer plusieurs valeurs 
//#ADDR pour l'interpreteur assembleur et FLOAT pour l'analyse par valeur du C dans le parser, str pour les char, int pour trouver le type
	struct s{
	int INT;
	float FLOAT;
	char* STR;
	int ADDR;
	} s;
}
 
%token  tCOMMA
%token  tIF tELSE 
%token  tDO tWHILE
%token  tOP tCP
%token  tOB tCB
%token  tVAR 
%token  tINT tVOID tCHAR tFLOAT tVIRG tMAIN tCONST
%token  tINT_VAL tFLOAT_VAL tCHAR_VAL
%token  tRETURN
%token  tPRINTF

%left tPLUS  tMOINS tADR
%left tFOIS  tDIVISE
%left tNEG
%left tCOMPARAISON tINFSTRICT tSUPSTRICT tAND tOR
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
    		$<s>$.FLOAT = $<s>1.FLOAT;
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
  		$<s>$.FLOAT=$<s>1.FLOAT;
		AutreOperation("AFC",tempAddr, $<s>$.FLOAT);
		tempAddr++;
		}
		//printf("\n\n r: %f 1: %f 3: %f",$<s>$.FLOAT,$<s>1.FLOAT,$<s>3.FLOAT);
  | Expression tPLUS Expression  { $<s>$.FLOAT=$<s>1.FLOAT+$<s>3.FLOAT;$<s>$.ADDR=tempAddr;operation("ADD",tempAddr, $<s>1.ADDR, $<s>3.ADDR);tempAddr++;}
  | Expression tMOINS Expression { $<s>$.FLOAT=$<s>1.FLOAT-$<s>3.FLOAT;$<s>$.ADDR=tempAddr;operation("SOU",tempAddr, $<s>1.ADDR, $<s>3.ADDR);tempAddr++;}
  | Expression tFOIS Expression  { $<s>$.FLOAT=$<s>1.FLOAT*$<s>3.FLOAT;$<s>$.ADDR=tempAddr; operation("MUL",tempAddr, $<s>1.ADDR, $<s>3.ADDR);tempAddr++;}
  | Expression tDIVISE Expression  { $<s>$.FLOAT=$<s>1.FLOAT/$<s>3.FLOAT;$<s>$.ADDR=tempAddr; operation("DIV",tempAddr, $<s>1.ADDR, $<s>3.ADDR);tempAddr++;}
  | Expression tCOMPARAISON Expression  { $<s>$.FLOAT=(float)($<s>1.FLOAT==$<s>3.FLOAT?1:0);$<s>$.ADDR=tempAddr; operation("CMP",tempAddr, $<s>1.ADDR, $<s>3.ADDR);tempAddr++;}
  | Expression tINFSTRICT Expression  { $<s>$.FLOAT=($<s>1.FLOAT < $<s>3.FLOAT?1:0);$<s>$.ADDR=tempAddr; operation("INF",tempAddr, $<s>1.ADDR, $<s>3.ADDR);tempAddr++;}
  | Expression tSUPSTRICT Expression  { $<s>$.FLOAT=($<s>1.FLOAT > $<s>3.FLOAT?1:0);$<s>$.ADDR=tempAddr; operation("SUP",tempAddr, $<s>1.ADDR, $<s>3.ADDR);tempAddr++;}
  | Expression tSUPEGAL Expression  { $<s>$.FLOAT=($<s>1.FLOAT >= $<s>3.FLOAT?1:0);$<s>$.ADDR=tempAddr; operation("SUE",tempAddr, $<s>1.ADDR, $<s>3.ADDR);tempAddr++;}
  | Expression tINFEGAL Expression  { $<s>$.FLOAT=($<s>1.FLOAT <= $<s>3.FLOAT?1:0);$<s>$.ADDR=tempAddr; operation("INE",tempAddr, $<s>1.ADDR, $<s>3.ADDR);tempAddr++;}
  | Expression tDIFF Expression  { $<s>$.FLOAT=($<s>1.FLOAT != $<s>3.FLOAT?1:0);$<s>$.ADDR=tempAddr; operation("DIF",tempAddr, $<s>1.ADDR, $<s>3.ADDR);tempAddr++;}
  | Expression tOR Expression  { $<s>$.FLOAT=(($<s>1.FLOAT || $<s>3.FLOAT)?1:0);$<s>$.ADDR=tempAddr; operation("COR",tempAddr, $<s>1.ADDR, $<s>3.ADDR);tempAddr++;}
  | Expression tAND Expression  { $<s>$.FLOAT=(($<s>1.FLOAT && $<s>3.FLOAT)?1:0);$<s>$.ADDR=tempAddr; operation("AND",tempAddr, $<s>1.ADDR, $<s>3.ADDR);tempAddr++;}
  | tNOT Expression  { $<s>$.FLOAT=($<s>2.FLOAT==0)?1:0;$<s>$.ADDR=tempAddr; oneOperation("NOT",tempAddr, $<s>2.ADDR);tempAddr++;}
  | tMOINS Expression {
		$<s>$.FLOAT = -$<s>2.FLOAT;
		$<s>$.ADDR = tempAddr;
		//printf("[YACC COP %d 0 ]", tempAddr);
		//printf("[YACC SOU %d %d %f ]", tempAddr, tempAddr, $<s>2.FLOAT);
		AutreOperation("AFC",tempAddr, 0);
		operation("SOU",tempAddr, tempAddr, $<s>2.ADDR);
		tempAddr++;
	}        %prec tNEG  
  | tOP Expression tCP  { $<s>$.FLOAT=$<s>2.FLOAT; $<s>$.ADDR=$<s>2.ADDR; }
  | tVAR	{/*^$$= value_of_variable_tVar */
  		//!\ il ne faut pas renvoyer l'adresse de la var mais une copie temp (sinon modifie définitivement la var)
  		//bad conversion (aka char)
  		char *buff=getValeurToPrint($<s>1.STR);
  		if(getType($<s>1.STR)==CHAR_TYPE)
  			$<s>$.FLOAT=(float)buff[0];
  		else{
  		$<s>$.FLOAT = atof(buff);
  		free(buff);
  		}
		$<s>$.ADDR=tempAddr;
		int varAddr = getAdresse($<s>1.STR,depth);
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
		ajouter($<s>1.STR, declaration_a_virg_last_type, false, false,depth);
  	} Liste
      | tVAR tVIRG  {
      		if(alreadyDeclaredVar($<s>1.STR)) {
					printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
					exit(-1);
		}
		ajouter($<s>1.STR, declaration_a_virg_last_type, false, false,depth);
 	} Instruction
      ;
If :tIF tOP {if(OPTI){
		wasInActifStateIf=activeInstruction;
		activeInstruction=0;}
		}
		Expression tCP {
		tempAddr=getIndice();//+1;
			/*GENERER JMF */ 
			if(OPTI){
				depth++;
				if(wasInActifStateIf){
					activeIf[lastJump]=$<s>4.FLOAT; 
					activeInstruction=$<s>4.FLOAT;
				}
			}else{
				IfOperation();
			}
		} Body {if(!OPTI && activeInstruction){
			IfPatchOperation(cp);
			}
			else if(OPTI){
			deleteVarDepht(depth);
			depth--;
			}
			activeInstruction=1;} ;
Else:tELSE { /*GENERER JMP*/
		activeInstruction=activeIf[lastJump]?0:1;
		if(!OPTI && activeInstruction){ElseOperation();}
		else if(OPTI){depth++;}
} Body {if(!OPTI && activeInstruction)
	{ElsePatchOperation();}
	else if(OPTI){deleteVarDepht(depth);depth--;}
	activeInstruction=1;};

Instruction:
  tVAR tPLUS tPLUS tVIRG  {wasInActifState=activeInstruction;if(OPTI)activeInstruction=0;}{
  		if(wasInActifState){
		int varAddr = getAdresse($1,depth);		
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
			char *buff=getValeurToPrint($1);
			int value;
			if(getType($<s>1.STR)==CHAR_TYPE)
				value=(float)buff[0];
			else{
			value = atof(buff);
			free(buff);
  			}
			setValeurFloat($1,value+1);
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
		tempAddr=getIndice();//+1;
   } Instruction
 | tVAR tMOINS tMOINS tVIRG {wasInActifState=activeInstruction;if(OPTI)activeInstruction=0;}{
 		if(wasInActifState){
   		int varAddr = getAdresse($1,depth);		
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
			int value;
			char *buff=getValeurToPrint($1);
			if(getType($<s>1.STR)==CHAR_TYPE)
				value=(float)buff[0];
			else{
				value = atof(buff);
				free(buff);
  			}
			setValeurFloat($1,value-1);
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
		tempAddr=getIndice();//+1;
   } Instruction
  |Type tVAR tEGAL{wasInActifState=activeInstruction;if(OPTI)activeInstruction=0;} Expression tVIRG {
		if(wasInActifState){
		if(alreadyDeclaredVar($<s>2.STR)) {
			printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
			exit(-1);
		}
		int varAddr =ajouter($<s>2.STR, $<s>1.INT, true,false,depth)-1;
		if(!varEstIni(varAddr)) {
			iniVar(varAddr);
		}
  		int type=$<s>1.INT;
		if(type==FLOAT_TYPE || type==INT_TYPE){
			setValeurFloat($<s>2.STR,(float)$<s>5.FLOAT);
			AutreOperation("COP",varAddr, $<s>5.ADDR);
		}
		else if(type==CHAR_TYPE){
			setValeurStr($2,$<s>5.STR);
			//printf("[YACC COP %d : %s]", varAddr , $<s>5.STR);
			AutreOperation("COP",varAddr, $<s>5.ADDR);
		}
		if(OPTI){
		activeInstruction=1;
		AutreOperation("AFC",varAddr, (float)$<s>5.FLOAT);
		}
		}
		tempAddr=getIndice();//+1;
  } Instruction
| Type tCONST tVAR tEGAL {wasInActifState=activeInstruction;if(OPTI)activeInstruction=0;} Expression tVIRG {
		if(wasInActifState){
		if(alreadyDeclaredVar($<s>3.STR)) {
			printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
			exit(-1);
		}
  		int varAddr = ajouter($3, $<s>1.INT, true,true,depth)-1;//cst
		int type=$<s>1.INT;
		if(type==FLOAT_TYPE || type==INT_TYPE){
			setValeurFloat($3,(float)$<s>6.FLOAT);
			AutreOperation("COP",varAddr, $<s>6.ADDR);
		}
		else if(type==CHAR_TYPE){
			setValeurStr($3,$<s>6.STR);
			AutreOperation("COP",varAddr, $<s>6.ADDR);
		}
		if(OPTI){
			activeInstruction=1;
			AutreOperation("AFC",varAddr, (float)$<s>6.FLOAT);
		}
		}
		tempAddr=getIndice();//+1;
  } Instruction
 | tCONST Type tVAR tEGAL{wasInActifState=activeInstruction;if(OPTI)activeInstruction=0;} Expression tVIRG {
 		if(wasInActifState){
 		if(alreadyDeclaredVar($<s>3.STR)) {
					printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
					exit(-1);
		}
    		int varAddr = ajouter($3, $<s>2.INT, true,true,depth)-1;
  		int type=$<s>2.INT;
  		if(type==FLOAT_TYPE || type==INT_TYPE){
				setValeurFloat($3,(float)$<s>6.FLOAT);
				AutreOperation("COP",varAddr, $<s>6.ADDR);
			}
		else if(type==CHAR_TYPE){
			setValeurStr($3,$<s>6.STR);
			AutreOperation("COP",varAddr, $<s>6.ADDR);
		}
		if(OPTI && wasInActifState){
			activeInstruction=1;
			AutreOperation("AFC",varAddr, (float)$<s>6.FLOAT);
		}
		}
		tempAddr=getIndice();//+1;
  } Instruction
| Type tVAR tVIRG {
		if(activeInstruction){
		if(alreadyDeclaredVar($<s>2.STR)) {
					printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
					exit(-1);
		}
		ajouter($2, $<s>1.INT, false, false,depth);
		}
  } Instruction
| Type tVAR tCOMMA {
	if(activeInstruction){
	if(alreadyDeclaredVar($<s>2.STR)) {
				printf("\033[01;31m FATAL ERROR : already declared var \033[0m");
				exit(-1);
	}
	declaration_a_virg_last_type= $<s>1.INT;
	ajouter($2, $<s>1.INT, false, false,depth);
	}
  } Liste
| tVAR tEGAL {wasInActifState=activeInstruction;if(OPTI)activeInstruction=0;}Expression tVIRG {
	if(wasInActifState){
	int varAddr = getAdresse($1,depth);		
			if(isSymbolConst(varAddr)) {
				printf("\033[01;31m FATAL ERROR : const variable cannot reaffect value \033[0m");
				exit(-1);
			}
			if(!varEstIni(varAddr)) {
				iniVar(varAddr);
			}
		int type=getType($1);
		if(type==FLOAT_TYPE || type==INT_TYPE){
			setValeurFloat($1,$<s>4.FLOAT);
			AutreOperation("COP",varAddr, $<s>4.ADDR);
		}
		else if(type==CHAR_TYPE){
			setValeurStr($1,$<s>4.STR);
			AutreOperation("COP",varAddr, $<s>4.ADDR);
		}
		if(OPTI){
			activeInstruction=1;
			AutreOperation("AFC",varAddr, (float)$<s>4.FLOAT);
		}
		}
		tempAddr=getIndice();//+1;
  }Instruction
| If Else Instruction
| If Instruction
| tDO { if(activeInstruction)loopStart();OPTI=0;/*pas d'opti de boucle*/} Body tWHILE tOP Expression tCP {if(activeInstruction)loopEnd();OPTI=user_want_opti;tempAddr=getIndice();} tVIRG Instruction
| tPRINTF tOP tVAR { if(activeInstruction){PrintfOperation($3, getValeurToPrint($3),getAdresse($3,depth) );}}tCP tVIRG Instruction 
| tRETURN tVAR tVIRG {
		if(activeInstruction){
			int varAddr = getAdresse($2,depth);
			if(voidOrIntMain==0){
				printf("\033[01;31m FATAL ERROR : void function cannot return a value, switch to int main() \033[0m");
				exit(-1);
			}
			if(!varEstIni(varAddr)) {
				printf("\033[01;33m Warning return uninitialized variable \033[0m");
			}
			hasAreturn =1;
			char* buff=getValeurToPrint($2);
			$<s>$.INT =atoi(buff);
			free(buff);
			$<s>$.ADDR=tempAddr;
			AutreOperation("COP",tempAddr, varAddr);
			ReturnOperation($<s>$.ADDR,$<s>$.INT);
			tempAddr++;
			}
			} Instruction
| tRETURN tINT_VAL tVIRG {
		if(activeInstruction){
		if(voidOrIntMain==0){
						printf("\033[01;31m FATAL ERROR : void function cannot return a value, switch to int main() \033[0m");
						exit(-1);
			}
		hasAreturn =1;
	         $<s>$.INT = $<s>2.INT;
		$<s>$.ADDR=tempAddr;
		AutreOperation("AFC",tempAddr, $<s>$.INT);
		ReturnOperation($<s>$.ADDR,$<s>$.INT);
		tempAddr++;
		}
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

