#include <iostream>
#include <fstream>
#include "../../lexer/include/Lexer.h"
#include "../include/Parser.h"

int main() {
    std::ifstream inputFile("parser_test.txt");

    if (!inputFile.is_open()) {
        std::cout << "Erreur : Impossible d'ouvrir le fichier." << std::endl;
        return 1;
    }

    std::string content((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    Lexer lexer;
    lexer.scan(content.c_str());

    Token *tokens = lexer.getTokenStream();
    int tokenCount = lexer.getTokenCount();

    Parser parser(tokens, tokenCount);
    parser.parse();

    return 0;
}
