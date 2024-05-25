#include "ConstDFA.h"
#include <ctype.h>

ConstDFA::ConstDFA() : currentState(State::Start), isFloatingPoint(false) {}

bool ConstDFA::processChar(char c) {
    switch (currentState){
        case State::Start:
            if (isdigit(c)) {
                currentString += c;
                currentToken = currentString;
                currentState = State::IntegerPart;
                return true;
            } else if (c == '-') {
                currentString += c;
                currentState = State::Minus;
                return true;
            } else if (c == 't') {
                currentString += c;
                currentState = State::true_1;
                return true;
            } else if (c == 'f') {
                currentString += c;
                currentState = State::false_1;
                return true;
            }else{
                currentState = State::FAIL;
                return false;
            }

        case State::Minus:
            if (isdigit(c)) {
                currentString += c;
                currentToken = currentString;
                currentState =State::IntegerPart;
                return true;
            } else {
                return false;
            }

        case State::IntegerPart:
            if (isdigit(c)) {
                currentString += c;
                currentToken = currentString;
                return true;
            } else if (c == '.') {  // Decimal point encountered
                currentString += c;
                currentState = State::DecimalPart;
                isFloatingPoint = true;  // Mark as floating point
                return true;
            } else {
                return false;
            }

        case State::DecimalPart:
            if (isdigit(c)) {
                currentString += c;
                currentToken = currentString;
                return true;
            } else {
                return false;
            }



        case State::false_1: {
            if (c == 'a'){
                currentString += c;
                currentState = State::false_2;
                return true;
            }else{
                return false;
            }
        }

        case State::false_2: {
            if (c == 'l'){
                currentString += c;
                currentState = State::false_3;
                return true;
            }else{
                return false;
            }
        }

        case State::false_3: {
            if (c == 's'){
                currentString += c;
                currentState = State::false_4;
                return true;
            }else{
                return false;
            }
        }

        case State::false_4: {
            if (c == 'e'){
                currentString += c;
                currentToken = currentString;
                currentState = State::false_5;
                return false;
            }else{
                return false;
            }
        }

        case State::true_1: {
            if (c == 'r'){
                currentString += c;
                currentState = State::true_2;
                return true;
            }else{
                return false;
            }
        }

        case State::true_2: {
            if (c == 'u'){
                currentString += c;
                currentState = State::true_3;
                return true;
            }else{
                return false;
            }
        }

        case State::true_3: {
            if (c == 'e'){
                currentString += c;
                currentToken = currentString;
                currentState = State::true_4;
                return false;
            }else{
                return false;
            }
        }

            
    }
    return false;  // Default return to handle any non-specified cases
}

Token ConstDFA::finalizeToken(){
    TokenType type;
    if(isFloatingPoint){
        type = TokenType::FLOAT_CONST;
    }else if (currentToken == "true"||currentToken == "false"){
        type = TokenType::BOOL;
    }else {
        type = TokenType::CONST;
    }

    Token token(type, currentToken);
    reset();
    return token;
}

bool ConstDFA::hasToken() const {
    return !currentToken.empty();
}

void ConstDFA::reset() {
    currentState = State::Start;
    currentString.clear();
    currentToken.clear();
    isFloatingPoint = false;  // Reset the floating-point tracker
}