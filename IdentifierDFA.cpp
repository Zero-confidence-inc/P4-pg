#include <string>
#include <vector>
#include <Token.h>

class indentifierDFA{
public:
std::vector<Token> tokenize(const std::string& input) {
    int DFA = 0;
    std::vector<Token> tokens;
    std::string currentToken = "";       
    for(char c : input)
    {
        if(isalpha(c) and DFA == 0){
            currentToken + c;
            DFA = 1;
        } else if (isalpha(c) and DFA == 1 or isalnum(c) and DFA == 1 or islink(c) and DFA == 1) {
            currentToken + c;
        } else
        DFA = -1;
    }
    if (!currentToken.empty()){
        tokens.push_back(Token(TokenType::IDENTIFIER, currentToken));
    }
    return tokens;
}
bool islink(char c)
{
    if (c == '_' or c == '-')
        return true;
    else return false;
}
};
