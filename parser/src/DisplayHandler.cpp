#include "../include/DisplayHandler.h"
#include <iostream>

using namespace std;

DisplayHandler::DisplayHandler()
{
}

void DisplayHandler::displayValue(const char *value, TokenType valueType,
                                  unordered_map<const char *, const char *, CharPtrHash, CharPtrEqual> &variables)
{
    if (valueType == TokenType::IDENTIFIER)
    {
        auto it = variables.find(value);
        if (it != variables.end())
        {
            cout << it->second;
        }
        else
        {
            cout << "Erreur : Variable inconnue.";
        }
    }
    else if (valueType == TokenType::STRING || valueType == TokenType::INTEGER || valueType == TokenType::DECIMAL ||
             valueType == TokenType::BOOLEAN)
    {
        cout << value;
    }
    else
    {
        cout << "Erreur : Type de valeur inconnu.";
    }
}

void DisplayHandler::parseDSPL(Token *tokens, int &currentIndex,
                               unordered_map<const char *, const char *, CharPtrHash, CharPtrEqual> &variables)
{
    if (tokens[currentIndex].type == TokenType::KEYWORD_DSPL)
    {
        ++currentIndex;

        if (tokens[currentIndex].type == TokenType::LPAREN)
        {
            ++currentIndex;

            bool isFirstArgument = true;

            while (tokens[currentIndex].type != TokenType::RPAREN)
            {
                if (!isFirstArgument)
                {
                    if (tokens[currentIndex].type != TokenType::COMMA)
                    {
                        cout << "Erreur: Virgule attendue pour séparer les arguments.";
                        return;
                    }

                    cout << " ";
                    ++currentIndex;
                }

                displayValue(tokens[currentIndex].lexeme, tokens[currentIndex].type, variables);
                ++currentIndex;
                isFirstArgument = false;
            }

            cout << endl;

            if (tokens[currentIndex].type != TokenType::RPAREN)
            {
                cout << "Erreur : Parenthèse fermante manquante." << endl;
                return;
            }
            ++currentIndex;

            if (tokens[currentIndex].type != TokenType::SEMICOLON)
            {
                cout << "Erreur : Point-virgule attendu pour terminer l'affichage." << std::endl;
                return;
            }
            ++currentIndex;
        }
        else
        {
            cout << "Erreur : Parenthèse ouvrante attendue pour l'affichage." << std::endl;
            return;
        }
    }
    else
    {
        cout << "Erreur : Commande non reconnue." << std::endl;
        return;
    }
}
