#ifndef CONST_DFA_H
#define CONST_DFA_H

#include "Token.h"

class ConstDFA : public DFA{
public:
    Token tokenize(const std::string& input);
};

#endif // CONST_DFA_H