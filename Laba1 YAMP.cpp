#include "Lexicheski_Analizator.h"
#include <iostream>
#include <fstream>

int main()
{
    Lexer lexer("input.txt", "error.txt");
    lexer.analyze();

    std::ofstream outputFile("output.txt");

    lexer.hashTable.print(outputFile);
    outputFile.close();
}
