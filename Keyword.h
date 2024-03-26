#ifndef KEYWORD_H
#define KEYWORD_H

#include "Token.h"

class Keyword {
public:
    Token tokenize(const std::string& input);
};

#endif // KEYWORD_H