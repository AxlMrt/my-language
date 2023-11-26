#define CATCH_CONFIG_MAIN
#include <iostream>
#include <catch2/catch.hpp>

#include "../include/Lexer.h"

TEST_CASE("Lexer::scanIdentifier() correctly tokenizes identifiers")
{
  Lexer lexer;
  Token tokens[50];
  Token *ptr_tokens = tokens;

  SECTION("Single identifier")
  {
    const char *identifier = "variable";    
    lexer.scanIdentifierOrKeyword(identifier, ptr_tokens);
    REQUIRE(tokens[0].type == TokenType::IDENTIFIER);
  }

  SECTION("Multiple identifiers")
  {
    const char *identifier = "variable1 var_2 anotherVar int_var string_var bool_var DECIMAL_var var124" ;
    lexer.scanIdentifierOrKeyword(identifier, ptr_tokens);
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

TEST_CASE("Lexer::scanKeywords() test cases")
{
  Lexer lexer;
  Token tokens[MAX_TOKENS];

  SECTION("Identify 'int' keyword")
  {
    const char *sourceCode = "int";
    const char *currentChar = sourceCode;

    lexer.scanIdentifierOrKeyword(currentChar, tokens);

    REQUIRE(tokens[0].type == TokenType::KEYWORD_INT);
    REQUIRE(strcmp(tokens[0].lexeme, "int") == 0);
  }

  SECTION("Identify 'decimal' keyword in a larger context")
  {
    const char *sourceCode = "int decimal x";
    const char *currentChar = sourceCode + 4;

    lexer.scanIdentifierOrKeyword(currentChar, tokens);

    REQUIRE(tokens[1].type == TokenType::KEYWORD_DECIMAL);
    REQUIRE(strcmp(tokens[1].lexeme, "decimal") == 0);
  }

  SECTION("Identify 'string' keyword")
  {
    const char *sourceCode = "string x";
    const char *currentChar = sourceCode;

    lexer.scanIdentifierOrKeyword(currentChar, tokens);

    REQUIRE(tokens[0].type == TokenType::KEYWORD_STRING);
    REQUIRE(strcmp(tokens[0].lexeme, "string") == 0);
  }

  SECTION("Identify 'bool' keyword at the end of the code")
  {
    const char *sourceCode = "x = true bool";
    const char *currentChar = sourceCode + 9;

    lexer.scanIdentifierOrKeyword(currentChar, tokens);

    REQUIRE(tokens[0].type == TokenType::KEYWORD_BOOL);
    REQUIRE(strcmp(tokens[0].lexeme, "bool") == 0);
  }

  SECTION("Identify 'dspl' keyword with a mix of characters")
  {
    const char *sourceCode = "dspl;print(dspl)";
    const char *currentChar = sourceCode;

    lexer.scanIdentifierOrKeyword(currentChar, tokens);

    REQUIRE(tokens[0].type == TokenType::KEYWORD_DSPL);
    REQUIRE(strcmp(tokens[0].lexeme, "dspl") == 0);
  }
}


TEST_CASE("Lexer::scanStrings() test cases")
{
  Lexer lexer;
  Token tokens[MAX_TOKENS];

  SECTION("Identify a string")
  {
    const char *sourceCode = R"("This is a test string")";
    const char *currentChar = sourceCode;

    lexer.scanStrings(currentChar, tokens);

    REQUIRE(tokens[0].type == TokenType::STRING);
    REQUIRE(strcmp(tokens[0].lexeme, "This is a test string") == 0);
  }

  SECTION("Identify an empty string")
  {
    const char *sourceCode = R"("")";
    const char *currentChar = sourceCode;

    lexer.scanStrings(currentChar, tokens);

    REQUIRE(tokens[0].type == TokenType::STRING);
    REQUIRE(strcmp(tokens[0].lexeme, "") == 0);
  }

  SECTION("No closing quote - should not identify a string")
  {
    const char *sourceCode = R"("Unclosed string)";
    const char *currentChar = sourceCode;

    lexer.scanStrings(currentChar, tokens);

    REQUIRE(tokens[0].type != TokenType::STRING);
  }
}

TEST_CASE("Lexer::scanBool() test cases")
{
  Lexer lexer;
  Token tokens[MAX_TOKENS];

  SECTION("Identify 'true' boolean")
  {
    const char *sourceCode = "true";
    const char *currentChar = sourceCode;

    lexer.scanBool(currentChar, tokens);

    REQUIRE(tokens[0].type == TokenType::BOOLEAN);
    REQUIRE(strcmp(tokens[0].lexeme, "true") == 0);
  }

  SECTION("Identify 'false' boolean") {
    const char *sourceCode = "false";
    const char *currentChar = sourceCode;

    lexer.scanBool(currentChar, tokens);

    REQUIRE(tokens[0].type == TokenType::BOOLEAN);
    REQUIRE(strcmp(tokens[0].lexeme, "false") == 0);
  }
}

TEST_CASE("Lexer::scanWhiteSpaceAndComment() tests") {
    Lexer lexer;

    SECTION("Skipping white spaces") {
        const char* sourceCode = "     a + b";
        lexer.scanWhiteSpaceAndComment(sourceCode);
        REQUIRE(*sourceCode == 'a');
    }

    SECTION("Skipping comments") {
        const char* sourceCode = "# This is a comment\na + b";
        lexer.scanWhiteSpaceAndComment(sourceCode);
        REQUIRE(*sourceCode == 'a');
    }

    SECTION("Skipping both white spaces and comments") {
        const char* sourceCode = "     # Comment\na + b";
        lexer.scanWhiteSpaceAndComment(sourceCode);
        REQUIRE(*sourceCode == 'a');
    }

    SECTION("Skipping no spaces or comments") {
        const char* sourceCode = "a + b";
        lexer.scanWhiteSpaceAndComment(sourceCode);
        REQUIRE(*sourceCode == 'a');
    }
}

TEST_CASE("Lexer::scan() test cases") {
    Lexer lexer;
    Token tokens[MAX_TOKENS];

    SECTION("Simple expression with identifiers and operators") {
        const char* sourceCode = "a + b * 123";
        lexer.scan(sourceCode, tokens);

        // Vérifie les tokens identifiés dans l'expression simple
        REQUIRE(tokens[0].type == TokenType::IDENTIFIER);
        REQUIRE(strcmp(tokens[0].lexeme, "a") == 0);
        std::cout << tokens[0].lexeme << std::endl;

        REQUIRE(tokens[1].type == TokenType::PLUS);

        REQUIRE(tokens[2].type == TokenType::IDENTIFIER);
        REQUIRE(strcmp(tokens[2].lexeme, "b") == 0);

        REQUIRE(tokens[3].type == TokenType::MULTIPLY);

        REQUIRE(tokens[4].type == TokenType::INTEGER);
        REQUIRE(strcmp(tokens[4].lexeme, "123") == 0);
    }

    SECTION("Ignored comments") {
        const char* sourceCode = "a + b # comment\nc * 123";
        lexer.scan(sourceCode, tokens);

        // Vérifie que les commentaires sont ignorés et les tokens sont identifiés correctement
        REQUIRE(tokens[0].type == TokenType::IDENTIFIER);
        REQUIRE(strcmp(tokens[0].lexeme, "a") == 0);

        REQUIRE(tokens[1].type == TokenType::PLUS);

        REQUIRE(tokens[2].type == TokenType::IDENTIFIER);
        REQUIRE(strcmp(tokens[2].lexeme, "b") == 0);

        REQUIRE(tokens[3].type == TokenType::MULTIPLY);

        REQUIRE(tokens[4].type == TokenType::IDENTIFIER);
        REQUIRE(strcmp(tokens[4].lexeme, "c") == 0);

        REQUIRE(tokens[5].type == TokenType::MULTIPLY);

        REQUIRE(tokens[6].type == TokenType::INTEGER);
        REQUIRE(strcmp(tokens[6].lexeme, "123") == 0);
    }

    SECTION("Empty source code") {
        const char* sourceCode = "";
        lexer.scan(sourceCode, tokens);

        // Vérifie qu'aucun token n'est généré pour une chaîne vide
        REQUIRE(tokens[0].type == TokenType::END_OF_FILE);
        REQUIRE(strcmp(tokens[0].lexeme, "") == 0);
    }

    // Ajoute d'autres sections pour les autres scénarios de test...
}
