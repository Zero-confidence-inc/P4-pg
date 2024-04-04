#include <string>
#include <vector>
#include "Token.h"

class PunctuationDFA {
public: 
    std::vector<Token> tokenize(const std::string& input) {
        std::vector<Token> tokens;
        std::string currentToken;
        State currentState = State::Start;

        // Loops through each character in the input string (one charater at a time)
        for (char c : input) {
            switch (currentState){
                case State::Start:
                    //more punctuation can be added here as needed
                    if (c == '{' || c == '}' || c == '(' || c == ')' || c == ';'){
                        currentToken += c;
                        currentState = State::Punctuation_confirmed;

                    }
                    break;
                    
                case State::Punctuation_confirmed:
                    // breaks afer complete operator is found
                    break;

            
            }
        }
        // appends the last token if it is not empty
        if (!currentToken.empty()){
            tokens.push_back(Token(TokenType::PUNCTUATION, currentToken));
        }

        return tokens;

    }

private: 
    // enum represents different states of the DFA for use in the switch case
    enum class State{
        Start,
        Punctuation_confirmed

    };

};