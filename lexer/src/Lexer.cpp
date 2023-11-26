#include <iostream>
#include <fstream>
#include <unordered_map>
#include "../include/Lexer.h"
#include "../include/Utils.h"

using namespace std;

Lexer::Lexer() {}
Lexer::~Lexer() {}

void Lexer::scanIdentifierOrKeywords(const char *&currentChar, Token *currentToken)
{
  const char *start = currentChar;

  while (my_isalnum(*currentChar) || *currentChar == '_')
    ++currentChar;

  int lexemeLength = currentChar - start;
  char *lexeme = createLexeme(start, currentChar);

  std::unordered_map<std::string, TokenType> keywords = {
      {"int", TokenType::KEYWORD_INT},
      {"bool", TokenType::KEYWORD_BOOL},
      {"dspl", TokenType::KEYWORD_DSPL},
      {"string", TokenType::KEYWORD_STRING},
      {"decimal", TokenType::KEYWORD_DECIMAL}
  };

  // Recherche dans le dictionnaire si le lexème correspond à un mot-clé
  auto it = keywords.find(std::string(lexeme, lexemeLength));
  if (it != keywords.end()) {
    currentToken->type = it->second;
    currentToken->lexeme = lexeme;
  } else {
    currentToken->type = TokenType::IDENTIFIER;
    currentToken->lexeme = lexeme;
  }
}

void Lexer::scanNumber(const char *&currentChar, Token *currentToken)
{
  bool isNegative = (*currentChar == '-');
  bool isDecimal = false;
  bool hasDecimal = false;
  bool hasDigits = false;
  bool hasNonZeroAfterDecimal = false;

  const char* start = currentChar; // start pointer for lexeme

  if (isNegative)
    ++currentChar;

  while (my_isdigit(*currentChar) || *currentChar == '.')
  {
    if (*currentChar == '.') {
      if (!hasDigits)
      {
        currentToken->type = TokenType::UNKNOWN;
        currentToken->lexeme = createLexeme("Invalid", "Invalid");
        return;
      }

      if (hasDecimal)
      {
        currentToken->type = isNegative ? TokenType::DECIMAL : TokenType::INTEGER;
        break;
      }

      isDecimal = true;
      hasDecimal = true;
    } else {
      hasDigits = true;
      if (isDecimal)
        hasNonZeroAfterDecimal = hasNonZeroAfterDecimal || (*currentChar != '0');
    }

    ++currentChar;
  }

  const char* end = currentChar; // End pointer for lexem

  if (!hasDigits && !hasDecimal)
  {
    currentToken->type = TokenType::UNKNOWN;
    currentToken->lexeme = createLexeme("Invalid", "Invalid");
    return;
  }

  if (isDecimal && !hasNonZeroAfterDecimal)
    currentToken->type = TokenType::INTEGER; // Decimal without digits after = integer
  else
    currentToken->type = isDecimal ? (isNegative ? TokenType::DECIMAL : TokenType::DECIMAL) : (isNegative ? TokenType::INTEGER : TokenType::INTEGER);

  currentToken->lexeme = createLexeme(start, end);
  ++currentToken;
}

void Lexer::scanOperators(const char *&currentChar, Token *currentToken)
{
  const std::unordered_map<char, TokenType> operators = {
    {'+', TokenType::PLUS},
    {'-', TokenType::MINUS},
    {'*', TokenType::MULTIPLY},
    {'/', TokenType::DIVIDE},
    {'=', TokenType::ASSIGN},
    {':', TokenType::COLON},
    {';', TokenType::SEMICOLON},
    {',', TokenType::COMMA},
    {'(', TokenType::LPAREN},
    {')', TokenType::RPAREN},
    {'{', TokenType::LBRACE},
    {'}', TokenType::RBRACE}
  };

  if (operators.find(*currentChar) != operators.end())
  {
    currentToken->type = operators.at(*currentChar);
    currentToken->lexeme = createLexeme(currentChar, currentChar + 1);
    ++currentToken;
    ++currentChar;
  }
}


