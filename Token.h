#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    IDENTIFIER,
    NUMBER, 
    EOF_TOKEN,
    STRING
};

struct Token {
    TokenType type;
    std::string value;
};

#endif 