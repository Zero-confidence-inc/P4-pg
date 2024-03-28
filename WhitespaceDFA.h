#ifndef WHITESPACE_DFA_H
#define WHITESPACE_DFA_H

#include "Token.h"

class WhitespaceDFA {
public:
    Token tokenize(const std::string& input);
};

#endif // WHITESPACE_DFA_H