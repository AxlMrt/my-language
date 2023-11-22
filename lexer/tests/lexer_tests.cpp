#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "../src/headers/Lexer.h"

TEST_CASE("Lexer::scanIdentifier() correctly tokenizes identifiers")
{
  Lexer lexer;
  Token tokens[50];
  Token *ptr_tokens = tokens;

  SECTION("Single identifier")
  {
    const char *identifier = "variable";    
    lexer.scanIdentifier(identifier, ptr_tokens);
    REQUIRE(tokens[0].type == TokenType::IDENTIFIER);
  }

  SECTION("Multiple identifiers")
  {
    const char *identifier = "variable1 var_2 anotherVar int_var string_var bool_var decimal_var var124" ;
    lexer.scanIdentifier(identifier, ptr_tokens);
    const TokenType expectedType = TokenType::IDENTIFIER;

    for (int i = 0; i < 8; ++i)
      REQUIRE(tokens[i].type == expectedType);
  }
}

TEST_CASE("Lexer::scanNumber() correctly tokenizes numbers")
{
  Lexer lexer;
  Token tokens[50];
  Token *ptr_tokens = tokens;

  SECTION("Integer")
  {
    const char *number = "123";
    lexer.scanNumber(number, ptr_tokens);
    REQUIRE(tokens[0].type == TokenType::INTEGER);
  }

  SECTION("Decimal")
  {
    const char *number = "3.14";
    lexer.scanNumber(number, ptr_tokens);
    REQUIRE(tokens[0].type == TokenType::DECIMAL);
  }
}

TEST_CASE("Lexer::scanOperators() correctly tokenizes operators")
{
  Lexer lexer;
  Token tokens[50];
  Token *ptr_tokens = tokens;

  SECTION("Plus operator")
  {
    const char *op = "+";
    lexer.scanOperators(op, ptr_tokens);
    REQUIRE(tokens[0].type == TokenType::PLUS);
  }

  SECTION("Minus operator")
  {
    const char *op = "-";
    lexer.scanOperators(op, ptr_tokens);
    REQUIRE(tokens[0].type == TokenType::MINUS);
  }

  SECTION("Multiply operator")
  {
    const char *op = "*";
    lexer.scanOperators(op, ptr_tokens);
    REQUIRE(tokens[0].type == TokenType::MULTIPLY);
  }

  SECTION("Divide operator")
  {
    const char *op = "/";
    lexer.scanOperators(op, ptr_tokens);
    REQUIRE(tokens[0].type == TokenType::DIVIDE);
  }

  SECTION("Assign operator")
  {
    const char *op = "=";
    lexer.scanOperators(op, ptr_tokens);
    REQUIRE(tokens[0].type == TokenType::ASSIGN);
  }

  SECTION("Colon operator")
  {
    const char *op = ":";
    lexer.scanOperators(op, ptr_tokens);
    REQUIRE(tokens[0].type == TokenType::COLON);
  }

  SECTION("Semicolon operator")
  {
    const char *op = ";";
    lexer.scanOperators(op, ptr_tokens);
    REQUIRE(tokens[0].type == TokenType::SEMICOLON);
  }

  SECTION("Left Parenthesis operator")
  {
    const char *op = "(";
    lexer.scanOperators(op, ptr_tokens);
    REQUIRE(tokens[0].type == TokenType::LPAREN);
  }

  SECTION("Right Parenthesis operator")
  {
    const char *op = ")";
    lexer.scanOperators(op, ptr_tokens);
    REQUIRE(tokens[0].type == TokenType::RPAREN);
  }

  SECTION("Left Brace operator")
  {
    const char *op = "{";
    lexer.scanOperators(op, ptr_tokens);
    REQUIRE(tokens[0].type == TokenType::LBRACE);
  }

  SECTION("Right Brace operator")
  {
    const char *op = "}";
    lexer.scanOperators(op, ptr_tokens);
    REQUIRE(tokens[0].type == TokenType::RBRACE);
  }
}
