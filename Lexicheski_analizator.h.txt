#pragma once

#include "Token.h"
#include "Hash_Table.h"
#include <fstream>

class Lexer
{
private:
    std::ifstream input_file;
    std::ofstream error_file;

    bool check_id(const std::string& lexeme) const;

    bool ARITHM_OP(char& elem) const;
    bool RELATION_OP(const std::string& elem) const;
    bool RELATION_OP(const char& elem) const;
    bool DELIMITER(const char elem) const;

    Token keyword(const std::string& lex);
    Token check_char_el(char elem);
    Token check_ID_el(char elem);
    Token check_num_el(char elem);
    Token check_unknown(char elem);

public:
    Lexer(const std::string& input)
    {
        input_file.open(input);
    }

    void analyze();
    HashTable hashTable;
    Token get_next_token();
};
