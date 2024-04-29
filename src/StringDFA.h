#ifndef STRING_DFA_H
#define STRING_DFA_H

#include "DFA.h"
#include "Token.h"
#include <string>

class StringDFA : public DFA{
public:
    StringDFA();
    bool processChar(char c) override;
    Token finalizeToken() override;
    bool hasToken() const override;
    void reset() override;


private:
    enum class State {
        Start,
        Content,
        ContentAlt,
        End
    };

    State currentState;
    std::string currentToken;
    std::string currentString;
};
#endif // STRING_DFA_H