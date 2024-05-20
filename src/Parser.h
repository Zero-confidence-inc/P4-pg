//
// Created by Yuki on 29/04/2024.
//
#ifndef PARSER_H
#define PARSER_H

#include "Token.h"
#include <vector>
#include <memory>
#include <iostream>

enum nodeType {
    declarationNode,
    charNode,
    forLoopNode,
    ifNode,
    structNode,
    functionNode,
    functionCallNode,
    valueNode,
    floatNode,
    stringNode,
    whileNode,
    conditionNode,
    caseNode,
    switchNode,
    intNode,
    usIntNode,
    consoleNode,
    boolNode,
    arrayNode,
    returnNode,
    identifierNode,
    randomNode,
    jumpNode,
    defaultNode
};

// Base class for all AST nodes
struct ASTNode {
    virtual ~ASTNode() = default;
    virtual nodeType getType() const = 0;

};

// Node for declarations
struct DeclarationNode : ASTNode {
    std::string identifier;
    std::string type;
    nodeType getType() const override { return nodeType::declarationNode; }

};

struct ConsoleNode : ASTNode {
    nodeType getType() const override { return nodeType::consoleNode; }
    std::vector<std::shared_ptr<ASTNode>> message;

};

struct CharNode : ASTNode {
    nodeType getType() const override { return nodeType::charNode; }
    std::string character;

};

struct ConditionNode : ASTNode {
    std::string condition;
    std::shared_ptr<ASTNode> aNode;
    std::shared_ptr<ASTNode> bNode;
    nodeType getType() const override { return nodeType::conditionNode; }

};

struct CaseNode : ASTNode {
    std::shared_ptr<ASTNode> sucessCondition;
    std::vector<std::shared_ptr<ASTNode>> Branch;
    nodeType getType() const override { return nodeType::caseNode; }

};

struct ForLoopNode : ASTNode {
    std::shared_ptr<DeclarationNode> declaration;
    std::shared_ptr<ConditionNode> condition;
    std::shared_ptr<ConditionNode> expression;
    std::vector<std::shared_ptr<ASTNode>> body;
    nodeType getType() const override { return nodeType::forLoopNode; }

};

struct IfNode : ASTNode {
    std::shared_ptr<ConditionNode> condition;
    std::vector<std::shared_ptr<ASTNode>> body;
    std::vector<std::shared_ptr<ASTNode>> elseBody;
    nodeType getType() const override { return nodeType::ifNode; }

};

// Node for Struct declarations
struct StructNode : DeclarationNode {
    std::shared_ptr<ASTNode> struct_main;
    std::vector<std::shared_ptr<ASTNode>> body;
    nodeType getType() const override { return nodeType::structNode; }

};

// Node for variable declarations
struct ValueNode : DeclarationNode {
    std::shared_ptr<ASTNode> value;
    nodeType getType() const override { return nodeType::valueNode; }

};

struct IdentifierNode : ASTNode {
    std::string identifier;
    nodeType getType() const override { return nodeType::identifierNode; }

};

struct ReturnNode : ASTNode {
    std::string returning;
    std::string identifier;
    nodeType getType() const override { return nodeType::returnNode; }

};

struct FloatNode : ASTNode {
    float Floating_Point;
    nodeType getType() const override { return nodeType::floatNode; }

};

struct IntNode : ASTNode {
    int integer;
    nodeType getType() const override { return nodeType::intNode; }

};

struct UsIntNode : ASTNode {
    int usinteger;
    nodeType getType() const override { return nodeType::usIntNode; }

};

struct BoolNode : ASTNode {
    bool boolean;
    nodeType getType() const override { return nodeType::boolNode; }

};

struct StringNode : ASTNode {
    std::string StringOfChars;
    nodeType getType() const override { return nodeType::stringNode; }

};

struct SwitchNode : ASTNode {
    std::shared_ptr<ConditionNode> condition;
    std::vector<std::shared_ptr<CaseNode>> caseBranch;
    std::shared_ptr<DefaultNode> deNode;
    nodeType getType() const override { return nodeType::switchNode; }
    SwitchNode() : condition(nullptr), caseBranch() {}

};

struct DefaultNode : ASTNode {
    std::vector<std::shared_ptr<ASTNode>> Branch;
    nodeType getType() const override { return nodeType::defaultNode; }
};

struct WhileNode : ASTNode {
    std::shared_ptr<ConditionNode> condition;
    std::vector<std::shared_ptr<ASTNode>> body;
    nodeType getType() const override { return nodeType::whileNode; }

};

struct JumpNode : ASTNode {
    std::string breaker;
    std::string continuer;
    nodeType getType() const override { return nodeType::jumpNode; }

};

struct RandomNode : DeclarationNode {
    std::vector<int> RandomIntRange;
    std::vector<float> RandomFloatRange;
    nodeType getType() const override { return nodeType::randomNode; }

};

struct ArrayNode : DeclarationNode {
    std::string size;
    std::vector<std::shared_ptr<ASTNode>> body;
    nodeType getType() const override { return nodeType::arrayNode; }

};

struct FunctionCallNode : IdentifierNode {
    std::vector<std::shared_ptr<ASTNode>> arguments;
    nodeType getType() const override { return nodeType::functionCallNode; }

};

struct FunctionNode : DeclarationNode {
    std::vector<std::shared_ptr<ASTNode>> arguments;
    std::vector<std::shared_ptr<ASTNode>> body;
    nodeType getType() const override { return nodeType::functionNode; }

};

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);
    void parseProgram();
    std::shared_ptr<ASTNode> parseDeclaration();
    std::shared_ptr<ASTNode> parseChar();
    std::shared_ptr<ASTNode> parseBool();
    std::shared_ptr<ASTNode> parseFloat();
    std::shared_ptr<ASTNode> parseInt();
    std::shared_ptr<ASTNode> parseString();
    std::shared_ptr<ASTNode> parseCondition();
    std::shared_ptr<ASTNode> parseForLoop();
    std::shared_ptr<ASTNode> parseSwitch();
    std::shared_ptr<ASTNode> parseStruct();
    //std::shared_ptr<ASTNode> parseArray();
    std::shared_ptr<ASTNode> parseIfStatement();
    std::shared_ptr<ASTNode> parseConsole();
    std::shared_ptr<ASTNode> parseJump();
    std::shared_ptr<ASTNode> parseWhileLoop();
    std::shared_ptr<ASTNode> parseRandom();
    std::shared_ptr<ASTNode> parseReturn();
    std::shared_ptr<ASTNode> parseValues();
    std::shared_ptr<ASTNode> parseUsInt();
    std::shared_ptr<ASTNode> parseIdentifier();
    std::shared_ptr<ASTNode> parseFunctionCall();
    std::vector<std::shared_ptr<ASTNode>> parseFunctionArguments();

private:
    std::vector<Token> tokens;
    size_t pos = 0;

    bool lookAhead(TokenType expectedType);
    void match(TokenType expectedType);
    void match(TokenType expectedType, const std::string& expectedValue);
    std::vector<std::shared_ptr<ASTNode>> parseFunctionBody();
    std::vector<std::shared_ptr<ASTNode>> parseStructBody();
    std::vector<std::shared_ptr<ASTNode>> parseLoopBody();
    std::vector<std::shared_ptr<ASTNode>> parseArrayContents();
};

#endif // PARSER_H
