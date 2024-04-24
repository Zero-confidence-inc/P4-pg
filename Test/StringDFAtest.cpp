//
// Created by Yuki on 24/04/2024.
//
#include <gtest/gtest.h>
#include "StringDFA.h"

class StringDFATest : public ::testing::Test {
protected:
    StringDFA dfa;

    void SetUp() override {
        // Setup if needed
    }

    void TearDown() override {
        // Clean up if needed
    }
};

TEST_F(StringDFATest, ProcessChar_whitespace_check) {
    EXPECT_TRUE(dfa.processChar('"')); // Should accept and transition
    EXPECT_TRUE(dfa.processChar('a')); // Should add 'a' and stay in Content
    EXPECT_TRUE(dfa.processChar(' ')); // might stoop here how knows
    EXPECT_TRUE(dfa.processChar('1'));
    EXPECT_FALSE(dfa.processChar('"'));
    Token token = dfa.finalizeToken();
    EXPECT_EQ(token.getText(), "\"a 1\"");
    EXPECT_EQ(token.getType(), TokenType::STRING);
}

TEST_F(StringDFATest, ProcessChar_RejectNonQuoteAtStart) {
    EXPECT_FALSE(dfa.processChar('a')); // Should reject non-quote at start
}

TEST_F(StringDFATest, ContinueBuildingString) {
    dfa.processChar('"');
    EXPECT_TRUE(dfa.processChar('h'));
    EXPECT_TRUE(dfa.processChar('i'));
    dfa.processChar('"'); // End quote
    EXPECT_EQ(dfa.finalizeToken().getText(), "\"hi\"");
}

TEST_F(StringDFATest, FinalizeToken) {
    dfa.processChar('"');
    dfa.processChar('h');
    dfa.processChar('i');
    dfa.processChar('"');
    Token token = dfa.finalizeToken();
    EXPECT_EQ(token.getText(), "\"hi\"");
    EXPECT_EQ(token.getType(), TokenType::STRING);
}

TEST_F(StringDFATest, HasToken) {
    EXPECT_FALSE(dfa.hasToken()); // Initially no token
    dfa.processChar('"');
    dfa.processChar('w');
    dfa.processChar('o');
    dfa.processChar('r');
    dfa.processChar('l');
    dfa.processChar('d');
    dfa.processChar('"');
    EXPECT_TRUE(dfa.hasToken()); // Should have token after closing quote
}

TEST_F(StringDFATest, Reset) {
    dfa.processChar('"');
    dfa.processChar('t');
    dfa.processChar('e');
    dfa.processChar('s');
    dfa.processChar('t');
    dfa.processChar('"');
    dfa.reset();
    EXPECT_FALSE(dfa.hasToken()); // No token after reset
    EXPECT_FALSE(dfa.processChar('t')); // Should not accept as it's reset to start
}