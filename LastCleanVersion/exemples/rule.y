%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "table_symboles.h"
	#include "table_instructions.h"
	char * type;
	int yylex(void);
	void yyerror(char*);
	int nb_symboles = 0;
%}

%union {
	int nb;
	char* str;
}

%token tVIRGULE
%token tFIN_INSTRUCTION
%token tPRINTF
%token tACCOLADE_OUVRANTE
%token tACCOLADE_FERMANTE
%token tPLUS
%token tMOINS
%token tFOIS
%token tDIVISE
%token tEGAL
%token tPARENTHESE_OUVRANTE
%token tPARENTHESE_FERMANTE
%token tCONST
%token tNOM
%token tNOMBRE
%token tTYPE
%token tINT
%token tCHAR
%token tVOID
%token tCARACTERE
%token tNULL
%token tWHILE
%token tGUILLEMET
%token tIF
%token tELSE
%token tDOUBLE_EGAL
%token tDIFFERENT
%token tINFERIEUR
%token tINFERIEUR_EGAL
%token tSUPERIEUR
%token tSUPERIEUR_EGAL
%token tPOINT_EXCLAM

%left tEGAL
%left tDOUBLE_EGAL tDIFFERENT tINFERIEUR tINFERIEUR_EGAL tSUPERIEUR tSUPERIEUR_EGAL
%left tPLUS tMOINS
%left tFOIS tDIVISE

%nonassoc tTRUC
%nonassoc tELSE

%type <str> tNOM tCHAR tCARACTERE tINT tVOID type
%type <nb> tNOMBRE bloc_if_action bloc_else_action bloc_while_action memo_instr

%%
start:fonctions ;

fonctions:
	  fonction fonctions
	|
	;

fonction:
	  type tNOM tPARENTHESE_OUVRANTE args tPARENTHESE_FERMANTE body
	;

type: tVOID {type = "void";} | tINT {type = "int";} | tCHAR {type = "char";};

args:arg args_suite
	| 
	;

args_suite: tVIRGULE arg args_suite
	| 
	; 

arg: type tNOM ;

body:
	tACCOLADE_OUVRANTE instrs tACCOLADE_FERMANTE
	;

instrs:
	instr instrs
	|
	;

instr:
	appel_fonction
	| declaration_variables
	| calcul
	| printf
	| bloc_if
	| bloc_while
	;


// While

bloc_while_action:
	{		
		addInstr("load", getIndice()-1, 9);
		addInstr("jmpc", getIndice(), 9); 
		decrementerIndice();
		$$ = getIndiceInstr() -1;
	} ;

memo_instr:
	{
		$$ = getIndiceInstr();
	};


bloc_while : tWHILE tPARENTHESE_OUVRANTE memo_instr operation tPARENTHESE_FERMANTE bloc_while_action body_while
		  		{ patchInstr($6, getIndiceInstr()+1); addInstr("jmp", $3 ,222);};

body_while : tACCOLADE_OUVRANTE instrs tACCOLADE_FERMANTE 
		 | instr tFIN_INSTRUCTION;





bloc_if_action:
	{		
		addInstr("load", getIndice()-1, 9);
		addInstr("jmpc", -1, 9); 
		decrementerIndice();
		$$ = getIndiceInstr() -1;} ;

// ELSE => Faire un saut de if vers le DEBUT de ELSE (Pas la fin de IF) si IF est faux
// Si IF est vrai, on fait les instructions puis on saute le ELSE

bloc_else_action:
	{ addInstr("jmp", -1, 222 ); 
	  $$ = getIndiceInstr() -1;} ;

bloc_if : tIF tPARENTHESE_OUVRANTE operation tPARENTHESE_FERMANTE bloc_if_action body_if
		  		{ patchInstr($5, getIndiceInstr()); } %prec tTRUC 
		  | tIF tPARENTHESE_OUVRANTE operation tPARENTHESE_FERMANTE bloc_if_action body_if
				bloc_else_action tELSE { patchInstr($5, getIndiceInstr()); } body_if { patchInstr($7 , getIndiceInstr()); }
		  ;



body_if : tACCOLADE_OUVRANTE instrs tACCOLADE_FERMANTE 
		 | instr tFIN_INSTRUCTION;






appel_fonction:
	tNOM tPARENTHESE_OUVRANTE valeurs tPARENTHESE_FERMANTE tFIN_INSTRUCTION ;

printf : tPRINTF tPARENTHESE_OUVRANTE operation tPARENTHESE_FERMANTE tFIN_INSTRUCTION 
		{ addInstr("print", getIndice()-1, 0); decrementerIndice(); } ;

decl: type tNOM {ajouter($2, type, 0, 1);} decl_affect ;

