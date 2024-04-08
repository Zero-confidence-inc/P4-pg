#include <string>
#include <vector>
#include <Token.h>

class indentifierDFA{
public:
std::vector<Token> tokenize(const std::string& input) {
    int DFA = 0;
    std::vector<Token> tokens;
    std::string currentToken = "";

    //Checks through all characters inside of the input string
    for(char c : input){
        //Checks if character is in the alphabet and is the first character in the currentToken string
        //If it is, the character is added to the currentToken string and DFA is set to 1 indicating that first character has been set
        if((isalpha(c) and DFA == 0) or (islink(c) and DFA == 0)){
            currentToken + c;
            DFA = 1;
        } 
        //Checks if the character is in the alphabet, is a number or is an acceptable linking symbol (see function further down)
        //Also checks if DFA is 1 indicating this is not the first character in the string. 
        //If this is true the character is added to the currentToken string.
        else if ((isalpha(c) and DFA == 1) or (isalnum(c) and DFA == 1) or (islink(c) and DFA == 1)) {
            currentToken + c;
        } else
        break;
    }
    
    if (!currentToken.empty()){
        tokens.push_back(Token(TokenType::IDENTIFIER, currentToken));
    }
    return tokens;
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
