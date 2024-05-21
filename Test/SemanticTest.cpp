#include "gtest/gtest.h"
#include "Parser.h"
#include "Semantic.h"

SemanticAnalyser semanticanalyser;

TEST(KowalskiTest, KowalskiFloat) {
    std::shared_ptr<FloatNode> node = std::make_shared<FloatNode>();
    node->Floating_Point = 1.2;
    EXPECT_FLOAT_EQ(1.2, node->Floating_Point);
}

TEST(KowalskiTest, KowalskiInt) {
    std::shared_ptr<IntNode> node = std::make_shared<IntNode>();
    node->integer = 1;
    EXPECT_EQ(1,node->integer);
}

TEST(KowalskiTest, KowalskiReturn) {
    std::shared_ptr<ReturnNode> node = std::make_shared<ReturnNode>();
    node->returning = "return";
    node->identifier = "xD";
    EXPECT_EQ("return",node->returning);
    EXPECT_EQ("xD",node->identifier);
}

TEST(KowalskiTest, KowalskiChar) {
    std::shared_ptr<CharNode> node = std::make_shared<CharNode>();
    node->character = "r";
    EXPECT_EQ("r",node->character);
}

TEST(KowalskiTest,KowalskiKondi){
    auto KondiNode = std::make_shared<ConditionNode>();
    auto aNode = std::make_shared<StringNode>();
    auto bNode = std::make_shared<StringNode>();
    std::cout<< KondiNode->condition<<std::endl;
    KondiNode->aNode = aNode;
    KondiNode->bNode = bNode;
    EXPECT_NO_THROW(semanticanalyser.kowalskiKondi(KondiNode));

}

TEST(KowalskiTest, KowalskiWhile) {
    std::shared_ptr<WhileNode> node = std::make_shared<WhileNode>();
    std::shared_ptr<IntNode> Anode = std::make_shared<IntNode>();
    std::shared_ptr<IntNode> Bnode = std::make_shared<IntNode>();
    Anode->integer = 4;
    Bnode->integer = 3;
    node->condition = std::make_shared<ConditionNode>();
    node->condition->aNode = Anode;
    node->condition->condition = ">=";
    node->condition->bNode = Bnode;
    auto body = std::shared_ptr<DeclarationNode>(); //lazy why to write it : )
    body->identifier = "abc";
    body->type = "int";
    node->body.push_back(body);

    EXPECT_NO_THROW(semanticanalyser.kowalskiWhile(node));
}

