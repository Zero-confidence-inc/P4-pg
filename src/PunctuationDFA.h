#ifndef PUNCTUATION_DFA_H
#define PUNCTUATION_DFA_H

#include "DFA.h"
#include "Token.h"
#include <string>

class PunctuationDFA : public DFA{
public:
    PunctuationDFA();
    bool processChar(char c) override;
    Token finalizeToken() override;
    bool hasToken() const override;
    void reset() override;

private: 
    enum class State{
        Start,
        Punctuation_confirmed

    };

    State currentState;
    std::string currentToken;

};

#endif // Punctuation_DFA_H