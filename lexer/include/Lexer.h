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
  PLUS,
  MINUS,
  MULTIPLY,
  DIVIDE,
  SEMICOLON,
  COLON,
  COMMA,
  LPAREN,
  RPAREN,
  LBRACE,
  RBRACE,
  ASSIGN,
  UNKNOWN,
  KEYWORD_INT,
  KEYWORD_DECIMAL,
  KEYWORD_BOOL,
  KEYWORD_STRING,
  KEYWORD_DSPL,
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

    //Get tokens
    bool getNextToken(Token &token);
    Token *getAllTokens(int &tokensCount);
    void revertToPreviousToken();

    // Analyze tokens
    void scan(const char *sourceCode, Token *tokens);
    void scanIdentifier(const char *&currentChar, Token *&currentToken);
    void scanNumber(const char *&currentChar, Token *&currentToken);
    void scanStrings(const char *&currentChar, Token *&currentToken);
    void scanBool(const char *&currentChar, Token *&currentToken);
    void scanOperators(const char *&currentChar, Token *&currentToken);
    void scanKeywords(const char *&currentChar, Token *&currentToken);

  private:
    Token tokens[MAX_TOKENS];
    int tokensCount;
    int currentTokenIndex;
};

#endif