decl_affect : | tEGAL operation { 
	addInstr("load", getIndice()-1, 0);
	decrementerIndice(); 
	//On récupère la valeur et on l'inscrit au bon endroit dans la mémoire
	addInstr("store", getIndice()-1, 0);
	 } ;

declaration_variables:
	decl declaration_variables_suite tFIN_INSTRUCTION;

declaration_variables_suite: tVIRGULE tNOM {ajouter($2, type, 0, 1);} declaration_variables_suite
							| ;

valeurs: operation valeurs_suite
		| 
		;

valeurs_suite: tVIRGULE operation valeurs_suite
				| 
				;

valeur_ar: tNOM
		  {
		  addInstr("load", getAdresse($1), 0);
		  addInstr("store", ajouterTmp("int"), 0);}
		| tNOMBRE 
		  {
		  addInstr("afc", 0, $1);
		  addInstr("store", ajouterTmp("int"), 0);
		  }
		| appel_fonction ;
/*
valeur_nar: tCARACTERE
		| tNULL
		| appel_fonction;
*/

operation : operation tPLUS operation {
				addInstr("load", getIndice()-1, 1);
				addInstr("load", getIndice()-2, 0);
				addInstr("add", 0, 1);
				addInstr("store", getIndice()-2, 0);
				decrementerIndice();
				}
			| operation tMOINS operation {
				addInstr("load", getIndice()-1, 1);
				addInstr("load", getIndice()-2, 0);
				addInstr("sub", 0, 1);
				addInstr("store", getIndice()-2, 0);
				decrementerIndice();
				}
			| operation tFOIS operation {
				addInstr("load", getIndice()-1, 1);
				addInstr("load", getIndice()-2, 0);
				addInstr("mul", 0, 1);
				addInstr("store", getIndice()-2, 0);
				decrementerIndice();
				}
			| operation tDIVISE operation {
				addInstr("load", getIndice()-1, 1);
				addInstr("load", getIndice()-2, 0);
				addInstr("div", 0, 1);
				addInstr("store", getIndice()-2, 0);
				decrementerIndice();
				}
			| operation tDOUBLE_EGAL operation {
				addInstr("load", getIndice()-1, 1);
				addInstr("load", getIndice()-2, 0);
				addInstr("equ", 0, 1);
				addInstr("store", getIndice()-2, 0);
				decrementerIndice();
				}
			| operation tDIFFERENT operation {
				addInstr("load", getIndice()-1, 1);
				addInstr("load", getIndice()-2, 0);
				addInstr("nequ", 0, 1);
				addInstr("store", getIndice()-2, 0);
				decrementerIndice();
				}
			| operation tINFERIEUR operation {
				addInstr("load", getIndice()-1, 1);
				addInstr("load", getIndice()-2, 0);
				addInstr("inf", 0, 1);
				addInstr("store", getIndice()-2, 0);
				decrementerIndice();
				}
			| operation tINFERIEUR_EGAL operation {
				addInstr("load", getIndice()-1, 1);
				addInstr("load", getIndice()-2, 0);
				addInstr("infe", 0, 1);
				addInstr("store", getIndice()-2, 0);
				decrementerIndice();
				}
			| operation tSUPERIEUR operation {
				addInstr("load", getIndice()-1, 1);
				addInstr("load", getIndice()-2, 0);
				addInstr("sup", 0, 1);
				addInstr("store", getIndice()-2, 0);
				decrementerIndice();
				}
			| operation tSUPERIEUR_EGAL operation {
				addInstr("load", getIndice()-1, 1);
				addInstr("load", getIndice()-2, 0);
				addInstr("supe", 0, 1);
				addInstr("store", getIndice()-2, 0);
				decrementerIndice();
				}
			| tPARENTHESE_OUVRANTE operation tPARENTHESE_FERMANTE
			| valeur_ar ;

calcul: tNOM tEGAL operation tFIN_INSTRUCTION {
		int a = getAdresse($1);
		addInstr("load", getIndice() - 1, 0);
		addInstr("store", a, 0);
		decrementerIndice(); } ;

%%

void yyerror(char *err) {
	extern int yylineno;
	printf("error: %s (%d)\n", err, yylineno);
	exit(1);
}

int main(){
	printf("Initialisation du compilateur...\n");
	init();
	initInstrs();
	printf("Parsing du code C...\n");
	yyparse();
	printf("Table des symboles générée :\n");
	afficherTableSymboles();
	printf("Code assembleur généré :\n");
	displayInstructions();
	printf("Ecriture du code assembleur dans le fichier output.asm...\n");
	genererAsm("output.asm");
	genererCodeHexa("outputHexa.asm");
} 
