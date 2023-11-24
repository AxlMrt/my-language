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
  KEYWORD_BOOL,
  KEYWORD_DSPL,
  KEYWORD_STRING,
  KEYWORD_DECIMAL,
  END_OF_FILE,
  // Fine for now
};

struct Token
{
  TokenType type;
  char *lexeme;
};

class Lexer
{
  public:
    Lexer();

    //Get tokens
    void revertToPreviousToken();
    bool getNextToken(Token &token);
    Token *getAllTokens(int &tokensCount);

    // Analyze tokens
    void scan(const char *sourceCode, Token *tokens);
    void scanWhiteSpaceAndComment(const char *&currentChar);
    void scanBool(const char *&currentChar, Token *currentToken);
    void scanNumber(const char *&currentChar, Token *currentToken);
    void scanStrings(const char *&currentChar, Token *currentToken);
    void scanKeywords(const char *&currentChar, Token *currentToken);
    void scanOperators(const char *&currentChar, Token *currentToken);
    void scanIdentifier(const char *&currentChar, Token *currentToken);
    void scanIdentifierOrKeyword(const char *&currentChar, Token *currentToken);
  private:
    int tokensCount;
    int currentTokenIndex;
    Token tokens[MAX_TOKENS];

    // Utility functions
    char *createLexeme(const char *start, const char *end);
};

#endif
