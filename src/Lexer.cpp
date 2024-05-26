#include "Lexer.h"

Lexer::Lexer() : errorOccurred(false), errorMessage("") {
    // Initialize all DFAs and store them in the vector
    dfas = {new LoopStatDFA(), new ControlStatDFA(), new IdentifierDFA(), new ConstDFA(),
            new TypeDFA(), new OperatorDFA(), new PunctuationDFA(), new StringDFA(),
            new WhitespaceDFA(), new CommentsDFA(), new JumpStatDFA(), new ConsoleDFA};
}

std::vector<Token> Lexer::tokenize(const std::string& input) {
    std::vector<Token> tokens;
    tokens.push_back({TokenType::START, "START"});
    size_t tokenStartIndex = 0;

    while (tokenStartIndex < input.size()) {
        std::vector<DFA*> activeDFAs;
        std::vector<DFA*> tokenReadyDFAs;
        size_t index = tokenStartIndex;

        //std::cout << "Starting new token at index: " << tokenStartIndex << std::endl;

        while (index <= input.size()) {
            char currentChar = index < input.size() ? input[index] : '\0';
            //std::cout << "Processing char '" << currentChar << "' at index: " << index << std::endl;

            bool anyActive = false;
            for (DFA* dfa : dfas) {
                if (dfa->processChar(currentChar)) {
                    anyActive = true;
                    //std::cout << "DFA " << typeid(*dfa).name() << " is active." << std::endl;

                } else if (dfa->hasToken()) {
                    tokenReadyDFAs.push_back(dfa);
                    //std::cout << "DFA " << typeid(*dfa).name() << " has a token ready." << std::endl;
                }
            }

            if (!anyActive && !tokenReadyDFAs.empty()) {
                //std::cout << "No active DFAs. Finalizing token." << std::endl;

                Token longestToken;
                size_t longestLength = 0;

                for (DFA* dfa : tokenReadyDFAs) {
                    Token currentToken = dfa->finalizeToken();
                    //std::cout << "Finalized token: " << currentToken.value << std::endl;
                    if (currentToken.value.length() > longestLength || currentToken.value.length() == longestLength && currentToken.type != TokenType::IDENTIFIER) {
                        longestLength = currentToken.value.length();
                        longestToken = currentToken;
                    }
                }

                if (longestToken.type != TokenType::WHITESPACE && longestToken.type != TokenType::COMMENTS) {
                    tokens.push_back(longestToken);
                    //std::cout << "Added token: " << longestToken.value << std::endl;
                }

                tokenStartIndex += longestLength;
                break;
            }

            if (!anyActive && tokenReadyDFAs.empty()) {
                errorOccurred = true;
                errorMessage = "Error: Unrecognized character/symbol starting at position " + std::to_string(tokenStartIndex);
                std::cout << errorMessage << std::endl;
                return tokens;
            }

            index++;
        }

        for (DFA* dfa : dfas) {
            dfa->reset();
            //std::cout << "Resetting DFA " << typeid(*dfa).name() << std::endl;
        }
    }

    return tokens;
}

bool Lexer::hasError() const {
    return errorOccurred;
}

std::string Lexer::getErrorMessage() const {
    return errorMessage;
}