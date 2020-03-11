to compile:
lex lex source2_printf
gcc lex.yy.c 
./a.out < exampleC

//Output actuel : printf la liste des tokens
Rq: pour l'instant on ne s'interesse pas aux retours #yacc seconde partie, on verra ça avec l'annale pour faire printf + return bien  

Installation sous windows :
https://stackoverflow.com/questions/5456011/how-to-compile-lex-yacc-files-on-windows#5545924


Nouvelle façon de faire (marche sans nécessiter le def.h) :
 yacc -d yacc.y
It will generate 3 files- y.tab.c , y.tab.h and y.output

 lex source2_avec_des_return
It will generate lex.yy.c file


Run the following commands

    gcc -o a.out y.tab.c lex.yy.c -lm               (-lfl possible)
    ./a.out < exampleC


