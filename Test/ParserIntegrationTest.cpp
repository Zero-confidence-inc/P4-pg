//
// Created by a guy who's ready to jump out the window from the 3rd floor on 20/05/2024.
//
#include "gtest/gtest.h"
#include "Parser.h"
#include "Token.h"
#include "TokenCreator.h"

// Integration test for parseProgram
TEST(ParserIntegrationTest, ParseProgram) {
    std::vector<Token> tokens = {
            createToken(TokenType::START, "START"),
            createToken(TokenType::TYPE, "int"),
            createToken(TokenType::IDENTIFIER, "x"),
            createToken(TokenType::OPERATOR, "="),
            createToken(TokenType::CONST, "42"),
            createToken(TokenType::PUNCTUATION, ";"),
            createToken(TokenType::TYPE, "float"),
            createToken(TokenType::IDENTIFIER, "y"),
            createToken(TokenType::OPERATOR, "="),
            createToken(TokenType::FLOAT_CONST, "3.14"),
            createToken(TokenType::PUNCTUATION, ";"),
            createToken(TokenType::CONTROL, "if"),
            createToken(TokenType::PUNCTUATION, "("),
            createToken(TokenType::IDENTIFIER, "x"),
            createToken(TokenType::OPERATOR, "=="),
            createToken(TokenType::CONST, "42"),
            createToken(TokenType::PUNCTUATION, ")"),
            createToken(TokenType::PUNCTUATION, "{"),
            createToken(TokenType::IDENTIFIER, "y"),
            createToken(TokenType::OPERATOR, "="),
            createToken(TokenType::FLOAT_CONST, "6.28"),
            createToken(TokenType::PUNCTUATION, ";"),
            createToken(TokenType::PUNCTUATION, "}")
    };

    Parser parser(tokens);
    auto ast = parser.parseProgram();

    ASSERT_FALSE(ast.empty());


    // Check the first node (declaration of int x = 42)
    auto firstNode = ast[0];
    ASSERT_NE(firstNode, nullptr);
    EXPECT_EQ(firstNode->getType(), valueNode);
    auto valueNode1 = std::dynamic_pointer_cast<ValueNode>(firstNode);
    ASSERT_NE(valueNode1, nullptr);
    EXPECT_EQ(valueNode1->type, "int");
    EXPECT_EQ(valueNode1->identifier, "x");
    EXPECT_EQ(valueNode1->value->getType(), intNode);

    // Check the second node (declaration of float y = 3.14)
    auto secondNode = ast[1];
    ASSERT_NE(secondNode, nullptr);
    EXPECT_EQ(secondNode->getType(), valueNode);
    auto valueNode2 = std::dynamic_pointer_cast<ValueNode>(secondNode);
    ASSERT_NE(valueNode2, nullptr);
    EXPECT_EQ(valueNode2->type, "float");
    EXPECT_EQ(valueNode2->identifier, "y");
    EXPECT_EQ(valueNode2->value->getType(), floatNode);

    // Check the third node (if statement)
    auto thirdNode = ast[2];
    ASSERT_NE(thirdNode, nullptr);
    EXPECT_EQ(thirdNode->getType(), ifNode);
    auto ifNodePtr = std::dynamic_pointer_cast<IfNode>(thirdNode);
    ASSERT_NE(ifNodePtr, nullptr);
    ASSERT_NE(ifNodePtr->condition, nullptr);
    EXPECT_EQ(ifNodePtr->condition->getType(), conditionNode);
    EXPECT_EQ(ifNodePtr->body.size(), 1); // Only one statement inside if
    auto ifBodyNode = ifNodePtr->body[0];
    ASSERT_NE(ifBodyNode, nullptr);
    EXPECT_EQ(ifBodyNode->getType(), valueNode);
    auto ifValueNode = std::dynamic_pointer_cast<ValueNode>(ifBodyNode);
    ASSERT_NE(ifValueNode, nullptr);
    EXPECT_EQ(ifValueNode->type, "float");
    EXPECT_EQ(ifValueNode->identifier, "y");
    EXPECT_EQ(ifValueNode->value->getType(), floatNode);
}
