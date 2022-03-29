#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

class PARSER
{
public:
    PARSER(LEXER* lex);


private:
    LEXER* m_lex;
};

#endif // PARSER_H
