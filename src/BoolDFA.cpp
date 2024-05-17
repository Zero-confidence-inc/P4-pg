#include "BOOLDFA.h"

BOOLDFA::BOOLDFA() : currentState(State::Start) {}

bool BOOLDFA::processChar(char c) {
    switch (currentState){
        case State::Start:
            if (c == 't'){
                currentString += c;
                currentState = State::T;
                return true;
            }
            else if (c=='f')
            {
                currentString += c;
                currentState = State::F;
            }
            
            else return false;
        case State::T:
            if (c == 'r'){
                currentString += c;
                currentState = State::TR;
                return true;
            }
            else return false;

        case State::TR:
            if (c == 'u'){
                currentString+= c;
                currentState = State::TRU;
                return true;
            }
            else return false;

        case State::TRU:
            if (c == 'e'){
                currentString+= c;
                currentState = State::TRUE;
                return false;
            }
            else return false;


        case State::F:
            if (c == 'a'){
                currentString += c;
                currentState = State::FA;
                return true;
            }
            else return false;

        case State::FA:
            if (c == 'l'){
                currentString+= c;
                currentState = State::FAL;
                return true;
            }
            else return false;

        case State::FAL:
            if (c == 's'){
                currentString+= c;
                currentState = State::TRUE;
                return false;
            }
            else return false; 
        case State::FALS:
            if (c == 'e'){
                currentString+= c;
                currentState = State::FALSE;
                return false;
            }
            else return false;   
        default:
            return false;
    }
}

Token BOOLDFA::finalizeToken(){
    Token token(TokenType::BOOL, currentToken);
    reset();
    return token;
}

bool BOOLDFA::hasToken() const {
    return !currentToken.empty();
}

void BOOLDFA::reset() {
    currentState = State::Start;
    currentString.clear();
    currentToken.clear();
}