#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table_instructions.h"

#define SIZE_TINSTR 1000
int indiceInstruction = 0;

struct instruction * tabInstr;

void initInstrs() {
	tabInstr = malloc(sizeof(struct instruction)*SIZE_TINSTR);
}

int getIndiceInstr() {
	return indiceInstruction;
}

void displayInstructions() {

	printf("	+----------------------------------+\n");
	printf("	|          Code assembleur         |\n");
	printf("	+----------------------------------+\n");
	for (int i=0; i < indiceInstruction ; i++) {
		printf("	| %2d | %9s | %6d | %6d |\n",i, tabInstr[i].instr, tabInstr[i].arg1, tabInstr[i].arg2);
		printf("	+----------------------------------+\n");
	}

}

void addInstr(char instr[16], int arg1, int arg2) {

	if (indiceInstruction < 0 || indiceInstruction >= SIZE_TINSTR) {
		printf("Erreur d'indice\n");
		exit(1);
	} else {
		struct instruction newLine = { .instr = "", .arg1 = arg1, .arg2 = arg2 };	
		strcpy(newLine.instr , instr);
		tabInstr[indiceInstruction] = newLine ;
		indiceInstruction++;
	}
}

void patchInstr(int indOrig, int indDest){
	tabInstr[indOrig].arg1 = indDest;
}

void genererAsm(char* filename)
{
    FILE * f;

    f = fopen(filename, "w");
    if (f != NULL)
    {
		for (int i=0; i < indiceInstruction ; i++) {
			fprintf(f, "%s %d %d\n", tabInstr[i].instr, tabInstr[i].arg1, tabInstr[i].arg2);
		}
        fclose(f);
    }
    else
        perror("hello.txt");
}

void genererCodeHexa(char* filename)
{
    FILE * f;

    f = fopen(filename, "w");
    if (f != NULL)
    {
		for (int i=0; i < indiceInstruction ; i++) {
			//if (tabInstr[i].instr)
			if ( !strcmp(tabInstr[i].instr,"add") ) {
				fprintf(f, "01%.2x%.2x00\n", tabInstr[i].arg1, tabInstr[i].arg2);
			} else if ( !strcmp(tabInstr[i].instr,"mul") ) {
				fprintf(f, "02%.2x%.2x00\n", tabInstr[i].arg1, tabInstr[i].arg2);
			} else if ( !strcmp(tabInstr[i].instr,"sub") ) {
				fprintf(f, "03%.2x%.2x00\n", tabInstr[i].arg1, tabInstr[i].arg2);
			} else if ( !strcmp(tabInstr[i].instr,"div") ) {
				fprintf(f, "04%.2x%.2x00\n", tabInstr[i].arg1, tabInstr[i].arg2);
			} else if ( !strcmp(tabInstr[i].instr,"print") ) {
				fprintf(f, "05%.2x%.2x00\n", tabInstr[i].arg1, tabInstr[i].arg2);
			} else if ( !strcmp(tabInstr[i].instr,"afc") ) {
				fprintf(f, "06%.2x%.2x00\n", tabInstr[i].arg1, tabInstr[i].arg2);
			} else if ( !strcmp(tabInstr[i].instr,"load") ) {
				fprintf(f, "07%.2x%.2x00\n", tabInstr[i].arg1, tabInstr[i].arg2);
			} else if ( !strcmp(tabInstr[i].instr,"store") ) {
				fprintf(f, "08%.2x%.2x00\n", tabInstr[i].arg1, tabInstr[i].arg2);
			} else if ( !strcmp(tabInstr[i].instr,"equ") ) {
				fprintf(f, "09%.2x%.2x00\n", tabInstr[i].arg1, tabInstr[i].arg2);
			} else if ( !strcmp(tabInstr[i].instr,"inf") ) {
				fprintf(f, "0a%.2x%.2x00\n", tabInstr[i].arg1, tabInstr[i].arg2);
			} else if ( !strcmp(tabInstr[i].instr,"infe") ) {
				fprintf(f, "0b%.2x%.2x00\n", tabInstr[i].arg1, tabInstr[i].arg2);
			} else if ( !strcmp(tabInstr[i].instr,"sup") ) {
				fprintf(f, "0c%.2x%.2x00\n", tabInstr[i].arg1, tabInstr[i].arg2);
			} else if ( !strcmp(tabInstr[i].instr,"supe") ) {
				fprintf(f, "0d%.2x%.2x00\n", tabInstr[i].arg1, tabInstr[i].arg2);
			} else if ( !strcmp(tabInstr[i].instr,"jmp") ) {
				fprintf(f, "0e%.2x%.2x00\n", tabInstr[i].arg1, tabInstr[i].arg2);
			} else if ( !strcmp(tabInstr[i].instr,"jmpc") ) {
				fprintf(f, "0f%.2x%.2x00\n", tabInstr[i].arg1, tabInstr[i].arg2);
			} else {}			
			
		}
        fclose(f);
    }
    else
        perror("hello.txt");
}
