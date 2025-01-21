#include "Sintax_analizator.h"
#include <stdexcept>
#include <iostream>

using namespace std;

std::shared_ptr<Node> Sintax_analyzator::Function()
{
    auto begin = Begin();
    if (!begin)
    {
        return nullptr; 
    }

    auto descriptions = Descriptions();
    if (!descriptions)
    {
        return nullptr; 
    }

    auto operators = Operators();
    if (!operators)
    {
        return nullptr; 
    }
  
    auto end = End();
    if (!end)
    {
        return nullptr;
    }

    auto functionNode = std::make_shared<Node>("Function");
    functionNode->add_child_root(begin);
    functionNode->add_child_root(descriptions);
    functionNode->add_child_root(operators);
    functionNode->add_child_root(end);
    return functionNode;
}

std::shared_ptr<Node> Sintax_analyzator::Begin()
{
    auto types = Type();
    auto names_function = FunctionName();

    if (curr_token.lexeme == "(")
    {
        auto open_parenthesis = curr_token;
        get_next_token();
        if (curr_token.lexeme == ")")
        {
            auto close_parenthesis = curr_token;
            get_next_token();
            if (curr_token.lexeme == "{")
            {
                auto open_curved_bracket = curr_token;
                get_next_token();
                auto beginNode = make_shared<Node>("Begin");
                beginNode->add_child_root(types);
                beginNode->add_child_root(names_function);
                beginNode->add_child_root(make_shared<Node>("{", "", "", 1,open_curved_bracket));

                return beginNode;
            }
            else
            {
                error("Ожидалось { после )");
                log_error("Ожидалось { после )");
            }
        }
        else
        {
            error("Ожидалось ) после (");
            log_error("Ожидалось ) после (");
        }
    }
    else 
    {
        error("Ожидалось ( после наименования функции");
        log_error("Ожидалось ( после наименования функции");
    }
    return nullptr;
}



std::shared_ptr<Node> Sintax_analyzator::End()
{
    //if (curr_token.lexeme != "return")
    //{
    //    error("Оператор return не найден");
    //    return nullptr;
    //}
    Token returnToken = curr_token;
    get_next_token();
    if (curr_token.type == TokenType::ID)
    {
        Token idToken = curr_token;
        get_next_token();
        if (curr_token.lexeme == ";")
        {
            Token finToken = curr_token;
            get_next_token();
            shared_ptr<Node> endNode = make_shared<Node>("End");
            endNode->add_child_root(make_shared<Node>(returnToken.lexeme, "", "", 1, returnToken));

            endNode->add_child_root(make_shared<Node>("Id", "", "", 1, idToken));
            endNode->add_child_root(make_shared<Node>(";", "", "", 1, finToken));
            endNode->add_child_root(make_shared<Node>("}"));
            return endNode;
        }
        else
        {
             error("Ожидалось ; перед оператором return.");
             log_error("Ожидалось ; перед оператором return.");
             return nullptr;
        }
    }
    else
    {
        error("Ожидалось полная конструкция с return.");
        log_error("Ожидалось полная конструкция с return.");
        return nullptr;
    }
    return nullptr;
}


std::shared_ptr<Node> Sintax_analyzator::FunctionName()
{
    if (curr_token.type == TokenType::ID)
    {
        auto token_id = curr_token;
        get_next_token();
        return std::make_shared<Node>("FunctionName",token_id);
    }
    else
    {
        error("Ожидалось название функции");
        log_error("Ожидалось название функции");
        return nullptr;
    }
}


std::shared_ptr<Node> Sintax_analyzator::Descriptions()
{
    auto descriptions = std::make_shared<Node>("Descriptions");
    while (curr_token.lexeme == "int")
    {
        auto descrNode = Descr();
        descriptions->add_child_root(descrNode);
    }
    return descriptions;
}


std::shared_ptr<Node> Sintax_analyzator::Operators()
{
    string trace = "";
    auto operators = std::make_shared<Node>("Operators");
    while (curr_token.type != TokenType::END_OF_FILE && curr_token.lexeme != "}")
    {
        auto op = Op();
        if (op == nullptr)
        {
            break;
        }
        operators->add_child_root(op);
    }
    return operators;
}



std::shared_ptr<Node> Sintax_analyzator::Descr()
{
    auto types = Type();
    if (!types)
    {
        return nullptr; 
    }
    auto varlist = VarList();
    if (!varlist)
    {
        return nullptr; 
    }

    if (curr_token.lexeme == ";")
    {
        auto separator_token = curr_token;
        get_next_token();
        auto node = make_shared<Node>("Descr");
        node->add_child_root(types);
        node->add_child_root(varlist);
        node->add_child_root(make_shared<Node>(";", "", "", 1, separator_token));
        return node;
    }
    else
    {
        error("Потерян ; после объявления переменных.");
        log_error("Потерян ; после объявления переменных.");
        return nullptr;
    }
}



