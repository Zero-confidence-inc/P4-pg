#ifndef Console_DFA_H
#define Console_DFA_H

#include "Token.h"
#include "DFA.h"
#include <string>

class ConsoleDFA : public DFA {
public:
    ConsoleDFA();
    bool processChar(char c) override;
    Token finalizeToken() override;
    bool hasToken() const override;
    void reset() override;

private:
    enum class State{
        Start,
        Console_1,
        Console_2,
        Console_3,
        Console_4,
        Console_5,
        Console_6,
        Console_7
        };

    State currentState;
    std::string currentString;
    std::string currentToken;
};

#endif //Console_DFA_H