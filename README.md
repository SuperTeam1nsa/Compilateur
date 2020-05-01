# Projet système informatique 
Ce projet a pour but de développer un compilateur capable de transcompiler efficacement du C vers l'assembleur.Il a aussi pour objectif de développer  un interpreteur de l'assembleur, et d'utiliser VHDL pour concevoir et programmer une carte FPGA.  
Les fichiers en C pour tester le compilateur sont disponibles dans `Compilateur/codeC/`.
## Exécution :  
### 1. Du compilateur
#### 1. Windows
Installez flex et bison sur votre système, accessibles dans le PATH.
Déplacez vous dans le dossier compilateur depuis powershell : `cd Compilateur/`
* **Mode couleur** : (utilisez le mode sans couleur si pas d'affichage) 
	`./run.bat codeC/le_fichier_c_voulu.c [Mode_optimise] | Out-Host `  
	avec:` Mode_optimise : 0 ou 1`  
	**exemple**:  
	`./run.bat codeC/full.c 1 | Out-Host `
  
* **sans couleur**: Utiliser cmd au lieu de powershell et sans `| Out-Host` 	 	
* 	**Sortie**: Les informations comprises et interprétées par Lex et par Yacc s'affichent dans la console, l'ASM généré est situé dans `interpreter/output.asm`  

**Pour en savoir plus sur les couleur** : [stackoverflow ](https://stackoverflow.com/questions/51680709/colored-text-output-in-powershell-console-using-ansi-vt100-codes#51681675)  
  
#### 2. Linux :  
Installez lex et yacc sur votre système, accessibles dans le PATH.
Mêmes commandes mais avec run.sh au lieu de run.bat et sans `| Out-Host` (les couleurs sont gérées nativement sur la plupart des distributions).
### 2. De l'interpréteur ASM 
#### 1. Windows
Installez flex et bison sur votre système, accessibles dans le PATH.
Déplacez vous dans le dossier interpreter depuis powershell : `cd Compilateur/interpreter`
	`./run.bat`  
* 	**Sortie**: l'exécution des commandes s'affiche dans la console
  
#### 2. Linux :  
Installez lex et yacc sur votre système, accessibles dans le PATH.
Mêmes commandes mais avec run.sh au lieu de run.bat

### 3. Du compilateur et de l'interpréteur:
Déplacez vous dans le dossier compilateur depuis powershell :  `cd Compilateur/`  

Utilisez `./runfull.bat codeC/le_fichier_c_voulu.c [Mode_optimise] | Out-Host `  
ou `./runfull.sh codeC/le_fichier_c_voulu.c [Mode_optimise]` selon votre OS.

## Fonctionnalités supportées  :  
*  nombre sous forme d'exposant (**ex**: 10e1)
*  declaration en ligne des variables sans affectation(**ex**: int a, b;)
*  declaration de varibales de type char, int ou float avec ou sans affectation
*  declaration de variables constantes
*  reaffectation de valeur à une variable déjà déclarée
*  gestion des espaces, tab, retour à la ligne
*  gestion de printf(var) qui affiche le nom de la variable et sa valeur
*  gestion des opérations arithmétiques standards( +-/*) et des priorités entre elles ainsi que des parenthèses
*  gestion des return
*  gestion des operateurs rapides (non imbriques) (++/--)
*  supporte les comparaisons (<,>,>=,<=,!,!=,==) en renvoyant un entier 0 ou 1 (vrai) conformément au sujet (pas de check de type => use parenthesis for negative value)
*  **gestion des if-else, if et imbrication** (max imbrication = MAX_INSIDE_IF)
*  **gestion de la boucle do while** (max imbrication = MAX_INSIDE_LOOP)
*  **interpreteur statique du C à la volée pour générer de l'ASM optimisé**, optimise  l'affectation des variables et les calculs statiques. Ainsi que les if . Résultat: **jusqu'à 4 fois moins d'instructions ASM** (sur l'exemple full.c)
**Remarque:** les boucles ne sont pas optimisées et les vérifications d'erreurs C sont moins nombreuses dans ce mode

## Tests d'erreurs réalisés:  
*  Réaffectation d'une variable => Erreur fatale
*  char de plus de un character (va etre tronqué) => warning
*  return d'une variable non-initialisé => warning
*  return sur une void function => Erreur fatale
*  Pas de return avec une fonction non-void => warning
*  declaration du même nom de variable 2 fois => fatal error
*  ++/-- sur autre chose qu'un int/float ou un const => fatal error
*  ++/-- sur une variable non-intialisée =>   fatal error
*  Vérification de la portée des variables (**par exemple:** utiliser une variable déclaré dans un if en-dehors du if n'est pas toléré )=> fatal error