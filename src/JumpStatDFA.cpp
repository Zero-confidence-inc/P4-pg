//
// Created by Yuki on 29/04/2024.
//

#include "JumpStatDFA.h"


JumpStatDFA::JumpStatDFA() : currentState(State::Start) {}

bool JumpStatDFA::processChar(char c) {
    switch (currentState){
        case State::Start:
            if (c == 'b'){
                currentString += c;
                currentState = State::break_1;
                return true;
            }
            else if (c =='c'){
                currentString += c;
                currentState = State::continue_1;
                return true;
            }
            else if (c == 'r' ){
                currentString += c;
                currentState = State::return_1;
                return true;
            }else{
                currentState = State::FAIL;
                return false;
            }


        case State::break_1:
            if (c == 'r'){
                currentString+= c;
                currentState = State::break_2;
                return true;
            }
            else return false;

        case State::break_2:
            if (c == 'e'){
                currentString+= c;
                currentState = State::break_3;
                return true;
            }
            else return false;

        case State::break_3:
            if (c == 'a'){
                currentString+= c;
                currentState = State::break_4;
                return true;
            }
            else return false;

        case State::break_4:
            if (c == 'k'){
                currentString+= c;
                currentToken = currentString;
                currentState = State::break_5;
                return false;
            }
            else return false;

        case State::continue_1:
            if (c == 'o'){
                currentString+= c;
                currentState = State::continue_2;
                return true;
            }
            else return false;

        case State::continue_2:
            if (c == 'n'){
                currentString+= c;
                currentState = State::continue_3;
                return true;
            }
            else return false;


        case State::continue_3:
            if (c == 't'){
                currentString+= c;
                currentState = State::continue_4;
                return true;
            }
            else return false;

        case State::continue_4:
            if (c == 'i'){
                currentString+= c;
                currentState = State::continue_5;
                return true;
            }
            else return false;

        case State::continue_5:
            if (c == 'n'){
                currentString += c;
                currentState = State::continue_6;
                return true;
            }
            else return false;

        case State::continue_6:
            if (c == 'u'){
                currentString+= c;
                currentState = State::continue_7;
                return true;
            }
            else return false;

        case State::continue_7:
            if (c == 'e'){
                currentString += c;
                currentToken = currentString;
                currentState = State::continue_8;
                return false;
            }
            else return false;


        case State::return_1:
            if (c == 'e'){
                currentString += c;
                currentState = State::return_2;
                return true;
            }
            else return false;

        case State::return_2:
            if (c == 't'){
                currentString+= c;
                currentState = State::return_3;
                return true;
            }
            else return false;

        case State::return_3:
            if (c == 'u'){
                currentString+= c;
                currentState = State::return_4;
                return true;
            }
            else return false;

        case State::return_4:
            if (c == 'r'){
                currentString+= c;
                currentState = State::return_5;
                return true;
            }
            else return false;

        case State::return_5:
            if (c == 'n'){
                currentString += c;
                currentToken = currentString;
                currentState = State::return_6;
                return false;
            }
            else return false;

        default:
            return false;
    }
}

Token JumpStatDFA::finalizeToken(){
    Token token(TokenType::JUMP, currentToken);
    reset();
    return token;
}

bool JumpStatDFA::hasToken() const {
    return !currentToken.empty();
}

void JumpStatDFA::reset() {
    currentState = State::Start;
    currentString.clear();
    currentToken.clear();
}