%{
    #include <stdio.h>
    #include "instructions.h"
    int yylex();
    void yyerror(char*);
    int yydebug = 1;
    extern int yylineno;
%}

/* Union for yylval */
%union {
    int nb;
}

%token tADD tMUL tSOU tDIV tCOP tAFC tJMP tJMF tINF tSUP tCMP tSUE tINE tDIF tNOT tPRI tRET tJMT tCOR tAND

%token <nb> tNB

%%

%start File;

File:
    Instructions;

Instructions:
    /* epsilon */
    | Instructions Instruction
    ;

Instruction:
    tADD tNB tNB tNB
        {asm_add_3(ADD, $2, $3, $4);}
    | tMUL tNB tNB tNB
        {asm_add_3(MUL, $2, $3, $4);}
    | tSOU tNB tNB tNB
        {asm_add_3(SOU, $2, $3, $4);}
    | tDIV tNB tNB tNB
        {asm_add_3(DIV, $2, $3, $4);}
    | tCOP tNB tNB
        {asm_add_2(COP, $2, $3);}
    | tAFC tNB tNB
        {asm_add_2(AFC, $2, $3);}
    | tJMP tNB
        {asm_add_1(JMP, $2);}
    | tJMF tNB
        {asm_add_1(JMF, $2);}
    | tJMT tNB
        {asm_add_1(JMT, $2);}
    | tINF tNB tNB tNB
        {asm_add_3(INF, $2, $3, $4);}
    | tCOR tNB tNB tNB
        {asm_add_3(COR, $2, $3, $4);}
    | tAND tNB tNB tNB
        {asm_add_3(AND, $2, $3, $4);}
    | tINE tNB tNB tNB
        {asm_add_3(INE, $2, $3, $4);}
    | tSUE tNB tNB tNB
        {asm_add_3(SUE, $2, $3, $4);}
    | tDIF tNB tNB tNB
        {asm_add_3(DIF, $2, $3, $4);}
    | tNOT tNB tNB
        {asm_add_2(NOT, $2, $3);}
    | tSUP tNB tNB tNB
        {asm_add_3(SUP, $2, $3, $4);}
    | tCMP tNB tNB tNB
        {asm_add_3(CMP, $2, $3, $4);}
    | tPRI tNB
        {asm_add_1(PRI, $2);}
    | tRET tNB
        {asm_add_1(RET, $2);}
    ;


%%

void yyerror(char* str) {
    extern int yylineno;
    fprintf(stderr, "ERROR yyparse : %s\n", str);
}

int main(int argc, char *argv[]) {
    asm_init();
    yyparse();
    printf("INFO yyparse : Parsing End\n");
    asm_run();
    return 0;
}

