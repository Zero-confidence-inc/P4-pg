#ifndef WHITESPACE_DFA_H
#define WHITESPACE_DFA_H

#include "DFA.h"
#include "Token.h"
#include <string>

class WhitespaceDFA : public DFA {
public:
    WhitespaceDFA();
    bool processChar(char c) override;
    Token finalizeToken() override;
    bool hasToken() const override;
    void reset() override;

private:
    enum class State{
        Start,
        Whitespace,
        FAIL
    };

    State currentState;
    std::string currentToken;

};

#endif // WHITESPACE_DFA_H