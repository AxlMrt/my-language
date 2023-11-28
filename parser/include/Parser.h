#ifndef PARSER_H
#define PARSER_H

#include "DisplayHandler.h"
#include "VariableHandler.h"
#include "../../lexer/include/Lexer.h"

class Parser 
{
  public:
    Parser(Token *tokens, int count);
    void parse();

  private:
    int tokenCount;
    Token *tokenStream;
    int currentTokenIndex;
    DisplayHandler displayHandler;
    VariableHandler variableHandler;
    unordered_map<const char*, const char*, CharPtrHash, CharPtrEqual> variables;
};

#endif
