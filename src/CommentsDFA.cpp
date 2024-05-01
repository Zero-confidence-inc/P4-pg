//
// Created by Tobias on 01/05/2024.
//
#include "CommentsDFA.h"
CommentsDFA::CommentsDFA() : currentState(State::Start) {}

bool CommentsDFA::processChar(char c) {
    switch (currentState){
        case State::Start:

            if (c == '/')
            {
                currentString += c; //changed to currentString instead of token cus token isn't recognized yet
                currentState = State::SingleLine_started;
                return true;
            } else if (c == '*')
            {
                currentString += c;
                currentState = State::MultiLine_started;
                return true;
            }
            else return false;
        case State::SingleLine_started: //new case to recognize full singleLine token
            if(c == '/')
            {
                currentString += c;
                currentToken = currentString;
                currentState = State::SingleLine_Called;
                return false; //return false as we recognize token and can't accept any future input without reset
            }
            else return false;

        case State::MultiLine_started: // same as above case but for multiline
            if(c == '/')
            {
                currentString += c;
                currentToken = currentString;
                currentState = State::MultiLine_Called;
                return false; //return false as we recognize token and can't accept any future input without reset
            }
            else return false;

        default: return false;
    }


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
        currentString.clear();//added clear for new sting variable
    }