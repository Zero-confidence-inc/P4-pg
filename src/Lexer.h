#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include <vector>
#include <string>
#include <algorithm>
#include "DFA.h"
#include "IdentifierDFA.h"
#include "OperatorDFA.h"
#include "ConstDFA.h"
#include "TypeDFA.h"
#include "PunctuationDFA.h"
#include "StringDFA.h"
#include "WhitespaceDFA.h"
#include "ControlStatDFA.h"
#include "LoopStatDFA.h"
#include "CommentsDFA.h"
#include "JumpStatDFA.h"
#include "ConsoleDFA.h"
#include <iostream>

class Lexer {
public:
    Lexer();
    std::vector<Token> tokenize(const std::string& input);
    bool hasError() const;
    std::string getErrorMessage() const;

private:
    std::vector<DFA*> dfas; // Vector to hold all DFAs
    bool errorOccurred;
    std::string errorMessage;
};

#endif // LEXER_H