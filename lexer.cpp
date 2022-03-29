#include "lexer.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

LEXER::LEXER(const string &source): m_source(source), m_source_size(source.length()){}

/*
    display_error();
    Display an error.
    Parameters :
        Err  : Error message.
        Line : Error line.
        Pos  : Error caractère position.
        Car  : Error caractère (or string).
*/
void display_error(const string &err, unsigned line = 0, unsigned pos = 0, string car = ""){
    if(car.length() <= 0)
        cout << "LEXER:ERR : " << err << endl;
    else
        cout << "LEXER:ERR [l" << line << ":" << pos << ":" << car << "] : " << err << endl;
}

/*
    setFilePath();
    Set the lexer file path.
*/
void LEXER::setFilePath(const string &path){
    m_lerxer_location_file = path;
}

/*
    set_lex_list();
    get on lexeme from lexer.wjc file.
*/
bool LEXER::set_lex_list(){
    if(m_lerxer_location_file.length() <= 0)
    {
        display_error("[lexer.wjc] - File location not specified. Please use LEXER::setFilePath()");
        return 0;
    }

    ifstream if_flux(m_lerxer_location_file);

    if(if_flux)
    {
        string line;
        string stage("0");
        vector<string> vlex;

        while(getline(if_flux, line))
        {
            if(line == "% keywords:"){
                stage = "0";
                continue;
            }else if(line == "% separators:"){
                stage = "1";
                continue;
            }

            if(line.length() <= 0 || line.find(" ") > line.length())
                continue;

            string lexeme = line.substr(0, line.find(" "));
            string token = line.substr(lexeme.length(), line.length());

            vlex.push_back(lexeme);
            vlex.push_back(token);
            vlex.push_back(stage);
            m_lex_list.push_back(vlex);
            vlex.clear();
        }

        if_flux.close();
        return true;
    }
    else
    {
        display_error("[lexer.wjc] - File not found");
        if_flux.close();
        return false;
    }
}

bool LEXER::is_separator(string car, token &tk) const{
    for (unsigned i(0); i < m_lex_list.size(); ++i)
        if(m_lex_list[i][2] == "1" && m_lex_list[i][0] == car){
            tk[0] = m_lex_list[i][1];
            return true;
        }

    return false;
}

bool isNumber(const string& s)
{
    for (char const &ch : s)
        if (isdigit(ch) == 0)
            return false;
    return true;
}

void LEXER::set_tk(string lex, token &tk) const{
    // If the lexeme is an grammar lexem :
    for(unsigned i(0); i < m_lex_list.size(); ++i)
        if(m_lex_list[i][0] == lex){
            tk[0] = m_lex_list[i][1];
            return;
        }

    //Else, check the type :

    //Number :
    if(isNumber(lex)){
        tk[0] = "LEXV_NUMBER";
        tk[1] = stoi(lex);
        return;
    }

    //ID :
    tk[0] = "LEXV_ID";
    tk[1] = lex;
    return;
}

token LEXER::get_next_lex(unsigned &source_position) const{
    token tk(2);
    string actual_lex;
    string actual_car;
    bool on_com(false);
    bool on_largecom(false);

    for (source_position; source_position < m_source_size; ++source_position) {
        actual_car = m_source[source_position];

        if(on_com && actual_car == "\n"){
            on_com = false;

            if(actual_lex.length() > 0){
                ++source_position;
                return tk;
            }
        }

        if(on_largecom && actual_car == "*" && m_source[source_position + 1] == '/'){
            on_largecom = false;
            ++source_position;

            if(actual_lex.length() > 0){
                ++source_position;
                return tk;
            }

            continue;
        }

        if(!on_com && !on_largecom && actual_car == "/" && m_source[source_position + 1] == '/'){
            on_com = true;

            if(actual_lex.length() > 0){
                set_tk(actual_lex, tk);
            }
        }

        if(!on_largecom && !on_com && actual_car == "/" && m_source[source_position + 1] == '*'){
            on_largecom = true;

            if(actual_lex.length() > 0){
                set_tk(actual_lex, tk);
            }
        }

        if(on_com || on_largecom)
            continue;

        if(is_separator(actual_car, tk)){
            if(actual_lex.length() <= 0){
                ++source_position;
                return tk;
            }else{
                set_tk(actual_lex, tk);
                return tk;
            }
        }

        if(actual_car == " " || actual_car == "\n"){
            if(actual_lex.length() <= 0)
                continue;
            set_tk(actual_lex, tk);
            ++source_position;
            return tk;
        }


        actual_lex += actual_car;
    }

    if(actual_lex.length() >= 0){
        set_tk(actual_lex, tk);
        return tk;
    }

    tk[0] = "NULL";
    return tk;
}

/*
    start_analyse();
    Start the lexical analysis.
    Return true on success else false.
*/
bool LEXER::start_analyse(){
    if(m_source_size <= 0)
    {
        display_error("Source is empty.");
        return false;
    }

    if(!set_lex_list()){
        return false;
    }

    unsigned source_position(0);
    int i(0);
    while(source_position < m_source_size){
        token tk(get_next_lex(source_position));
        cout << "TK : " << tk[0] << "(" << tk[1] << ")" << endl;

        ++i;
        if(i > 30)
            break;
    }

    return true;
}

