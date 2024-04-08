#ifndef IDENTIFIER_DFA_H
#define IDENTIFIER_DFA_H

#include "Token.h"

class IdentifierDFA {
public:
    IdentifierDFA();
    bool processChar(char c) override;
    Token finalizeToken() override;
    bool hasToken() const override;
    void reset() override;
private:
    enum class State{
    Start,
    Working
    };
    State currentState;
    std::string currentToken;
};

#endif // IDENTIFIER_DFA_H
