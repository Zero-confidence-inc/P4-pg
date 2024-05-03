//
// Created by Tobias on 01/05/2024.
//
#include "CommentsDFA.h"
CommentsDFA::CommentsDFA() : currentState(State::Start) {}

bool CommentsDFA::processChar(char c) {
    switch (currentState){
        case State::Start:

            if (c == '/'){
                currentString += c;
                currentState = State::CommentStarted;
                return true;
            }
            else return false;
        case State::CommentStarted:
            if(c == '/'){
                currentString += c;
                currentToken = currentString;
                currentState = State::SingleLineCalled;
                return false;
            }
            else if (c=='*'){
                currentString+= c;
                currentState = State::MultiLineContent;
                return true;
            }
            else return false;

        case State::MultiLineContent:
            if(isalnum(c)|| c == ' '|| c == '\n' || c == '\t'){
                currentString += c;
                currentState = State::MultiLineContent;
                return true;
            }
            else if(c == '*'){
                currentString += c;
                currentState = State::MultiLineEnd1;
                return true;
            }
            else return false;
        case State::MultiLineEnd1:
            if(c == '/'){
                currentString += c;
                currentToken = currentString;
                currentState = State::MultiLineEnd2;
                return false;
            }
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