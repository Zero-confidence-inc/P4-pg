#include <iostream>
#include <fstream>
#include <sstream>
#include "Lexer.h"
#include "Parser.h"
#include "Semantic.h"
#include "CodeGenerator.h"
#include <cstdlib>  // For system()


int main() {

    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    std::string input = buffer.str();

    Lexer lexer;
    auto tokens = lexer.tokenize(input);

    Parser parser(tokens);// this would be stupid if we ever planed on running it more than once per main call
    std::vector<std::shared_ptr<ASTNode>> ast = parser.parseProgram();

    Kowalski kowalski;
    try {
        kowalski.Analyse(ast);
    } catch (const std::runtime_error& e) {
        std::cerr << "Semantic analysis error: " << e.what() << std::endl;
        return 1;
    }

    CodeGenerator codeGenerator;
    std::string code = codeGenerator.generateCode(ast);

    std::ofstream outputFile("output.cpp");
    if (!outputFile) {
        std::cerr << "Error creating output file!" << std::endl;
        return 1;
    }
    outputFile << code;
    outputFile.close();

    // Compile the generated file using g++
    int result = system("g++ output.cpp -o output_executable");
    if (result != 0) {
        std::cerr << "Compilation failed!" << std::endl;
        return 1;
    }

    std::cout << "Compilation successful. Executable created: output_executable" << std::endl;

    return 0;
}