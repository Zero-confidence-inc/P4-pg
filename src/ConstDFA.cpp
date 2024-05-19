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
            } else {
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
            
    }
    return false;  // Default return to handle any non-specified cases
}

Token ConstDFA::finalizeToken(){
    TokenType type = isFloatingPoint ? TokenType::FLOAT_CONST : TokenType::CONST;
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