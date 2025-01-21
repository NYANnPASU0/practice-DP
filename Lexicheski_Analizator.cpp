#include "Lexicheski_Analizator.h"
#include <iostream>
#include <vector>

std::vector <std::string> keywords = { "int", "do" , "while", "return" };

Token Lexer::keyword(const std::string& lex)
{
    std::string lex_ = "";

    int ind = 0;
    int ind_keyword = 0;
    int count = 0;


    if (lex[0] == 'i')
    {
        ind_keyword = 0;
    }
    else if (lex[0] == 'd')
    {
        ind_keyword = 1;
    }
    else if (lex[0] == 'w')
    {
        ind_keyword = 2;
    }
    else if (lex[0] == 'r')
    {
        ind_keyword = 3;
    }
    for (int i = 0; i < lex.size(); i++)
    {
        char elem = lex[i];
        lex_ += elem;
        if (ind >= keywords[ind_keyword].size())
        {
            break;
        }
        if (elem == keywords[ind_keyword][ind])
        {
            count++;
            ind++;
        }
    }
    if (count == keywords[ind_keyword].size())
    {
        if (ind_keyword == 0)
        {
            if (lex.size() == count)
            {
                return Token(TokenType::TYPE, lex, 0);
            }
            else
            {
                return Token(TokenType::UNKNOWN, lex, 0);
            }
        }
        else
        {
            if (lex.size() == count)
            {
                return Token(TokenType::OP, lex, 0);
            }
            else
            {
                return Token(TokenType::UNKNOWN, lex, 0);
            }
        }
    }
    else
    {
        return Token(TokenType::UNKNOWN, lex, 0);
    }
}

void Lexer::analyze()
{
    Token token;
    while ((token = get_next_token()).type != TokenType::UNKNOWN)
    {
        if (token.type == TokenType::ERROR)
        {
            hashTable.insert(token);
        }
        else
        {
            hashTable.insert(token);
        }
    }
}

bool Lexer::check_id(const std::string& lexeme) const
{
    for (size_t i = 0; i < lexeme.length(); i++)
    {
        char elem = lexeme[i];
        if (!isalpha(elem))
        {
            return false;
        }
    }
    return true;
}

bool Lexer::ARITHM_OP(char& elem) const
{
    return (elem == '+' || elem == '-' || elem == '=');
}

bool Lexer::RELATION_OP(const std::string& elem) const
{
    return (elem == ">" || elem == "<" || elem == "<=" || elem == ">=" || elem == "==" || elem == "!=" || elem == "=");
}

bool Lexer::RELATION_OP(const char& elem) const
{
    return (elem == '>' || elem == '<' || elem == '=');
}

bool Lexer::DELIMITER(const char elem) const
{
    return (elem == ')' || elem == '(' || elem == ',' || elem == ';' || elem == '{' || elem == '}');
}

Token Lexer::get_next_token()
{
    char elem;
    while (input_file.get(elem))
    {
        if (isspace(elem))
        {
            continue;
        }
        Token token = check_char_el(elem);
        if (token.type != TokenType::UNKNOWN)
        {
            return token;
        }
    }
    return Token(TokenType::UNKNOWN, "", 0);
}

Token Lexer::check_char_el(char elem)
{
    if (isalpha(elem))
    {
        return check_ID_el(elem);
    }
    else if (isdigit(elem))
    {
        return check_num_el(elem);
    }
    else if (DELIMITER(elem))
    {
        return Token(TokenType::DELIMITER, std::string(1, elem), 0);
    }
    else if (ARITHM_OP(elem))
    {
        char next_el;
        if (input_file.get(next_el))
        {
            if (elem == '=')
            {
                std::string whish_operator = std::string(1, elem) + next_el;
                if (whish_operator == "==")
                {
                    return Token(TokenType::RELATION_OPERATOR, std::string(1, elem) + next_el, 0);
                }
                else
                {
                    return Token(TokenType::OP, std::string(1, elem), 0);
                }
            }
            else
            {
                return Token(TokenType::OP, std::string(1, elem), 0);
            }
        }
    }
    else if (elem == '>' || elem == '!' || elem == '<')
    {
        char next_el;
        if (input_file.get(next_el))
        {
            if (elem == '=')
            {
                return Token(TokenType::RELATION_OPERATOR, std::string(1, elem) + next_el, 0);
            }
            else
            {
                if (next_el == '=')
                {
                    return Token(TokenType::RELATION_OPERATOR, std::string(1, elem) + next_el, 0);
                }
                else
                {
                    input_file.unget();
                    return Token(TokenType::RELATION_OPERATOR, std::string(1, elem), 0);
                }
            }
        }
    }
    return check_unknown(elem);
}

Token Lexer::check_ID_el(char elem)
{
    std::string lexeme(1, elem);
    while (input_file.get(elem) && isalnum(elem) && !DELIMITER(elem))
    {
        lexeme += elem;
    }
    input_file.unget();
    if (!isalpha(lexeme[0]))
    {
        return Token(TokenType::UNKNOWN, lexeme, 0);
    }
    Token a = keyword(lexeme);
    if (a.type == TokenType::UNKNOWN)
    {
        if (check_id(lexeme))
        {
            a = Token(TokenType::ID, lexeme, 0);
            return a;
        }
        else
        {
            a = Token(TokenType::ERROR, lexeme, 0);
            return a;
        }
    }
    return a;
}

Token Lexer::check_num_el(char elem)
{
    std::string lexeme(1, elem);

    bool whole_num = false;
    bool double_num = false;

    while (input_file.get(elem) && !isspace(elem) && !DELIMITER(elem))
    {
        if (isalpha(elem))
        {
            whole_num = true;
        }
        if (elem == '.')
        {
            double_num = true;
        }
        lexeme += elem;
    }
    if (lexeme[0] == '0' && lexeme.size() > 1)
    {
        return Token(TokenType::ERROR, lexeme, 0);
    }
    input_file.unget();
    if (!double_num)
    {
        return Token(TokenType::CONST, lexeme, 0);
    }
    else
    {
        return Token(TokenType::ERROR, lexeme, 0);
    }
}

Token Lexer::check_unknown(char elem)
{
    std::string lexeme(1, elem);
    while (input_file.get(elem) && !isspace(elem) && !DELIMITER(elem))
    {
        lexeme += elem;
    }
    input_file.unget();
    return Token(TokenType::ERROR, lexeme, 0);
}