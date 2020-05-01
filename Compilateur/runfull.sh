cd interpreter
rm output.asm
cd ..
rm lex.yy.c
rm parser.tab.c
rm parser.tab.h
rm parser.output
rm compilateur.exe
yacc -d -v parser.y
lex lexer.l
gcc -std=c99 -g -o compilateur.exe lex.yy.c parser.tab.c symboltable.c -lm
compilateur.exe $2 < $1
cd interpreter
run.sh