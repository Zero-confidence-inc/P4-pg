//
// Created by Yuki on 22/04/2024.
//
#include "gtest/gtest.h"
#include "TypeDFA.h"

// Define the test fixture class
class KeywordDFATest : public ::testing::Test {
protected:
    TypeDFA dfa;  // DFA instance for testing

    void SetUp() override {
        // This function is called before each test is run
        // Setup code here is optional since the DFA should reset automatically
    }

    void TearDown() override {
        // This function is called after each test is run
        // Cleanup code here is also optional
    }
};

// Test for recognizing the keyword 'int'
TEST_F(KeywordDFATest, RecognizesKeywordInt) {
    std::string keyword = "int";
    for (size_t i = 0; i < keyword.length(); ++i) {
        EXPECT_TRUE(dfa.processChar(keyword[i]));  // Expect true as each character should be valid
    }
    // Assume ' ' (space) to be a delimiter that confirms the end of a keyword
    EXPECT_FALSE(dfa.processChar(' '));
    auto token = dfa.finalizeToken();
    EXPECT_EQ(token.value, "int");
    EXPECT_EQ(token.type, TokenType::TYPE);
}

// Test for recognizing the keyword 'float'
TEST_F(KeywordDFATest, RecognizesKeywordFloat) {
    std::string keyword = "float";
    for (char c : keyword) {
        EXPECT_TRUE(dfa.processChar(c));
    }
    EXPECT_FALSE(dfa.processChar(' '));  // Using space as a delimiter
    auto token = dfa.finalizeToken();
    EXPECT_EQ(token.value, "float");
    EXPECT_EQ(token.type, TokenType::TYPE);
}

// Test for invalid character input
TEST_F(KeywordDFATest, RejectsInvalidCharacters) {
    EXPECT_FALSE(dfa.processChar('x'));  // 'x' is not a start of any valid keyword
    EXPECT_FALSE(dfa.hasToken());        // No valid token should be formed
}

// Test for handling multiple keywords with reset
TEST_F(KeywordDFATest, HandlesMultipleKeywordsWithReset) {
    std::string firstKeyword = "int";
    for (char c : firstKeyword) {
        dfa.processChar(c);
    }
    EXPECT_FALSE(dfa.processChar(' '));
    EXPECT_EQ(dfa.finalizeToken().value, "int");

    dfa.reset();  // Resetting the DFA for new input

    std::string secondKeyword = "float";
    for (char c : secondKeyword) {
        dfa.processChar(c);
    }
    EXPECT_FALSE(dfa.processChar(' '));
    EXPECT_EQ(dfa.finalizeToken().value, "float");
}

// Test for the transition and state handling within DFA
TEST_F(KeywordDFATest, ComplexKeywordHandling) {
    // Testing complex transitions within a single test
    dfa.processChar('i');
    dfa.processChar('n');
    EXPECT_TRUE(dfa.processChar('t'));
    EXPECT_FALSE(dfa.processChar(' '));
    auto token = dfa.finalizeToken();
    EXPECT_EQ(token.value, "int");
    EXPECT_EQ(token.type, TokenType::TYPE);

    dfa.reset();

    // Continuing with another keyword after reset
    std::string sequence = "float";
    for (char c : sequence) {
        dfa.processChar(c);
    }
    EXPECT_FALSE(dfa.processChar(' '));
    token = dfa.finalizeToken();
    EXPECT_EQ(token.value, "float");
}