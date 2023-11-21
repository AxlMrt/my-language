#include <unordered_map>
#include "Lexer.h"

bool my_isspace(char ch)
{
  return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || ch == '\v' || ch == '\f';
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
  return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_';
}

bool my_isalnum(char ch)
{
  return my_isalpha(ch) || my_isdigit(ch);
}

int my_strncmp(const char *str1, const char *str2, int n)
{
  for (int i = 0; i < n; ++i)
  {
    if (str1[i] != str2[i])
      return str1[i] - str2[i];
    if (str1[i] == '\0')
      return 0;
  }

  return 0;
}

Lexer::Lexer() {}

void Lexer::scanIdentifier(const char *&currentChar, Token *&currentToken)
{
  currentToken->type = TokenType::IDENTIFIER;
  int i = 0;

  while (my_isalnum(*currentChar) || *currentChar == '_')
    currentToken->lexeme[i++] = *currentChar++;
  

  currentToken->lexeme[i] = '\0';
  ++currentToken;
}

void Lexer::scanNumber(const char *&currentChar, Token *&currentToken)
{
  bool isDecimal = (*currentChar == '.');
  bool hasDecimal = isDecimal;

  if (my_isdigit(*currentChar) || *currentChar == '.')
  {

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
  }
}


void Lexer::scanOperators(const char *&currentChar, Token *&currentToken)
{
  const std::unordered_map<char, TokenType> operators = {
    {'+', TokenType::PLUS},
    {'-', TokenType::MINUS},
    {'*', TokenType::MULTIPLY},
    {'/', TokenType::DIVIDE},
    {'=', TokenType::ASSIGN},
    {':', TokenType::COLON},
    {';', TokenType::SEMICOLON},
    {'(', TokenType::LPAREN},
    {')', TokenType::RPAREN},
    {'{', TokenType::LBRACE},
    {'}', TokenType::RBRACE}
  };

  if (operators.find(*currentChar) != operators.end())
  {
    currentToken->type = operators.at(*currentChar);
    currentToken->lexeme[0] = *currentChar;
    currentToken->lexeme[1] = '\0';
    ++currentToken;
    ++currentChar;
  }
}

void Lexer::scanKeywords(const char *&currentChar, Token *&currentToken)
{
  if (my_strncmp(currentChar, "int", 3) == 0 && !my_isalnum(currentChar[3]))
  {
    currentToken->type = TokenType::KEYWORD_INT;
    my_strcpy(currentToken->lexeme, "int");
    currentChar += 3;
    ++currentToken;
  }

  if (my_strncmp(currentChar, "decimal", 7) == 0 && !my_isalnum(currentChar[7]))
  {
    currentToken->type = TokenType::KEYWORD_DECIMAL;
    my_strcpy(currentToken->lexeme, "decimal");
    currentChar += 7;
    ++currentToken;
  }

  if (my_strncmp(currentChar, "string", 6) == 0 && !my_isalnum(currentChar[6]))
  {
    currentToken->type = TokenType::KEYWORD_STRING;
    my_strcpy(currentToken->lexeme, "string");
    currentChar += 6;
    ++currentToken;
  }

  if (my_strncmp(currentChar, "bool", 4) == 0 && !my_isalnum(currentChar[4]))
  {
    currentToken->type = TokenType::KEYWORD_BOOL;
    my_strcpy(currentToken->lexeme, "bool");
    currentChar += 4;
    ++currentToken;
  }

  if (my_strncmp(currentChar, "dspl", 4) == 0 && !my_isalnum(currentChar[4])) {
    currentToken->type = TokenType::KEYWORD_DSPL;
    my_strcpy(currentToken->lexeme, "dspl");
    currentChar += 4;
    ++currentToken;
  }
}


void Lexer::scanStrings(const char *&currentChar, Token *&currentToken)
{
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
  }
}


void Lexer::scanBool(const char *&currentChar, Token *&currentToken)
{
  if (*currentChar == 't' || *currentChar == 'f')
  {
    if (*(currentChar + 1) == 'r' && *(currentChar + 2) == 'u' && *(currentChar + 3) == 'e') {
      currentToken->type = TokenType::BOOLEAN;
      my_strcpy(currentToken->lexeme, "true");
      currentChar += 4;
      ++currentToken;
    } else if (*(currentChar + 1) == 'a' && *(currentChar + 2) == 'l' && *(currentChar + 3) == 's' && *(currentChar + 4) == 'e') {
      currentToken->type = TokenType::BOOLEAN;
      my_strcpy(currentToken->lexeme, "false");
      currentChar += 5;
      ++currentToken;
    }
  }

}

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

    scanNumber(currentChar, currentToken);
    scanStrings(currentChar, currentToken);
    scanBool(currentChar, currentToken);
    scanOperators(currentChar, currentToken);

    if (my_isalpha(*currentChar))
    {
      scanKeywords(currentChar, currentToken);
      scanIdentifier(currentChar, currentToken);
    }
    
    ++currentChar;
  }

  currentToken->type = TokenType::END_OF_FILE;
  my_strcpy(currentToken->lexeme, "EOF");
}
