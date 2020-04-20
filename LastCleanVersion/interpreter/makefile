SRCC:= ./src/*.c

all: interpreter

interpreter: ./src/interpreter.y ./src/interpreter.l ./src/instructions.c
	yacc -d ./src/interpreter.y
	lex ./src/interpreter.l
	gcc lex.yy.c y.tab.c ./src/instructions.c -Isrc -o interpreter

run: interpreter
	./interpreter < input.txt

clean:
	rm -f lex.yy.c interpreter y.tab.h y.tab.c *.o
