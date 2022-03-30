#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <vector>

using namespace std;

typedef vector<string> token;

class LEXER
{
public:
    LEXER(const string &source);
    bool start_analyse();
    void setFilePath(const string &path);
    void test_analyse();

private:
    string m_source;
    unsigned m_source_size;
    vector<token> m_lex_list;
    string m_lexer_location_file;

    bool set_lex_list();
    token get_next_lex(unsigned &source_position) const;
    bool is_separator(string car, token &tk) const;
    void set_tk(string lex, token &tk) const;
};

#endif // LEXER_H
