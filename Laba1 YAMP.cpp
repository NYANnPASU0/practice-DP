﻿#include "Lexicheski_Analizator.h"
#include "Sintax_analizator.h"
#include "Semantic_analizer.h" 
#include <iostream>
#include <fstream>

int main()
{
    setlocale(LC_ALL, "RUS");

    Lexer lexer("input.txt");
    lexer.analyze();
    std::ofstream outputFile("output.txt");
    lexer.hashTable.print(outputFile);
    Lexer lexer1("input.txt");

    std::ofstream outputFileSintax("sintax_analizator.output.txt");
    Sintax_analyzator syntaxAnalyzer(lexer1);
    std::shared_ptr<Node> parseTree = syntaxAnalyzer.parse();

    if (parseTree)
    {
        /*parseTree->print_to_console(parseTree, 0);*/
        parseTree->print_to_file(parseTree, 0, outputFileSintax);
        SemanticAnalyzer semanticAnalyzer;
        semanticAnalyzer.parsing_all(*parseTree);
    }
    else
    {
        std::cerr << "Ошибка разбора." << std::endl;
    }
    outputFile.close();
    outputFileSintax.close();
}
