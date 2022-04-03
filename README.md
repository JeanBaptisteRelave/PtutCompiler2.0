# PtutCompiler2.0
2.0 Version - Compiler IUT Aix-Marseille University

<img src="https://upload.wikimedia.org/wikipedia/fr/thumb/8/83/Univ_Aix-Marseille_-_IUT.svg/1200px-Univ_Aix-Marseille_-_IUT.svg.png" width="300" height="105" /> <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/1/18/ISO_C++_Logo.svg/1822px-ISO_C++_Logo.svg.png" width="50" height="55" />

<img src="https://i.ibb.co/41LQ3bT/Marcla-Parse-1.png" width="300" height="65" /> <img src="https://i.ibb.co/JjD7gCh/CasaLex.png" width="300" height="65" />

# Summary :
- [Technical documentation](#technical-documentation)
	- [Function main()](#main)
	- [Classes definition](#classes-definition)
		- [LEXER](#lexer-class)
		- [PARSER](#parser-class)
	- [WJC Files](#wjc-files)
		- [Lexer.wjc](#lexer.wjc)
		- [Parser.wjc](#parser.wjc)
	- [Errors](#errors)
- [Lexer Test](#lexer-test)

# Technical documentation
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

*First, it read the source file and write it as a string.
Then a LEXER class object is created with the source as a parameter.
It next uses the "setFilePath" function which defines the way to reach the lexer file.
After that, a PARSER class object is created with a pointer to the LEXER class object previously created as a paramater.
And then it uses the "setFilePath" function which defines the way to reach the parser file.
Finally, it uses the PARSER class "start_analyse" method which launch the syntax analysis*

<hr/>

## Classes definition

### LEXER class

#### *Description :*

> This class realise the whole lexical analysis and is used by the PARSER class which needs the tokens generated.

#### *Methods:*
``` c++
LEXER(const string &source)
```

> This constructor take a string type source that we have to analyse as a parameter. 
> This parameter is mandatory to initialyse a LEXER class object

<br/>

``` c++
void setFilePath(const string &path)
```

> This procedure is mandatory for our class to initialise a grammary. 
> It takes the path to the lexer file as a parameter

<br/>

``` c++
void  test_analyse()
```
> This method can be used to test the lexer by strings written into a terminal

<br/>

``` c++
bool set_lex_list()
```

> This method uses the lexer definition file to associate the lexemes with their definition and then, put the association into a two-dimensionnal string array.
> It returns false if there is a mistake or true if everything is right.

<br/>

``` c++
token get_next_lex(unsigned &source_position)
```

> This method returns a token which is a two-dimensionnal string array with three strings : The first is the lexeme id, the second is his value, the third identifies if it's a keyword (when the parameter is 0) or a separator (when the parameter is 1).
> The source_position parameter informs us on the position where the source reading stopped at this point.
> The Parser will call this method to get the next token to analyse

**Technical:**
*The method avoid the comments by identifing them (// and /* */). It get every tokens that are between two separators (a space or a carriage return). If the lexeme is found on the grammary, it will return the related token, else, it returns a token related to the token type (Number, string). It calls the "set_tk()" method that generate a token*

<br/>

``` c++
bool is_separator(string car, token &tk)
```

> This method returns true if the character is a separator or false if it is not.
> The parameter car is the character that will be tested. The second parameter tk is a token pointer to the token processed in the "get_next_lex()" method so we can directly modify it.  

<br/>

``` c++
void set_tk(string lex, token &tk)
```

> This method used in the "get_next_lex()" method generate the token (the 3 string array).
> The first parameter "lex" is the lexeme to process. The "tk" parameter is used by the "get_next_lex()" method to add or modify the lexeme's information.

**Technical:**
*First, the, the lexem is compared to the lexicon and if there is a match, the token is modified, else, it will verify the token type (number or string) to create a token with a value and a type.*

<br/><br/>
#### *Attributes :*
``` c++
std::string m_source;
``` 
> The source code we want to analyse.

<br/>

``` c++
unsigned m_source_size;
``` 
> The source code size (numbers of characters).

<br/>

``` c++
std::vector<token> m_lex_list;
``` 
> Lexicon.

<br/>

``` c++
std::string m_lexer_location_file;
``` 
> Path to the lexicon ("lexer.wjc").

<br/><br/>
#### *Token :*

> Identifiants :

```
Integer                 : LEXV_NUMBER
Float                   : LEXV_FLOAT
String                  : LEXV_ID
Unknown or false lexeme : LEXV_ERROR
``` 
<br/><br/>
### PARSER class 

#### *Description :*

> Cette classe fait une analyse syntaxique du code source analysé par le LEXER, elle est donc connecté avec cette deuxième classe.

#### *Methods:*
``` c++
PARSER(LEXER* lex)
```

> The constructor take a pointer to a LEXER class object as a parameter to get its tokens
<br/>

``` c++
bool start_analyse() const
```

> This method get every token generated par LEXER and analyse their syntax. It returns true if everything is right and false if there is a mistake.
<br/>

``` c++
void setFilePath(const string &path)
```

> This method defines the path to the syntax definition file "parser.wjc" which will permit the generation of the syntactic tree.
<br/>

<br/><br/>
#### *Attributes :*
``` c++
LEXER* m_lex;
``` 
> This attribute is a pointer to the LEXER class object that we want to syntactically analyse.
<br/>

``` c++
parser_tree* m_ptree;
``` 
> This attribute is a pointer to a parser_tree class object that permit the creation of a syntactic tree
<br/>

``` c++
std::string m_parser_location_file;
``` 
> This defines the path to the syntax definition file ("parser.wjc").
<br/>

``` c++
bool m_valid_tree;
``` 
> This attribute informs if the tree is valid to launch an analysis.
<br/>

<br/><br/>
## WJC Files

### Lexer.wjc

    % keywords:
    
    if IF_CONDITION
    ELSE ELSE_CONDITION
    end FIN_PROG
    
    % separators:
    
    ; PV
    , VRGL

> There's an example for this file.
> 
> "% keywords :" - From there, we define the protected lexemes that are used in the grammary.
> 
> "% separators:" - From there, we define the separators lexemes that are used in the grammary.

	if IF_CONDITION
> First, we have to write the lexeme as how it have to be found in the source, and then you have to precise the lexeme identifier which will be used in the syntactic analysis.


### Parser.wjc

	S : ALGO LEXV_ID CORPS;
	
	CORPS : DEBUT PROG FIN;
	
	PROG : DECLARATION | AFFECTATION | DECLARATION_SOUS_PROGRAMME | APPEL
		   | STRUCTURE_DE_CONTROLE | BREAK | PROG PROG;
> There's an example for this file.
> Here, we define our syntax, so it is this file that will be used to generate the syntactic tree. It is crucial to organize it well to avoid any PARSER errors.

	S : ALGO LEXV_ID CORPS;

> Here, we define the axiom, it is mandatory because it is simply the root of syntactic tree. Without this, it is just impossible for the PARSER to generate the tree.

	CORPS : DEBUT PROG FIN;
> "CORPS :" - Here, we define a node in our syntactic tree and his definition (the syntax to respect) which includes other nodes or token identifiers

<br/><br/>
## Errors
### Parser :

    Erreur : The axiom must be 'S'
> In the syntax definition file ("parser.wjc") the first definition must be the axiome definition (with a capital S), if it is not the case, the syntactic tree cannot be built and an error is thrown
> Solution : You have to start your syntax definition with the axiom (S : ...).

    [parser.wjc] - File not found
 > The parser cannot find the file "parser.wjc".
 > Solution : Make sure that you have used the good file path as parameter for the PARSER class method "setFilePath"

    [parser.wjc]  -  File  location  not  specified.  Please  use  PARSER::setFilePath()
 > The PARSER file path as not been defined
 > Solution : After the creation of a PARSER object you have to use the "setFilePath()" method and write the defintion file path as the parameter.

    The  syntax  tree  is  not  correct.
> This error is thrown when you try to launch the analysis with a incorrect syntactic tree
> Solution : Make sure that you don't have a mistake with the PARSER::setFilePath() method which generate the syntactic tree or in the syntactic definition file.

### Lexer :

    [lexer.wjc] - File location not specified. Please use LEXER::setFilePath()
 > The lexer cannot find the file "lexer.wjc".
 > Solution : Make sure that you have used the good file path as parameter for the LEXER class method "setFilePath"

    [lexer.wjc] - File not found
 > The LEXER file path as not been defined
 > Solution : After the creation of a LEXER object you have to use the "setFilePath()" method and write the definition file path as the parameter.

    Too many dots in this lexeme
> The LEXER informs you that a lexeme contains too many dots (for example : "58.23.65").
> Solution : Correct your source code.

    Source is empty.
> This error occurs when the source code given to the LEXER is empty.
> Solution : Make sure that the code source as a string affected to the LEXER contains something.

<br/><br/><br/>
# Lexer Test

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
