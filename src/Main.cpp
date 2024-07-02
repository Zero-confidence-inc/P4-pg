#include <iostream>
#include <fstream>
#include <sstream>
#include "Lexer.h"
#include "Parser.h"
#include "Semantic.h"
#include "CodeGenerator.h"
#include <cstdlib>  // For system()
#include <cstdio>   // For std::remove

int main() {
    std::string input;
    std::cout << "Enter your code (end with an empty line):" << std::endl;
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) break;
        input += line + "\n";
    }

    std::cout << "Input read from console." << std::endl;

    Lexer lexer;
    auto tokens = lexer.tokenize(input);
    std::cout << "Tokenization complete." << std::endl;

    Parser parser(tokens);
    std::vector<std::shared_ptr<ASTNode>> ast = parser.parseProgram();
    std::cout << "Parsing complete." << std::endl;

    Kowalski kowalski;
    try {
        kowalski.Analyse(ast);
        std::cout << "Semantic analysis complete." << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Semantic analysis error: " << e.what() << std::endl;
        return 1;
    }

    CodeGenerator codeGenerator;
    std::string code = codeGenerator.generateCode(ast);
    std::cout << "Code generation complete." << std::endl;

    std::ofstream outputFile("output.cpp");
    if (!outputFile) {
        std::cerr << "Error creating output file!" << std::endl;
        std::cout << "error found." << std::endl;
        return 1;
    }

    outputFile << code;
    outputFile.close();
    std::cout << "Generated code written to output.cpp." << std::endl;

    // Verify the content of output.cpp
    std::ifstream verifyFile("output.cpp");
    if (verifyFile) {
        std::cout << "output.cpp exists. Content:" << std::endl;
        std::string line;
        while (std::getline(verifyFile, line)) {
            std::cout << line << std::endl;
        }
        verifyFile.close();
    } else {
        std::cerr << "Error: output.cpp does not exist!" << std::endl;
        return 1;
    }

    // Compile the generated file using g++
    std::string compileCommand = "g++ output.cpp -o output_executable";
    std::cout << "Executing compile command: " << compileCommand << std::endl;
    int result = system(compileCommand.c_str());
    if (result != 0) {
        std::cerr << "Compilation failed!" << std::endl;
        return 1;
    }

    std::cout << "Compilation successful. Executable created: output_executable" << std::endl;

    return 0;
}