#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    IDENTIFIER,
    CONST,
    OPERATOR, 
    EOF_TOKEN,
    PUNCTUATION,
    STRING,
    KEYWORD,
    WHITESPACE,
    PHT
};

struct Token {
    TokenType type;
    std::string value;

    //default token constructor
    Token() : type(TokenType::PHT), value(""){}

    //parameterized constructor (please use this one when possible)
    Token(TokenType t, const std::string& v) : type(t), value(v) {}
};

#endif 