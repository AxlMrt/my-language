#include <iostream>
#include <fstream>
#include "../include/Lexer.h"

using namespace std;

const char *tokenNames[] = {
    "IDENTIFIER",
    "INTEGER",
    "DECIMAL",
    "STRING",
    "CHARACTER",
    "BOOLEAN",
    "PLUS",
    "MINUS",
    "MULTIPLY",
    "DIVIDE",
    "SEMICOLON",
    "COLON",
    "COMMA",
    "LPAREN",
    "RPAREN",
    "LBRACE",
    "RBRACE",
    "ASSIGN",
    "UNKNOWN",
    "KEYWORD_INT",
    "KEYWORD_DECIMAL",
    "KEYWORD_BOOL",
    "KEYWORD_STRING",
    "KEYWORD_DSPL",
    "END_OF_FILE"
};

int main()
{
  ifstream file("test.txt");
  string content;

  if (file.is_open()) {
    string line;
    while (getline(file, line))
      content += line + '\n';
        
    file.close();
  } else {
    cerr << "Erreur lors de l'ouverture du fichier syntax.txt" << endl;
    return 1;
  }

  Lexer lexer;
  lexer.scan(content.c_str());

  Token *tokens = lexer.getTokenStream();
  int count = lexer.getTokenCount();

  for (int i = 0; i < count; ++i)
    cout << "Token type: " << tokenNames[static_cast<int>(tokens[i].type)] << ", Lexeme: " << tokens[i].lexeme << endl;

  delete[] tokens;

  return 0;
}
