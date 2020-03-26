#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symboltable.h"

#define SIZE 10

struct ligne * tab;
int indiceCourant = 0; 

/*int main() {

	tab = init();
	ajouter ("i", "int", 1, 1);
	ajouter ("j", "double", 0, 1);
	ajouter ("k", "int", 0, 1);
	int add = ajouterTmp ("int");
	printf ("Adresse Tmp : %d\n", add); 
	
	afficher (tab); 
	
	return 0;

}*/


int getIndice() {
	return indiceCourant;
}

void init() {

	tab = malloc(sizeof(struct ligne)*SIZE);
}

void decrementerIndice(){
	indiceCourant--;
}

void afficherTableSymboles() {

	printf("	+------------------------------+\n");
	printf("	|      Table des symboles      |\n");
	printf("	+------------------------------+\n");
	for (int i=0; i < indiceCourant ; i++) {
		printf("	| %5s | %8s | %3d | %3d |\n",tab[i].id, tab[i].type, tab[i].init, tab[i].depth);
		printf("	+------------------------------+\n");
	}

}


int getAdresse(char *s) {
	for (int i=indiceCourant - 1; i >= 0 ; i--) {
		if (!strcmp(s, tab[i].id)) {
			return i;
		}
	}
	return -1;
}

void ajouter(char id[16], char type[8], int init, int depth) {

	if (indiceCourant < 0 || indiceCourant >= SIZE) {
		printf("Erreur d'indice\n");
		exit(1);
	} else {
		struct ligne newLine = { .id = "", .type = "", .init = init, .depth = depth };	
		strcpy(newLine.id , id);	
		strcpy(newLine.type , type);
		tab[indiceCourant] = newLine ;
		indiceCourant++;
	}
}

int ajouterTmp (char type[8]){
	if (indiceCourant < 0 || indiceCourant >= SIZE) {
		printf("Erreur d'indice\n");
		exit(1);
	} else {
		struct ligne newLine = { .id = "#", .type = "", .init = 1, .depth = 0 };	
		strcpy(newLine.type , type);
		tab[indiceCourant] = newLine ;
	}
	return indiceCourant++;
}



