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
    REQUIRE(lexer.getTokenStream()[7].type == TokenType::UNKNOWN);
  }

  // Other test sections for operators, keywords, strings, booleans, etc.
}
