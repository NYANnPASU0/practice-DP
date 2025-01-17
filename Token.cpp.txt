#include "Token.h"

std::string Token::get_typeof_token()
{
    std::string tokenType = "UNKNOWN";
    switch (type)
    {
    case TokenType::OP:
        return "OP";
        break;
    case TokenType::TYPE:
        return "TYPE";
        break;
    case TokenType::CONST:
        return "CONST";
        break;
    case TokenType::DO:
        return "DO";
        break;
    case TokenType::WHILE:
        return "WHILE";
        break;
    case TokenType::DELIMITER:
        return "DELIMITER";
        break;
    case TokenType::ID:
        return "ID";
        break;
    case TokenType::RELATION_OPERATOR:
        return"RELATION_OPERATOR";
        break;
    case TokenType::ERROR:
        return "ERROR";
        break;
    case TokenType::END_OF_FILE:
        tokenType = "END_OF_FILE";
        break;
    default:
        return "UNKNOWN";
        break;
    }
}


