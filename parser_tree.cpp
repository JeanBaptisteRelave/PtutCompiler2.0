#include "parser_tree.h"

parser_tree::parser_tree(){}

void parser_tree::add_token(string idd){
    vector<token> tk;
    token tk2;

    tk2.push_back(idd);
    tk.push_back(tk2);

    m_token_list.push_back(tk);
}

int parser_tree::chearch_token(string token_id) const{
    int id(0);

    for(id; id + 1 < m_token_list.size() && token_id != m_token_list[id][0][0]; ++id);

    if(token_id != m_token_list[id][0][0])
        return -1;

    return id;
}

void parser_tree::add_token_child(string token_id, string child_token_id, unsigned vect_pos){
    unsigned tk_id(chearch_token(token_id));

    if(m_token_list[tk_id].size() - 1 < vect_pos){
        token tk;
        tk.push_back(child_token_id);
        m_token_list[tk_id].push_back(tk);
    }else
        m_token_list[tk_id][vect_pos].push_back(child_token_id);
}

bool parser_tree::isToken(string id, LEXER *lexer) const{
    if(id == "LEXV_NUMBER") return true;
    if(id == "LEXV_FLOAT") return true;
    if(id == "LEXV_ID") return true;
    if(id == "LEXV_ERROR") return true;

    if(chearch_token(id) == -1 && !lexer->is_token(id)) return false;
    return true;
}

bool parser_tree::check_tree(LEXER *lexer) const{
    for(unsigned i(0); i < m_token_list.size(); ++i){
        for(unsigned j(1); j < m_token_list[i].size(); ++j){
            for(unsigned h(0); h < m_token_list[i][j].size(); ++h){
                if(!isToken(m_token_list[i][j][h], lexer)){
                    cout << "PARSER::ERROR : Token not defined [" << m_token_list[i][j][h] << "]" << endl;
                    return false;
                }
            }
        }
    }

    return true;
}
