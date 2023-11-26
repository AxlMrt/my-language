#ifndef LEXER_H
#define LEXER_H

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
    ~Lexer();
    
    void scan(const char *filename);
    Token *getTokenStream() const;
    int getTokenCount() const;
  private:
    Token *tokenStream;
    int tokenCount;
    int maxTokens;

    // Analyze tokens
    void scanWhiteSpaceAndComment(const char *&currentChar);
    void scanBool(const char *&currentChar, Token *currentToken);
    bool readFile(const char *filename, char *&fileContent);
    void scanIdentifierOrKeywords(const char *&currentChar, Token *currentToken);
    void scanNumber(const char *&currentChar, Token *currentToken);
    void scanStrings(const char *&currentChar, Token *currentToken);
    void scanKeywords(const char *&currentChar, Token *currentToken);
    void scanOperators(const char *&currentChar, Token *currentToken);
    void scanIdentifier(const char *&currentChar, Token *currentToken);

    // Utility functions
    char *createLexeme(const char *start, const char *end);
};

#endif
