#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symboltable.h"

#define SIZE 100
#define MAX_VAR_SIZE 64
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
bool alreadyDeclaredVar(char* id){
	for (int i=profondeur - 1; i >= 0 ; i--) {
			if (strcmp(id, tab[i].id)==0) {
				return true;
			}
		}
	return false;
}
int getType(char *id) {
	for (int i=profondeur - 1; i >= 0 ; i--) {
		if (strcmp(id, tab[i].id)==0) {
			return tab[i].type;
		}
	}
	printf("\033[01;31m Erreur fatale : pas de symbole \"%s\" dans la table, hint: did you declare it first ? \033[0m", id);
	exit(-1);
}
int getAdresse(char *id) {
	for (int i=profondeur - 1; i >= 0 ; i--) {
		// Be carreful Hichem negative or positive, anything that's not a 0 is a true value in if
		if (strcmp(id, tab[i].id)==0) {
			return i;
		}
	}
	printf("\033[01;31m Erreur fatale : pas de symbole \"%s\" dans la table, hint: did you declare it first ? \033[0m", id);
	exit(-1);
}
void setValeurStr(char* id, char* valeur){
		bool found=false;
	for (int i=profondeur - 1; i >= 0 ; i--) {
			if (strcmp(id, tab[i].id)==0) {
				found=true;
				tab[i].valeur=malloc (sizeof (char) * strlen(valeur));
				strncpy(tab[i].valeur,valeur, sizeof(tab[i].valeur));
			}
		}
	if(!found){
				printf("\033[01;31m Erreur fatale : pas de symbole \"%s\" dans la table, hint: did you declare it first ?\033[0m", id);
				exit(-1);
		}
}
void setValeurFloat(char* id, float valeur){
	char *buffer = malloc (sizeof (char) * MAX_VAR_SIZE);
	snprintf(buffer, (sizeof (char) * MAX_VAR_SIZE), "%f", valeur);
	bool found=false;
	for (int i=profondeur - 1; i >= 0 ; i--) {
			if (strcmp(id, tab[i].id)==0) {
				found=true;
				tab[i].valeur=malloc (sizeof (char) * MAX_VAR_SIZE);
				strncpy(tab[i].valeur,buffer,(sizeof (char) * MAX_VAR_SIZE));
			}
		}
	if(!found){
				printf("\033[01;31m Erreur fatale : pas de symbole \"%s\" dans la table, hint: did you declare it first ? \033[0m", id);
				exit(-1);
		}
}
/*
void setValeurInt(char* id, int valeur){
	char *buffer = malloc (sizeof (char) * 64);
	snprintf(buffer, sizeof buffer, "%d", valeur);
	bool found=false;
	//printf("HERRRRRRRRRRRRRRRRRRR  + %s + %d",buffer,valeur);
	for (int i=profondeur - 1; i >= 0 ; i--) {
			if (strcmp(id, tab[i].id)==0) {
				//printf(" \n \n FOUND + i : %d id: %s tabid: %s ",i,id,tab[i].id);
				found=true;
				tab[i].valeur=malloc (sizeof (char) * strlen(buffer));
				strncpy(tab[i].valeur,buffer,sizeof(tab[i].valeur));
			}
		}
		if(!found){
			printf("Erreur fatale : pas de symbole \"%s\" dans la table", id);
			exit(-1);
		}
}
void setValeur(char* id, void* valeur){
	char *buffer = malloc (sizeof (char) * 64);
	for (int i=profondeur - 1; i >= 0 ; i--) {
			if (strcmp(id, tab[i].id)==0) {
				if(tab[i].type == INT_TYPE){
					snprintf(buffer, sizeof buffer, "%d", *(int*)valeur);
					strncpy(tab[i].valeur,buffer, strlen(buffer));
				}else if(tab[i].type == FLOAT_TYPE){
					snprintf(buffer, sizeof buffer, "%f", *(float*)valeur);
					strncpy(tab[i].valeur,buffer, strlen(buffer));
				}else if(tab[i].type == CHAR_TYPE){
					strncpy(tab[i].valeur,(char*)valeur, strlen(buffer));
				}
			}
		}
	printf("Erreur fatale : pas de symbole \"%s\" dans la table", id);
	exit(-1);
}*/
char* getValeurToPrint(char* id){
	char *buffer = malloc (sizeof (char) * MAX_VAR_SIZE);
	for (int i=profondeur - 1; i >= 0 ; i--) {
				if (strcmp(id, tab[i].id)==0) {
						snprintf(buffer, MAX_VAR_SIZE, "%s", tab[i].valeur);
						return buffer;
				}
			}
	printf("\033[01;31m Erreur fatale : pas de symbole \"%s\" dans la table, hint: did you declare it first ? \033[0m", id);
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
		printf("\033[01;31m Variable non déclarée ! Surement pas initialise de facto :p \033[0m");
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



