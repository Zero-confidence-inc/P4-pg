#include "ConstDFA.h"
#include <ctype.h>


ConstDFA::ConstDFA() : currentState(State::Start) {}

bool ConstDFA::processChar(char c) {
    switch (currentState){
        case State::Start:
            // Checks for various single-character operators
            if ( isdigit(c)){
                currentString += c;
                currentToken = currentString;
                currentState = State::IntegerPart;
                return true;
            }else if (c=='-'){
                currentString += c;
                currentState = State::Minus;
                return true;
            }
            else return false;

        case State::Minus:
            if (isdigit(c)){
            currentString += c;
            currentToken = currentString;
            currentState = State::IntegerPart;
            return true;
            }
            else return false;



        case State::IntegerPart:
            // breaks after complete operator is found
            if ( isdigit(c)){
                currentString += c;
                currentToken = currentString;
                currentState = State::IntegerPart;
                return true;
                }
            else if (c = ','){
            currentString += c;
            currentState = State::Comma;
            return true;
            }
            else return false;

        case State::Comma:
            if (isdigit(c)){
                currentString += c;
                currentToken = currentString;
                currentState = State::DecimalPart;
                return true;
            }
            else return false;


    
        case State::DecimalPart:
            if (isdigit(c)){
                currentString += c;
                currentToken = currentString;
                currentState = State::DecimalPart;
                return true;
            }
            else return false;
            }
        }
        
Token ConstDFA::finalizeToken(){
    Token token(TokenType::CONST, currentToken);
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
}    