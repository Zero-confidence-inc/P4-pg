#include <string>
#include <vector>
#include "Token.h"

class KeywordDFA {
public:
    std::vector<Token> tokenize(const std::string& input) {
        std::vector<Token> tokens;
        std::string currentToken;
        std::string currentString[] = {};
        State currentState = State::Start;
        

        for (char c : input){
            switch (currentState)
            {
            case State::Start:
                if (c == 'i'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::int_i;
                }
                else if (c =='u'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::usint_u;
                }
                else if (c == 'c' ){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::char_c;
                }
                else if (c == 's'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::string_s;
                }
                else if (c == 'f'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::float_f;
                }
                else if (c == 'b'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::bool_b;
                }
                else if (c == '?'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::random_qmark;
                }
                break;


            case State::int_i:
                if (c == 'n'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::int_n;
                }
                break;
            case State::int_n:
                if (c == 't'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::int_t;
                }
                break;
            

            case State::usint_u:
                if (c == 's'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::usint_s;
                }
                break;
            case State::usint_s:
                if (c == 'i'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::usint_i;
                }
                break;
            case State::usint_i:
                if (c == 'n'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::usint_n;
                }
                break;
            case State::usint_n:
                if (c == 't'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::usint_t;
                }
                break;
            

            case State::char_c:
                if (c == 'h'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::char_h;
                }
                break;
            case State::char_h:
                if (c == 'a'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::char_a;
                }
                break;
            case State::char_a:
                if (c == 'r'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::char_r;
                }
                break;
            

            case State::string_s:
                if (c == 't'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::string_t;
                }
                break;
            case State::string_t:
                if (c == 'r'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::string_r;
                }
                break;
            case State::string_r:
                if (c == 'i'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::string_i;
                }
                break;
            case State::string_i:
                if (c == 'n'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::string_n;
                }
                break;
            case State::string_n:
                if (c == 'g'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::string_g;
                }
                break;
            

            case State::float_f:
                if (c == 'l'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::float_l;
                }
                break;
            case State::float_l:
                if (c == 'o'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::float_o;
                }
                break;
            case State::float_o:
                if (c == 'a'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::float_a;
                }
                break;
            case State::float_a:
                if (c == 't'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::float_t;
                }
                break;


            case State::bool_b:
                if (c == 'o'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::bool_o1;
                }
                break;
            case State::bool_o1:
                if (c == 'o'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::bool_o2;
                }
                break;
            case State::bool_o2:
                if (c == 'l'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::bool_l;
                }
                break;


            case State::random_qmark:
                if (c == '<'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::random_bracet_start;
                }
                break;
            case State::random_bracet_start:
                if (c == '0' | c == '1' | c == '2' | c == '3' | c == '4' | c == '5' | c == '6' | c == '7' | c == '8' | c == '9'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::random_low;
                }
                break;
            case State::random_low:
                if (c == '0' | c == '1' | c == '2' | c == '3' | c == '4' | c == '5' | c == '6' | c == '7' | c == '8' | c == '9'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::random_low;
                }
                else if (c == ','){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::random_comma;
                }
                break;
            case State::random_comma:
                if (c == '0' | c == '1' | c == '2' | c == '3' | c == '4' | c == '5' | c == '6' | c == '7' | c == '8' | c == '9'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::random_high;
                }
                break;
            case State::random_high:
                if (c == '0' | c == '1' | c == '2' | c == '3' | c == '4' | c == '5' | c == '6' | c == '7' | c == '8' | c == '9'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::random_high;
                }
                else if (c == '>'){
                    currentToken += c;
                    currentString->push_back(c);
                    currentState = State::random_bracet_end;
                }
                break;

            default:
                break;
            }
        }
        if (!currentToken.empty()){
            tokens.push_back(Token(TokenType::KEYWORD, currentToken));
        }
        return tokens;
    };

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
            random_bracet_start,
            random_low,
            random_comma,
            random_high,
            random_bracet_end
        };
};