#include <string>
#include <vector>
#include <Token.h>

class StringDFA
{
public:
std::vector<Token> tokenize(const std::string& input){

std::vector<Token> tokens;
std::string currentToken = "";

for(char c : input){

    currentToken + c;
}

if (currentToken.empty() != true)
{
   tokens.push_back(Token(TokenType::STRING, currentToken));
}
return tokens;


}
};

