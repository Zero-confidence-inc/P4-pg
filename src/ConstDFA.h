#ifndef CONST_DFA_H
#define CONST_DFA_H

#include <string>
#include "Token.h"
#include "DFA.h"

class ConstDFA : public DFA {
public:
    ConstDFA();  // Constructor
    bool processChar(char c) override;  // Process the next character
    Token finalizeToken() override;  // Finalize and return the current token
    bool hasToken() const override;  // Check if there is a current token
    void reset() override;  // Reset the DFA to the initial state

private:
    enum class State {
        Start,
        Minus,
        IntegerPart,
        DecimalPart,
        true_1,
        true_2,
        true_3,
        true_4,
        false_1,
        false_2,
        false_3,
        false_4,
        false_5,
        FAIL
    };
    bool isFloatingPoint;
    State currentState;
    std::string currentToken;
    std::string currentString;
};

#endif // CONST_DFA_H