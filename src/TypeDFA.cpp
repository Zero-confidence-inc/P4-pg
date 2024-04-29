#include "TypeDFA.h"


TypeDFA::TypeDFA() : currentState(State::Start) {}

bool TypeDFA::processChar(char c) { 
    switch (currentState){
        case State::Start:
            if (c == 'i'){
                
                currentString += c;
                currentState = State::int_i;
                return true;
            }
            else if (c =='u'){
                
                currentString += c;
                currentState = State::usint_u;
                return true;
            }
            else if (c == 'c' ){
                
                currentString += c;
                currentState = State::char_c;
                return true;
            }
            else if (c == 's'){
                
                currentString += c;
                currentState = State::string_s;
                return true;
            }
            else if (c == 'f'){
                
                currentString+= c;
                currentState = State::float_f;
                return true;
            }
            else if (c == 'b'){
                
                currentString+= c;
                currentState = State::bool_b;
                return true;
            }
            else return false;


        case State::int_i:
            if (c == 'n'){
                
                currentString+= c;
                currentState = State::int_n;
                return true;
            }
            else return false;

        case State::int_n:
            if (c == 't'){
                currentString+= c;
                currentToken = currentString;
                currentState = State::int_t;
                return true;
            }
            else return false;
        
        case State::usint_u:
            if (c == 's'){
                
                currentString+= c;
                currentState = State::usint_s;
                return true;
            }
            else return false;

        case State::usint_s:
            if (c == 'i'){
                
                currentString+= c;
                currentState = State::usint_i;
                return true;
            }
            else return false;

        case State::usint_i:
            if (c == 'n'){
                
                currentString+= c;
                currentState = State::usint_n;
                return true;
            }
            else return false;

        case State::usint_n:
            if (c == 't'){
                currentString+= c;
                currentToken = currentString;
                currentState = State::usint_t;
                return true;
            }
            else return false;
        

        case State::char_c:
            if (c == 'h'){
                
                currentString+= c;
                currentState = State::char_h;
            }
            else return false;
        case State::char_h:
            if (c == 'a'){
                
                currentString+= c;
                currentState = State::char_a;
                return false;
            }
            else return false;

        case State::char_a:
            if (c == 'r'){
                currentString += c;
                currentToken = currentString;
                currentState = State::char_r;
                return true;
            }
            else return false;
        

        case State::string_s:
            if (c == 't'){
                
                currentString += c;
                currentState = State::string_t;
                return true;
            }
            else return false;

        case State::string_t:
            if (c == 'r'){
                
                currentString += c;
                currentState = State::string_r;
                return true;
            }
            else return false;

        case State::string_r:
            if (c == 'i'){
                
                currentString += c;
                currentState = State::string_i;
                return true;
            }
            else return false;

        case State::string_i:
            if (c == 'n'){
                
                currentString += c;
                currentState = State::string_n;
                return false;
            }
            else return false;

        case State::string_n:
            if (c == 'g'){
                currentString += c;
                currentToken = currentString;
                currentState = State::string_g;
                return true;
            }
            else return false;
        

        case State::float_f:
            if (c == 'l'){
                
                currentString += c;
                currentState = State::float_l;
                return true;
            }
            else return false;

        case State::float_l:
            if (c == 'o'){
                
                currentString += c;
                currentState = State::float_o;
                return true;
            }
            else return false;

        case State::float_o:
            if (c == 'a'){
                
                currentString += c;
                currentState = State::float_a;
                return true;
            }
            else return false;
        case State::float_a:
            if (c == 't'){
                currentString += c;
                currentToken = currentString;
                currentState = State::float_t;
                return true;
            }
            else return false;

        case State::bool_b:
            if (c == 'o'){
                
                currentString += c;
                currentState = State::bool_o1;
                return true;
            }
            else return false;

        case State::bool_o1:
            if (c == 'o'){
                
                currentString+= c;
                currentState = State::bool_o2;
                return true;
            }
            else return false;

        case State::bool_o2:
            if (c == 'l'){
                currentString += c;
                currentToken = currentString;
                currentState = State::bool_l;
                return true;
            }
            else return false;


        case State::int_t:
            if (c == '?'){
                currentString += c;
                currentToken = currentString;
                currentState = State::random_qmark;
                return false;
            }
            else return false;

        case State::usint_t:
            if (c == '?'){
                currentString += c;
                currentToken = currentString;
                currentState = State::random_qmark;
                return false;
            }
            else return false;

            case State::float_t:
            if (c == '?'){
                currentString += c;
                currentToken = currentString;
                currentState = State::random_qmark;
                return false;
            }
            else return false;

            case State::bool_l:
            if (c == '?'){
                currentString += c;
                currentToken = currentString;
                currentState = State::random_qmark;
                return false;
            }
            else return false;

        default:
            return false;
        }
}

Token TypeDFA::finalizeToken(){
    Token token(TokenType::TYPE, currentToken);
    reset();
    return token;

}

bool TypeDFA::hasToken() const {
    return !currentToken.empty();
}

void TypeDFA::reset() {
    currentState = State::Start;
    currentString.clear();
    currentToken.clear();
}