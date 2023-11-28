#ifndef VARIABLE_HANDLER_H
#define VARIABLE_HANDLER_H

#include <iostream>
#include <unordered_map>
#include <cstring>
#include "../../lexer/include/Lexer.h"

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

class VariableHandler
{
  public:
    VariableHandler();
    bool hasVariableType(Token *tokens, int currentIndex);
    void parseVariableDeclaration(Token *tokens, int &currentIndex, unordered_map<const char*, const char*, CharPtrHash, CharPtrEqual> &variables);
};

#endif
