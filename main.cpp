#include <iostream>
#include <fstream>
#include "lexer.h"
#include "parser.h"

using namespace std;

int main()
{
    ifstream if_stream("C:/Users/jeanb/Documents/DUT2/PTUT/main.pdut");
    string source;

    string line;
    while(getline(if_stream, line))
        source += line + "\n";

    LEXER lex(source);
    lex.setFilePath("C:/Users/jeanb/Documents/DUT2/PTUT/compiler/lexer.wjc");

    PARSER synt(lex *);
    synt.setFilePath("C:/Users/jeanb/Documents/DUT2/PTUT/compiler/parser.wjc");

    synt.start_analyse();

    return 0;
}
