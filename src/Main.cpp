#include "Lexer.h"

int main() {
    Lexer lexer;
    std::string input = "";// not sure how we do the input yet will revisit
    auto tokens = lexer.tokenize(input);
    // Process the tokens here (aka lexer done syntax next)
    return 0;
}