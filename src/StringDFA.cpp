#include "StringDFA.h"

StringDFA::StringDFA() : currentState(State::Start) {}

bool StringDFA::processChar(char c) {
    const std::regex pattern("[^ \'\"]");
    switch (currentState){
        case State::Start:
            if (c == '"'){
                currentString += c;
                currentState = State::Content;
                return true;
            }else if (c == '\''){
                currentString += c;
                currentState = State::ContentAlt;
                return true;
            }
            else return false;
        
        case State::Content:
            if (c == '"'){
                currentString += c;
                currentToken = currentString;
                currentState = State::End;
                return false;
            }

            else if (isalnum(c)|| c == ' '){
                currentString += c;
                currentState = State::Content;
                return true;
            }
            else return false;

        case State::ContentAlt:
            if (c == '\''){
                currentString += c;
                currentToken = currentString;
                currentState = State::End;
                return false;
            }

            else if (isalnum(c)|| c == ' '){
                currentString += c;
                currentState = State::ContentAlt;
                return true;
            }
            else return false;
        default: return false;
    }
}

Token StringDFA::finalizeToken() {
    Token token(TokenType::STRING, currentToken);
    reset();
    return token;
}

bool StringDFA::hasToken() const {
    return !currentToken.empty();
}

void StringDFA::reset(){
    currentState = State::Start;
    currentString.clear();
    currentToken.clear();
}