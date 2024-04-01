#ifndef PUNCTUATION_DFA_H
#define PUNCTUATION_DFA_H

#include "Token.h"

class PunctuationDFA {
public:
    Token tokenize(const std::string& input);
};

#endif // Punctuation_DFA_H