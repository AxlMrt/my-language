# Lexer
This project consists of a lexer that tokenizes source code into meaningful units in C++.

## Files and Directory Structure
### Source Files

- **Lexer.cpp**: Contains the implementation of the lexer class methods.
- **Utils.cpp**: Contains utility functions utilized by the lexer.
- **main.cpp**: The main program to test the lexer.

### Header Files

- **Lexer.h**: Contains the declaration of the Lexer class and token-related structures.
- **Utils.h**: Holds the function declarations for utility operations used by the lexer.

### Test Suite

- **lexer_tests.cpp**: Contains the Catch2 test suite for validating lexer functionality.

## Running Tests

To execute tests:

```bash
clang++ -std=c++11 -Wall -Wextra -o lexer_tests ./lexer/tests/lexer_tests.cpp ./lexer/src/Lexer.cpp ./lexer/src/Utils.cpp -I ./lexer/src/headers && ./lexer_tests
```

## Running the Lexer

To run the lexer on a file:

```bash
clang++ ./lexer/src/main.cpp ./lexer/src/Lexer.cpp ./lexer/src/Utils.cpp -o lexer && ./lexer
```



## Token Types

The lexer categorizes tokens into various types, including:
- IDENTIFIER
- INTEGER
- DECIMAL
- STRING
- CHARACTER
- BOOLEAN
- Operators (+, -, *, /, =, :, ;, (, ), {, })
- Keywords (int, decimal, string, bool, dspl)

## Usage

- Instantiate the Lexer class.
- Use the `scan()` method to tokenize source code and obtain tokens.
- Tokens can be accessed for analysis or further processing.

Feel free to explore the source code for more details about usage and implementation.
