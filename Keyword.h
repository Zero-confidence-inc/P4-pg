#ifndef KEYWORD_DFA_H
#define KEYWORD_DFA_H

#include "Token.h"
#include "DFA.h"
#include <string>

class KeywordDFA : public DFA {
public:
    bool processChar(char c) override;
    Token finalizeToken() override;
    bool hasToken() const override;
    void reset() override;

private:
    enum class State{
        Start,
        int_i,
        int_n,
        int_t,
        usint_u,
        usint_s,
        usint_i,
        usint_n,
        usint_t,
        char_c,
        char_h,
        char_a,
        char_r,
        string_s,
        string_t,
        string_r,
        string_i,
        string_n,
        string_g,
        float_f,
        float_l,
        float_o,
        float_a,
        float_t,
        bool_b,
        bool_o1,
        bool_o2,
        bool_l,
        random_qmark,
    };

    State currentState;
    std::string currentString;
    std::string currentToken;
};

#endif // KEYWORD_H