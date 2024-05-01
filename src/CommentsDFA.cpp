//
// Created by Tobias on 01/05/2024.
//
#include "CommentsDFA.h"
CommentsDFA::CommentsDFA() : currentState(State::Start) {}

bool CommentsDFA::processChar(char c) {
    switch (currentState){
        case State::Start:

            if (c == '//')
            {
                currentToken += c;
                currentState = State::SingleLine_started;
                return true;
            } else if (c == '*/')
            {
                currentToken += c;
                currentState = State::MultiLine_started;
                return true;
            }
            else return false;
        default: return false;
    }


    Token CommentsDFA::finalizeToken() {
        Token token(TokenType::COMMENTS, currentToken);
        reset();
        return token;
    }

    bool CommentsDFA::hasToken() const {
        return !currentToken.empty();
    }

    void CommentsDFA::reset() {
        currentState = State::Start;
        currentToken.clear();
    }