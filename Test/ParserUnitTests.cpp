#include "gtest/gtest.h"
#include "Parser.h"
#include "Token.h"

// Helper function to create a token
Token createToken(TokenType type, const std::string& value) {
    Token token;
    token.type = type;
    token.value = value;
    return token;
}

// Test for parseDeclaration
TEST(ParserTest, ParseDeclaration) {
    std::vector<Token> tokens = {
            createToken(TokenType::START, "START"),
            createToken(TokenType::TYPE, "bool"),
            createToken(TokenType::IDENTIFIER, "x"),
            createToken(TokenType::OPERATOR, "="),
            createToken(TokenType::STRING, "true"),
            createToken(TokenType::PUNCTUATION, ";")
    };
    Parser parser(tokens);
    auto node = parser.parseDeclaration();
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->getType(), valueNode);
}

// Test for parseChar
TEST(ParserTest, ParseChar) {
    std::vector<Token> tokens = {
            createToken(TokenType::START, "START"),
            createToken(TokenType::STRING, "'a'")
    };
    Parser parser(tokens);
    auto node = parser.parseChar();
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->getType(), charNode);
}

// Test for parseBool
TEST(ParserTest, ParseBool) {
    std::vector<Token> tokens = {
            createToken(TokenType::START, "START"),
            createToken(TokenType::BOOL, "true"),

    };
    Parser parser(tokens);
    auto node = parser.parseBool();
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->getType(), boolNode);
}

// Test for parseFloat
TEST(ParserTest, ParseFloat) {
    std::vector<Token> tokens = {
            createToken(TokenType::START, "START"),
            createToken(TokenType::FLOAT_CONST, "3.14")
    };
    Parser parser(tokens);
    auto node = parser.parseFloat();
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->getType(), floatNode);
}

// Test for parseInt
TEST(ParserTest, ParseInt) {
    std::vector<Token> tokens = {
            createToken(TokenType::START, "START"),
            createToken(TokenType::CONST, "123")
    };
    Parser parser(tokens);
    auto node = parser.parseInt();
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->getType(), intNode);
}

// Test for parseString
TEST(ParserTest, ParseString) {
    std::vector<Token> tokens = {
            createToken(TokenType::START, "START"),
            createToken(TokenType::STRING, "\"Hello, World!\"")
    };
    Parser parser(tokens);
    auto node = parser.parseString();
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->getType(), stringNode);
}

// Test for parseCondition
TEST(ParserTest, ParseCondition) {
    std::vector<Token> tokens = {
            createToken(TokenType::START, "START"),
            createToken(TokenType::IDENTIFIER, "x"),
            createToken(TokenType::OPERATOR, "=="),
            createToken(TokenType::CONST, "10"),
            createToken(TokenType::OPERATOR, "+"),
            createToken(TokenType::CONST, "10")
    };
    Parser parser(tokens);
    auto node = parser.parseCondition();
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->getType(), conditionNode);
}

// Test for parseForLoop
TEST(ParserTest, ParseForLoop) {
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
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->getType(), forLoopNode);
}

// Test for parseSwitch
TEST(ParserTest, ParseSwitch) {
    std::vector<Token> tokens = {
            createToken(TokenType::START, "START"),
            createToken(TokenType::CONTROL, "switch"),
            createToken(TokenType::PUNCTUATION, "("),
            createToken(TokenType::IDENTIFIER, "x"),
            createToken(TokenType::PUNCTUATION, ")"),
            createToken(TokenType::PUNCTUATION, "{"),
            createToken(TokenType::CONTROL, "case"),
            createToken(TokenType::CONST, "1"),
            createToken(TokenType::PUNCTUATION, ":"),
            createToken(TokenType::TYPE, "int"),
            createToken(TokenType::IDENTIFIER, "y"),
            createToken(TokenType::OPERATOR, "="),
            createToken(TokenType::CONST, "2"),
            createToken(TokenType::PUNCTUATION, ";"),
            createToken(TokenType::PUNCTUATION, "}")
    };
    Parser parser(tokens);
    auto node = parser.parseSwitch();
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->getType(), switchNode);
}

// Test for parseStruct
TEST(ParserTest, ParseStruct) {
    std::vector<Token> tokens = {
            createToken(TokenType::START, "START"),
            createToken(TokenType::TYPE, "struct"),
            createToken(TokenType::IDENTIFIER, "MyStruct"),
            createToken(TokenType::PUNCTUATION, "{"),
            createToken(TokenType::TYPE, "int"),
            createToken(TokenType::IDENTIFIER, "a"),
            createToken(TokenType::PUNCTUATION, ";"),
            createToken(TokenType::TYPE, "float"),
            createToken(TokenType::IDENTIFIER, "b"),
            createToken(TokenType::PUNCTUATION, ";"),
            createToken(TokenType::PUNCTUATION, "}")
    };
    Parser parser(tokens);
    auto node = parser.parseStruct();
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->getType(), structNode);
}

// Test for parseArray
TEST(ParserTest, ParseArray) {
    std::vector<Token> tokens = {
            createToken(TokenType::START, "START"),
            createToken(TokenType::TYPE, "int"),
            createToken(TokenType::IDENTIFIER, "arr"),
            createToken(TokenType::PUNCTUATION, "["),
            createToken(TokenType::CONST, "10"),
            createToken(TokenType::PUNCTUATION, "]"),
            createToken(TokenType::PUNCTUATION, ";")
    };
    Parser parser(tokens);
    auto node = parser.parseDeclaration();
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->getType(), arrayNode);
}

