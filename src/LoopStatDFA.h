//
// Created by Yuki on 29/04/2024.
//
#ifndef LoopStat_DFA_H
#define LoopStat_DFA_H

#include "Token.h"
#include "DFA.h"
#include <string>

class LoopStatDFA : public DFA {
public:
    LoopStatDFA();
    bool processChar(char c) override;
    Token finalizeToken() override;
    bool hasToken() const override;
    void reset() override;

private:
    enum class State{
        Start,
        for_1,
        for_2,
        for_3,
        while_1,
        while_2,
        while_3,
        while_4,
        while_5,
        do_1,
        do_2,
        FAIL
    };

    State currentState;
    std::string currentString;
    std::string currentToken;
};

#endif //loopStat_DFA_H