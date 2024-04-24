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
    PHT, // don't even remember what this was supposed to mean
    FLOAT_CONST
};

struct Token {
    TokenType type;
    std::string value;

    //default token constructor
    Token() : type(TokenType::PHT), value(""){}

    //parameterized constructor (please use this one when possible)
    Token(TokenType t, const std::string& v) : type(t), value(v) {}

    const std::string& getText() const { return value; }
    TokenType getType() const { return type; }
};

#endif 