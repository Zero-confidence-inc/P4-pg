//
// Created by Yuki on 24/04/2024.
//
#include <gtest/gtest.h>
#include "ConstDFA.h"

class ConstDFATest : public ::testing::Test {
protected:
    ConstDFA dfa;

    void SetUp() override {
        // Setup can be done here
    }
};

// Start state tests
TEST_F(ConstDFATest, AcceptsDigitsAtStart) {
    EXPECT_TRUE(dfa.processChar('3'));
    EXPECT_EQ(dfa.finalizeToken().getType(), TokenType::CONST);
}

TEST_F(ConstDFATest, AcceptsMinusAtStart) {
    EXPECT_TRUE(dfa.processChar('-'));
    EXPECT_FALSE(dfa.processChar('a'));  // Should reject non-digit
}

TEST_F(ConstDFATest, RejectsInvalidStartCharacters) {
    EXPECT_FALSE(dfa.processChar('a'));
    EXPECT_FALSE(dfa.processChar('.'));
}

// Integer part tests
TEST_F(ConstDFATest, HandlesMultipleDigits) {
    dfa.processChar('1');
    dfa.processChar('2');
    EXPECT_TRUE(dfa.processChar('3'));
}

TEST_F(ConstDFATest, TransitionsToDecimalOnDot) {
    dfa.processChar('1');
    EXPECT_TRUE(dfa.processChar('.'));
    EXPECT_TRUE(dfa.processChar('0'));
    EXPECT_EQ(dfa.finalizeToken().getType(), TokenType::FLOAT_CONST);
}

// Decimal part tests
TEST_F(ConstDFATest, HandlesDigitsInDecimalPart) {
    dfa.processChar('1');
    dfa.processChar('.');
    EXPECT_TRUE(dfa.processChar('1'));
    EXPECT_EQ(dfa.finalizeToken().getType(), TokenType::FLOAT_CONST);
}

// Finalize token tests
TEST_F(ConstDFATest, FinalizesAsConstWhenNoDecimal) {
    dfa.processChar('1');
    dfa.processChar('2');
    Token token = dfa.finalizeToken();
    EXPECT_EQ(token.getType(), TokenType::CONST);
    EXPECT_EQ(token.getText(), "12");
}

TEST_F(ConstDFATest, FinalizesAsFloatConstWithDecimal) {
    dfa.processChar('1');
    dfa.processChar('.');
    dfa.processChar('2');
    Token token = dfa.finalizeToken();
    EXPECT_EQ(token.getType(), TokenType::FLOAT_CONST);
    EXPECT_EQ(token.getText(), "1.2");
}

// Reset tests
TEST_F(ConstDFATest, ResetsCorrectly) {
    dfa.processChar('1');
    dfa.processChar('.');
    dfa.processChar('2');
    dfa.reset();
    EXPECT_FALSE(dfa.hasToken());
    EXPECT_FALSE(dfa.processChar('.'));
}