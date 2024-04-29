//
// Created by Yuki on 29/04/2024.
//

#include "LoopStatDFA.h"

LoopStatDFA::LoopStatDFA() : currentState(State::Start) {}

bool LoopStatDFA::processChar(char c) {
    switch (currentState){
        case State::Start:
            if (c == 'f'){
                currentString += c;
                currentState = State::for_1;
                return true;
            }
            else if (c =='w'){
                currentString += c;
                currentState = State::while_1;
                return true;
            }
            else if (c == 'd' ){
                currentString += c;
                currentState = State::do_1;
                return true;
            }
            else return false;


        case State::do_1:
            if (c == 'o'){
                currentString+= c;
                currentToken = currentString;
                currentState = State::do_2;
                return false;
            }
            else return false;

        case State::while_1:
            if (c == 'h'){
                currentString+= c;
                currentState = State::while_2;
                return true;
            }
            else return false;

        case State::while_2:
            if (c == 'i'){
                currentString+= c;
                currentState = State::while_3;
                return true;
            }
            else return false;

        case State::while_3:
            if (c == 'l'){
                currentString+= c;
                currentState = State::while_4;
                return true;
            }
            else return false;

        case State::while_4:
            if (c == 'e'){
                currentString+= c;
                currentToken = currentString;
                currentState = State::while_5;
                return false;
            }
            else return false;

        case State::for_1:
            if (c == 'o'){
                currentString+= c;
                currentState = State::for_2;
                return true;
            }
            else return false;

        case State::for_2:
            if (c == 'r'){
                currentString+= c;
                currentToken = currentString;
                currentState = State::for_3;
                return true;
            }
            else return false;

        default:
            return false;
    }
}

Token LoopStatDFA::finalizeToken(){
    Token token(TokenType::CONTROL, currentToken);
    reset();
    return token;
}

bool LoopStatDFA::hasToken() const {
    return !currentToken.empty();
}

void LoopStatDFA::reset() {
    currentState = State::Start;
    currentString.clear();
    currentToken.clear();
}