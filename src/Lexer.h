#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include <vector>
#include <string>
#include "IdentifierDFA.h"
#include "OperatorDFA.h"
#include "ConstDFA.h"
#include "TypeDFA.h"
#include "PunctuationDFA.h"
#include "StringDFA.h"
#include "WhitespaceDFA.h"
#include "ControlStatDFA.h"
#include "LoopStatDFA.h"
#include "DFA.h"

class Lexer {
public:
    Lexer();
    std::vector<Token> tokenize(const std::string& input);

private:
    IdentifierDFA identifierDFA;
    ConstDFA constDFA;
    OperatorDFA operatorDFA;
    TypeDFA typeDFA;
    PunctuationDFA punctuationDFA;
    StringDFA stringDFA;
    WhitespaceDFA whitespaceDFA;
    ControlStatDFA controlStatDfa;
    LoopStatDFA loopStatDfa;

};

#endif // LEXER_H
