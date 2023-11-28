CC=clang++
CFLAGS=-std=c++11 -Wall -Wextra

SRCDIR=./parser/src/
LEXDIR=./lexer/src/
LEXTESTDIR=./lexer/tests/

LEXERSOURCES=$(LEXDIR)Lexer.cpp $(LEXDIR)Utils.cpp
LEXERTESTSOURCES=$(LEXTESTDIR)lexer_tests.cpp $(LEXERSOURCES)

SOURCES=$(SRCDIR)main.cpp $(LEXERSOURCES) $(SRCDIR)Parser.cpp $(SRCDIR)DisplayHandler.cpp $(SRCDIR)VariableHandler.cpp

all: parse_test lexer_tests

parse_test: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o parse_test

lexer_tests: $(LEXERTESTSOURCES)
	$(CC) $(CFLAGS) $(LEXERTESTSOURCES) -I$(LEXDIR)headers -o lexer_tests && ./lexer_tests

clean:
	rm -f parse_test lexer_tests
