#include <string>
#include <vector>
#include "Token.h"

class OperatorDFA {
public: 
    std::vector<Token> tokenize(const std::string& input) {
        std::vector<Token> tokens;
        std::string currentToken;
        State currentState = State::Start;

        for (char c : input) {
            switch (currentState){
                case State::Start:
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
                    break;

                case State::Minus_operator:
                    if (c == '-' || c == '='){
                        currentToken += c;
                        currentState = State::Operator;
                    }
                    break;
                    
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
        if (!currentToken.empty()){
            tokens.push_back(Token(TokenType::OPERATOR, currentToken));
        }

        return tokens;

    }

private: 
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