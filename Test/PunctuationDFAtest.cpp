//
// Created by Yuki on 24/04/2024.
//
#include <gtest/gtest.h>
#include "PunctuationDFA.h"

class PunctuationDFATest : public ::testing::Test {
protected:
    PunctuationDFA dfa;

    void SetUp() override {
        // Setup can be done here if necessary
    }
};

// Test each punctuation character
TEST_F(PunctuationDFATest, ProcessesCurlyBraceOpen) {
    EXPECT_FALSE(dfa.processChar('{'));
    EXPECT_EQ(dfa.finalizeToken().getText(), "{");
}

TEST_F(PunctuationDFATest, ProcessesCurlyBraceClose) {
    EXPECT_FALSE(dfa.processChar('}'));
    EXPECT_EQ(dfa.finalizeToken().getText(), "}");
}

TEST_F(PunctuationDFATest, ProcessesParenthesisOpen) {
    EXPECT_FALSE(dfa.processChar('('));
    EXPECT_EQ(dfa.finalizeToken().getText(), "(");
}

TEST_F(PunctuationDFATest, ProcessesParenthesisClose) {
    EXPECT_FALSE(dfa.processChar(')'));
    EXPECT_EQ(dfa.finalizeToken().getText(), ")");
}

TEST_F(PunctuationDFATest, ProcessesSemicolon) {
    EXPECT_FALSE(dfa.processChar(';'));
    EXPECT_EQ(dfa.finalizeToken().getText(), ";");
}

// Test incorrect character rejection
TEST_F(PunctuationDFATest, RejectsNonPunctuation) {
    EXPECT_FALSE(dfa.processChar('a')); // Assuming 'a' should not be accepted
    EXPECT_TRUE(dfa.finalizeToken().getText().empty()); // No token should be finalized
}

// Additional test to ensure reset functionality
TEST_F(PunctuationDFATest, ResetFunctionality) {
    dfa.processChar('(');
    dfa.reset();
    EXPECT_TRUE(dfa.hasToken() == false);
    EXPECT_FALSE(dfa.processChar('a')); // Check if DFA correctly resets
}