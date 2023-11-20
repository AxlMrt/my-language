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

    
    if (my_isdigit(*currentChar) || *currentChar == '.')
    {
      bool isDecimal = (*currentChar == '.');
      bool hasDecimal = isDecimal;

      if (isDecimal && !my_isdigit(*(currentChar + 1))) {
        currentToken->type = TokenType::UNKNOWN;
        ++currentChar;
      } else {
        currentToken->type = TokenType::INTEGER;
        int i = 0;

        while (my_isdigit(*currentChar) || *currentChar == '.')
        {
          if (*currentChar == '.')
          {
            if (hasDecimal)
            {
              currentToken->type = TokenType::UNKNOWN;
              break;
            }
            
            hasDecimal = true;
          }
          
          currentToken->lexeme[i++] = *currentChar++;
        }

        currentToken->lexeme[i] = '\0';

        if (hasDecimal)
            currentToken->type = TokenType::DECIMAL;
      }

      ++currentToken;
      continue;
    }

    if (*currentChar == 't' || *currentChar == 'f')
    {
      if (*(currentChar + 1) == 'r' && *(currentChar + 2) == 'u' && *(currentChar + 3) == 'e') {
        currentToken->type = TokenType::BOOLEAN;
        my_strcpy(currentToken->lexeme, "true");
        currentChar += 4;
        ++currentToken;
        continue;
      } else if (*(currentChar + 1) == 'a' && *(currentChar + 2) == 'l' && *(currentChar + 3) == 's' && *(currentChar + 4) == 'e') {
        currentToken->type = TokenType::BOOLEAN;
        my_strcpy(currentToken->lexeme, "false");
        currentChar += 5;
        ++currentToken;
        continue;
      }
    }

    if (*currentChar == '"')
    {
      ++currentChar;
      currentToken->type = TokenType::STRING;
      int i = 0;

      while (*currentChar != '"' && *currentChar != '\0')
        currentToken->lexeme[i++] = *currentChar++;

      if (*currentChar == '"')
        ++currentChar;

      currentToken->lexeme[i] = '\0';
      ++currentToken;
      continue;
    }

    ++currentChar;
  }

    currentToken->type = TokenType::END_OF_FILE;
    my_strcpy(currentToken->lexeme, "EOF");
}
