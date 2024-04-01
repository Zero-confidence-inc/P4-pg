#include <string>
#include <vector>
#include "Token.h"

class OperatorDFA {
public: 
    std::vector<Token> tokenize(const std::string& input) {
        std::vector<Token> tokens;
        std::string currentToken;
        State currentState = State::Start;

        // Loops through each character in the input string (one charater at a time)
        for (char c : input) {
            switch (currentState){
                case State::Start:
                    // Checks for various single-character operators
                    if (c == '/' || c == '%' || c == '*' || c == '^'){
                        currentToken += c;
                        currentState = State::Operator;

                    }else if (c == '<' || c == '>' || c == '!' || c == '='){
                        currentToken += c;
                        currentState = State::Mesuring_operator;

                    }else if (c == '+'){
                        currentToken += c;
                        currentState = State::Plus_operator;

                    }else if (c == '-'){
                        currentToken += c;
                        currentState = State::Minus_operator;

                    }else if (c == '&'){
                        currentToken += c;
                        currentState = State::And_operator;

                    }else if (c == '|'){
                        currentToken += c;
                        currentState = State::Or_operator;

                    }
                    break;
                    
                case State::Operator:
                    // breaks afer complete operator is found
                    break;

                case State::Minus_operator:
                    if (c == '-' || c == '='){
                        currentToken += c;
                        currentState = State::Operator;
                    }
                    break;
                    
                
                // all states below here checks for double operators(also allows for their single counterpart to be used)
                case State::Plus_operator:
                    if (c == '+' || c == '='){
                        currentToken += c;
                        currentState = State::Operator;
                    }
                    break;

                case State::Mesuring_operator:
                    if (c == '='){
                        currentToken += c;
                        currentState = State::Operator;
                    }
                    break;

                case State::And_operator:
                    if (c == '&'){
                        currentToken += c;
                        currentState = State::Operator;
                    }
                    break;

                case State::Or_operator:
                    if (c == '|'){
                        currentToken += c;
                        currentState = State::Operator;
                    }
                    break;

            

            }
        }
        // appends the last token if it is not empty
        if (!currentToken.empty()){
            tokens.push_back(Token(TokenType::OPERATOR, currentToken));
        }

        return tokens;

    }

private: 
    // enum represents different states of the DFA for use in the switch case
    enum class State{
        Start,
        Operator,
        Minus_operator,
        Plus_operator,
        Mesuring_operator,
        And_operator,
        Or_operator
        
    };

};