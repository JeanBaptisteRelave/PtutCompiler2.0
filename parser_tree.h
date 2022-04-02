#ifndef PARSER_TREE_H
#define PARSER_TREE_H

#include <iostream>
#include <vector>
#include "lexer.h"

using namespace std;

typedef vector<string> token;

class parser_tree
{
public:
    parser_tree();
    void add_token(string idd);
    void add_token_child(string token_id, string child_token_id, unsigned vect_pos);
    bool check_tree(LEXER *lexer) const;

    vector<vector<token>> m_token_list;

    int chearch_token(string token_id) const;
    bool isToken(string id, LEXER *lexer) const;
};

#endif // PARSER_TREE_H
