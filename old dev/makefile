
# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = g++
CC = gcc
CFLAGS  = -g -Wall

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: final

# To create the executable file final we need the object files
# yacc.o, lex.o
#
final:  yacc.o lex.o  
	$(CC) $(CFLAGS) -o final yacc.o lex.o 


yacc.o:  yacc.y
    bison -d yacc.y
	$(CC) $(CFLAGS) -c yacc.tab.c

# To create the object file lex.o, we need the source files
# counter.c and counter.h:
#
lex.o:  lex.yy.c
	$(CC) $(CFLAGS) -c lex.yy.c

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) final *.o *~
