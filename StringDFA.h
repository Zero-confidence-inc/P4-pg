#ifndef STRING_DFA_H
#define STRING_DFA_H

#include "Token.h"

class StringDFA : public DFA{
public:
    Token tokenize(const std::string& input);
};

#endif // STRING_DFA_H