#ifndef ControlStatDFA_DFA_H
#define ControlStatDFA_DFA_H

#include "Token.h"
#include "DFA.h"
#include <string>

class ControlStatDFA : public DFA {
public:
    ControlStatDFA();
    bool processChar(char c) override;
    Token finalizeToken() override;
    bool hasToken() const override;
    void reset() override;

private:
    enum class State{
        Start,
        if_1,
        if_2,
        else_1,
        else_2,
        else_3,
        else_4,
        switch_1,
        switch_2,
        switch_3,
        switch_4,
        switch_5,
        switch_6,
        case_1,
        case_2,
        case_3,
        case_4
    };

    State currentState;
    std::string currentString;
    std::string currentToken;
};

#endif //ControlStatDFA_H