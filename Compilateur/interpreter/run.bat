cd src
del lex.yy.c
del simulator.tab.c
del simulator.tab.h
del simulator.output
del interpreteur.exe
bison -d -v simulator.y
flex simulator.l
gcc -std=c99 -g -o interpreteur.exe lex.yy.c simulator.tab.c instructions.c -lm
interpreteur.exe < ../output.asm