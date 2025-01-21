﻿#pragma once

#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <iostream>
#include "Token.h"

class Node
{
private:
    std::string name;
    Token token;
    std::string type;
    std::string trace;
    int count_el;

public:
    std::vector<std::shared_ptr<Node>> children;

    Node(const std::string& name, const std::string& type, const std::string& trace, int count_el, const Token& token)
        : name(name), type(type), trace(trace), count_el(count_el), token(token) {}

    Node(const std::string& name, const Token& token = Token())
        : name(name), token(token) {}

    void add_child_root(std::shared_ptr<Node> child)
    {
        children.push_back(child);
    }

    const std::string& get_name() const
    {
        return name;
    }

    const Token& get_token() const
    {
        return token;
    }

    const std::string& get_type() const
    {
        return type;
    }

    void set_type(const std::string& str)
    {
        type = str; 
    }

    const std::vector<std::shared_ptr<Node>>& get_vect_child() const
    {
        return children;
    }

    std::shared_ptr<Node> get_child(size_t index)
    {
        if (index < children.size())
        {
            return children[index];
        }
        return nullptr;
    }

    void print_to_console(const std::shared_ptr<Node>& node, int indent);
    void print_to_file(const std::shared_ptr<Node>& node, int indent, std::ofstream& output);
};
