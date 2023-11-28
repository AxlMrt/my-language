#ifndef DISPLAY_HANDLER_H
#define DISPLAY_HANDLER_H

#include <iostream>
#include "../../lexer/include/Lexer.h"
#include "VariableHandler.h"

using namespace std;

class DisplayHandler
{
  public:
    DisplayHandler();
    void displayValue(const char* value, TokenType valueType, unordered_map<const char*, const char*, CharPtrHash, CharPtrEqual> &variables);
    void parseDSPL(Token *tokens, int &currentIndex, unordered_map<const char*, const char*, CharPtrHash, CharPtrEqual> &variables);
};

#endif
