struct ligne
{
  char id[16]; //Adresse : 10 ou 16 ?
  char type[8]; //type de var -- 5 ou 8  ?
  int init; // A voir si c'est utile
  int depth; //profondeur
};

// On fait un malloc
void init();

void decrementerIndice();

void afficherTableSymboles();

void ajouter(char id[16], char type[8], int init, int depth);

int ajouterTmp (char type[8]);

//On regarde l'id, si erreur -1
int getAdresse(char *);

int getIndice();
