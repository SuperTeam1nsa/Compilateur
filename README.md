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

Erreur tests réalisés:  
*  const reaffectation => Fatal error
*  char +1 character => warning
*  declaration du même nom de variable 2 fois => fatal error

TODO errors :
*  non initialise: test en gérant var++
*  coherence des types dans l'affectation => warning quand int prend la valeur d'un float

TODO features :
*  int a, b; a = b = 10; 
*  int a, b = 10, c = 20;
*  gestion des return (cf sujet voir ce qu'il faut implémenter )
