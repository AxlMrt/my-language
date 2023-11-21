#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "../src/Lexer.h"

TEST_CASE("Lexer can tokenize simple expressions")
{
  Lexer lexer;

  SECTION("Test case 1: Identifiers")
  {
    Token tokens[50];
    lexer.scan("variable another_variable int_var string_var bool_var decimal_var var124", tokens);
    for (int i = 0; i < 7; i++)
      REQUIRE(tokens[i].type == TokenType::IDENTIFIER);
  }

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

  }
}
