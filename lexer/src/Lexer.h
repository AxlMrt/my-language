#ifndef LEXER_H
#define LEXER_H

#define MAX_SOURCE_SIZE 10000
#define MAX_TOKENS 1000
#define MAX_LEXEME_SIZE 100

enum class TokenType
{
  IDENTIFIER,
  INTEGER,
  DECIMAL,
  STRING,
  CHARACTER,
  BOOLEAN,
  POINTER,
  REFERENCE,
  PLUS,
  MINUS,
  MULTIPLY,
  DIVIDE,
  SEMICOLON,
  COLON,
  LPAREN,
  RPAREN,
  LBRACE,
  RBRACE,
  ASSIGN,
  COMMENT,
  UNKNOWN,
  KEYWORD_CONST,
  KEYWORD_FOR,
  KEYWORD_WHILE,
  KEYWORD_DO,
  KEYWORD_IF,
  KEYWORD_ELSE,
  KEYWORD_FUNCTION,
  KEYWORD_RETURN,
  KEYWORD_LOG,
  END_OF_FILE,
  // Fine for now
};

struct Token
{
  TokenType type;
  char lexeme[MAX_LEXEME_SIZE];
};

class Lexer
{
  public:
    Lexer();

    void scan(const char *sourceCode, Token *tokens);
};

#endif
