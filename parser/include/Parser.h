#ifndef PARSER_H
#define PARSER_H

#include "../../lexer/include/Lexer.h"
#include <unordered_map>
#include <iostream>
#include <cstring>

using namespace std;

struct CharPtrHash
{
  size_t operator()(const char *str) const {
     // Fonction de hachage simple pour const char*
    size_t hash = 0;
    while (*str)
    {
      hash = hash * 31 + static_cast<size_t>(*str);
      ++str;
    }
    return hash;
  }
};

struct CharPtrEqual
{
  bool operator()(const char *a, const char *b) const {
    return strcmp(a, b) == 0;
  }
};

class Parser
{
  public:
    Parser(Token *tokens, int count);
    void parse();
    void displayValue(const char* value, TokenType valueType);
    void parseDSPL(Token *tokens, int &currentIndex);
    void parseVariableDeclaration(Token *tokens, int &currentIndex);
  private:
    Token *tokenStream;
    int tokenCount;
    int currentTokenIndex;
    unordered_map<const char*, const char*, CharPtrHash, CharPtrEqual> variables;
    
    bool hasVariableType();
};

#endif
