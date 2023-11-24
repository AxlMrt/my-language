#include <unordered_map>
#include "../include/Lexer.h"
#include "../include/Utils.h"

Lexer::Lexer() : tokensCount(0), currentTokenIndex(0) {}

//GET tokens
bool Lexer::getNextToken(Token& token)
{
  if (currentTokenIndex < tokensCount) {
    token = tokens[currentTokenIndex++];
    return true;
  }
  return false;
}

Token *Lexer::getAllTokens(int &tokensCount)
{
  tokensCount = this->tokensCount;
  return tokens;
}

void Lexer::revertToPreviousToken()
{
  if (currentTokenIndex > 0)
    --currentTokenIndex;
}

//ANALYZE TOKENS
void Lexer::scanIdentifier(const char *currentChar, Token *currentToken)
{
  currentToken->type = TokenType::IDENTIFIER;
  int i = 0;
  
  currentToken->lexeme = createLexeme(currentChar, currentChar);

  while (my_isalnum(*currentChar) || *currentChar == '_')
    currentToken->lexeme[i++] = *currentChar++;
  
  currentToken->lexeme[i] = '\0';
  ++currentToken;
}



void Lexer::scanNumber(const char *currentChar, Token *currentToken)
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
}

void Lexer::scanOperators(const char *currentChar, Token *currentToken)
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

void Lexer::scanKeywords(const char *currentChar, Token *currentToken)
{
  if (my_strncmp(currentChar, "int", 3) == 0 && !my_isalnum(currentChar[3]))
  {
    currentToken->type = TokenType::KEYWORD_INT;
    currentToken->lexeme = createLexeme(currentChar, currentChar + 3);
    currentChar += 3;
    ++currentToken;
  }

  if (my_strncmp(currentChar, "decimal", 7) == 0 && !my_isalnum(currentChar[7]))
  {
    currentToken->type = TokenType::KEYWORD_DECIMAL;
    currentToken->lexeme = createLexeme(currentChar, currentChar + 7);
    currentChar += 7;
    ++currentToken;
  }

  if (my_strncmp(currentChar, "string", 6) == 0 && !my_isalnum(currentChar[6]))
  {
    currentToken->type = TokenType::KEYWORD_STRING;
    currentToken->lexeme = createLexeme(currentChar, currentChar + 6);
    currentChar += 6;
    ++currentToken;
  }

  if (my_strncmp(currentChar, "bool", 4) == 0 && !my_isalnum(currentChar[4]))
  {
    currentToken->type = TokenType::KEYWORD_BOOL;
    currentToken->lexeme = createLexeme(currentChar, currentChar + 4);
    currentChar += 4;
    ++currentToken;
  }

  if (my_strncmp(currentChar, "dspl", 4) == 0 && !my_isalnum(currentChar[4])) {
    currentToken->type = TokenType::KEYWORD_DSPL;
    currentToken->lexeme = createLexeme(currentChar, currentChar + 4);
    currentChar += 4;
    ++currentToken;
  }
}


void Lexer::scanStrings(const char *currentChar, Token *currentToken)
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
      return;
    }

    ++currentToken;
  }
}

void Lexer::scanBool(const char *currentChar, Token *currentToken)
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


void Lexer::scanWhiteSpaceAndComment(const char *currentChar)
{
  while (my_isspace(*currentChar) || *currentChar == '#')
  {
    if (my_isspace(*currentChar)) {
      ++currentChar;
    } else if (*currentChar == '#') {
      while (*currentChar != '\n' && *currentChar != '\0')
        ++currentChar;
    }
  }
}


void Lexer::scan(const char *sourceCode, Token *tokens)
{
  const char *currentChar = sourceCode;
  Token *currentToken = tokens;

  while (*currentChar != '\0' && currentToken - tokens < MAX_TOKENS - 1)
  {
    if (my_isspace(*currentChar) || *currentChar == '#')
      scanWhiteSpaceAndComment(currentChar);

    if (my_isdigit(*currentChar) || *currentChar == '-')
      scanNumber(currentChar, currentToken);
    
    if (*currentChar == '"')
      scanStrings(currentChar, currentToken);
    
    if (*currentChar == 't' || *currentChar == 'f')
      scanBool(currentChar, currentToken);
    
    if (my_isoperator(*currentChar))
      scanOperators(currentChar, currentToken);
    
    if (my_isalpha(*currentChar)) {
      scanKeywords(currentChar, currentToken);
      scanIdentifier(currentChar, currentToken);
    } else {
      currentToken->type = TokenType::UNKNOWN;
      currentToken->lexeme = createLexeme("Invalid", "Invalid");
    }

    ++currentChar;
  }

  currentToken->type = TokenType::END_OF_FILE;
  currentToken->lexeme = createLexeme("", "");
}

char* Lexer::createLexeme(const char *start, const char *end)
{
  int lexemeSize = end - start;
  if (lexemeSize >= MAX_LEXEME_SIZE)
    return nullptr;

  char* lexeme = new char[lexemeSize + 1];
  my_strncpy(lexeme, start, lexemeSize);
  lexeme[lexemeSize] = '\0';

  return lexeme;
}
