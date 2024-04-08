#include "OperatorDFA.h"

OperatorDFA::OperatorDFA() : currentState(State::Start) {}

bool OperatorDFA::processChar(char c) {
    switch (currentState){
        case State::Start:
            // Checks for various single-character operators
            if (c == '/' || c == '%' || c == '*' || c == '^'){
                currentToken += c;
                currentState = State::Operator;
                return true;

            }else if (c == '<' || c == '>' || c == '!' || c == '='){
                currentToken += c;
                currentState = State::Measuring_operator;
                return true;

            }else if (c == '+'){
                currentToken += c;
                currentState = State::Plus_operator;
                return true;

            }else if (c == '-'){
                currentToken += c;
                currentState = State::Minus_operator;
                return true;

            }else if (c == '&'){
                currentToken += c;
                currentState = State::And_operator;
                return true;

            }else if (c == '|'){
                currentToken += c;
                currentState = State::Or_operator;
                return true;

            }
            return false;
            
        case State::Operator:
            return false;

        case State::Minus_operator:
            if (c == '-' || c == '='){
                currentToken += c;
                currentState = State::Operator;
                return false;
            }
            break;
            
        
        // all states below here checks for double operators(also allows for their single counterpart to be used)
        case State::Plus_operator:
            if (c == '+' || c == '='){
                currentToken += c;
                currentState = State::Operator;
                return false;
            }
            break;

        case State::Measuring_operator:
            if (c == '='){
                currentToken += c;
                currentState = State::Operator;
                return false;
            }
            break;

        case State::And_operator:
            if (c == '&'){
                currentToken += c;
                currentState = State::Operator;
                return false;
            }
            break;

        case State::Or_operator:
            if (c == '|'){
                currentToken += c;
                currentState = State::Operator;
                return false;
            }
            break;
    }
}
Token OperatorDFA::finalizeToken() {
    // Assumes OPERATOR type exists in your TokenType enum
    Token token(TokenType::OPERATOR, currentToken);
    reset(); // Prepare for the next token
    return token;  
}

bool OperatorDFA::hasToken() const {
    return !currentToken.empty();
}

void OperatorDFA::reset() {
    currentState = State::Start;
    currentToken.clear();
}