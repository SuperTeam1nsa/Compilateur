cd interpreter
rm output.asm
cd ..
rm lex.yy.c
rm parser.tab.c
rm parser.tab.h
rm parser.output
rm compilateur.exe
yacc -d -v -b parser parser.y
lex lexer.l
gcc -g -o compilateur.exe lex.yy.c parser.tab.c symboltable.c -lm
./compilateur.exe $2 < $1
