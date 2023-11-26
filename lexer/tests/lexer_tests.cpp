#define CATCH_CONFIG_MAIN
#include <iostream>
#include <catch2/catch.hpp>

#include "../include/Lexer.h"


TEST_CASE("Lexer::scan() test cases")
{
  Lexer lexer;

  SECTION("Identify identifiers")
  {
    const char* sourceCode = "variable1 var_2 anotherVar int_var string_var bool_var DECIMAL_var var124";
    lexer.scan(sourceCode);

    const TokenType expectedType = TokenType::IDENTIFIER;
    for (int i = 0; i < lexer.getTokenCount(); ++i)
    {
      REQUIRE(lexer.getTokenStream()[i].type == expectedType);
    }
  }

  SECTION("Identify numbers")
  {
    const char* sourceCode = "123 3.14 -42 -2.5 3. 999999999999999999 0.000000000000000001 abc";
    lexer.scan(sourceCode);

    REQUIRE(lexer.getTokenStream()[0].type == TokenType::INTEGER);
    REQUIRE(lexer.getTokenStream()[1].type == TokenType::DECIMAL);
    REQUIRE(lexer.getTokenStream()[2].type == TokenType::INTEGER);
    REQUIRE(lexer.getTokenStream()[3].type == TokenType::DECIMAL);
    REQUIRE(lexer.getTokenStream()[4].type == TokenType::INTEGER);
    REQUIRE(lexer.getTokenStream()[5].type == TokenType::INTEGER);
    REQUIRE(lexer.getTokenStream()[6].type == TokenType::DECIMAL);
    REQUIRE(lexer.getTokenStream()[7].type == TokenType::IDENTIFIER);
  }

  SECTION("Identify operators")
  {
    const char* sourceCode = "+ - * / = : ; , ( ) { }";
    lexer.scan(sourceCode);

    REQUIRE(lexer.getTokenStream()[0].type == TokenType::PLUS);
    REQUIRE(lexer.getTokenStream()[1].type == TokenType::MINUS);
    REQUIRE(lexer.getTokenStream()[2].type == TokenType::MULTIPLY);
    REQUIRE(lexer.getTokenStream()[3].type == TokenType::DIVIDE);
    REQUIRE(lexer.getTokenStream()[4].type == TokenType::ASSIGN);
    REQUIRE(lexer.getTokenStream()[5].type == TokenType::COLON);
    REQUIRE(lexer.getTokenStream()[6].type == TokenType::SEMICOLON);
    REQUIRE(lexer.getTokenStream()[7].type == TokenType::COMMA);
    REQUIRE(lexer.getTokenStream()[8].type == TokenType::LPAREN);
    REQUIRE(lexer.getTokenStream()[9].type == TokenType::RPAREN);
    REQUIRE(lexer.getTokenStream()[10].type == TokenType::LBRACE);
    REQUIRE(lexer.getTokenStream()[11].type == TokenType::RBRACE);
  }

  SECTION("Identify keywords")
  {
    const char* sourceCode = "int bool dspl string decimal";
    lexer.scan(sourceCode);

    REQUIRE(lexer.getTokenStream()[0].type == TokenType::KEYWORD_INT);
    REQUIRE(lexer.getTokenStream()[1].type == TokenType::KEYWORD_BOOL);
    REQUIRE(lexer.getTokenStream()[2].type == TokenType::KEYWORD_DSPL);
    REQUIRE(lexer.getTokenStream()[3].type == TokenType::KEYWORD_STRING);
    REQUIRE(lexer.getTokenStream()[4].type == TokenType::KEYWORD_DECIMAL);
  }

  SECTION("Identify a string")
  {
    const char *sourceCode = R"("This is a test string")";

    lexer.scan(sourceCode);
    REQUIRE(lexer.getTokenStream()[0].type == TokenType::STRING);
  }

  SECTION("Identify an empty string")
  {
    const char *sourceCode = R"("")";

    lexer.scan(sourceCode);
    REQUIRE(lexer.getTokenStream()[0].type == TokenType::STRING);
  }

  SECTION("No closing quote - should not identify a string")
  {
    const char *sourceCode = R"("Unclosed string)";

    lexer.scan(sourceCode);
    REQUIRE(lexer.getTokenStream()[0].type != TokenType::STRING);
    REQUIRE(lexer.getTokenStream()[0].type == TokenType::UNKNOWN);
  }

  SECTION("Identify booleans")
  {
    const char* sourceCode = "true false";
    lexer.scan(sourceCode);

    REQUIRE(lexer.getTokenStream()[0].type == TokenType::BOOLEAN);
    REQUIRE(lexer.getTokenStream()[1].type == TokenType::BOOLEAN);
  }

  SECTION("Identify comments")
  {
    const char* sourceCode = R"(
      # This is a comment
      int a = 5; # Another comment
    )";
    lexer.scan(sourceCode);

    REQUIRE(lexer.getTokenStream()[0].type == TokenType::KEYWORD_INT);
    REQUIRE(lexer.getTokenStream()[1].type == TokenType::IDENTIFIER);
    REQUIRE(lexer.getTokenStream()[2].type == TokenType::ASSIGN);
    REQUIRE(lexer.getTokenStream()[3].type == TokenType::INTEGER);
    REQUIRE(lexer.getTokenStream()[4].type == TokenType::SEMICOLON);
  }

  SECTION("Identify whitespaces")
  {
    const char* sourceCode = " \t\n int \t variable \n = \t 5 \t ; \n ";
    lexer.scan(sourceCode);

    REQUIRE(lexer.getTokenStream()[0].type == TokenType::KEYWORD_INT);
    REQUIRE(lexer.getTokenStream()[1].type == TokenType::IDENTIFIER);
    REQUIRE(lexer.getTokenStream()[2].type == TokenType::ASSIGN);
    REQUIRE(lexer.getTokenStream()[3].type == TokenType::INTEGER);
    REQUIRE(lexer.getTokenStream()[4].type == TokenType::SEMICOLON);
  }

  SECTION("Identify unknown tokens")
  {
    const char* sourceCode = "@ $ %";
    lexer.scan(sourceCode);

    REQUIRE(lexer.getTokenStream()[0].type == TokenType::UNKNOWN);
    REQUIRE(lexer.getTokenStream()[1].type == TokenType::UNKNOWN);
    REQUIRE(lexer.getTokenStream()[2].type == TokenType::UNKNOWN);
  }

}
