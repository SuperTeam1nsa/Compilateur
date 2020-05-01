#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#include "table_instructions.h"

#define SIZE_TINSTR 1000

int indiceInstruction = 0;
int nbInstructions;
int reg[16];
int memoireDonnees[1024];
int ip = 0;
struct instruction * tabInstr;

void initInstrs() {
	tabInstr = malloc(sizeof(struct instruction)*SIZE_TINSTR);
}

void printRegistres() {
	printf("	+---------------------+\n");
	printf("	|      Registres      |\n");
	printf("	+---------------------+\n");
	for (int i=0; i < 16 ; i++) {
		printf("	| %3d |           %3d |\n",i, reg[i]);
	}
	printf("	+---------------------+\n");
}

void interpreter() {
	printf("Interprétation du code ASM...\n");
	while (ip < nbInstructions){

		if (!strcmp(tabInstr[ip].instr,"jmp") ) { //OK
			printf("\033[0;36m[Interpréteur] \033[0;35m[ip =%3d]\033[0m jmp   détecté, arg1 =%3d, arg2 =%3d\n", ip, tabInstr[ip].arg1, tabInstr[ip].arg2);
			printf("\033[0;36m[Interpréteur]\033[0m On saute à l'instruction %d.\n", tabInstr[ip].arg1);
			ip = tabInstr[ip].arg1 ;
		} else if (!strcmp(tabInstr[ip].instr,"jmpc")) { //OK
			printf("\033[0;36m[Interpréteur] \033[0;35m[ip =%3d]\033[0m jmpc  détecté, arg1 =%3d, arg2 =%3d\n", ip, tabInstr[ip].arg1, tabInstr[ip].arg2);
			if (reg[tabInstr[ip].arg2]==0) {
				printf("\033[0;36m[Interpréteur]\033[0m On saute à l'adresse %d car le contenu du registre %d vaut 0.\n", 
					tabInstr[ip].arg1, tabInstr[ip].arg2);
				ip = tabInstr[ip].arg1 ;
			} else {
				printf("\033[0;36m[Interpréteur]\033[0m On ne saute pas à l'adresse %d car le contenu du registre %d est différent de 0.\n", 
					tabInstr[ip].arg1, tabInstr[ip].arg2);
				ip++;
			}
		} else if (!strcmp(tabInstr[ip].instr,"add")) { //OK
			printf("\033[0;36m[Interpréteur] \033[0;35m[ip =%3d]\033[0m add   détecté, arg1 =%3d, arg2 =%3d\n", ip, tabInstr[ip].arg1, tabInstr[ip].arg2);
			printf("\033[0;36m[Interpréteur]\033[0m On inscrit dans le registre %d la somme des valeurs contenues dans les registres %d et %d, soient %d et %d.\n"
				,tabInstr[ip].arg1, tabInstr[ip].arg1, tabInstr[ip].arg2, reg[tabInstr[ip].arg1], reg[tabInstr[ip].arg2]);
			reg[tabInstr[ip].arg1] += reg[tabInstr[ip].arg2];
			ip++;
		} else if (!strcmp(tabInstr[ip].instr,"sub")) { //OK
			printf("\033[0;36m[Interpréteur] \033[0;35m[ip =%3d]\033[0m sub   détecté, arg1 =%3d, arg2 =%3d\n", ip, tabInstr[ip].arg1, tabInstr[ip].arg2);
			printf("\033[0;36m[Interpréteur]\033[0m On inscrit dans le registre %d la soustraction des valeurs contenues dans les registres %d et %d, soient %d et %d.\n"
				,tabInstr[ip].arg1, tabInstr[ip].arg1, tabInstr[ip].arg2, reg[tabInstr[ip].arg1], reg[tabInstr[ip].arg2]);
			reg[tabInstr[ip].arg1] -= reg[tabInstr[ip].arg2];
			ip++;
		} else if (!strcmp(tabInstr[ip].instr,"mul")) { //OK
			printf("\033[0;36m[Interpréteur] \033[0;35m[ip =%3d]\033[0m mul   détecté, arg1 =%3d, arg2 =%3d\n", ip, tabInstr[ip].arg1, tabInstr[ip].arg2);
			printf("\033[0;36m[Interpréteur]\033[0m On inscrit dans le registre %d la multiplication des valeurs contenues dans les registres %d et %d, soient %d et %d.\n"
				,tabInstr[ip].arg1, tabInstr[ip].arg1, tabInstr[ip].arg2, reg[tabInstr[ip].arg1], reg[tabInstr[ip].arg2]);
			reg[tabInstr[ip].arg1] *= reg[tabInstr[ip].arg2];
			ip++;
		} else if (!strcmp(tabInstr[ip].instr,"div")) {
			printf("\033[0;36m[Interpréteur] \033[0;35m[ip =%3d]\033[0m div   détecté, arg1 =%3d, arg2 =%3d\n", ip, tabInstr[ip].arg1, tabInstr[ip].arg2);
			printf("\033[0;36m[Interpréteur]\033[0m On inscrit dans le registre %d la division des valeurs contenues dans les registres %d et %d, soient %d et %d.\n"
				,tabInstr[ip].arg1, tabInstr[ip].arg1, tabInstr[ip].arg2, reg[tabInstr[ip].arg1], reg[tabInstr[ip].arg2]);
			if (reg[tabInstr[ip].arg2] != 0) {
				reg[tabInstr[ip].arg1] = reg[tabInstr[ip].arg1]/reg[tabInstr[ip].arg2];
			} else {
				printf("\033[0;36m[Interpréteur]\033[0m \033[0;31mERREUR DIVISION PAR ZERO.\033[0m \n");
				exit(1);
			}
			ip++;
		} else if (!strcmp(tabInstr[ip].instr,"cop") ) { //OK
			printf("\033[0;36m[Interpréteur] \033[0;35m[ip =%3d]\033[0m cop   détecté, arg1 =%3d, arg2 =%3d\n", ip, tabInstr[ip].arg1, tabInstr[ip].arg2);
			printf("\033[0;36m[Interpréteur]\033[0m On copie dans le registre %d la valeur contenue dans le registre %d, soit %d.\n"
				,tabInstr[ip].arg1, tabInstr[ip].arg2, reg[tabInstr[ip].arg2]);
			reg[tabInstr[ip].arg1] = reg[tabInstr[ip].arg2];
			ip++;
		} else if (!strcmp(tabInstr[ip].instr,"equ")) { //OK
			printf("\033[0;36m[Interpréteur] \033[0;35m[ip =%3d]\033[0m equ   détecté, arg1 =%3d, arg2 =%3d\n", ip, tabInstr[ip].arg1, tabInstr[ip].arg2);
			if (reg[tabInstr[ip].arg1]==reg[tabInstr[ip].arg2]) {
				reg[tabInstr[ip].arg1] = 1;
				printf("\033[0;36m[Interpréteur]\033[0m On inscrit 1 dans le registre %d car %d est égal à %d.\n", 
					tabInstr[ip].arg1, reg[tabInstr[ip].arg1], reg[tabInstr[ip].arg2]);
			} else {
				reg[tabInstr[ip].arg1] = 0;
				printf("\033[0;36m[Interpréteur]\033[0m On inscrit 0 dans le registre %d car %d est différent de %d.\n", 
					tabInstr[ip].arg1, reg[tabInstr[ip].arg1], reg[tabInstr[ip].arg2]);
			}
			ip++;
		} else if (!strcmp(tabInstr[ip].instr,"nequ")) { //OK
			printf("\033[0;36m[Interpréteur] \033[0;35m[ip =%3d]\033[0m nequ  détecté, arg1 =%3d, arg2 =%3d\n", ip, tabInstr[ip].arg1, tabInstr[ip].arg2);
			if (reg[tabInstr[ip].arg1]!=reg[tabInstr[ip].arg2]) {
				reg[tabInstr[ip].arg1] = 1;
				printf("\033[0;36m[Interpréteur]\033[0m On inscrit 1 dans le registre %d car %d est différent de %d.\n", 
					tabInstr[ip].arg1, reg[tabInstr[ip].arg1], reg[tabInstr[ip].arg1]);
			} else {
				reg[tabInstr[ip].arg1] = 0;
				printf("\033[0;36m[Interpréteur]\033[0m On inscrit 0 dans le registre %d car %d est égal à %d.\n", 
					tabInstr[ip].arg1, reg[tabInstr[ip].arg1], reg[tabInstr[ip].arg1]);
			}
			ip++;
		} else if (!strcmp(tabInstr[ip].instr,"inf")) { //OK
			printf("\033[0;36m[Interpréteur] \033[0;35m[ip =%3d]\033[0m inf   détecté, arg1 =%3d, arg2 =%3d\n", ip, tabInstr[ip].arg1, tabInstr[ip].arg2);
			if (reg[tabInstr[ip].arg1]<reg[tabInstr[ip].arg2]) {
				reg[tabInstr[ip].arg1] = 1;
				printf("\033[0;36m[Interpréteur]\033[0m On inscrit 1 dans le registre %d car %d est inférieur à %d.\n", 
					tabInstr[ip].arg1, reg[tabInstr[ip].arg1], reg[tabInstr[ip].arg1]);
			} else {
				reg[tabInstr[ip].arg1] = 0;
				printf("\033[0;36m[Interpréteur]\033[0m On inscrit 0 dans le registre %d car %d n'est pas inférieur à %d.\n", 
					tabInstr[ip].arg1, reg[tabInstr[ip].arg1], reg[tabInstr[ip].arg1]);
			}
			ip++;
		} else if (!strcmp(tabInstr[ip].instr,"infe")) { //OK
			printf("\033[0;36m[Interpréteur] \033[0;35m[ip =%3d]\033[0m infe  détecté, arg1 =%3d, arg2 =%3d\n", ip, tabInstr[ip].arg1, tabInstr[ip].arg2);
			if (reg[tabInstr[ip].arg1]<=reg[tabInstr[ip].arg2]) {
				reg[tabInstr[ip].arg1] = 1;
				printf("\033[0;36m[Interpréteur]\033[0m On inscrit 1 dans le registre %d car %d est inférieur ou égal à %d.\n", 
					tabInstr[ip].arg1, reg[tabInstr[ip].arg1], reg[tabInstr[ip].arg1]);
			} else {
				reg[tabInstr[ip].arg1] = 0;
				printf("\033[0;36m[Interpréteur]\033[0m On inscrit 0 dans le registre %d car %d n'est pas inférieur ou égal à %d.\n", 
					tabInstr[ip].arg1, reg[tabInstr[ip].arg1], reg[tabInstr[ip].arg1]);
			}
			ip++;
		} else if (!strcmp(tabInstr[ip].instr,"sup")) { //OK
			printf("\033[0;36m[Interpréteur] \033[0;35m[ip =%3d]\033[0m sup   détecté, arg1 =%3d, arg2 =%3d\n", ip, tabInstr[ip].arg1, tabInstr[ip].arg2);
			if (reg[tabInstr[ip].arg1]>reg[tabInstr[ip].arg2]) {
				reg[tabInstr[ip].arg1] = 1;
				printf("\033[0;36m[Interpréteur]\033[0m On inscrit 1 dans le registre %d car %d est supérieur à %d.\n", 
					tabInstr[ip].arg1, reg[tabInstr[ip].arg1], reg[tabInstr[ip].arg1]);
			} else {
				reg[tabInstr[ip].arg1] = 0;
				printf("\033[0;36m[Interpréteur]\033[0m On inscrit 0 dans le registre %d car %d n'est pas supérieur à %d.\n", 
					tabInstr[ip].arg1, reg[tabInstr[ip].arg1], reg[tabInstr[ip].arg1]);
			}
			ip++;
		} else if (!strcmp(tabInstr[ip].instr,"supe")) { //OK
			printf("\033[0;36m[Interpréteur] \033[0;35m[ip =%3d]\033[0m supe  détecté, arg1 =%3d, arg2 =%3d\n", ip, tabInstr[ip].arg1, tabInstr[ip].arg2);
			if (reg[tabInstr[ip].arg1]>=reg[tabInstr[ip].arg2]) {
				reg[tabInstr[ip].arg1] = 1;
				printf("\033[0;36m[Interpréteur]\033[0m On inscrit 1 dans le registre %d car %d est supérieur ou égal à %d.\n", 
					tabInstr[ip].arg1, reg[tabInstr[ip].arg1], reg[tabInstr[ip].arg1]);
			} else {
				reg[tabInstr[ip].arg1] = 0;
				printf("\033[0;36m[Interpréteur]\033[0m On inscrit 0 dans le registre %d car %d n'est pas supérieur ou égal %d.\n", 
					tabInstr[ip].arg1, reg[tabInstr[ip].arg1], reg[tabInstr[ip].arg1]);
			}
			ip++;
		} else if (!strcmp(tabInstr[ip].instr,"afc")) { //OK
			printf("\033[0;36m[Interpréteur] \033[0;35m[ip =%3d]\033[0m afc   détecté, arg1 =%3d, arg2 =%3d\n", ip, tabInstr[ip].arg1, tabInstr[ip].arg2);
			reg[tabInstr[ip].arg1] = tabInstr[ip].arg2;
			printf("\033[0;36m[Interpréteur]\033[0m On met dans le registre %d la valeur %d.\n",
				tabInstr[ip].arg1, tabInstr[ip].arg2);
			//printRegistres();
			ip++;
		} else if (!strcmp(tabInstr[ip].instr,"store")) { //OK
			printf("\033[0;36m[Interpréteur] \033[0;35m[ip =%3d]\033[0m store détecté, arg1 =%3d, arg2 =%3d\n", ip, tabInstr[ip].arg1, tabInstr[ip].arg2);
			memoireDonnees[tabInstr[ip].arg1] = reg[tabInstr[ip].arg2];
			printf("\033[0;36m[Interpréteur]\033[0m On a stocké dans la mémoire de données à l'adresse %d la valeur %d venant du registre %d.\n", 
				tabInstr[ip].arg1, memoireDonnees[tabInstr[ip].arg1], tabInstr[ip].arg2);
			ip++;
		} else if ((!strcmp(tabInstr[ip].instr,"load"))) { //OK
			printf("\033[0;36m[Interpréteur] \033[0;35m[ip =%3d]\033[0m load  détecté, arg1 =%3d, arg2 =%3d\n", ip, tabInstr[ip].arg1, tabInstr[ip].arg2);
			reg[tabInstr[ip].arg2] = memoireDonnees[tabInstr[ip].arg1];
			printf("\033[0;36m[Interpréteur]\033[0m On a stocké dans le registre %d la valeur %d contenue dans la mémoire de données à l'adresse %d.\n", 
				tabInstr[ip].arg2, memoireDonnees[tabInstr[ip].arg1], tabInstr[ip].arg1);
			ip++;
		} else if ((!strcmp(tabInstr[ip].instr,"print"))) { //OK
			printf("\033[0;36m[Interpréteur] \033[0;35m[ip =%3d]\033[0m print détecté, arg1 =%3d, arg2 =%3d\n", ip, tabInstr[ip].arg1, tabInstr[ip].arg2);
			printf("\033[0;36m[Interpréteur]\033[0m On affiche à l'écran %d, le contenu de la mémoire à l'adresse %d.\n", 
				memoireDonnees[tabInstr[ip].arg1], tabInstr[ip].arg1);
			printf("\033[0;33m> %d\033[0m\n", memoireDonnees[tabInstr[ip].arg1]);
			ip++;
		} else {
			printf("\033[0;36m[Interpréteur]\033[0m \033[0;31mERREUR INSTRUCTION INCONNUE, ip=%d, arg1=%d, arg2=%d\033[0m\n", ip, tabInstr[ip].arg1, tabInstr[ip].arg2);
			printRegistres();
			ip++;
		}
	}   
	printf("\n\033[0;32m\\(^_^)/ Interprétation terminée ! \\(^_^)/\033[0m\n\n");

}


