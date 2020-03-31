#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symboltable.h"

#define SIZE 10

struct ligne * tab;
int profondeur = 0; 

/*int main() {

    //TEST
	tab = init();
	ajouter ("a", "int", 1, 1);
	ajouter ("b", "double", 0, 1);
	ajouter ("c", "int", 0, 1);
	int add = ajouterTmp ("int");
	printf ("Adresse Tmp : %d\n", add); 
	
	afficher (tab); 
	
	return 0;

}*/


void init() {

	tab = malloc(sizeof(struct ligne)*SIZE);
}

int getIndice() {
	return profondeur;
}


void decrementerIndice(){
	profondeur--;
}

void afficherTableSymboles() {

	printf("	               ***              \n");
	printf("	|      Table des symboles      |\n");
	printf("	+              ***             + \n");
    printf("	+------------------------------+\n");
	for (int i=0; i < profondeur ; i++) {
		printf("	| %5s | %8s | %3d | %3d |\n",tab[i].id, tab[i].type, tab[i].init, tab[i].depth);
		printf("	+------------------------------+\n");
	}

}


int getAdresse(char *s) {
	for (int i=profondeur - 1; i >= 0 ; i--) {
		if (!strcmp(s, tab[i].id)) {
			return i;
		}
	}
	return -1;
}

void ajouter(char id[16], char type[8], int init, int depth) {

	if (profondeur < 0 || profondeur >= SIZE) {
		printf("Erreur ajouter TABLESYMBOL indice\n");
		exit(1);
	} else {
		struct ligne newLine = { .id = "", .type = "", .init = init, .depth = depth };	
		strcpy(newLine.id , id);	
		strcpy(newLine.type , type);
		tab[profondeur] = newLine ;
		profondeur++;
	}
}

int ajouterTmp (char type[8]){
	if (profondeur < 0 || profondeur >= SIZE) {
		printf("Erreur ajouterTMP TABLESYMBOL indice pr\n");
		exit(1);
	} else {
		struct ligne newLine = { .id = "#", .type = "", .init = 1, .depth = 0 };	
		strcpy(newLine.type , type);
		tab[profondeur] = newLine ;
	}
	return profondeur++;
}



