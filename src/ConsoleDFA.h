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
        C_1,
        Cin_1,
        Cin_2,
        Cout_1,
        Cout_2,
        Cout_3,
        FAIL
    };

    State currentState;
    std::string currentString;
    std::string currentToken;
};

#endif //Console_DFA_h