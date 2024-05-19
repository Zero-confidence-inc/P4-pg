//
// Created by Yuki on 29/04/2024.
//
#include <gtest/gtest.h>
#include "Lexer.h"



// Test basic tokenization
TEST(LexerTest, BasicTokenization) {
Lexer lexer;
std::string input = "int? abc = 5;"; // weird feature single character identifiers are now illegal and will be ignored
std::cout << "Input: " << input << std::endl;



auto tokens = lexer.tokenize(input);


    std::cout << "Number of tokens: " << tokens.size() << std::endl;
    for (const auto& token : tokens) {
        std::cout << "Token Type: " << static_cast<int>(token.type)   // Casting enum to int for readability
                  << ", Token Value: '" << token.value << "'" << std::endl;
    }
//ASSERT_EQ(tokens.size(), 5);
EXPECT_EQ(tokens[0].type, TokenType::TYPE);
EXPECT_EQ(tokens[1].type, TokenType::IDENTIFIER);
EXPECT_EQ(tokens[2].type, TokenType::OPERATOR);
EXPECT_EQ(tokens[3].type, TokenType::CONST);
EXPECT_EQ(tokens[4].type, TokenType::PUNCTUATION);
}

// Test handling of mixed token types
TEST(LexerTest, MixedTokenTypes) {
Lexer lexer;
std::string input = "func(123, 'text324');";
auto tokens = lexer.tokenize(input);
ASSERT_EQ(tokens.size(), 7);
EXPECT_EQ(tokens[0].type, TokenType::IDENTIFIER);
EXPECT_EQ(tokens[1].type, TokenType::PUNCTUATION);
EXPECT_EQ(tokens[2].type, TokenType::CONST);
EXPECT_EQ(tokens[3].type, TokenType::PUNCTUATION);
EXPECT_EQ(tokens[4].type, TokenType::STRING);
EXPECT_EQ(tokens[5].type, TokenType::PUNCTUATION);
EXPECT_EQ(tokens[6].type, TokenType::PUNCTUATION);
}

// Test error handling
TEST(LexerTest, ErrorHandling) {
    Lexer lexer;
    std::string input = "x+¤";
    std::cout << "Testing input: " << input << std::endl;

    auto tokens = lexer.tokenize(input);

    std::cout << "Lexer tokens:" << std::endl;
    for (const auto& token : tokens) {
        std::cout << "Token Type: " << static_cast<int>(token.type)
                  << ", Token Value: '" << token.value << "'" << std::endl;
    }

    std::cout << "Lexer error state: " << lexer.hasError() << std::endl;
    std::cout << "Lexer error message: " << lexer.getErrorMessage() << std::endl;

    ASSERT_TRUE(lexer.hasError());
    EXPECT_EQ(lexer.getErrorMessage(), "Error: Unrecognized character/symbol starting at position 2");
}

// Test end of input handling
TEST(LexerTest, EndOfInputHandling) {
Lexer lexer;
std::string input = "value";
auto tokens = lexer.tokenize(input);
ASSERT_EQ(tokens.size(), 1);
EXPECT_EQ(tokens[0].type, TokenType::IDENTIFIER);
EXPECT_EQ(tokens[0].getText(), "value");
}

// Main function to run all tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}