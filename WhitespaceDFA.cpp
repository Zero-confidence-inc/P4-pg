#include <string>
#include <vector>
#include "Token.h"

class WhitespaceDFA {
public:
    std::vector<Token> tokenize(const std:: string& input) {
        std::vector<Token> tokens;
        std::string currentToken;
        State currentState = State::Start;

        for (char c : input) {
            switch (currentState) {
                case State::Start:

                if (c == ' ' || c == '\n' || c == '\t'){
                    currentToken += c;
                }  else {
                    tokens.push_back(Token(TokenType::WHITESPACE, currentToken));
                    currentToken.clear();
                    currentState = State::Start;
                }
                break;
            }

        }
        if (!currentToken.empty() && currentState == State::Whitespace){
            tokens.push_back(Token(TokenType::WHITESPACE, currentToken));

        }

        return tokens;
    }
private:
enum class State{
    Start,
    Whitespace
    };
};