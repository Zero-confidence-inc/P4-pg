#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Token.h"

class ConstDFA {
public:
    std::vector<Token> tokenize(const std::string& input) {
        std::vector<Token> tokens;
        std::string currentToken;
        std::string currentString;
        State currentState = State::Start;

        // Loops through each character in the input string (one charater at a time)
        for (char c : input) {
            switch (currentState){
                case State::Start:
                    // Checks for various single-character operators
                    if ( isdigit(c)){
                        currentString += c;
                        currentToken = currentString;
                        currentState = State::Hel;
                    }else if (c=='-'){
                    currentString += c;
                    currentState = State::Minus;
                    }
                    break;

                case State::Minus:
                    if (isdigit(c)){
                    currentString += c;
                    currentToken = currentString;
                    currentState = State::Hel;
                    }



                case State::Hel:
                    // breaks afer complete operator is found
                    if ( isdigit(c)){
                       currentString += c;
                       currentToken = currentString;
                       currentState = State::Hel;
                       }
                    else if (c=','){
                    currentString += c;
                    currentState = State::Komma;
                    }
                    break;

                case State::Komma:
                    if (isdigit(c)){
                        currentString += c;
                        currentToken = currentString;
                        currentState = State::EfterKomma;
                    }
                    break;


                // all states below here checks for double operators(also allows for their single counterpart to be used)
                case State::EfterKomma:
                    if (isdigit(c)){
                        currentString += c;
                        currentToken = currentString;
                        currentState = State::EfterKomma;
                    }
                    break;
            }
        }
        // appends the last token if it is not empty
        if (!currentToken.empty()){
            tokens.push_back(Token(TokenType::CONST, currentToken));
        }

        return tokens;

    }

private:
    // enum represents different states of the DFA for use in the switch case
    enum class State{
        Start,
        Minus,
        Hel,
        Komma,
        EfterKomma


    };

};
