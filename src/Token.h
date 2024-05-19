#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    IDENTIFIER,
    CONST,
    OPERATOR, 
    EOF_TOKEN,// also not used
    PUNCTUATION,
    STRING,
    TYPE,
    WHITESPACE,
    PHT, //not used disregard
    FLOAT_CONST,
    CONTROL,
    LOOP,
    JUMP,
    COMMENTS,
    CONSOLE,
    BOOL,
    START
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