std::shared_ptr<Node> Sintax_analyzator::VarList()
{
    auto varlist = std::make_shared<Node>("VarList");
    if (curr_token.type != TokenType::ID)
    {
        error("Ожидалось название переменной");
        log_error("Ожидалось название переменной");
        return nullptr;
    }
    auto token_id = curr_token;
    get_next_token(); 
    varlist->add_child_root(std::make_shared<Node>("Id",token_id));

    while (curr_token.lexeme == ",")
    {
        auto delToken = curr_token;
        get_next_token();

        if (curr_token.type != TokenType::ID)
        {
            error("Ожидалась переменная после , ");
            log_error("Ожидалась переменная после , ");
            return nullptr;
        }
        else
        {
            varlist->add_child_root(make_shared<Node>(",", "", "", 1, delToken));

            shared_ptr<Node> tmp = VarList();
            varlist->add_child_root(tmp);
        }
    }

    return varlist;
}



std::shared_ptr<Node> Sintax_analyzator::Type()
{
    if (curr_token.type == TokenType::TYPE)
    {
        auto token_int = curr_token;
        lexer.hashTable.insert(token_int);
        get_next_token();
        auto types = make_shared<Node>("Type" ,token_int);
        return types;
    }
    else
    {
        error("Ожидался единственный тип int.");
        log_error("Ожидался единственный тип int.");
        return nullptr;
    }
}



std::shared_ptr<Node> Sintax_analyzator::Op()
{
    if (curr_token.type == TokenType::ID)
    {
        Token id_Tok = curr_token;
        get_next_token();
        if (curr_token.lexeme == "=")
        {
            Token assignToken = curr_token;
            get_next_token();
            std::shared_ptr<Node> expr = Expr();
            if (curr_token.lexeme == ";")
            {
                Token semicolonToken = curr_token;
                get_next_token();
                std::shared_ptr<Node> oper = std::make_shared<Node>("Op");
                oper->add_child_root(std::make_shared<Node>("Id", "", "", 1, id_Tok));
                oper->add_child_root(std::make_shared<Node>("=", "", "", 1, assignToken));
                oper->add_child_root(expr);
                oper->add_child_root(std::make_shared<Node>(";", "", "", 1, semicolonToken));

                return oper;
            }
            else
            {
                error("Ожидалось завершающее ;.");
                log_error("Ожидалось завершающее ;.");
                return nullptr;
            }
        }
        else
        {
            error("Ожидалось = перед выражением");
            log_error("Ожидалось = перед выражением");
            return nullptr;
        }
    }
    else if (curr_token.lexeme == "do")
    {
        Token doToken = curr_token;
        get_next_token();
        if (curr_token.lexeme == "{")
        {
            Token open_brace = curr_token;
            get_next_token();
            std::shared_ptr<Node> operators_in_do = Operators();
            if (curr_token.lexeme == "}")
            {
                Token close_brace = curr_token;
                get_next_token();
                if (curr_token.lexeme == "while")
                {
                    Token token_while = curr_token;
                    get_next_token();
                    if (curr_token.lexeme == "(")
                    {
                        Token open_bracket = curr_token;
                        get_next_token();
                        std::shared_ptr<Node> condition = Condition();
                        if (curr_token.lexeme == ")")
                        {
                            Token close_bracket = curr_token;
                            get_next_token();
                            std::shared_ptr<Node> oper = std::make_shared<Node>("Op");
                            oper->add_child_root(std::make_shared<Node>("do", "", "", 1, doToken));
                            oper->add_child_root(std::make_shared<Node>("{", "", "", 1, open_brace));
                            oper->add_child_root(operators_in_do);
                            oper->add_child_root(std::make_shared<Node>("}", "", "", 1, close_brace));
                            oper->add_child_root(std::make_shared<Node>("while", "", "", 1, token_while));
                            oper->add_child_root(std::make_shared<Node>("(", "", "", 1, open_bracket));
                            oper->add_child_root(condition);
                            oper->add_child_root(std::make_shared<Node>(")", "", "", 1, close_bracket));
                            get_next_token();
                            return oper;
                        }
                        else
                        {
                            error("Ожидалось ')' после условия.");
                            log_error("Ожидалось ')' после условия.");
                            return nullptr;
                        }
                    }
                    else
                    {
                        error("Ожидалось ( после while.");
                        log_error("Ожидалось ( после while.");
                        return nullptr;
                    }
                }
                else
                {
                    error("Ожидалось while после }.");
                    log_error("Ожидалось while после }.");
                    return nullptr;
                }
            }
            else
            {
                error("Ожидалось завершающее }.");
                log_error("Ожидалось завершающее }.");
                return nullptr;
            }
        }
        else
        {
            error("Ожидалось { после do.");
            log_error("Ожидалось { после do.");
            return nullptr;
        }
    }
    return nullptr;
}



