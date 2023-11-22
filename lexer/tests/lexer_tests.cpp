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
    const char *identifier = "variable1 var_2 anotherVar int_var string_var bool_var DECIMAL_var var124" ;
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

  SECTION("INTEGER")
  {
    const char *num = "123";
    lexer.scanNumber(num, ptr_tokens);
    REQUIRE(tokens[0].type == TokenType::INTEGER);
    REQUIRE(std::stoi(tokens[0].lexeme) == 123);
  }

  SECTION("DECIMAL")
  {
    const char *num = "3.14";
    lexer.scanNumber(num, ptr_tokens);
    REQUIRE(tokens[0].type == TokenType::DECIMAL);
    REQUIRE(std::stod(tokens[0].lexeme) == 3.14);
  }

  SECTION("Negative INTEGER")
  {
    const char *num = "-42";
    lexer.scanNumber(num, ptr_tokens);
    REQUIRE(tokens[0].type == TokenType::INTEGER);
    REQUIRE(std::stoi(tokens[0].lexeme) == -42);
  }

  SECTION("Negative DECIMAL")
  {
    const char *num = "-2.5";
    lexer.scanNumber(num, ptr_tokens);
    REQUIRE(tokens[0].type == TokenType::DECIMAL);
    REQUIRE(std::stod(tokens[0].lexeme) == -2.5);
  }

  SECTION("Dot without numbers after")
  {
    const char *num = "3.";
    lexer.scanNumber(num, ptr_tokens);
    REQUIRE(tokens[0].type == TokenType::INTEGER);
    REQUIRE(std::stoi(tokens[0].lexeme) == 3);
  }

  SECTION("No digits at all")
  {
    const char *num = ".";
    lexer.scanNumber(num, ptr_tokens);
    REQUIRE(tokens[0].type == TokenType::UNKNOWN);
  }

  SECTION("Large INTEGER")
  {
    const char *num = "999999999999999999";
    lexer.scanNumber(num, ptr_tokens);
    REQUIRE(tokens[0].type == TokenType::INTEGER);
    REQUIRE(std::stoll(tokens[0].lexeme) == 999999999999999999);
  }

  SECTION("Very Small DECIMAL")
  {
    const char *num = "0.000000000000000001";
    lexer.scanNumber(num, ptr_tokens);
    REQUIRE(tokens[0].type == TokenType::DECIMAL);
    REQUIRE(std::stod(tokens[0].lexeme) == 0.000000000000000001);
  }

  SECTION("Invalid Number")
  {
    const char *num = "abc";
    lexer.scanNumber(num, ptr_tokens);
    REQUIRE(tokens[0].type == TokenType::UNKNOWN);
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
