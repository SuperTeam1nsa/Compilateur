%{
             
#include <stdlib.h>
#include "parser.tab.h"

%}

blancs    [ \t]+
chiffre   [0-9]
entier    {chiffre}+
exposant  [eE][+-]?{entier}
nom_variable [a-zA-Z]+
reel    {entier}("."{entier})?{exposant}?

%%

{blancs}  { /* On ignore */ }
{reel}    {/* yylval.nb=atoi(yytext);*/printf("tNOMBRE"); return(tNOMBRE);}
"+"   {printf("tPLUS"); return(tPLUS);}
"-"   {printf("tMOINS"); return(tMOINS);}
"*"   {printf("tFOIS"); return(tFOIS);}
"/"   {printf("tDIVISE"); return(tDIVISE);}
"^"   {printf("tPUISSANCE"); return(tPUISSANCE);}
"("   {printf("tOP"); return(tOP);}
")"   {printf("tCP"); return(tCP);}
"=="  {printf("tCOMPARAISON"); return(tCOMPARAISON);}
"="   {printf("tEGAL"); return(tEGAL);}
"<"   {printf("tINFSTRICT"); return(tINFSTRICT);}
">"   {printf("tSUPSTRICT"); return(tSUPSTRICT);}
">="  {printf("tSUPEGAL"); return(tSUPEGAL);}
"<="  {printf("tINFEGAL"); return(tINFEGAL);}
"!="  {printf("tDIFF"); return(tDIFF);}
"int" { yylval.str = strdup(yytext); return tINT ; }
";"   {printf("tVIRG"); return(tVIRG);}
"while" { yylval.str = strdup(yytext); return tWHILE ; }
"main" {printf("tMAIN"); return(tMAIN);}
"const" {printf("tCONST"); return(tCONST);}
{nom_variable} {printf(" variable : %s",yytext); return(tVAR);}

%%

int yywrap(void)
{
   return 1;
}
//%"\n"  {printf("tNEW_LINE"); return(tNEW_LINE);}