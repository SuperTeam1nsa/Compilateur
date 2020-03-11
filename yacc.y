%{

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

	int yylex(void);
	int yyerror(const char *s);
	int success = 1;

%}

%token  tNOMBRE
%token  tPLUS  tMOINS tFOIS  tDIVISE  tPUISSANCE
%token  tOP tCP
%token  tOB tCB
%token  tIF tELSE tVAR
%token  tCOMPARAISON tEGAL tINFSTRICT tSUPSTRICT
%token  tSUPEGAL tINFEGAL tDIFF tNOT 
%token  tINT tVOID tCHAR tVIRG tMAIN tCONST

%left tPLUS  tMOINS
%left tFOIS  tDIVISE
%left tNEG
%left tCOMPARAISON tEGAL tINFSTRICT tSUPSTRICT
%left tSUPEGAL tINFEGAL tDIFF
%right tNOT
%right tPUISSANCE

%start program
%%

program :
    | type tMAIN tOP tCP body 
    ;
type :
    | tINT
    |tVOID
    |tCHAR
    ;

body :
    | tOB instruction tCB 
    | tIF body 
    | tIF body tELSE
    ;

instruction :
    | Expression tVIRG { printf("Resultat : %f\n",$1); }
    | type tVAR tEGAL tNOMBRE tVIRG

Expression:
    tNOMBRE      { $$=$1; }
  | Expression tPLUS Expression  { $$=$1+$3; }
  | Expression tMOINS Expression { $$=$1-$3; }
  | Expression tFOIS Expression  { $$=$1*$3; }
  | Expression tDIVISE Expression  { $$=$1/$3; }
  | tMOINS Expression %prec tNEG  { $$=-$2; }
  | Expression tPUISSANCE Expression { $$=pow($1,$3); }
  | tOP Expression tCP  { $$=$2; }
  ;


%%

int main()
{
    yyparse();
    if(success)
    	printf("Parsing Successful\n");
    return 0;
}

int yyerror(const char *msg)
{
	extern int yylineno;
	printf("Parsing Failed\nLine Number: %d %s\n",yylineno,msg);
	success = 0;
	return 0;
}

