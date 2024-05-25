#include "ConsoleDFA.h"

ConsoleDFA::ConsoleDFA() : currentState(State::Start) {}

bool ConsoleDFA::processChar(char c) {
    switch (currentState){
        case State::Start:
            if (c == 'c'){
                currentString += c;
                currentState = State::Console_1;
                return true;
            }else{
                currentState = State::FAIL;
                return false;
            }
        case State::Console_1:
            if (c == 'o'){
                currentString += c;
                currentState = State::Console_2;
                return true;
            }
            else return false;

        case State::Console_2:
            if (c == 'n'){
                currentString+= c;
                currentState = State::Console_3;
                return true;
            }
            else return false;

        case State::Console_3:
            if (c == 's'){
                currentString+= c;
                currentState = State::Console_4;
                return true;
            }
            else return false;

        case State::Console_4:
            if (c == 'o'){
                currentString+= c;
                currentState = State::Console_5;
                return true;
            }
            else return false;

        case State::Console_5:
            if (c == 'l'){
                currentString += c;
                currentToken = currentString;
                currentState = State::Console_6;
                return true;
            }
            else return false;
        case State::Console_6:
            if (c == 'e'){
                currentString += c;
                currentToken = currentString;
                currentState = State::Console_7;
                return false;
            }
            else return false;

        default:
            return false;
    }
}

Token ConsoleDFA::finalizeToken(){
    Token token(TokenType::CONSOLE, currentToken);
    reset();
    return token;
}

bool ConsoleDFA::hasToken() const {
    return !currentToken.empty();
}

void ConsoleDFA::reset() {
    currentState = State::Start;
    currentString.clear();
    currentToken.clear();
}