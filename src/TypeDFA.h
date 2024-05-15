#ifndef TYPE_DFA_H
#define TYPE_DFA_H

#include "Token.h"
#include "DFA.h"
#include <string>

class TypeDFA : public DFA {
public:
    TypeDFA();
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
        void_1,
        void_2,
        void_3,
        void_4,
        struct_1,
        struct_2,
        struct_3,
        struct_4,
        struct_5,
        struct_6
    };

    State currentState;
    std::string currentString;
    std::string currentToken;
};

#endif // TYPE_DFA_H