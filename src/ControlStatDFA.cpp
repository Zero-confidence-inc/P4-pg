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
            else if (c == 'f') {
                currentString += c;
                currentState = State::function_1;
                return true;
            }
            else if (c == 'd') {
                currentString += c;
                currentState = State::default_1;
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

        case State::default_1:
            if (c == 'e') {
                currentString += c;
                currentState = State::default_2;
                return true;
            }
            else return false;

        case State::default_2:
            if (c == 'f') {
                currentString += c;
                currentState = State::default_3;
                return true;
            }
            else return false;

        case State::default_3:
            if (c == 'a') {
                currentString += c;
                currentState = State::default_4;
                return true;
            }
            else return false;

        case State::default_4:
            if (c == 'u') {
                currentString += c;
                currentState = State::default_5;
                return true;
            }
            else return false;

        case State::default_5:
            if (c == 'l') {
                currentString += c;
                currentState = State::default_6;
                return true;
            }
            else return false;

        case State::default_6:
            if (c == 't') {
                currentString += c;
                currentToken = currentString;
                currentState = State::default_7;
                return false;
            }
            else return false;


        case State::function_1:
            if (c == 'u') {
                currentString += c;
                currentState = State::function_2;
                return true;
            }
            else return false;

        case State::function_2:
            if (c == 'n') {
                currentString += c;
                currentState = State::function_3;
                return true;
            }
            else return false;

        case State::function_3:
            if (c == 'c') {
                currentString += c;
                currentState = State::function_4;
                return true;
            }
            else return false;

        case State::function_4:
            if (c == 't') {
                currentString += c;
                currentState = State::function_5;
                return true;
            }
            else return false;

        case State::function_5:
            if (c == 'i') {
                currentString += c;
                currentState = State::function_6;
                return true;
            }
            else return false;

        case State::function_6:
            if (c == 'o') {
                currentString += c;
                currentState = State::function_7;
                return true;
            }
            else return false;

        case State::function_7:
            if (c == 'n') {
                currentString += c;
                currentToken = currentString;
                currentState = State::function_8;
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