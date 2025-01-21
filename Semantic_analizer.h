#pragma once
#include "Token.h"
#include "Node.h"
#include <vector>
#include <fstream>
#include <set>

class SemanticAnalyzer
{
public:
	std::vector<std::string> names_int;
	void parsing_all(Node& root);
	void Begin(std::shared_ptr<Node>& node) ;
	void End(std::shared_ptr<Node>& node);
	bool Descriptions(std::shared_ptr<Node>& descr);
	void VarList(std::shared_ptr<Node>& varListNode, std::string& str, bool& flag);
	void DoWhile(std::shared_ptr<Node>& varListNode);
	void Condition1(std::shared_ptr<Node>& condition);
	std::string Expr(std::shared_ptr<Node>& expr_node);
	std::string SimpleExpr(std::shared_ptr<Node>& expr_node);
	void Operators(std::shared_ptr<Node>& oper_node);
	void Out_Error(const std::string& message);
	void Out_to_file(const std::string& message);

	void print(std::string& str);
private:
	std::set<std::string> povtori;
};