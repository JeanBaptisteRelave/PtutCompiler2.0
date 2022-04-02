#include "parser.h"
#include "parser_tree.h"
#include <iostream>
#include <vector>
#include <fstream>

PARSER::PARSER(LEXER* lex): m_lex(lex), m_valid_tree(false){
    m_ptree = new parser_tree();
}

PARSER::~PARSER(){
    m_ptree = NULL;
    delete m_ptree;
}

/*
    parse_display_error();
    Display an error.
    Parameters :
        Err  : Error message.
        Line : Error line.
        Pos  : Error caractère position.
        Car  : Error caractère (or string).
*/
void parser_display_error(const string &err, unsigned line = 0, unsigned pos = 0, string car = ""){
    if(car.length() <= 0)
        cout << "PARSER:ERR : " << err << endl;
    else
        cout << "PARSER:ERR [l" << line << ":" << pos << ":" << car << "] : " << err << endl;
}

bool PARSER::start_analyse() const{
    if(m_parser_location_file.length() <= 0){
        parser_display_error("[parser.wjc] - File location not specified. Please use PARSER::setFilePath()");
        return false;
    }

    if(!m_valid_tree){
        parser_display_error("The syntax tree is not correct.");
        return false;
    }

    if(!m_lex->start_analyse())
        return false;

    unsigned source_position(0);
    while(source_position < m_lex->get_source_size()){
        token tk(m_lex->get_next_lex(source_position));



    }

    return true;
}

void PARSER::setFilePath(const string &path){
    m_parser_location_file = path;

    ifstream if_flux(m_parser_location_file);

    if(if_flux)
    {
        string line;
        string actual_token_id;
        string lex;
        unsigned vect_pos(1);
        bool root(true);
        bool instance(true);

        while(getline(if_flux, line))
        {
            for(unsigned i(0); i < line.length(); ++i){
                //Before ':' is instance, after is not.
                if(line[i] == '|')
                    ++vect_pos;

                if(line[i] == ' ' || line[i] == '\n' || line[i] == ';' || line[i] == ':'|| line[i] == '|'){
                    if(lex.length() <= 0)
                        continue;
                    else{
                        //If is root and is not 'S' :
                        if(root && lex != "S"){
                            parser_display_error("The axiom must be 'S'", 0, 1, lex);
                            return;
                        }else if(root && lex == "S"){
                            m_ptree->add_token("S");
                            actual_token_id = "S";
                            root = false;
                        }

                        if(instance){
                            m_ptree->add_token(lex);
                            actual_token_id = lex;
                        }else{
                            m_ptree->add_token_child(actual_token_id, lex, vect_pos);
                        }

                        if(line[i] == ':')
                            instance = !instance;

                        if(line[i] == ';'){
                            vect_pos = 1;
                            instance = true;
                        }

                        lex = "";
                        continue;
                    }
                }

                lex += line[i];
            }
        }

        if(!m_ptree->check_tree(m_lex))
            m_valid_tree = false;
        else
            m_valid_tree = true;

    }else{
        parser_display_error("[parser.wjc] - File not found");
        m_valid_tree = false;
    }
}















