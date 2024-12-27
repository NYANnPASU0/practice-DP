#pragma once

#include "Token.h"
#include <iostream>
#include <iomanip>
#include <fstream>

class HashTable
{
private:
    static const int size = 1000;
    Token* table[size];
    int count_token;

public:
    HashTable() 
    {
        count_token = 0;
        for (int i = 0; i < size; i++)
        {
            table[i] = nullptr;
        }
    }

    ~HashTable()
    {
        for (int i = 0; i < size; i++)
        {
            delete table[i];
        }
    }

    int hash(const std::string& lexeme) const;
    void insert(const Token& token);
    void print(std::ofstream& input);
};
