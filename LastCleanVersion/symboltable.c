#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symboltable.h"

#define SIZE 100

struct ligne tab[SIZE];//malloc(sizeof(struct ligne)*100);
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
		printf("	| %5s | %8s | %3d | %3d | %s \n",tab[i].id, tab[i].type, tab[i].init, tab[i].depth,"%s", tab[i].isConst ? "true" : "false");
		printf("	+------------------------------+\n");
	}

}


int getAdresse(char *id) {
	for (int i=profondeur - 1; i >= 0 ; i--) {
		// Be carreful Hichem negative or positive, anything that's not a 0 is a true value in if
		if (strcmp(id, tab[i].id)==0) {
			return i;
		}
	}
	printf("Erreur fatale : pas de symbole \"%s\" dans la table", id);
	exit(-1);
}

int ajouter(char id[16], float type, int init, bool isConst) {

	if (profondeur < 0 || profondeur >= SIZE) {
		printf("Erreur ajouter TABLESYMBOL indice\n");
		exit(1);
	} else {
		struct ligne newLine = { .id = "", .type = type, .init = init, .depth = profondeur, .isConst=isConst };
		strcpy(newLine.id , id);
		//strcpy(newLine.type , type);
		tab[profondeur] = newLine ;
		profondeur++;
	}
	return profondeur;
}

///???
int ajouterTmp (float type){
	if (profondeur < 0 || profondeur >= SIZE) {
		printf("Erreur ajouterTMP TABLESYMBOL indice pr\n");
		exit(1);
	} else {
		struct ligne newLine = { .id = "#", .type = type, .init = 1, .depth = 0, .isConst=false};
		//strcpy(newLine.id , id);
		//strcpy(newLine.type , type);
		tab[profondeur] = newLine ;
	}
	return profondeur++;
}

//check if var à cette adresse est initialisée
bool varEstIni(int addr) {
	if(addr <= profondeur)
		return tab[addr].init;
	else{
		printf("Variable non déclarée ! Surement pas initialise de facto :p ");
		exit(-1);
	}
}

//quand on affecte une valeur à la variable on appelle cette fonction pour dire ok ini
void iniVar(int addr) {
	tab[addr].init = true;
}

//check const before affect value
bool isSymbolConst(int addr) {
	return tab[addr].isConst;
}



