bison -d hello.y
flex hello.l
gcc -o compilateur.exe hello.tab.c lex.yy.c -lm