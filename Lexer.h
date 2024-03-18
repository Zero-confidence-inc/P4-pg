#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include "IdentifierDFA.h"
#include "NumberDFA.h"
#include <vector>

class Lexer {
public:
    Lexer();
    std::vector<Token> tokenize(const std::string& input);

private:
    IdentifierDFA identifierDFA;
    NumberDFA numberDFA;
    // Add more DFAs as needed
};

#endif // LEXER_H
