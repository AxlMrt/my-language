#include "../include/VariableHandler.h"
#include <iostream>

using namespace std;

VariableHandler::VariableHandler()
{
}

bool VariableHandler::hasVariableType(Token *tokens, int currentIndex)
{
    return (tokens[currentIndex].type == TokenType::KEYWORD_INT ||
            tokens[currentIndex].type == TokenType::KEYWORD_DECIMAL ||
            tokens[currentIndex].type == TokenType::KEYWORD_BOOL ||
            tokens[currentIndex].type == TokenType::KEYWORD_STRING);
}

void VariableHandler::parseVariableDeclaration(
    Token *tokens, int &currentIndex, unordered_map<const char *, const char *, CharPtrHash, CharPtrEqual> &variables)
{
    if (tokens[currentIndex].type != TokenType::IDENTIFIER)
    {
        cout << "Erreur : Nom de variable attendu." << endl;
        return;
    }

    const char *nom_variable = tokens[currentIndex].lexeme;
    ++currentIndex;

    if (tokens[currentIndex].type != TokenType::COLON)
    {
        cout << "Erreur : Symbole ':' attendu." << endl;
        return;
    }

    ++currentIndex;

    if (!hasVariableType(tokens, currentIndex))
    {
        cout << "Erreur : Type de variable attendu." << endl;
        return;
    }

    ++currentIndex;

    if (tokens[currentIndex].type != TokenType::ASSIGN)
    {
        cout << "Erreur : Symbole '=' attendu." << endl;
        return;
    }

    ++currentIndex;

    // A modifier pour assigner une valeur plus loin dans le code
    if ((tokens[currentIndex].type != TokenType::INTEGER && tokens[currentIndex].type != TokenType::DECIMAL &&
         tokens[currentIndex].type != TokenType::STRING && tokens[currentIndex].type != TokenType::BOOLEAN))
    {
        cout << "Erreur : Valeur attendue pour la variable." << endl;
        return;
    }

    const char *valeur_variable = tokens[currentIndex].lexeme;
    ++currentIndex;

    if (tokens[currentIndex].type != TokenType::SEMICOLON)
    {
        cout << "Erreur : Symbole ';' attendu." << endl;
        return;
    }

    variables[nom_variable] = valeur_variable;
    ++currentIndex;
}
