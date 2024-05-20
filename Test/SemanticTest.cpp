#include "gtest/gtest.h"
#include "Parser.h"
#include "Semantic.h"


TEST(KowalskiTest, KowalskiFloat) {
    const std::shared_ptr<FloatNode> node;
    node->Floating_Point = 420.69;
    EXPECT_FLOAT_EQ(420.69, kowalskiFloat(node));
}

TEST(KowalskiTest, KowalskiInt) {
    const std::shared_ptr<IntNode> node;
    node->integer = 42;
    EXPECT_EQ(42, kowalskiInt(node));
}

TEST(KowalskiTest, KowalskiForLoop) {

}

TEST(KowalskiTest, KowalskiRandom) {

}