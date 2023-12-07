#include "../include/Parser.h"
#include "../include/DisplayHandler.h"
#include "../include/VariableHandler.h"
#include <iostream>

using namespace std;

Parser::Parser(Token *tokens, int count) : tokenStream(tokens), tokenCount(count), currentTokenIndex(0)
{
}

void Parser::parse()
{
    while (currentTokenIndex < tokenCount)
    {
        if (tokenStream[currentTokenIndex].type == TokenType::KEYWORD_DSPL)
        {
            DisplayHandler displayHandler;
            displayHandler.parseDSPL(tokenStream, currentTokenIndex, variables);
        }
        else if (tokenStream[currentTokenIndex].type == TokenType::IDENTIFIER)
        {
            VariableHandler variableHandler;
            variableHandler.parseVariableDeclaration(tokenStream, currentTokenIndex, variables);
        }
        else
        {
            cout << "Erreur : Instruction non reconnue." << endl;
            ++currentTokenIndex;
        }
    }
}
