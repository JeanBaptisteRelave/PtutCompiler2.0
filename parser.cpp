#include "parser.h"
#include <iostream>
#include <vector>
#include <fstream>

PARSER::PARSER(LEXER* lex): m_lex(lex){}

/*
    parse_display_error();
    Display an error.
    Parameters :
        Err  : Error message.
        Line : Error line.
        Pos  : Error caract√®re position.
        Car  : Error caract√®re (or string).
*/
void parse_display_error(const string &err, unsigned line = 0, unsigned pos = 0, string car = ""){
    if(car.length() <= 0)
        cout << "PARSER:ERR : " << err << endl;
    else
        cout << "PARSER:ERR [l" << line << ":" << pos << ":" << car << "] : " << err << endl;
}

bool PARSER::start_analyse(){

    return true;
}

void PARSER::setFilePath(const string &path){
    m_parser_location_file = path;

    ifstream if_flux(m_parser_location_file);

    if(if_flux)
    {
        string line;

        while(getline(if_flux, line))
        {
            // GÈnÈrer arbre syntaxique !!
        }
    }else{
        parse_display_error("[parser.wjc] - File not found");
    }
}
