cd src
rm lex.yy.c
rm simulator.tab.c
rm simulator.tab.h
rm simulator.output
rm interpreteur.exe
yacc -d -v simulator.y
lex simulator.l
gcc -std=c99 -g -o interpreteur.exe lex.yy.c simulator.tab.c instructions.c -lm
interpreteur.exe < ../output.asm