std::shared_ptr<Node> Sintax_analyzator::SimpleExpr()
{
    if (curr_token.type == TokenType::ID)
    {
        auto token_id = curr_token;
        get_next_token();
        if (token_id.type == TokenType::ERROR)
        {
            error("Ошибка: переменная не является типом int");
            log_error("Ошибка: переменная не является типом int");
        }

        return std::make_shared<Node>("SimpleExpr", token_id);
    }
    else if (curr_token.type == TokenType::CONST)
    {
        auto constToken = curr_token;
        get_next_token();
        if (constToken.type == TokenType::ERROR)
        {
            error("Ошибка: константа имеет недопустимый тип");
            log_error("Ошибка: константа имеет недопустимый тип");
        }
        return std::make_shared<Node>("SimpleExpr", constToken);
    }
    else if (curr_token.lexeme == "(")
    {
        get_next_token();
        auto expr = Expr();
        if (curr_token.lexeme != ")")
        {
            error("Ожидалось )");
            log_error("Ожидалось )");
        }
        get_next_token();
        return expr;
    }
    else if (curr_token.type == TokenType::ERROR)
    {
        error("Константа имеет недопустимый тип");
        log_error("Константа имеет недопустимый тип");
    }
    error("Ожидалось выражение");
    log_error("Ожидалось выражение");
    return nullptr;
}




std::shared_ptr<Node> Sintax_analyzator::Expr()
{
    auto simpl_ex = SimpleExpr();

    while (curr_token.lexeme == "+" || curr_token.lexeme == "-")
    {
        Token opToken = curr_token;
        get_next_token();
        shared_ptr<Node> expr = make_shared<Node>("Expr");
        expr->add_child_root(simpl_ex);
        expr->add_child_root(make_shared<Node>(opToken.lexeme, "", "", 1, opToken));
        shared_ptr<Node> exprRightPartNode = SimpleExpr();
        expr->add_child_root(exprRightPartNode);

        simpl_ex = expr;
    }
    return simpl_ex;
}



std::shared_ptr<Node> Sintax_analyzator::Condition()
{
    shared_ptr<Node> leftExpr = Expr();
    if (isRelationOperator(curr_token.lexeme))
    {
        Token relOpToken = curr_token;
        get_next_token();
        shared_ptr<Node> rightExpr = Expr();
        shared_ptr<Node> condNode = make_shared<Node>("Condition");
        condNode->add_child_root(leftExpr);
        condNode->add_child_root(make_shared<Node>("RelationsOperators", "", "", 1, relOpToken));
        condNode->add_child_root(rightExpr);
        return condNode;
    }
    else
    {
        error("Потерян оператор сравнения");
        log_error("Потерян оператор сравнения");
        return nullptr;
    }
}



std::shared_ptr<Node> Sintax_analyzator::RelationOperators()
{
    if (curr_token.lexeme == "==")
    {
        auto token = curr_token;
        get_next_token(); 
        return std::make_shared<Node>("RelationOperator", token);
    }

    else if (curr_token.lexeme == "!=")
    {
        auto token = curr_token;
        get_next_token();
        return std::make_shared<Node>("RelationOperator", token);
    }

    else if (curr_token.lexeme == ">=")
    {
        auto token = curr_token;
        get_next_token();
        return std::make_shared<Node>("RelationOperator", token);
    }

    else if (curr_token.lexeme == "<=")
    {
        auto token = curr_token;
        get_next_token();
        return std::make_shared<Node>("RelationOperator", token);
    }

    else if (curr_token.lexeme == ">")
    {
        auto token = curr_token;
        get_next_token();
        return std::make_shared<Node>("RelationOperator", token);
    }

    else if (curr_token.lexeme == "<")
    {
        auto token = curr_token;
        get_next_token();
        return std::make_shared<Node>("RelationOperator", token);
    }
    
    error("Неизвестный оператор сравнения.");
    return nullptr; 
}

bool Sintax_analyzator::isRelationOperator(const std::string op)
{
    return op == "==" || op == "!=" || op == "<" || op == ">" || op == "<=" || op == ">=";
}

void Sintax_analyzator::log_error(const std::string& message)
{
    std::ofstream error_file("error.txt", std::ios_base::app);
    if (error_file.is_open())
    {
        error_file << message << std::endl;
        error_file.close();
    }
    else
    {
        std::cerr << "Не удалось открыть файл для записи ошибок." << std::endl;
    }
}