int parse( char* filename )
{
	printf("Lecture du fichier %s...\n", filename);
	initInstrs();

	//static const char filename[] = "output.asm";
	FILE *file = fopen ( filename, "r" );
	if ( file != NULL )
	{
		char line [ 128 ]; 
 
		while ( fgets ( line, sizeof line, file ) != NULL )
		{

			char *str = line;
			char *token;
		 
			//Découper la chaîne selon les espaces
			token = strtok (str," ");

		 	struct instruction newLine = { .instr = "", .arg1 = -1, .arg2 = -1 };	
			for (int i=0; i<3; i++)
			{				
				if (i==0) {				
					strcpy(newLine.instr , token);
				} else if (i == 1) {
					newLine.arg1 = atoi(token);
				} else if (i == 2) {
					newLine.arg2 = atoi(token);
				}	 
				token = strtok (NULL, " ,");
			}
			
			tabInstr[indiceInstruction++] = newLine ;

		}
		nbInstructions = indiceInstruction;
		fclose ( file );
	}
	else
	{
		perror ( filename ); // why didn't the file open? 
	}
	return 0;
}

void displayInstructions() {

	printf("	+----------------------------------+\n");
	printf("	|   Code ASM lu dans le fichier    |\n");
	printf("	+----------------------------------+\n");
	for (int i=0; i < indiceInstruction ; i++) {
		printf("	| %2d | %9s | %6d | %6d |\n",i, tabInstr[i].instr, tabInstr[i].arg1, tabInstr[i].arg2);
		printf("	+----------------------------------+\n");
	}

}

int main(int argc, char *argv[]) {
	printf("Lancement de l'interpréteur...\n");
	if (argc!=2) {
		printf("Un argument SVP (vous en avez rentré %d).\n", (argc-1));
		exit(-1);
	}
	printf("Parsing du fichier output.asm...\n");
	parse(argv[1]);
	printf("Instructions lues dans le fichier output.asm :\n");
	displayInstructions();
	printf("Interprétation :\n");
	interpreter();
	return 0;
}



