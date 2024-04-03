#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    IDENTIFIER,
    CONST,
    OPERATOR, 
    EOF_TOKEN,
    PPUNCTUATION
};

struct Token {
    TokenType type;
    std::string value;

    Token(TokenType t, const std::string& v) : type(t), value(v) {}
};

#endif 