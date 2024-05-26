#include "Lexer.h"
#include "Parser.h"
#include "Semantic.h"
#include "CodeGenerator.h"


int main() {

    std::string input = "";// to be changed to a file reader

    Lexer lexer;
    auto tokens = lexer.tokenize(input);

    Parser parser(tokens);// this would be stupid if we ever planed on running it more than once per main call
    std::vector<std::shared_ptr<ASTNode>> ast = parser.parseProgram();

    Kowalski kowalski;
    kowalski.Analyse(ast);

    CodeGenerator codeGenerator;
    std::string code = codeGenerator.generateCode(ast);


    return 0;
}