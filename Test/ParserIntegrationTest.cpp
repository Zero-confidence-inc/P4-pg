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
            createToken(TokenType::PUNCTUATION, ";"),//10
            createToken(TokenType::TYPE,"int"),
            createToken(TokenType::IDENTIFIER,"Function1"),
            createToken(TokenType::PUNCTUATION,"("),
            createToken(TokenType::PUNCTUATION,")"),
            createToken(TokenType::PUNCTUATION,"{"),
            createToken(TokenType::CONTROL, "if"),
            createToken(TokenType::PUNCTUATION, "("),
            createToken(TokenType::IDENTIFIER, "x"),
            createToken(TokenType::OPERATOR, "=="),
            createToken(TokenType::CONST, "42"),//20
            createToken(TokenType::PUNCTUATION, ")"),
            createToken(TokenType::PUNCTUATION, "{"),
            createToken(TokenType::IDENTIFIER, "y"),
            createToken(TokenType::OPERATOR, "="),
            createToken(TokenType::FLOAT_CONST, "6.28"),
            createToken(TokenType::PUNCTUATION, ";"),
            createToken(TokenType::PUNCTUATION, "}"),
            createToken(TokenType::PUNCTUATION,"}")//28
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

    // Check the third node (function declaration)
    auto thirdNode = ast[2];
    ASSERT_NE(thirdNode, nullptr);
    EXPECT_EQ(thirdNode->getType(), functionNode);
    auto functionNodePtr = std::dynamic_pointer_cast<FunctionNode>(thirdNode);
    ASSERT_NE(functionNodePtr, nullptr);
    EXPECT_EQ(functionNodePtr->type, "int");
    EXPECT_EQ(functionNodePtr->identifier, "Function1");

    // Check the function's body (if statement)
    ASSERT_FALSE(functionNodePtr->body.empty());
    auto ifNodePtr = std::dynamic_pointer_cast<IfNode>(functionNodePtr->body[0]);
    ASSERT_NE(ifNodePtr, nullptr);
    ASSERT_NE(ifNodePtr->condition, nullptr);
    EXPECT_EQ(ifNodePtr->condition->getType(), conditionNode);

    // Check the if body node (should be a condition node representing y = 6.28)
    EXPECT_EQ(ifNodePtr->body.size(), 1); // Only one statement inside if
    auto ifBodyNode = ifNodePtr->body[0];
    ASSERT_NE(ifBodyNode, nullptr);
    EXPECT_EQ(ifBodyNode->getType(), conditionNode);
    auto conditionNode = std::dynamic_pointer_cast<ConditionNode>(ifBodyNode);
    ASSERT_NE(conditionNode, nullptr);
    EXPECT_EQ(conditionNode->condition, "=");
    ASSERT_NE(conditionNode->aNode, nullptr);
    EXPECT_EQ(conditionNode->aNode->getType(), identifierNode);
    auto identifierNodePtr = std::dynamic_pointer_cast<IdentifierNode>(conditionNode->aNode);
    ASSERT_NE(identifierNodePtr, nullptr);
    EXPECT_EQ(identifierNodePtr->identifier, "y");
    ASSERT_NE(conditionNode->bNode, nullptr);
    EXPECT_EQ(conditionNode->bNode->getType(), floatNode);
    auto floatNodePtr = std::dynamic_pointer_cast<FloatNode>(conditionNode->bNode);
    ASSERT_NE(floatNodePtr, nullptr);
    EXPECT_EQ(floatNodePtr->Floating_Point, 6.28f);
}
