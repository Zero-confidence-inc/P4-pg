#include "gtest/gtest.h"
#include "Parser.h"
#include "Token.h"
#include "Semantic.h"

// Helper function to create a token
Token createToken(TokenType type, const std::string& value) {
    Token token;
    token.type = type;
    token.value = value;
    return token;
}

TEST(KowalskiTest, KowalskiFloat) {
    const std::shared_ptr<FloatNode> node;
    node->Floating_Point = 420.69;
    EXPECT_FLOAT_EQ(420.69, kowalskiFloat(node));
}

TEST(KowalskiTest, KowalskiInt) {
    std::vector<Token> tokens = {
        createToken(TokenType::START, "START"),
        createToken(TokenType::CONST, "42")
};
    Parser parser(tokens);
    auto node = parser.parseInt();
    auto convNode = std::dynamic_pointer_cast<IntNode>(node);
    EXPECT_EQ(42, kowalskiInt(convNode));
}

TEST(KowalskiTest, KowalskiForLoop) {
    std::vector<Token> tokens = {
        createToken(TokenType::START, "START"),
        createToken(TokenType::LOOP, "for"),
        createToken(TokenType::PUNCTUATION, "("),
        createToken(TokenType::TYPE, "int"),
        createToken(TokenType::IDENTIFIER, "i"),
        createToken(TokenType::OPERATOR, "="),
        createToken(TokenType::CONST, "0"),
        createToken(TokenType::PUNCTUATION, ";"),
        createToken(TokenType::IDENTIFIER, "i"),
        createToken(TokenType::OPERATOR, "<"),
        createToken(TokenType::CONST, "10"),
        createToken(TokenType::PUNCTUATION, ";"),
        createToken(TokenType::IDENTIFIER, "i"),
        createToken(TokenType::OPERATOR, "++"),
        createToken(TokenType::PUNCTUATION, ")"),
        createToken(TokenType::PUNCTUATION, "{"),
        createToken(TokenType::PUNCTUATION, "}")
};
    Parser parser(tokens);
    auto node = parser.parseForLoop();
    auto convNode = std::dynamic_pointer_cast<ForLoopNode>(node);
    SemanticAnalyser::kowalskiFor(convNode);
}

TEST(KowalskiTest, KowalskiRandom) {
    std::vector<Token> tokens = {
        createToken(TokenType::START, "START"),
        createToken(TokenType::TYPE, "bool?"),
        createToken(TokenType::IDENTIFIER, "abc"),


    };
    Parser parser(tokens);
    auto node = parser.parseRandom();
    auto convNode = std::dynamic_pointer_cast<RandomNode>(node);
    SemanticAnalyser::kowalskiRandom(convNode);
}