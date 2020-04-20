del interpreter/output.asm
del lex.yy.c
del parser.tab.c
del parser.tab.h
del parser.output
del compilateur.exe
bison -d -v parser.y
flex lexer.l
gcc -std=c99 -g -o compilateur.exe lex.yy.c parser.tab.c symboltable.c -lm
compilateur.exe < codeC.c
cd interpreter
run.bat