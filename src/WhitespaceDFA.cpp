#include "WhitespaceDFA.h"

WhitespaceDFA::WhitespaceDFA() : currentState(State::Start) {}

bool WhitespaceDFA::processChar(char c) {
    switch (currentState) {
        case State::Start:

        if (c == ' ' || c == '\n' || c == '\t'){
            currentToken += c;
            return false;
        }
        default:return false;
    }
}

Token WhitespaceDFA::finalizeToken() {
    Token token(TokenType::WHITESPACE, currentToken);
    reset();
    return token;
}

bool WhitespaceDFA::hasToken() const {
    return !currentToken.empty();
}

void WhitespaceDFA::reset() {
    currentState = State::Start;
    currentToken.clear();
}