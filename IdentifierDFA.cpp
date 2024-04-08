#include <Identifier.h>

IdentiferDFA::IdentifierDFA() : currentState(State::Start) {}
bool IdentifierDFA::processChar(char c) {
    //Checks if character is in the alphabet and is the first character in the currentToken string
    //If it is, the character is added to the currentToken string
    if((isalpha(c) and currentState = Start) or (islink(c) and currentState = Start)){
        currentToken += c;
        currentState = Working;
        return true;
    }
        //Checks if the character is in the alphabet, is a number or is an acceptable linking symbol (see function further down)
        //Also checks if the state is "Working" indicating this is not the first character in the string. 
        //If this is true the character is added to the currentToken string.
    else if ((isalpha(c) and currentState = Working) or (isalnum(c) and currentState = Working) or (islink(c) and currentState = Working)) {
        currentToken += c;
        return true;
    }
    return false;
}
//Function that sends back if a character is one that is accepted between letters and numbers #Example "Health_Bar-2"
bool islink(char c){
    if (c == '_' or c == '-')
        return true;
    else return false;
}

Token IdentifierDFA::finalizeToken() {
    // Assumes IDENTIFIER type exists in your TokenType enum
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
};
