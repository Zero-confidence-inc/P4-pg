//
// Created by Yuki on 24/04/2024.
//
#include <gtest/gtest.h>
#include "IdentifierDFA.h"

class IdentifierDFATest : public ::testing::Test {
protected:
    IdentifierDFA dfa;

    void SetUp() override {
        // Setup necessary for each test, if any
    }

    void TearDown() override {
        // Clean up after each test, if any
    }
};

TEST_F(IdentifierDFATest, ProcessCharStartsWithLetter) {
    EXPECT_TRUE(dfa.processChar('a')); // Start state, should accept
    EXPECT_EQ(dfa.finalizeToken().getText(), "a");
}

TEST_F(IdentifierDFATest, ProcessCharStartsWithUnderscore) {
    EXPECT_TRUE(dfa.processChar('_')); // Start state, should accept
    EXPECT_EQ(dfa.finalizeToken().getText(), "_");
}

TEST_F(IdentifierDFATest, ProcessCharStartsWithNumber) {
    EXPECT_FALSE(dfa.processChar('1')); // Start state, should not accept
}

TEST_F(IdentifierDFATest, ContinueBuildingToken) {
    dfa.processChar('a'); // Start with valid character
    EXPECT_TRUE(dfa.processChar('1')); // Continue with number
    EXPECT_TRUE(dfa.processChar('_')); // Continue with underscore
    EXPECT_FALSE(dfa.processChar(' ')); //does it stop with no input?
    EXPECT_EQ(dfa.finalizeToken().getText(), "a1_");
}

TEST_F(IdentifierDFATest, HasToken) {
    EXPECT_FALSE(dfa.hasToken()); // Initially no token
    dfa.processChar('a');
    EXPECT_TRUE(dfa.hasToken()); // Now should have token
}

TEST_F(IdentifierDFATest, Reset) {
    dfa.processChar('a');
    dfa.reset();
    EXPECT_FALSE(dfa.hasToken()); // No token after reset
    EXPECT_FALSE(dfa.processChar('1')); // Should not accept since it's reset to start
}