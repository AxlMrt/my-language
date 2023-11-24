#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "../include/Lexer.h"


TEST_CASE("Lexer::getNextToken() test cases") {
    Lexer lexer;

    SECTION("Retrieve all tokens") {
        const char* sourceCode = "identifier123 + 3.14";
        Token tokens[MAX_TOKENS];

        lexer.scan(sourceCode, tokens);

        Token retrievedToken;
        int tokensCount = 0;
        Token* allTokens = lexer.getAllTokens(tokensCount);
  for (int i = 0; i < tokensCount; ++i) {
    bool success = lexer.getNextToken(retrievedToken);
    REQUIRE(success);
    REQUIRE(retrievedToken.type == allTokens[i].type);
    REQUIRE(strcmp(retrievedToken.lexeme, allTokens[i].lexeme) == 0); // Comparaison de chaînes

    if (i == tokensCount - 1) {
        bool noMoreTokens = lexer.getNextToken(retrievedToken);
        REQUIRE_FALSE(noMoreTokens); // Vérifie qu'aucun autre token n'est récupéré après le dernier
    }
  }

        bool lastToken = lexer.getNextToken(retrievedToken);
        REQUIRE_FALSE(lastToken); // Vérifie que false est retourné après avoir récupéré tous les tokens
    }

    SECTION("Get token when no tokens available") {
        Token retrievedToken;
        bool success = lexer.getNextToken(retrievedToken);
        REQUIRE_FALSE(success); // Vérifie que false est retourné lorsqu'aucun token n'est disponible
    }
}

TEST_CASE("Lexer::getAllTokens() test cases")
{
}

TEST_CASE("Lexer::revertToPreviousToken() test cases")
{
}
