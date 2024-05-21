// TokenCreator.h
#ifndef TOKEN_CREATOR_H
#define TOKEN_CREATOR_H

#include "Token.h"

inline Token createToken(TokenType type, const std::string& value) {
    Token token;
    token.type = type;
    token.value = value;
    return token;
}

#endif // TOKEN_CREATOR_H
