#include "Lexer.h"

Lexer::Lexer() : errorOccurred(false), errorMessage("") {
    // Initialize all DFAs and store them in the vector
    dfas = {new LoopStatDFA(), new ControlStatDFA(), new IdentifierDFA(), new ConstDFA(),
            new TypeDFA(), new OperatorDFA(), new PunctuationDFA(), new StringDFA(),
            new WhitespaceDFA(), new CommentsDFA()};
}

std::vector<Token> Lexer::tokenize(const std::string& input) {
    std::vector<Token> tokens;
    tokens.push_back({TokenType::START, "START"});
    size_t tokenStartIndex = 0;

    while (tokenStartIndex < input.size()) {
        std::vector<DFA*> activeDFAs;
        std::vector<DFA*> tokenReadyDFAs;
        size_t index = tokenStartIndex;

        while (index <= input.size()) {
            char currentChar = index < input.size() ? input[index] : '\0';

            bool anyActive = false;
            for (DFA* dfa : dfas) {
                if (dfa->processChar(currentChar)) {
                    anyActive = true;
                } else if (dfa->hasToken()) {
                    tokenReadyDFAs.push_back(dfa);
                }
            }

            if (!anyActive && !tokenReadyDFAs.empty()) {
                Token longestToken;
                size_t longestLength = 0;

                for (DFA* dfa : tokenReadyDFAs) {
                    Token currentToken = dfa->finalizeToken();
                    if (currentToken.value.length() > longestLength) {
                        longestLength = currentToken.value.length();
                        longestToken = currentToken;
                    }
                }

                if (longestToken.type != TokenType::WHITESPACE && longestToken.type != TokenType::COMMENTS) {
                    tokens.push_back(longestToken);
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