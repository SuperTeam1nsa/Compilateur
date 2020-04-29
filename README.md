# Compilateur
On windows :  
in powershell (with color (desactivate it if no output)  
.\run.bat codeC/le_fichier_c_voulu.c [Mode_optimise] | Out-Host  
avec Mode_optimise : 0 ou 1  
e.g :  
.\run.bat codeC/opti.c 1 | Out-Host 
or in cmd (without color or follow : https://stackoverflow.com/questions/51680709/colored-text-output-in-powershell-console-using-ansi-vt100-codes#51681675 to activate color broadlly)   
  
on linux :  
Same with run.sh 
   
Features support tests :  
*  nombre sous forme d'exposant (ex: 10e1)
*  declaration en ligne des variables sans affectation(ex: int a, b;)
*  declaration de varibales de type char, int ou float avec ou sans affectation
*  declaration de variables constantes
*  reaffectation de valeur à une variable déjà déclarée
*  gestion des espaces, tab, retour à la ligne
*  gestion de printf(var) qui affiche le nom de la variable et sa valeur
*  gestion des opérations arithmétiques standards( +-/*) et des priorités entre elles ainsi que des parenthèses
*  gestion des return
*  gestion des operateurs rapides (non imbriques) (++/--)
*  supporte les comparaisons (<,>,>=,<=,!,!=,==) en renvoyant un entier 0 ou 1 (vrai) conformément au sujet (pas de check de type => use parenthesis for negative value)
*  gestion des if-else, if et imbrication (max imbrication = MAX_INSIDE_IF)
*  interpreteur statique du C à la volée pour générer de l'ASM optimisé (sur l'affectation des variables et les calculs statiques (ne gère pas les if)): 3 fois moins d'instructions ASM sur l'exemple

Erreur tests réalisés:  
*  const reaffectation => Fatal error
*  char de plus de un character (va etre tronque) => warning
*  return uninitialized var => warning
*  return sur une void function => fatal error
*  no return on a non-void function => warning
*  more than one return in a function (without conditional jump #dead code) => warning
*  declaration du même nom de variable 2 fois => fatal error
*  ++/-- sur autre chose qu'un int/float ou un const => fatal error
*  ++/-- on unintialized var =>   fatal error
*  scope check for var (use a var declared in a if outside is not tolerated)=> fatal error



