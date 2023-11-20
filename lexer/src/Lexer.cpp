#include "Lexer.h"

bool my_isspace(char ch)
{
  return (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || ch == '\v' || ch == '\f');
}

bool my_isdigit(char ch)
{
  return (ch >= '0' && ch <= '9');
}

void my_strcpy(char *dest, const char *src)
{
  while (*src != '\0')
  {
    *dest = *src;
    ++dest;
    ++src;
  }
  *dest = '\0';
}

Lexer::Lexer() {}


void Lexer::scan(const char *sourceCode, Token *tokens)
{
  const char *currentChar = sourceCode;
  Token *currentToken = tokens;

  while (*currentChar != '\0')
  {
    if (my_isspace(*currentChar))
    {
      ++currentChar;
      continue;
    }

    if (my_isdigit(*currentChar))
    {
      currentToken->type = TokenType::INTEGER;
      int i = 0;

      while (my_isdigit(*currentChar))
        currentToken->lexeme[i++] = *currentChar++;

      currentToken->lexeme[i] = '\0';
      ++currentToken;
      continue;
    }

    ++currentChar;
  }

    currentToken->type = TokenType::END_OF_FILE;
    my_strcpy(currentToken->lexeme, "EOF");
}
