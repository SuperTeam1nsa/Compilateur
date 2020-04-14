#include <stdbool.h>
#define INT_TYPE 1
#define FLOAT_TYPE 2
#define CHAR_TYPE 3
#define VOID_TYPE 4

struct ligne
{
  char id[16]; //nom de la var
  int type; //type de var
  int init;
  char* valeur;//conversion selon le type ensuite
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
int getAdresse(char * symbole);
int getType(char *id);
//id=symbole
void setValeurStr(char* symbole, char* valeur);
void setValeurFloat(char* symbole, float valeur);
//void setValeurInt(char* symbole, int valeur);
//void setValeur(char* symbole, void* valeur);
char* getValeurToPrint(char* symbole);
bool alreadyDeclaredVar(char* symbole);
int getIndice();
bool varEstIni(int addr);
void iniVar(int addr);
bool isSymbolConst(int addr);