// Test for parseIfStatement
TEST(ParserTest, ParseIfStatement) {
    std::vector<Token> tokens = {
            createToken(TokenType::START, "START"),
            createToken(TokenType::CONTROL, "if"),
            createToken(TokenType::PUNCTUATION, "("),
            createToken(TokenType::IDENTIFIER, "x"),
            createToken(TokenType::OPERATOR, "=="),
            createToken(TokenType::CONST, "10"),
            createToken(TokenType::PUNCTUATION, ")"),
            createToken(TokenType::PUNCTUATION, "{"),
            createToken(TokenType::PUNCTUATION, "}")
    };
    Parser parser(tokens);
    auto node = parser.parseIfStatement();
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->getType(), ifNode);
}

// Test for parseConsole
TEST(ParserTest, ParseConsole) {
    std::vector<Token> tokens = {
            createToken(TokenType::START, "START"),
            createToken(TokenType::CONSOLE, "console"),
            createToken(TokenType::PUNCTUATION, "("),
            createToken(TokenType::STRING, "\"Hello\""),
            createToken(TokenType::PUNCTUATION, ")")
    };
    Parser parser(tokens);
    auto node = parser.parseConsole();
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->getType(), consoleNode);
}

// Test for parseJump
TEST(ParserTest, ParseJump) {
    std::vector<Token> tokens = {
            createToken(TokenType::START, "START"),
            createToken(TokenType::JUMP, "break")
    };
    Parser parser(tokens);
    auto node = parser.parseJump();
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->getType(), jumpNode); // Assuming parseJump creates a JumpNode
}

// Test for parseWhileLoop
TEST(ParserTest, ParseWhileLoop) {
    std::vector<Token> tokens = {
            createToken(TokenType::START, "START"),
            createToken(TokenType::CONTROL, "while"),
            createToken(TokenType::PUNCTUATION, "("),
            createToken(TokenType::IDENTIFIER, "x"),
            createToken(TokenType::OPERATOR, "<"),
            createToken(TokenType::CONST, "10"),
            createToken(TokenType::PUNCTUATION, ")"),
            createToken(TokenType::PUNCTUATION, "{"),
            createToken(TokenType::PUNCTUATION, "}")
    };
    Parser parser(tokens);
    auto node = parser.parseWhileLoop();
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->getType(), whileNode);
}

// Test for parseRandom
TEST(ParserTest, ParseRandom) {
    std::vector<Token> tokens = {
            createToken(TokenType::START, "START"),
            createToken(TokenType::TYPE, "bool?"),
            createToken(TokenType::IDENTIFIER, "abc"),


    };
    Parser parser(tokens);
    auto node = parser.parseRandom();
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->getType(), randomNode);
}

// Test for parseReturn
TEST(ParserTest, ParseReturn) {
    std::vector<Token> tokens = {
            createToken(TokenType::START, "START"),
            createToken(TokenType::JUMP, "return"),
            createToken(TokenType::IDENTIFIER, "x")
    };
    Parser parser(tokens);
    auto node = parser.parseReturn();
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->getType(), returnNode);
}


// Test for parseUsInt
TEST(ParserTest, ParseUsInt) {
    std::vector<Token> tokens = {
            createToken(TokenType::START, "START"),
            createToken(TokenType::CONST, "42")
    };
    Parser parser(tokens);
    auto node = parser.parseUsInt();
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->getType(), usIntNode);
}

// Test for parseIdentifier
TEST(ParserTest, ParseIdentifier) {
    std::vector<Token> tokens = {
            createToken(TokenType::START, "START"),
            createToken(TokenType::IDENTIFIER, "x")
    };
    Parser parser(tokens);
    auto node = parser.parseIdentifier();
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->getType(), identifierNode);
}

// Test for parseFunctionCall
TEST(ParserTest, ParseFunctionCall) {
    std::vector<Token> tokens = {
            createToken(TokenType::START, "START"),
            createToken(TokenType::IDENTIFIER, "foo"),
            createToken(TokenType::PUNCTUATION, "("),
            createToken(TokenType::IDENTIFIER, "x"),
            createToken(TokenType::PUNCTUATION, ")")
    };
    Parser parser(tokens);
    auto node = parser.parseFunctionCall();
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->getType(), functionCallNode);
}

// Test for parseFunctionArguments
TEST(ParserTest, ParseFunctionArguments) {
    std::vector<Token> tokens = {
            createToken(TokenType::START, "START"),
            createToken(TokenType::TYPE, "int"),
            createToken(TokenType::IDENTIFIER, "x"),
            createToken(TokenType::PUNCTUATION, ","),
            createToken(TokenType::TYPE, "float"),
            createToken(TokenType::IDENTIFIER, "y"),
            createToken(TokenType::PUNCTUATION, ")")
    };
    Parser parser(tokens);
    auto arguments = parser.parseFunctionArguments();
    ASSERT_FALSE(arguments.empty());  // Expect arguments to be non-empty

    // Verify the types of the nodes in the arguments vector
    EXPECT_EQ(arguments[0]->getType(), declarationNode);
    EXPECT_EQ(arguments[1]->getType(), declarationNode);
}