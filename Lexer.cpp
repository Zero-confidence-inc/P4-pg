#include "Lexer.h"
#include <iostream>

// Assuming the constructor initializes all the DFA objects
Lexer::Lexer(){}
std::vector<Token> Lexer::tokenize(const std::string& input) {
    std::vector<Token> tokens;
    // Array of pointers to DFA instances.
    std::vector<DFA*> activeDFAs = {&IdentifierDFA, &ConstDFA, &KeywordDFA, &OperatorDFA, &PunctuationDFA, &StringDFA, &WhitespaceDFA};

    size_t index = 0; // Index to track our position in the input string.
    while (index < input.length()) {
        char currentChar = input[index];
        bool anyActive = false; // Flag to check if any DFA is still processing the current token.

        // Processes the current character with each active DFA.
        for (auto& dfa : activeDFAs) {
            if (dfa->processChar(currentChar)) {
                anyActive = true; // At least one DFA successfully processed the character.
            }
        }

        if (!anyActive) {
            // All DFAs have failed to process the current character.
            // This means the end of the current token, so we finalize and reset the DFAs.
            for (auto& dfa : activeDFAs) {
                Token token = dfa->finalizeToken();
                if (token.type != TokenType::WHITESPACE) { // Assuming you might not want to keep whitespace tokens.
                    tokens.push_back(token);
                }
                dfa->reset();
            }
            // After resetting, all DFAs are considered active again for the next character.
        }
        ++index;
    }

    // Handle any final token at the end of the input.
    for (auto& dfa : activeDFAs) {
        if (dfa->hasToken()) { // Assuming a method to check if DFA has an unfinished token.
            tokens.push_back(dfa->finalizeToken());
        }
    }

    return tokens;
}