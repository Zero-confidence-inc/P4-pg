#include "ConsoleDFA.h"
#include <iostream>

ConsoleDFA::ConsoleDFA() : currentState(State::Start) {}

bool ConsoleDFA::processChar(char c) {
    switch (currentState){
        case State::Start:
            if (c == 'c'){
                currentString += c;
                currentState = State::C_1;
                return true;
            }else{
                currentState = State::FAIL;
                return false;
            }
        case State::C_1:
            if (c == 'o'){
                currentString += c;
                currentState = State::Cout_1;
                return true;
            }
            else if (c == 'i'){
                currentString += c;
                currentState = State::Cin_1;
                return true;
            } else return false;

        case State::Cout_1:
            if (c == 'u'){
                currentString+= c;
                currentState = State::Cout_2;
                return true;
            }
            else return false;

        case State::Cout_2:
            if (c == 't'){
                currentString+= c;
                currentToken=currentString;
                currentState = State::Cout_3;
                return false;
            }
            else return false;

        case State::Cin_1:
            if (c == 'n'){
                currentString+= c;
                currentToken = currentString;
                currentState = State::Cin_2;
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