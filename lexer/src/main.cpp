#include <iostream>
#include <fstream>
#include "Lexer.h"

using namespace std;


const char *tokenNames[] = {
    "IDENTIFIER",
    "INTEGER",
    "DECIMAL",
    "STRING",
    "CHARACTER",
    "BOOLEAN",
    "POINTER",
    "REFERENCE",
    "PLUS",
    "MINUS",
    "MULTIPLY",
    "DIVIDE",
    "SEMICOLON",
    "COLON",
    "LPAREN",
    "RPAREN",
    "LBRACE",
    "RBRACE",
    "ASSIGN",
    "UNKNOWN",
    "KEYWORD_CONST",
    "KEYWORD_INT",
    "KEYWORD_DECIMAL",
    "KEYWORD_BOOL",
    "KEYWORD_STRING",
    "KEYWORD_FOR",
    "KEYWORD_WHILE",
    "KEYWORD_DO",
    "KEYWORD_IF",
    "KEYWORD_ELSE",
    "KEYWORD_FUNCTION",
    "KEYWORD_RETURN",
    "KEYWORD_DSPL",
    "END_OF_FILE"
};

int main()
{
    ifstream inputFile("test");
    string syntaxContent((istreambuf_iterator<char>(inputFile)),
                         istreambuf_iterator<char>());

    Lexer lexer;
    Token tokens[MAX_TOKENS];

    lexer.scan(syntaxContent.c_str(), tokens);

    for (int i = 0; tokens[i].type != TokenType::END_OF_FILE; ++i)
        cout << "Token type: " << tokenNames[static_cast<int>(tokens[i].type)] << ", Lexeme: " << tokens[i].lexeme << endl;

    return 0;
}
