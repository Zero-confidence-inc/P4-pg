#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include <vector>
#include <string>
#include "IdentifierDFA.h"
#include "OperatorDFA.h"
#include "ConstDFA.h"
#include "Keyword.h"
#include "PunctuationDFA.h"
#include "StringDFA.h"
#include "WhitespaceDFA.h"
#include "ControlStatDFA.h"
#include "DFA.h"

class Lexer {
public:
    Lexer();
    std::vector<Token> tokenize(const std::string& input);

private:
    IdentifierDFA identifierDFA;
    ConstDFA constDFA;
    OperatorDFA operatorDFA;
    KeywordDFA keywordDFA;
    PunctuationDFA punctuationDFA;
    StringDFA stringDFA;
    WhitespaceDFA whitespaceDFA;
    ControlStatDFA controlStatDfa;

};

#endif // LEXER_H
