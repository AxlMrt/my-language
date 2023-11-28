#include "../include/Parser.h"
#include <iostream>

using namespace std;

Parser::Parser(Token *tokens, int count)
    : tokenStream(tokens), tokenCount(count), currentTokenIndex(0) {}

bool Parser::hasVariableType()
{
  return (tokenStream[currentTokenIndex].type == TokenType::KEYWORD_INT ||
          tokenStream[currentTokenIndex].type == TokenType::KEYWORD_DECIMAL ||
          tokenStream[currentTokenIndex].type == TokenType::KEYWORD_BOOL ||
          tokenStream[currentTokenIndex].type == TokenType::KEYWORD_STRING);
}

void Parser::parse()
{
  while (currentTokenIndex < tokenCount)
  {
    if (tokenStream[currentTokenIndex].type == TokenType::KEYWORD_DSPL) {
      parseDSPL(tokenStream, currentTokenIndex);
    } else if (tokenStream[currentTokenIndex].type == TokenType::IDENTIFIER) {
      parseVariableDeclaration(tokenStream, currentTokenIndex);
    } else {
      cout << "Erreur : Instruction non reconnue." << endl;
      ++currentTokenIndex;
    }
  }
}

void Parser::parseVariableDeclaration(Token *tokens, int &currentIndex)
{
  if (tokens[currentIndex].type != TokenType::IDENTIFIER)
  {
    cout << "Erreur : Nom de variable attendu." << endl;
    return;
  }

  const char* nom_variable = tokens[currentIndex].lexeme;
  ++currentIndex;

  if (tokens[currentIndex].type != TokenType::COLON)
  {
    cout << "Erreur : Symbole ':' attendu." << endl;
    return;
  }

  ++currentIndex;

  if (!hasVariableType())
  {
    cout << "Erreur : Type de variable attendu." << endl;
    return;
  }

  const char* type_variable = tokens[currentIndex].lexeme;
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

  const char* valeur_variable = tokens[currentIndex].lexeme;
  ++currentIndex;

  if (tokens[currentIndex].type != TokenType::SEMICOLON)
  {
    cout << "Erreur : Symbole ';' attendu." << endl;
    return;
  }

  variables[nom_variable] = valeur_variable;
  ++currentIndex;
}

void Parser::displayValue(const char* value, TokenType valueType)
{
  if (valueType == TokenType::IDENTIFIER) {
    auto it = variables.find(value);
    if (it != variables.end()) {
      cout << it->second << endl;
    } else {
      cout << "Erreur : Variable inconnue." << endl;
    }
  } else {
    cout << value << endl;
  }
}

void Parser::parseDSPL(Token *tokens, int &currentIndex)
{
  if (tokens[currentIndex].type == TokenType::KEYWORD_DSPL) {
    ++currentIndex;

    if (tokens[currentIndex].type == TokenType::LPAREN) {
      ++currentIndex;

      displayValue(tokens[currentIndex].lexeme, tokens[currentIndex].type);
      ++currentIndex;

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
      
    } else {
        cout << "Erreur : Parenthèse ouvrante attendue pour l'affichage." << std::endl;
        return;
    }
  } else {
      cout << "Erreur : Commande non reconnue." << std::endl;
    return;
  }
}
