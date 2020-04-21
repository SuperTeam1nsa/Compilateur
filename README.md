# Compilateur
On windows :  
in powershell (with color (desactivate it if no output)  
.\run.bat | Out-Host  
or in cmd (without color or follow : https://stackoverflow.com/questions/51680709/colored-text-output-in-powershell-console-using-ansi-vt100-codes#51681675 to activate color broadlly)  
run.bat  
  
on linux :  
make makefilebis  
   
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



