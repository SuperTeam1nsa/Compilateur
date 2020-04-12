%{
             
#include <stdlib.h>
#include "parser.tab.h"

%}

blancs    [ \t]+
chiffre   [0-9]
entier    {chiffre}+
float {entier}*\.{entier}+
char '(\\[ntbr0])|.'
exposant  [eE][+-]?{entier}
reel    {entier}("."{entier})?{exposant}?
nom_variable [a-zA-Z][a-zA-Z0-9_]*

%%

{blancs}  { /* On ignore */ }
"+"   {printf("tPLUS "); return(tPLUS);}
"-"   {printf("tMOINS "); return(tMOINS);}
"*"   {printf("tFOIS "); return(tFOIS);}
"/"   {printf("tDIVISE "); return(tDIVISE);}
"{"   {printf("tOB "); return(tOB);}
"}"   {printf("tCB "); return(tCB);}
"("   {printf("tOP "); return(tOP);}
")"   {printf("tCP "); return(tCP);}
","   {printf("tCOMMA "); return(tCOMMA);}
"=="  {printf("tCOMPARAISON "); return(tCOMPARAISON);}
"="   {printf("tEGAL "); return(tEGAL);}
"<"   {printf("tINFSTRICT "); return(tINFSTRICT);}
">"   {printf("tSUPSTRICT "); return(tSUPSTRICT);}
">="  {printf("tSUPEGAL "); return(tSUPEGAL);}
"<="  {printf("tINFEGAL "); return(tINFEGAL);}
"!="  {printf("tDIFF "); return(tDIFF);}
"int" {printf("tINT ");/*yylval.str = strdup(yytext);*/ return tINT ; }
"float" {printf("tFLOAT ");return(tFLOAT);}
"void" {printf("tVOID ");return(tVOID);}
"char" {printf("tCHAR ");return(tCHAR);}
";"   {printf("tVIRG "); return(tVIRG);}
"main" {printf("tMAIN "); return(tMAIN);}
"printf" {printf("tPRINTF ");return(tPRINTF);}
"return" { printf("tRETURN ");return(tRETURN);}
"const" { printf("tCONST ");return(tCONST);}
{entier} {printf("tINT_VAL ");yylval.nb = atoi(yytext);return(tINT_VAL);}
{float} {printf("tFLOAT_VAL ");yylval.reel= atof(yytext);return(tFLOAT_VAL);}
{reel}    {printf("tFLOAT_VAL ");yylval.reel= atof(yytext);return(tFLOAT_VAL);}
{char} {printf("tCHAR_VAL ");yylval.str = yytext;return(tCHAR_VAL);}
{nom_variable} {printf("tVAR [LEXER :%s] ",yytext);yylval.str = yytext; return(tVAR);}

%%
/*
"while" { yylval.str = strdup(yytext); return tWHILE ; }
"^"   {printf("tPUISSANCE"); return(tPUISSANCE);}
exposant  [eE][+-]?{entier}
reel    {entier}("."{entier})?{exposant}?
{reel}    {// yylval.nb=atoi(yytext);printf("tNOMBRE"); return(tNOMBRE);}
int yywrap(void)
{
   return 1;
}
//%"\n"  {printf("tNEW_LINE"); return(tNEW_LINE);}
*/