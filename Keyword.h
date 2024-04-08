#ifndef KEYWORD_DFA_H
#define KEYWORD_DFA_H

#include "Token.h"

class KeywordDFA : public DFA {
public:
    Token tokenize(const std::string& input);
};

#endif // KEYWORD_H