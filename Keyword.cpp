#include "Keyword.h"


KeywordDFA::KeywordDFA() : currentState(State::Start) {}

bool KeywordDFA::processChar(char c) { 
    switch (currentState){
        case State::Start:
            if (c == 'i'){
                currentToken += c;
                currentString += c;
                currentState = State::int_i;
                return true;
            }
            else if (c =='u'){
                currentToken += c;
                currentString += c;
                currentState = State::usint_u;
                return true;
            }
            else if (c == 'c' ){
                currentToken += c;
                currentString += c;
                currentState = State::char_c;
                return true;
            }
            else if (c == 's'){
                currentToken += c;
                currentString += c;
                currentState = State::string_s;
                return true;
            }
            else if (c == 'f'){
                currentToken += c;
                currentString+= c;
                currentState = State::float_f;
                return true;
            }
            else if (c == 'b'){
                currentToken += c;
                currentString+= c;
                currentState = State::bool_b;
                return true;
            }
            else if (c == '?'){
                currentToken += c;
                currentString+= c;
                currentState = State::random_qmark;
                return true;
            }
            else return false;


        case State::int_i:
            if (c == 'n'){
                currentToken += c;
                currentString+= c;
                currentState = State::int_n;
                return true;
            }
            else return false;

        case State::int_n:
            if (c == 't'){
                currentToken += c;
                currentString+= c;
                currentState = State::int_t;
                return true;
            }
            else return false;
        
        case State::usint_u:
            if (c == 's'){
                currentToken += c;
                currentString+= c;
                currentState = State::usint_s;
                return true;
            }
            else return false;

        case State::usint_s:
            if (c == 'i'){
                currentToken += c;
                currentString+= c;
                currentState = State::usint_i;
                return true;
            }
            else return false;

        case State::usint_i:
            if (c == 'n'){
                currentToken += c;
                currentString+= c;
                currentState = State::usint_n;
                return true;
            }
            else return false;

        case State::usint_n:
            if (c == 't'){
                currentToken += c;
                currentString+= c;
                currentState = State::usint_t;
                return true;
            }
            else return false;
        

        case State::char_c:
            if (c == 'h'){
                currentToken += c;
                currentString+= c;
                currentState = State::char_h;
            }
            else return false;
        case State::char_h:
            if (c == 'a'){
                currentToken += c;
                currentString+= c;
                currentState = State::char_a;
                return false;
            }
            else return false;

        case State::char_a:
            if (c == 'r'){
                currentToken += c;
                currentString += c;
                currentState = State::char_r;
                return true;
            }
            else return false;
        

        case State::string_s:
            if (c == 't'){
                currentToken += c;
                currentString += c;
                currentState = State::string_t;
                return true;
            }
            else false;

        case State::string_t:
            if (c == 'r'){
                currentToken += c;
                currentString += c;
                currentState = State::string_r;
                return true;
            }
            else return false;

        case State::string_r:
            if (c == 'i'){
                currentToken += c;
                currentString += c;
                currentState = State::string_i;
                return true;
            }
            else return false;

        case State::string_i:
            if (c == 'n'){
                currentToken += c;
                currentString += c;
                currentState = State::string_n;
                return false;
            }
            else return false;

        case State::string_n:
            if (c == 'g'){
                currentToken += c;
                currentString += c;
                currentState = State::string_g;
                return true;
            }
            else return false;
        

        case State::float_f:
            if (c == 'l'){
                currentToken += c;
                currentString += c;
                currentState = State::float_l;
                return true;
            }
            else return false;

        case State::float_l:
            if (c == 'o'){
                currentToken += c;
                currentString += c;
                currentState = State::float_o;
                return true;
            }
            else return false;

        case State::float_o:
            if (c == 'a'){
                currentToken += c;
                currentString += c;
                currentState = State::float_a;
                return true;
            }
            else return false;
        case State::float_a:
            if (c == 't'){
                currentToken += c;
                currentString += c;
                currentState = State::float_t;
                return true;
            }
            else return false;

        case State::bool_b:
            if (c == 'o'){
                currentToken += c;
                currentString += c;
                currentState = State::bool_o1;
                return true;
            }
            else return false;

        case State::bool_o1:
            if (c == 'o'){
                currentToken += c;
                currentString+= c;
                currentState = State::bool_o2;
                return true;
            }
            else return false;

        case State::bool_o2:
            if (c == 'l'){
                currentToken += c;
                currentString += c;
                currentState = State::bool_l;
                return true;
            }
            else return false;


        case State::int_t:
            if (c == '?'){
                currentToken += c;
                currentString += c;
                currentState = State::random_qmark;
                return false;
            }
            else return false;

        case State::usint_t:
            if (c == '?'){
                currentToken += c;
                currentString += c;
                currentState = State::random_qmark;
                return false;
            }
            else return false;

            case State::float_t:
            if (c == '?'){
                currentToken += c;
                currentString += c;
                currentState = State::random_qmark;
                return false;
            }
            else return false;

            case State::bool_l:
            if (c == '?'){
                currentToken += c;
                currentString += c;
                currentState = State::random_qmark;
                return false;
            }
            else return false;

        default:
            false;
        }
}

Token KeywordDFA::finalizeToken(){
    Token token(TokenType::KEYWORD, currentToken);
    reset();
    return token;

}

bool KeywordDFA::hasToken() const {
    return !currentToken.empty();
}

void KeywordDFA::reset() {
    currentState = State::Start;
    currentString.clear();
    currentToken.clear();
}