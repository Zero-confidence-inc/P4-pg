//
// Created by Yuki on 29/04/2024.
//

#ifndef JumpStat_DFA_H
#define JumpStat_DFA_H

#include "Token.h"
#include "DFA.h"
#include <string>

class JumpStatDFA : public DFA {
public:
    JumpStatDFA();
    bool processChar(char c) override;
    Token finalizeToken() override;
    bool hasToken() const override;
    void reset() override;

private:
    enum class State{
        Start,
        break_1,
        break_2,
        break_3,
        break_4,
        break_5,
        continue_1,
        continue_2,
        continue_3,
        continue_4,
        continue_5,
        continue_6,
        continue_7,
        continue_8,
        return_1,
        return_2,
        return_3,
        return_4,
        return_5,
        return_6,
        FAIL
    };

    State currentState;
    std::string currentString;
    std::string currentToken;
};

#endif //JumpStat_DFA_H