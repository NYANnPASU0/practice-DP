#include "Semantic_analizer.h"
#include <set>
#include <cctype>
#include <fstream>
#include <cstdlib>

void SemanticAnalyzer::parsing_all(Node& root)
{
    if (!root.children.empty())
    {
        Begin(root.children[0]);
        Descriptions(root.children[1]);
        Operators(root.children[2]);
        End(root.children[3]);
    }
}




void SemanticAnalyzer::Begin(std::shared_ptr<Node>& node)
{
    std::string str_id_func = "";
    std::string name_finc = "";
    std::string begin = "";
    std::vector<std::shared_ptr<Node>> kids_begin = node->get_vect_child();

    if (!kids_begin.empty())
    {
        str_id_func += kids_begin[0]->get_token().lexeme;
        name_finc += kids_begin[1]->get_token().lexeme;
        begin += str_id_func + " " + name_finc + " FunctionBegin";
        print(begin);
        Out_to_file(begin);
    }
    else
    {
        std::cerr << "Нет дочерних узлов для текущего узла." << std::endl;
        return;
    }
}

void SemanticAnalyzer::End(std::shared_ptr<Node>& node)
{
    std::vector<std::shared_ptr<Node>> END = node->get_vect_child();
    std::string oper = END[0]->get_name();
    std::string id = END[1]->get_token().lexeme;

    std::string end_res = oper + " " + id + " functionEnd";
    print(end_res);
    Out_to_file(end_res);
}






bool SemanticAnalyzer::Descriptions(std::shared_ptr<Node>& descr)
{
    bool flag = false;
    for (size_t i = 0; i < descr->get_vect_child().size(); i++)
    {
        auto child = descr->get_vect_child()[i];
        std::string s = "";
        if (child->get_name() == "Descr")
        {
            s += child->children[0]->get_token().lexeme;
            auto varl = child->children[1];
            std::string var_name = varl->get_token().lexeme;
            VarList(varl, s, flag); 
        }
    }
    return flag;
}



void SemanticAnalyzer::VarList(std::shared_ptr<Node>& varList,std::string& type, bool& flag)
{
    std::string varl = "";
    int count = 0;

    while (varList->get_vect_child().size() != 0)
    {
        std::string var_name = varList->get_vect_child()[0]->get_token().lexeme;
        if (povtori.find(var_name) != povtori.end())
        {
            std::cerr << "Ошибка: Переменная '" << var_name[0] << "' уже объявлена." << std::endl;
            Out_Error("Ошибка: Переменная  '" + var_name +  "' уже объявлена.");
        }
        povtori.insert(var_name);
        count++;
        varl += (" " + var_name);
        if (varList->get_vect_child().size() < 3)
        {
            break;
        }
        else
        {
            varList = varList->get_vect_child()[2];
        }
    }
    std::string var = type + varl + "  " + std::to_string(count) + " DECL";
    print(var);
    Out_to_file(var);
}





void SemanticAnalyzer::DoWhile(std::shared_ptr<Node>& varListNode)
{
    std::vector<std::shared_ptr<Node>> listKids = varListNode->get_vect_child();
    std::shared_ptr<Node> operators = listKids[2];
    std::shared_ptr<Node> condition = listKids[6];
    
    Operators(operators);
    Condition1(condition);

}



void SemanticAnalyzer::Condition1(std::shared_ptr<Node>& condition)
{
    std::string res = "";
    std::vector<std::shared_ptr<Node>> nodee = condition->get_vect_child();
    std::string relation_operator = nodee[1]->get_token().lexeme;

    std::string first, second;

    if (nodee[0]->get_name() == "Expr")
    {
        first = Expr(nodee[0]);
    }
    else
    {
        first = SimpleExpr(nodee[0]);
    }

    if (nodee[2]->get_name() == "Expr")
    {
        second = Expr(nodee[2]);
    }
    else
    {
        second = SimpleExpr(nodee[2]);
    }

    res = first + " " + second + " " + relation_operator;
    print(res);
    Out_to_file(res);
}




