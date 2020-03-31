#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 1000
#define INT_TYPE 1
#define CHAR_TYPE 2

void icnrementDepth();
void decrementDepth();
void pushSymbol(char * id, int type, bool isConst, bool isInit);
int getSymbolAddr(char * id);
bool isSymbolInit(int addr);
void initializeSymbol(int addr);
bool isSymbolConst(int addr);