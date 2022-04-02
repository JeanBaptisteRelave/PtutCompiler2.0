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
    void setFilePath(const string &path);
    void test_analyse();
    bool is_token(string id) const;
    bool start_analyse() const;
    token get_next_lex(unsigned &source_position) const;
    unsigned get_source_size() const;

private:
    string m_source;
    unsigned m_source_size;
    vector<token> m_lex_list;
    string m_lexer_location_file;

    bool set_lex_list();
    bool is_separator(string car, token &tk) const;
    void set_tk(string lex, token &tk) const;
};

#endif // LEXER_H
