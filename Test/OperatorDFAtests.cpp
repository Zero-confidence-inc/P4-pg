//
// Created by Yuki on 22/04/2024.
//
#include "gtest/gtest.h"
#include "OperatorDFA.h"

// Fixture for setting up the OperatorDFA and providing a clean state for each test
class OperatorDFATest : public ::testing::Test {
protected:
    OperatorDFA dfa;

    void SetUp() override {
        // Any common setup can go here
    }

    void TearDown() override {
        // Any cleanup needed after each test
    }
};

// Tests that single character operators are processed correctly
TEST_F(OperatorDFATest, RecognizesSingleCharacterOperators) {
    EXPECT_FALSE(dfa.processChar('/')); // Single '/' should not finalize the token immediately
    EXPECT_EQ(dfa.finalizeToken().getText(), "/");
    EXPECT_EQ(dfa.finalizeToken().getType(), TokenType::OPERATOR);
}

// Tests that combined operators such as += are recognized correctly
TEST_F(OperatorDFATest, RecognizesCombinedOperators) {
    dfa.processChar('+');
    EXPECT_FALSE(dfa.processChar('=')); // '+=' should finalize the token
    EXPECT_EQ(dfa.finalizeToken().getText(), "+=");
    EXPECT_EQ(dfa.finalizeToken().getType(), TokenType::OPERATOR);
}

// Tests the DFAs ability to ignore invalid characters
TEST_F(OperatorDFATest, IgnoresInvalidCharacters) {
    EXPECT_FALSE(dfa.processChar('a')); // 'a' is not a valid operator character
    EXPECT_FALSE(dfa.hasToken());       // No token should be created
}

// Tests the reset functionality to ensure the DFA state is cleared
TEST_F(OperatorDFATest, ResetClearsDFAState) {
    dfa.processChar('*');
    dfa.reset();
    EXPECT_FALSE(dfa.hasToken());
    EXPECT_EQ(dfa.finalizeToken().getText(), ""); // After reset, no token should be present
}

// Tests for specific edge cases, such as handling multiple characters where only the first is valid
TEST_F(OperatorDFATest, HandlesEdgeCases) {
    EXPECT_TRUE(dfa.processChar('&'));
    EXPECT_FALSE(dfa.processChar('&')); // '&&' should finalize the token
    EXPECT_EQ(dfa.finalizeToken().getText(), "&&");

    // Testing reset after handling an operator
    dfa.reset();
    dfa.processChar('+');
    EXPECT_FALSE(dfa.processChar('b')); // '+b' should not be valid, '+b' isn't an operator
    EXPECT_EQ(dfa.finalizeToken().getText(), "+"); // Only '+' should be recognized
}