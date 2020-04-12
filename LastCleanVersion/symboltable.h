#include <stdbool.h>
struct ligne
{
  char id[16]; //Adresse
  char type[8]; //type de var -- 5 ou 8  ?
  int init;
  int depth; //profondeur
  bool isConst;//const ou pas #reaffectable ou pas
};

// On fait un malloc => direct
//void init();

void decrementerIndice();

void afficherTableSymboles();

int ajouter(char id[16], float type, int init, bool isConst);

int ajouterTmp (float type);

//On regarde l'id, si erreur -1
int getAdresse(char *);

int getIndice();
bool varEstIni(int addr);
void iniVar(int addr);
bool isSymbolConst(int addr);