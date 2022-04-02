#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "parser_tree.h"

#include <iostream>
#include <vector>

class PARSER
{
public:
    PARSER(LEXER* lex);
    ~PARSER();
    bool start_analyse() const;
    void setFilePath(const string &path);

private:
    LEXER* m_lex;
    parser_tree* m_ptree;
    string m_parser_location_file;
    bool m_valid_tree;
};

#endif // PARSER_H
