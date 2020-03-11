bison -d yacc.y
lex source2
gcc -c lex.yy.c -o lex.o
gcc -c yacc.tab.c -o yacc.o
gcc -o final lex.o yacc.o
