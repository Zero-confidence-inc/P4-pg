#ifndef BOOL_DFA_H
#define BOOL_DFA_H

#include <string>
#include "Token.h"
#include "DFA.h"

class BOOLDFA : public DFA {
public:
    BOOLDFA();  // Constructor
    bool processChar(char c) override;  // Process the next character
    Token finalizeToken() override;  // Finalize and return the current token
    bool hasToken() const override;  // Check if there is a current token
    void reset() override;  // Reset the DFA to the initial state

private:
    enum class State {
        Start,
        T,
        TR,
        TRU,
        TRUE,
        F,
        FA,
        FAL,
        FALS,
        FALSE,
        
    };
    State currentState;
    std::string currentToken;
    std::string currentString;
};

#endif // BOOL_DFA_H
