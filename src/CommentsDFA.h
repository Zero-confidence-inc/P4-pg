//
// Created by Tobias on 01/05/2024.
//

#ifndef COMMENTS_DFA_H
#define COMMENTS_DFA_H

#include "DFA.h"
#include "Token.h"
#include <string>

class CommentsDFA : public DFA{
public:
    CommentsDFA();
    bool processChar(char c) override;
    Token finalizeToken() override;
    bool hasToken() const override;
    void reset() override;

private:
    enum class State{
        Start,
        SingleLine_started,
        MultiLine_started

    };

    State currentState;
    std::string currentToken;

};

#endif // Comments_DFA_h