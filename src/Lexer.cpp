#include "Lexer.h"
#include <algorithm>  // For max_element and sort

Lexer::Lexer() {}

std::vector<Token> Lexer::tokenize(const std::string& input) {
    std::vector<Token> tokens;
    std::vector<DFA*> activeDFAs = {&loopStatDfa, &controlStatDfa, &identifierDFA, &constDFA, &typeDFA, &operatorDFA, &punctuationDFA, &stringDFA, &whitespaceDFA};
    std::vector<DFA*> tokenReadyDFAs;

    size_t tokenStartIndex = 0; // Index of the first character of the current token

    size_t index = 0;
    while (index <= input.length()) {
        char currentChar = index < input.length() ? input[index] : '\0';  // Handle end of input
        bool anyActive = false;

        // Process the current character through each DFA
        for (DFA* dfa : activeDFAs) {
            if (!dfa->processChar(currentChar)) {
                if (dfa->hasToken()) {
                    tokenReadyDFAs.push_back(dfa);
                }
            } else {
                anyActive = true;
            }
        }

        // If no DFAs are active, process ready tokens
        if (!anyActive && !tokenReadyDFAs.empty()) {
            Token longestToken;
            size_t longestLength = 0;

            // Finalize tokens from ready DFAs and find the longest one
            for (DFA* dfa : tokenReadyDFAs) {
                Token currentToken = dfa->finalizeToken();
                if (currentToken.value.length() > longestLength) {
                    longestLength = currentToken.value.length();
                    longestToken = currentToken;
                } else if (currentToken.value.length() == longestLength) {
                    // Apply tie-breaking logic here, based on DFA type
                }
            }

            // checks if token is empty
            if (longestLength > 0) {
                tokens.push_back(longestToken);
            } //add fail logic here

            // Resets all DFAs for the next round of tokenization
            for (DFA* dfa : activeDFAs) {
                dfa->reset();
                tokenStartIndex += longestLength;
                index = tokenStartIndex - 1;
            }
            tokenReadyDFAs.clear();
        }

        index++;  // Moves to the next character
    }

    return tokens;
}