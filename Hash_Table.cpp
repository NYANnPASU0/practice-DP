#include "Hash_Table.h"

int HashTable::hash(const std::string& lexeme) const
{
    int val = 0;
    for (int i = 0; i < lexeme.size(); i++)
    {
        char element = lexeme[i];
        val = (val * 23 + element) % size;
    }
    return val;
}

void HashTable::insert(const Token& token)
{
    int index = hash(token.lexeme);
    while (table[index] != nullptr && table[index]->lexeme != token.lexeme)
    {
        index = (index + 1) % size;
    }
    table[index] = new Token(token);
    count_token++;
}

void HashTable::print(std::ofstream& input)
{
    for (int i = 0; i < size; i++)
    {
        if (table[i] != nullptr && table[i]->type != TokenType::ERROR)
        {
            input << std::setw(18) << table[i]->get_typeof_token() << std::setw(10) << " | "
                << std::setw(10) << table[i]->lexeme << std::setw(10) << " | " << std::setw(10) << i << std::endl;
        }
    }

    input << std::endl;

    for (int i = 0; i < size; i++)
    {
        if (table[i] != nullptr && table[i]->type == TokenType::ERROR)
        {
            input << std::setw(18) << table[i]->get_typeof_token() << std::setw(10) << " | "
                << std::setw(10) << table[i]->lexeme << std::setw(10) << " | " << std::setw(10) << i << std::endl;
        }
    }
}