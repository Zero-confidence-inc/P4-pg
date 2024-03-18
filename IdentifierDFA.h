#ifndef IDENTIFIER_DFA_H
#define IDENTIFIER_DFA_H

#include "Token.h"

class IdentifierDFA {
public:
    Token tokenize(const std::string& input);
};

#endif // IDENTIFIER_DFA_H