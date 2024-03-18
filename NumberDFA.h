#ifndef NUMBER_DFA_H
#define NUMBER_DFA_H

#include "Token.h"

class NumberDFA {
public:
    Token tokenize(const std::string& input);
};

#endif // NUMBER_DFA_H
