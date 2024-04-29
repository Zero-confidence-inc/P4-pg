#include "PunctuationDFA.h"

PunctuationDFA::PunctuationDFA() : currentState(State::Start) {}
bool PunctuationDFA::processChar(char c) {
    switch (currentState){
        case State::Start:
            //more punctuation can be added here as needed
            if (c == '{' || c == '}' || c == '(' || c == ')' || c == ';'|| c==','){
                currentToken += c;
                currentState = State::Punctuation_confirmed;
                return false;

            }
            else return false;
        default: return false;

    }
}

Token PunctuationDFA::finalizeToken() {
    Token token(TokenType::PUNCTUATION, currentToken);
    reset();
    return token;
}

bool PunctuationDFA::hasToken() const {
    return !currentToken.empty();
}

void PunctuationDFA::reset(){
    currentState = State::Start;
    currentToken.clear();
}