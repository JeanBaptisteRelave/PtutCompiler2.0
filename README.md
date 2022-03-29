# PtutCompiler2.0
2.0 Version - Compiler IUT Aix-Marseille University

# Documentation technique
## Main

*La fonction principale de ce programme est simplifier afin de pouvoir être modifier facilement par
n'importe qui.*

``` c++
LEXER lex(source);
lex.setFilePath("C:/Users/jeanb/Documents/DUT2/PTUT/compiler/lexer.wjc");
              
// lex.start_analyse();
```

*Premièrement on lit le fichier source afin de le stocker dans une chaine de caractère.
Ensuite on creer un objet de la class LEXER et en paramètre on lui passe la source.
Ensuite on utilise la fonction "setFilePath" pour définir à notre objet la destination (chemin) du 
fichier "lexer.wjc"
On pourrait par la suite utiliser la fonction "start_analyse()" afin de vérifier si l'analyse lexicale
se passe bien.*

<hr/>

## Définition des classes

### { Class LEXER }

#### *Description :*

> Cette classe effectue l'intégralité de l'analyse léxical et est utilisé par la classe PARSER afin de lui communiqué des tokens.

#### *Fonctions :*
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
bool start_analyse()
```

> Cette fonction permet de lancer l'analyse lexicale, elle peux être
> utilisé directement sur notre objet mais elle sera surtout utilisé par
> un objet de type PARSER.
> Elle retourne True si tout se passe bien sinon False.

<br/>

``` c++
bool set_lex_list()
```

> Cette fonction va lire le fichier "lexer.wjc" afin de récuperer et
> stocker les lexèmes de notre grammaire dans un vecteur de vecteur de
> chaine de caractère. Il stock le lexème et son identifiant. Retourne
> False si il y a une erreur sinon True.

<br/>

``` c++
token get_next_lex(unsigned &source_position)
```

> Cette fonction retourne un token qui est un vecteur de chaine de caractère avec trois chaines, la première est l'identifiant du lexème, le deuxième est sa valeur (optionnel) et pour la troisième si la valeur est "0" alors c'est un simple lexème si la valeur est "1" alors c'est un séparateur ex: ;, (, [.
> Le paramètre est un entier naturel qui est la position de lecture sur notre source,
> c'est à dire le caractère sur lequel on s'est arreté. Le Parser va appellé cette fonction pour récupérer le prochain token de notre analyse. 

**Technique:**
*Cette fonction prend en compte les commentaire afin de les éviter (// et /* */). Elle va simplement récuperer tous les lexèmes qui se séparents entre un séparateur, un espace ou un retour à la ligne, si le lexème trouvé est dans notre grammaire elle va retourner un token correspondant à ce lexème sinon elle retourne un token correspondant au type trouvé (Nombre, chaine de caractère). Elle fait appelle à la fonction set_tk() afin de générer un token.*

<br/>

``` c++
bool is_separator(string car, token &tk)
```

> Cette fonction retourne True si le caractère est un séparateur dans notre grammaire sinon False.
> Le premier paramètre "car" est notre caractère en type string afin de simplifier le traitement, le deuxième paramètre est un pointer vers le token utilisé dans la fonction get_next_lex() afin de pouvoir le modifier directement et l'assigner au lexème séparateur.

<br/>

``` c++
void set_tk(string lex, token &tk)
```

> Cette fonction utilisé par la fonction get_next_lex() nous sert à generer un token qui est un vecteur de 3 chaines de caractères.
> Le premier paramètre "lex" est le lexème à traiter et le deuxième "tk" est le token utilisé par  		la fonction get_next_lex() afin de le modifier pour y ajouter les informations du lexème.

**Technique:**
*Premièrement la fonction boucle dans dans le vecteur "m_lex_list" afin de comparer le lexème actuel avec les lexèmes de notre grammaire, si elle trouve une correspondance alors le token est modifier sinon elle va vérifier le type de ce lexème (Nombre, chaine de caractère) afin de faire un token avec une valeur et un type.*

<br/><br/>
#### *Variables :*
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
Nombre              : LEXV_NUMBER
Chaine de caractère : LEXV_ID
``` 
