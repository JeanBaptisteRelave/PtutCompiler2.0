# PtutCompiler2.0
2.0 Version - Compiler IUT Aix-Marseille University

<img src="https://upload.wikimedia.org/wikipedia/fr/thumb/8/83/Univ_Aix-Marseille_-_IUT.svg/1200px-Univ_Aix-Marseille_-_IUT.svg.png" width="300" height="105" /> <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/1/18/ISO_C++_Logo.svg/1822px-ISO_C++_Logo.svg.png" width="50" height="55" />

<img src="https://i.ibb.co/41LQ3bT/Marcla-Parse-1.png" width="100" height="100" /> <img src="https://i.ibb.co/JjD7gCh/CasaLex.png" width="100" height="100" />

# Sommaire :
- [Documentation technique](#documentation-technique)
	- [Fonction main()](#main)
	- [Définition des classes](#définition-des-classes)
		- [LEXER](#class-lexer)
		- [PARSER](#class-parser)
	- [Fichiers WJC](#fichiers-wjc)
		- [Lexer.wjc](#lexer.wjc)
		- [Parser.wjc](#parser.wjc)
	- [Les erreurs](#les-erreurs)
- [Test Lexer](#test-lexer)

# Documentation technique
## Main

``` c++
#include <iostream>
#include <fstream>
#include "lexer.h"
#include "parser.h"

using namespace std;

int main(int argc, char const *argv[])
{
    ifstream if_flux("/main.pdut");
    string source;

    string line;
    while(getline(if_flux, line))
        source += line + "\n";

    LEXER lex(source);
    lex.setFilePath("/lexer.wjc");
    
    PARSER synt(&lex);
    synt.setFilePath("/parser.wjc");
    
    synt.start_analyse();
    return 0;
}
```

*Premièrement on lit le fichier source afin de le stocker dans une chaine de caractère.
Ensuite on creer un objet de la classe LEXER et en paramètre on lui passe la source.
Ensuite on utilise la fonction "setFilePath" pour définir à notre objet la destination (chemin) du 
fichier "lexer.wjc"
Par la suite on creer un objet de la classe PARSER en lui passant en paramètre un pointer vers notre objet LEXER.
On utilise la méthode "setFilePath" en lui passant en paramètre le chemin vers le fichier "parser.wjc".
En lance ensuite l'analyse avec la méthode "start_analyse" de notre class PARSER.*

<hr/>

## Définition des classes

### Class LEXER

#### *Description :*

> Cette classe effectue l'intégralité de l'analyse léxical et est utilisé par la classe PARSER afin de lui communiqué des tokens.

#### *Méthodes:*
``` c++
LEXER(const string &source)
```

> Le constructeur prend en paramètre une source de type string, il
> s'agit simplement du code source que l'on doit analyser, ce paramètre
> est obligatoire pour initialiser un objet de type LEXER.

<br/>

``` c++
void setFilePath(const string &path)
```

> Cette procédure est essentiel pour que notre class initialise une
> grammaire, elle prend en paramètre une chaine de caractère qui est le
> chemin vers le fichier "lexer.wjc" qui sera expliquer plus loins.

<br/>

``` c++
void  test_analyse()
```
> Cette méthode permet de tester le lexer en entrant des chaines de caractère dans le terminal.

<br/>

``` c++
bool set_lex_list()
```

> Cette méthode va lire le fichier "lexer.wjc" afin de récuperer et
> stocker les lexèmes de notre grammaire dans un vecteur de vecteur de
> chaine de caractère. Il stock le lexème et son identifiant. Retourne
> False si il y a une erreur sinon True.

<br/>

``` c++
token get_next_lex(unsigned &source_position)
```

> Cette méthode retourne un token qui est un vecteur de chaine de caractère avec trois chaines, la première est l'identifiant du lexème, le deuxième est sa valeur (optionnel) et pour la troisième si la valeur est "0" alors c'est un simple lexème si la valeur est "1" alors c'est un séparateur ex: ;, (, [.
> Le paramètre est un entier naturel qui est la position de lecture sur notre source,
> c'est à dire le caractère sur lequel on s'est arreté. Le Parser va appellé cette méthode pour récupérer le prochain token de notre analyse. 

**Technique:**
*Cette méthode prend en compte les commentaire afin de les éviter (// et /* */). Elle va simplement récuperer tous les lexèmes qui se séparents entre un séparateur, un espace ou un retour à la ligne, si le lexème trouvé est dans notre grammaire elle va retourner un token correspondant à ce lexème sinon elle retourne un token correspondant au type trouvé (Nombre, chaine de caractère). Elle fait appelle à la méthode set_tk() afin de générer un token.*

<br/>

``` c++
bool is_separator(string car, token &tk)
```

> Cette méthode retourne True si le caractère est un séparateur dans notre grammaire sinon False.
> Le premier paramètre "car" est notre caractère en type string afin de simplifier le traitement, le deuxième paramètre est un pointer vers le token utilisé dans la méthode get_next_lex() afin de pouvoir le modifier directement et l'assigner au lexème séparateur.

<br/>

``` c++
void set_tk(string lex, token &tk)
```

> Cette méthode utilisé par la méthode get_next_lex() nous sert à generer un token qui est un vecteur de 3 chaines de caractères.
> Le premier paramètre "lex" est le lexème à traiter et le deuxième "tk" est le token utilisé par  		la fonction get_next_lex() afin de le modifier pour y ajouter les informations du lexème.

**Technique:**
*Premièrement la méthode boucle dans dans le vecteur "m_lex_list" afin de comparer le lexème actuel avec les lexèmes de notre grammaire, si elle trouve une correspondance alors le token est modifier sinon elle va vérifier le type de ce lexème (Nombre, chaine de caractère) afin de faire un token avec une valeur et un type.*

<br/><br/>
#### *Attributs :*
``` c++
std::string m_source;
``` 
> Correspond au code source que nous devons analyser.

<br/>

``` c++
unsigned m_source_size;
``` 
> Est la taille de notre code source (nombre de caractère).

<br/>

``` c++
std::vector<token> m_lex_list;
``` 
> Est la liste des lexèmes de notre grammaire.

<br/>

``` c++
std::string m_lexer_location_file;
``` 
> Est le chemin vers le fichier "lexer.wjc".

<br/><br/>
#### *Token :*

> Identifiants :

```
Nombre entier               : LEXV_NUMBER
Nombre flotant              : LEXV_FLOAT
Chaine de caractère         : LEXV_ID
Lexème inconnu ou éroné     : LEXV_ERROR
``` 
<br/><br/>
### Class PARSER

#### *Description :*

> Cette classe fait une analyse syntaxique du code source analysé par le LEXER, elle est donc connecté avec cette deuxième classe.

#### *Méthodes:*
``` c++
PARSER(LEXER* lex)
```

> Le constructeur prend en paramètre un pointer vers un objet de la classe LEXER afin de pouvoir communiqué avec lui pour récupérer les tokens.
<br/>

``` c++
bool start_analyse() const
```

> Cette méthode lance récupère un à un les token généraient par le LEXER et effectue une analyse, elle envoie True si tout ce passe bien sinon False.
<br/>

``` c++
void setFilePath(const string &path)
```

> Cette méthode permet de définir le fichier "parser.wjc" qui va permettre au parser de générer un arbre syntaxique.
<br/>

<br/><br/>
#### *Attributs :*
``` c++
LEXER* m_lex;
``` 
> Cet attribut est un pointer vers un objet de la classe LEXER qui permet a notre parser de communiquer avec.
<br/>

``` c++
parser_tree* m_ptree;
``` 
> Voici un pointer vers un objet de la classe parser_tree qui permet la création d'un arbre syntaxique.
<br/>

``` c++
std::string m_parser_location_file;
``` 
> Cet attribut contient le chemin vers le fichier "parser.wjc".
<br/>

``` c++
bool m_valid_tree;
``` 
> Cet attribut permet au parser de savoir si l'arbre syntaxique est correcte afin de pouvoir lancer une analyse.
<br/>

<br/><br/>
## Fichiers WJC

### Lexer.wjc

    % keywords:
    
    if IF_CONDITION
    ELSE ELSE_CONDITION
    end FIN_PROG
    
    % separators:
    
    ; PV
    , VRGL

> Voici un exemple pour ce fichier.
> 
> "% keywords :" - A partir d'ici on précise que les prochaines lignes définissent des lexèmes protégés donc utilisés dans notre grammaire.
> 
> "% separators:" - A partir d'ici on précise que les prochaines lignes définissent des lexèmes séparateurs utilisés dans notre grammaire.

	if IF_CONDITION
> En premier on écrit le lexème tel qui doit être trouvé dans notre source, séparé d'un espace on précise l'identifiant de ce lexème, qui sera utilisé pour l'analyse syntaxique.


### Parser.wjc

	S : ALGO LEXV_ID CORPS;
	
	CORPS : DEBUT PROG FIN;
	
	PROG : DECLARATION | AFFECTATION | DECLARATION_SOUS_PROGRAMME | APPEL
		   | STRUCTURE_DE_CONTROLE | BREAK | PROG PROG;
> Voici un exemple (non complet) pour ce fichier.
> Ici nous définissons la syntaxe de notre langage, la class PARSER va par la suite générer un arbre syntaxique en référence à ce fichier, il est donc essentiel de bien l'organiser pour éviter les erreurs du parser.

	S : ALGO LEXV_ID CORPS;

> Ici on définit notre axiome "S", il est obligatoire dans ce fichier car c'est la racine de l'arbre syntaxique, sans ça le parser ne pourras pas créer d'arbre.

	CORPS : DEBUT PROG FIN;
> "CORPS :" - Ici nous définissons un nœud de notre arbre syntaxique et après les deux points nous définissons sa forme, avec d'autres nœuds ou des identifiants de token.

<br/><br/>
## Les Erreurs
### Parser :

    Erreur : The axiom must be 'S'
> Dans votre fichier "parser.wjc" la première définition doit être la racine de l'arbre syntaxique qu'on appel l'axiome, et doit être un S majuscule, si ce n'est pas le cas, l'arbre de ne pas être construit donc le parser vous renvoie une erreur.
> Solution : commencez votre définition de syntaxe par (S : ...).

    [parser.wjc] - File not found
 > Le parser ne trouve pas le fichier "parser.wjc".
 > Solution : Assurez vous lors de l'utilisation de la méthode "setFilePath" sur votre objet de type parser d'avoir passé en paramètre le bon chemin vers ce fichier.

    [parser.wjc]  -  File  location  not  specified.  Please  use  PARSER::setFilePath()
 > Ici on vous dit que le chemin vers le fichier "parser.wjc" n'a pas été définis.
 > Solution : Après avoir créer un objet de la class PARSER, utilisez la méthode "setFilePath()" et passez lui en paramètre le chemin vers ce fichier.

    The  syntax  tree  is  not  correct.
> Cette erreur arrive lorsque vous essayez de lancer l'analyse syntaxique alors que l'arbre syntaxique n'est pas correctement construit.
> Solution : Assurez vous de ne pas avoir d'erreur lors de l'utilisation de la méthode PARSER::setFilePath() qui génère l'arbre syntaxique.

### Lexer :

    [lexer.wjc] - File location not specified. Please use LEXER::setFilePath()
 > Ici on vous dit que le chemin vers le fichier "lexer.wjc" n'a pas été définis.
 > Solution : Après avoir créer un objet de la class LEXER, utilisez la méthode "setFilePath()" et passez lui en paramètre le chemin vers ce fichier.

    [lexer.wjc] - File not found
 > Le lexer ne trouve pas le fichier "lexer.wjc".
 > Solution : Assurez vous lors de l'utilisation de la méthode "setFilePath" sur votre objet de type lexer d'avoir passé en paramètre le bon chemin vers ce fichier.

    Lexeme with too many dots
> Ici le lexer vous dit qu'il a trouvé un lexème contenant trop de points exemple : "58.23.65".
> Solution : Corrigez votre code source.

    Source is empty.
> Cette erreur parvient lorsque le code source donné au lexer est vide.
> Solution : Lorsque vous passez un code source à votre lexer, assurez vous que la chaine de caractère n'est pas vide.

<br/><br/><br/>
# Test Lexer

> Fichier main.cpp :
``` c++
#include <iostream>
#include "lexer.h"

using namespace std;

int main(int argc, char const *argv[])
{
	string source(" ");
	LEXER lex(source);
	lex.setFilePath("chemin/lexer.wjc");
	
	lex.test_analyse();
	return 0;
}
```

> Terminal :

    LEXER - TEST ANALYSE ('quit' to exit)
    
     > test
	    Token : LEXV_ID
    
     > declarer
	    Token :  DEC
    
     > 45
	    Token : LEXV_NUMBER
    
     > 2.67
	    Token : LEXV_FLOAT
    
     > 52.12.65
	 LEXER:ERR [l0:0:52.12.65] : Lexeme with too many dots
	    Token : LEXV_ERROR
