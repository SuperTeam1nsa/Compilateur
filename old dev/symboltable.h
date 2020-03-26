struct ligne
{
	char id[16];
	char type[8];
	int init;
	int depth;
};

void init();

void decrementerIndice();

int getIndice();

void afficherTableSymboles();

void ajouter(char id[16], char type[8], int init, int depth);

int ajouterTmp (char type[8]);

int getAdresse(char *);
