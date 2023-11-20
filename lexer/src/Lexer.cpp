#include "Lexer.h"

Lexer::Lexer() {}

bool isAlphabetic(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isNumeric(char c) {
  return (c >= '0' && c <= '9');
}

bool isSpace(char c) {
  return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v';
}

void Lexer::scan(const char *sourceCode, Token *tokens) {
  int currentPosition = 0;
  int tokenIndex = 0;

  while (sourceCode[currentPosition] != '\0' && tokenIndex < MAX_TOKENS) {
    char currentChar = sourceCode[currentPosition];

    if (isAlphabetic(currentChar)) {
      int lexemeIndex = 0;
      tokens[tokenIndex].type = TokenType::IDENTIFIER;

      while ((isAlphabetic(currentChar) || isNumeric(currentChar)) && lexemeIndex < MAX_LEXEME_SIZE) {
        tokens[tokenIndex].lexeme[lexemeIndex++] = currentChar;
        currentChar = sourceCode[++currentPosition];
      }

      tokens[tokenIndex].lexeme[lexemeIndex] = '\0';
      tokenIndex++;
    } else if (isNumeric(currentChar)) {
      int lexemeIndex = 0;
      tokens[tokenIndex].type = TokenType::INTEGER;

      while (isNumeric(currentChar) && lexemeIndex < MAX_LEXEME_SIZE) {
        tokens[tokenIndex].lexeme[lexemeIndex++] = currentChar;
        currentChar = sourceCode[++currentPosition];
      }

      tokens[tokenIndex].lexeme[lexemeIndex] = '\0';
      tokenIndex++;
    } else if (isSpace(currentChar)) {
      currentPosition++;
    } else {
      switch (currentChar) {
        case '#':
          tokens[tokenIndex].type = TokenType::COMMENT;
          break;
        case '+':
          tokens[tokenIndex].type = TokenType::PLUS;
          break;
        case '-':
          tokens[tokenIndex].type = TokenType::MINUS;
          break;
        case '*':
          tokens[tokenIndex].type = TokenType::MULTIPLY;
          break;
        case '/':
          tokens[tokenIndex].type = TokenType::DIVIDE;
          break;
        case ';':
          tokens[tokenIndex].type = TokenType::SEMICOLON;
          break;
        case '(':
          tokens[tokenIndex].type = TokenType::LPAREN;
          break;
        case ')':
          tokens[tokenIndex].type = TokenType::RPAREN;
          break;
        case '{':
          tokens[tokenIndex].type = TokenType::LBRACE;
          break;
        case '}':
          tokens[tokenIndex].type = TokenType::RBRACE;
          break;
        case '=':
          tokens[tokenIndex].type = TokenType::ASSIGN;
          break;
      }

      tokens[tokenIndex].lexeme[0] = currentChar;
      tokens[tokenIndex].lexeme[1] = '\0';
      tokenIndex++;
      currentPosition++;
    }
  }

  tokens[tokenIndex].type = TokenType::END_OF_FILE;
}
