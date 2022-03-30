#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

#include <iostream>
#include <vector>

class PARSER
{
public:
    PARSER(LEXER* lex);
    bool start_analyse();
    void setFilePath(const string &path);

private:
    LEXER* m_lex;
    string m_parser_location_file;
};

#endif // PARSER_H
