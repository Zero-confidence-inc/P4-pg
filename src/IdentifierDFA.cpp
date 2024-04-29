#include "IdentifierDFA.h"

IdentifierDFA::IdentifierDFA() : currentState(State::Start) {}

bool IdentifierDFA::processChar(char c) {
    if (currentState == State::Start && (isalpha(c) || c == '_')) {
        currentToken += c;
        currentState = State::Working;
        return true;
    } else if (currentState == State::Working && (isalnum(c) || c == '_')) {
        currentToken += c;
        return true;
    } else
        return false;


}


Token IdentifierDFA::finalizeToken() {
    Token token(TokenType::IDENTIFIER, currentToken);
    reset(); // Prepare for the next token
    return token;  
}

bool IdentifierDFA::hasToken() const {
    return !currentToken.empty();
}

void IdentifierDFA::reset() {
    currentState = State::Start;
    currentToken.clear();
}
