#pragma once

#include "Lexicheski_Analizator.h"

#include "Node.h"
#include <memory>
#include <iostream>
#include <vector>

class Sintax_analyzator
{
private:
    Lexer& lexer;
    Token curr_token;
    void get_next_token()
    {
        curr_token = lexer.get_next_token();
    }

    void error(const std::string& message)
    {
        std::cerr << "Синтаксическая ошибка: " << message << std::endl;
    }

    std::shared_ptr<Node> Function();
    std::shared_ptr<Node> Begin();
    std::shared_ptr<Node> End();
    std::shared_ptr<Node> FunctionName();
    std::shared_ptr<Node> Descriptions();
    std::shared_ptr<Node> Operators();
    std::shared_ptr<Node> Descr();
    std::shared_ptr<Node> VarList();
    std::shared_ptr<Node> Type();
    std::shared_ptr<Node> Op();
    std::shared_ptr<Node> SimpleExpr();
    std::shared_ptr<Node> Expr();
    std::shared_ptr<Node> Condition();
    std::shared_ptr<Node> RelationOperators();

    bool isRelationOperator(const std::string op);

public:
    Sintax_analyzator(Lexer& lexer) : lexer(lexer)
    {
        get_next_token();
    }

    std::shared_ptr<Node> parse()
    {
        return Function();
    }

    void log_error(const std::string& message);
};
