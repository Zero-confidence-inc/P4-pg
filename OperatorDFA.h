#ifndef OPERATOR_DFA_H
#define OPERATOR_DFA_H

#include "Token.h"

class OperatorDFA {
public:
    Token tokenize(const std::string& input);
};

#endif // OPERATOR_DFA_H