#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "../src/headers/Lexer.h"


TEST_CASE("Lexer tokenizes identifiers correctly")
{
  Lexer lexer;
  Token tokens[50];

  SECTION("Test case: Single identifiers")
  {
    lexer.scan("variable", tokens);
    REQUIRE(tokens[0].type == TokenType::IDENTIFIER);
  }

  SECTION("Test case: Multiple identifiers")
  {
    lexer.scan("variable1 var_2 anotherVar int_var string_var bool_var decimal_var var124", tokens);
    const TokenType expectedType = TokenType::IDENTIFIER;

    for (int i = 0; i < 8; ++i)
      REQUIRE(tokens[i].type == expectedType);
  }
}


TEST_CASE("Lexer can tokenize simple expressions")
{
  Lexer lexer;

  SECTION("Test case 2: Keywords")
  {
    Token tokens[50];

    lexer.scan("int", tokens);
    REQUIRE(tokens[0].type == TokenType::KEYWORD_INT);

    lexer.scan("decimal", tokens);
    REQUIRE(tokens[0].type == TokenType::KEYWORD_DECIMAL);

    lexer.scan("string", tokens);
    REQUIRE(tokens[0].type == TokenType::KEYWORD_STRING);

    lexer.scan("bool", tokens);
    REQUIRE(tokens[0].type == TokenType::KEYWORD_BOOL);

    lexer.scan("dspl", tokens);
    REQUIRE(tokens[0].type == TokenType::KEYWORD_DSPL);
  }

  SECTION("Test case 3: Operations")
  {
    Token tokens[50];
    struct Operation
    {
      const char *operationString;
      TokenType operationToken;
    };

    const Operation operations[] = {
      { "a = b + c;", TokenType::PLUS },
      { "a = b - c;", TokenType::MINUS },
      { "a = b * c;", TokenType::MULTIPLY },
      { "a = b / c;", TokenType::DIVIDE },
    };

    for (const Operation &operation : operations)
    {
      lexer.scan(operation.operationString, tokens);
      REQUIRE(tokens[3].type == operation.operationToken);
    }
  }
}
