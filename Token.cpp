#include "Token.h"

std::string Token::get_typeof_token()
{
    std::string tokenType = "UNKNOWN";
    switch (type)
    {
    case TokenType::OP:
        return "OP";
    case TokenType::TYPE:
        return "TYPE";
    case TokenType::CONST:
        return "CONST";
    case TokenType::DO:
        return "DO";
    case TokenType::WHILE: 
        "WHILE";
    case TokenType::DELIMITER:
        return "DELIMITER";
    case TokenType::ID:
        return "ID";
    case TokenType::RELATION_OPERATOR:
        return"RELATION_OPERATOR";
    case TokenType::ERROR:
        return "ERROR";
    default: return "UNKNOWN";
    }
}


