#include "Lexer.h"


Lexer::Lexer() : errorOccurred(false), errorMessage("") {
    // Initialize all DFAs and store them in the vector
    dfas = {new LoopStatDFA(), new ControlStatDFA(), new IdentifierDFA(), new ConstDFA(),
            new TypeDFA(), new OperatorDFA(), new PunctuationDFA(), new StringDFA(), new WhitespaceDFA()};
}

std::vector<Token> Lexer::tokenize(const std::string& input) {
    std::vector<Token> tokens;
    std::vector<DFA*> tokenReadyDFAs;
    size_t tokenStartIndex = 0;

    for (size_t index = 0; index <= input.length(); ++index) {
        char currentChar = index < input.length() ? input[index] : '\0'; // Handle end of input

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
                } else if (currentToken.value.length() == longestLength) {
                    // Deprioritize Identifier tokens when there's a tie
                    if (currentToken.type != TokenType::IDENTIFIER && longestToken.type == TokenType::IDENTIFIER) {
                        if (currentToken.type != TokenType::WHITESPACE) {
                            longestToken = currentToken;
                        }
                    }
                }
            }

            if (longestLength > 0 && longestToken.type != TokenType::WHITESPACE) {
                tokens.push_back(longestToken);
                // Update tokenStartIndex based on the length of the token, not the current index
                tokenStartIndex += longestToken.value.length();
            } else if (longestToken.type == TokenType::WHITESPACE) {
                // If it's whitespace and shouldn't be added, still update tokenStartIndex
                tokenStartIndex += longestToken.value.length();
            } else {
                errorOccurred = true;
                errorMessage = "Error: Unrecognized token starting at position " + std::to_string(tokenStartIndex);
                break; // Stop processing on error
            }

            for (DFA* dfa : dfas) {
                dfa->reset();
            }
            tokenReadyDFAs.clear();
            index = tokenStartIndex - 1; // Adjust index to start at the next potential token start
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