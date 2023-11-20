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

bool my_isalpha(char ch)
{
  return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

bool my_isalnum(char ch)
{
  return (my_isalpha(ch) || (ch >= '0' && ch <= '9'));
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

    if (*currentChar == '#')
    {
      while (*currentChar != '\n' && *currentChar != '\0')
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

    if (*currentChar == '+' || *currentChar == '-' || *currentChar == '*' || *currentChar == '/' || *currentChar == '=' || *currentChar == ':' || *currentChar == ';')
    {
      switch (*currentChar)
      {
        case '+':
          currentToken->type = TokenType::PLUS;
          break;
        case '-':
          currentToken->type = TokenType::MINUS;
          break;
        case '*':
          currentToken->type = TokenType::MULTIPLY;
          break;
        case '/':
          currentToken->type = TokenType::DIVIDE;
          break;
        case '=':
          currentToken->type = TokenType::ASSIGN;
          break;
        case ':':
          currentToken->type = TokenType::COLON;
          break;
        case ';':
          currentToken->type = TokenType::SEMICOLON;
          break;
        default:
          currentToken->type = TokenType::UNKNOWN;
          break;
      }

      currentToken->lexeme[0] = *currentChar;
      currentToken->lexeme[1] = '\0';
      ++currentToken;
      ++currentChar;
      continue;
    }

    if (my_isalpha(*currentChar))
    {
      currentToken->type = TokenType::IDENTIFIER;
      int i = 0;

      while (my_isalnum(*currentChar) || *currentChar == '_')
        currentToken->lexeme[i++] = *currentChar++;

      currentToken->lexeme[i] = '\0';
      ++currentToken;
      continue;
    }

    if (*currentChar == '=')
    {
      currentToken->type = TokenType::ASSIGN;
      currentToken->lexeme[0] = '=';
      currentToken->lexeme[1] = '\0';
      ++currentToken;
      ++currentChar;
      continue;
    }

    if (*currentChar == ':')
    {
      currentToken->type = TokenType::COLON;
      currentToken->lexeme[0] = ':';
      currentToken->lexeme[1] = '\0';
      ++currentToken;
      ++currentChar;
      continue;
    }

    if (*currentChar == ';')
    {
      currentToken->type = TokenType::SEMICOLON;
      currentToken->lexeme[0] = ';';
      currentToken->lexeme[1] = '\0';
      ++currentToken;
      ++currentChar;
      continue;
    }

    ++currentChar;
  }

  currentToken->type = TokenType::END_OF_FILE;
  my_strcpy(currentToken->lexeme, "EOF");
}