std::string SemanticAnalyzer::Expr(std::shared_ptr<Node>& expr_node)
{
    std::vector<std::shared_ptr<Node>> NODEEEE = expr_node->get_vect_child();
    std::string result_expr = "";
    std::string first_simple;
    std::string second_simple;
    std::string oper;

    if (NODEEEE[0]->get_name() == "Expr")
    {
        first_simple += Expr(NODEEEE[0]);
    }
    else
    {
        if (NODEEEE[0]->get_vect_child().size() == 0)
        {
            first_simple = NODEEEE[0]->get_token().lexeme;
        }
        else
        {
            std::shared_ptr<Node> tmp = NODEEEE[0];
            std::shared_ptr<Node> tmp2 = tmp->get_vect_child()[1];
            first_simple += Expr(tmp2);
        }
    }

    oper = NODEEEE[1]->get_token().lexeme;

    if (NODEEEE[2]->get_name() == "Expr")
        second_simple += Expr(NODEEEE[2]);
    else {
        if (NODEEEE[2]->get_vect_child().size() == 0)
            second_simple = NODEEEE[2]->get_token().lexeme;
        else
        {
            std::shared_ptr<Node> tmp = NODEEEE[2];
            std::shared_ptr<Node> tmp2 = tmp->get_vect_child()[1];
            second_simple += Expr(tmp2);
        }
    }

    result_expr = first_simple + " " + second_simple + " " + oper + " ";

    if (!first_simple.empty() && povtori.find(first_simple) == povtori.end() && !isdigit(first_simple[0]))
    {
        std::cerr << "Ошибка: Переменная '" << first_simple[0] << "' не инициализирована." << std::endl;
        Out_Error("Ошибка: Переменная '" +  first_simple + "' не инициализирована.");
        std::exit(1);
    }
    /*if (!second_simple.empty() && povtori.find(second_simple) == povtori.end() && !isdigit(second_simple[0]))
    {
        std::cerr << "Ошибка: Переменная '" << second_simple[0] << "' не инициализирована." << std::endl;
        Out_Error("Ошибка: Переменная '" + second_simple + "' не инициализирована.");
        std::exit(1);
    }*/

    return result_expr;
}

std::string SemanticAnalyzer::SimpleExpr(std::shared_ptr<Node>& expr_node)
{
    std::vector<std::shared_ptr<Node>> simple = expr_node->get_vect_child();
    std::string result_simple_expr = "";

    if (simple.size() == 0)
    {
        result_simple_expr += expr_node->get_token().lexeme;
    }
    else
    {
        result_simple_expr += SimpleExpr(simple[1]) + " ";
    }

    return result_simple_expr;
}

void SemanticAnalyzer::Operators(std::shared_ptr<Node>& oper_node)
{
    std::vector<std::shared_ptr<Node>> op_list = oper_node->get_vect_child();

    std::string res = "";
    for (int i = 0; i < op_list.size(); i++)
    {
        std::shared_ptr<Node> op = op_list[i];
        if (op->get_vect_child()[0]->get_name() == "Id")
        {
            res += Expr(op); 
            res += '\n';
        }
    }
    print(res);
    Out_to_file(res);
    for (int i = 0; i < op_list.size(); i++)
    {
        std::shared_ptr<Node> op = op_list[i];
        if (op->get_vect_child()[0]->get_name() == "do")
        {
            DoWhile(op);
        }
    }
}

void SemanticAnalyzer::Out_Error(const std::string& message)
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

void SemanticAnalyzer::Out_to_file(const std::string& message)
{
    std::ofstream error_file("semantic_analizator_output.txt", std::ios_base::app);
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



void SemanticAnalyzer::print(std::string& str)
{
    std::cout << str << std::endl;
}
