
#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "Lexer.h"
#include "Parser.h"
#include "Semantic.h"
#include "CodeGenerator.h"

class AcceptanceTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create the input source code file
        std::ofstream inputFile("input.txt");
        inputFile << R"(
        bool cryptoMine(bool hard, string vString) {
            while (hard) {
                if (vString == "") {
                    for (float i = 5.6; i > 0; i--) {
                        cryptoMine(false, vString );
                    }
                }
                hard = false;
            }
            return true;
        }

        int main() {
            bool result = cryptoMine(true, "");
            return 0;
        }
        )";
        inputFile.close();
    }

    void TearDown() override {
        // Clean up generated files
        remove("input.txt");
        remove("output.cpp");
        remove("output_executable");
    }
};

TEST_F(AcceptanceTest, EndToEndTest) {
    // Step 1: Read the input file
    std::ifstream inputFile("input.txt");
    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    std::string input = buffer.str();

    // Step 2: Tokenize the input
    Lexer lexer;
    auto tokens = lexer.tokenize(input);
    ASSERT_FALSE(lexer.hasError()) << "Lexer error: " << lexer.getErrorMessage();

    // Step 3: Parse the tokens
    Parser parser(tokens);
    auto ast = parser.parseProgram();
    std::cout<< "parser parsed"<< std::endl;
    ASSERT_FALSE(ast.empty()) << "Parser error: AST is empty";

    // Step 4: Semantic analysis
    Kowalski kowalski;
    ASSERT_NO_THROW(kowalski.Analyse(ast)) << "Semantic analysis error";
    std::cout<< " semantics done" <<std::endl;
    // Step 5: Generate code
    CodeGenerator codeGenerator;
    std::string generatedCode = codeGenerator.generateBodyCode(ast);

    // Write the generated code to an output file
    std::ofstream outputFile("output.cpp");
    outputFile << generatedCode;
    outputFile.close();

    // Step 6: Compile the generated code
    int result = system("g++ output.cpp -o output_executable");
    ASSERT_EQ(result, 0) << "Compilation failed";

    // Step 7: Run the compiled executable
    result = system("./output_executable > result.txt");
    ASSERT_EQ(result, 0) << "Execution failed";

    // Step 8: Check the output
    std::ifstream resultFile("result.txt");
    std::stringstream resultBuffer;
    resultBuffer << resultFile.rdbuf();
    std::string output = resultBuffer.str();
    EXPECT_EQ(output, "Result: 1\n") << "Unexpected output: " << output;

    // Clean up the result file
    remove("result.txt");
}