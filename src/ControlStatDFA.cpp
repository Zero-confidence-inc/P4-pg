//
// Created by Yuki on 24/04/2024.
//
#include "ControlStatDFA.h"

ControlStatDFA::ControlStatDFA() : currentState(State::Start) {}

bool ControlStatDFA::processChar(char c) {
    switch (currentState){
        case State::Start:
            if (c == 'i'){
                currentString += c;
                currentState = State::if_1;
                return true;
            }
            else if (c =='e'){
                currentString += c;
                currentState = State::else_1;
                return true;
            }
            else if (c == 's' ){
                currentString += c;
                currentState = State::switch_1;
                return true;
            }
            else if (c == 'c'){
                currentString += c;
                currentState = State::case_1;
                return true;
            }
            else return false;


        case State::if_1:
            if (c == 'f'){
                currentString+= c;
                currentToken = currentString;
                currentState = State::if_2;
                return false;
            }
            else return false;

        case State::else_1:
            if (c == 'l'){
                currentString+= c;
                currentState = State::else_2;
                return true;
            }
            else return false;

        case State::else_2:
            if (c == 's'){
                currentString+= c;
                currentState = State::else_3;
                return true;
            }
            else return false;

        case State::else_3:
            if (c == 'e'){
                currentString+= c;
                currentToken = currentString;
                currentState = State::else_4;
                return false;
            }
            else return false;

        case State::switch_1:
            if (c == 'w'){
                currentString+= c;
                currentState = State::switch_2;
                return true;
            }
            else return false;

        case State::switch_2:
            if (c == 'i'){
                currentString+= c;
                currentState = State::switch_3;
                return true;
            }
            else return false;


        case State::switch_3:
            if (c == 't'){
                currentString+= c;
                currentState = State::switch_4;
            }
            else return false;

        case State::switch_4:
            if (c == 'c'){
                currentString+= c;
                currentState = State::switch_5;
                return true;
            }
            else return false;

        case State::switch_5:
            if (c == 'r'){
                currentString += c;
                currentToken = currentString;
                currentState = State::switch_6;
                return false;
            }
            else return false;
        case State::case_1:
            if (c == 'a'){
                currentString += c;
                currentState = State::case_2;
                return true;
            }
            else return false;


        case State::case_2:
            if (c == 's'){

                currentString += c;
                currentState = State::case_3;
                return true;
            }
            else return false;

        case State::case_3:
            if (c == 'e'){
                currentString += c;
                currentToken = currentString;
                currentState = State::case_4;
                return false;
            }
            else return false;

        default:
            return false;
    }
}

Token ControlStatDFA::finalizeToken(){
    Token token(TokenType::CONTROL, currentToken);
    reset();
    return token;
}

bool ControlStatDFA::hasToken() const {
    return !currentToken.empty();
}

void ControlStatDFA::reset() {
    currentState = State::Start;
    currentString.clear();
    currentToken.clear();
}