void Lexer::scanStrings(const char *&currentChar, Token *currentToken)
{
  if (*currentChar == '"')
  {
    ++currentChar;
    currentToken->type = TokenType::STRING;

    const char *start = currentChar; //point to the start of string

    while (*currentChar != '"' && *currentChar != '\0')
      ++currentChar;

    currentToken->lexeme = createLexeme(start, currentChar);

    if (*currentChar == '"')
      ++currentChar;
    else {
      currentToken->type = TokenType::UNKNOWN;
      currentToken->lexeme = createLexeme(start, currentChar);
    }

    ++currentToken;
  }
}

void Lexer::scanBool(const char *&currentChar, Token *currentToken)
{
  if (*currentChar == 't' || *currentChar == 'f')
  {
    if (*(currentChar + 1) == 'r' && *(currentChar + 2) == 'u' && *(currentChar + 3) == 'e') {
      currentToken->type = TokenType::BOOLEAN;
      currentToken->lexeme = createLexeme(currentChar, currentChar + 4);
      currentChar += 4;
      ++currentToken;
    } else if (*(currentChar + 1) == 'a' && *(currentChar + 2) == 'l' && *(currentChar + 3) == 's' && *(currentChar + 4) == 'e') {
      currentToken->type = TokenType::BOOLEAN;
      currentToken->lexeme = createLexeme(currentChar, currentChar + 5);
      currentChar += 5;
      ++currentToken;
    }
  }
}

void Lexer::scanWhiteSpaceAndComment(const char *&currentChar)
{
  while (my_isspace(*currentChar) || *currentChar == '#')
  {
    if (my_isspace(*currentChar)) {
      ++currentChar;
    } else if (*currentChar == '#') {
      while (*currentChar != '\n' && *currentChar != '\0')
        ++currentChar;

      if (*currentChar == '\n')
        ++currentChar;
    }
  }
}

char* Lexer::createLexeme(const char *start, const char *end)
{
  int lexemeSize = end - start;
  char* lexeme = new char[lexemeSize + 1];

  for (int i = 0; i < lexemeSize; ++i)
    lexeme[i] = start[i];

  lexeme[lexemeSize] = '\0';
  return lexeme;
}

int Lexer::getTokenCount() const
{
    return tokenCount;
}

Token *Lexer::getTokenStream() const
{
    return tokenStream;
}

void Lexer::scan(const char *input)
{
  const char *currentChar = input;
  const int INITIAL_CAPACITY = 10;  // Capacité initiale du tableau
  tokenCount = 0;                   // Initialisation du compteur de tokens
  maxTokens = INITIAL_CAPACITY;     // Initialisation de la capacité maximale

  tokenStream = new Token[INITIAL_CAPACITY];  // Allocation initiale du tableau

  while (*currentChar != '\0')
  {
      scanWhiteSpaceAndComment(currentChar);

      if (*currentChar == '\0')
        break;
      
      Token currentToken;
      if ((*currentChar == '-' && my_isdigit(*(currentChar + 1))) || my_isdigit(*currentChar)) {
        scanNumber(currentChar, &currentToken);
      } else if (*currentChar == 't' || *currentChar == 'f') {
        scanBool(currentChar, &currentToken);
      } else if (my_isalpha(*currentChar) || *currentChar == '_') {
        scanIdentifierOrKeywords(currentChar, &currentToken);
      } else if (my_isoperator(*currentChar)) {
        scanOperators(currentChar, &currentToken);
      } else if (*currentChar == '"') {
        scanStrings(currentChar, &currentToken);
      } else {
        currentToken.type = TokenType::UNKNOWN;
        currentToken.lexeme = createLexeme(currentChar, currentChar + 1);
        ++currentChar;
      }

      if (tokenCount >= maxTokens)
      {  // Vérification de la capacité maximale atteinte
        maxTokens *= 2;               // Double la capacité maximale
        Token *temp = new Token[maxTokens];  // Nouvelle allocation avec la capacité doublée

        for (int i = 0; i < tokenCount; ++i)
          temp[i] = tokenStream[i];  // Copie les tokens actuels dans le nouveau tableau
        
        delete[] tokenStream;  // Libère l'ancien tableau
        tokenStream = temp;    // Met à jour le pointeur pour pointer vers le nouveau tableau
      }

      // Ajoute le nouveau token à la fin du tableau
      tokenStream[tokenCount++] = currentToken;
    }
}
