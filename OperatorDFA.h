#ifndef OPERATOR_DFA_H
#define OPERATOR_DFA_H

#include "DFA.h"
#include "Token.h"
#include <string>

class OperatorDFA : public DFA {
public:
    OperatorDFA();
    bool processChar(char c) override;
    Token finalizeToken() override;
    bool hasToken() const override;
    void reset() override;

private:
    enum class State {
        Start,
        Operator,
        Minus_operator,
        Plus_operator,
        Measuring_operator,
        And_operator,
        Or_operator
    };

    State currentState;
    std::string currentToken;
};

#endif // OPERATOR_DFA_H
