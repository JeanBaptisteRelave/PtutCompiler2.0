#include <iostream>
#include <fstream>
#include "lexer.h"
#include "parser.h"

using namespace std;

int main(int argc, char const *argv[])
{
    ifstream if_flux("C:/Users/jeanb/Documents/DUT2/PTUT/main.pdut");
    string source;

    string line;
    while(getline(if_flux, line))
        source += line + "\n";

    LEXER lex(source);
    lex.setFilePath("C:/Users/jeanb/Documents/DUT2/PTUT/compiler/lexer.wjc");

    lex.start_analyse();

    //PARSER synt(&lex);

    return 0;
}
