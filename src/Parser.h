//
// Created by Yuki on 29/04/2024.
//
#ifndef PARSER_H
#define PARSER_H

#include "Token.h"
#include <vector>
#include <memory>
#include <iostream>
enum nodeType{
    declarationNode,
    charNode,
    forLoopNode,
    ifNode,
    structNode,
    functionNode,
    variableNode,
    floatNode,
    stringNode,
    operatorNode,
    whileNode,
    conditionNode,
    caseNode,
    switchNode,
    intNode,
    usIntNode,
    consoleNode,
    boolNode
};
// Base class for all AST nodes
struct ASTNode {
    virtual ~ASTNode() {}
public:
    virtual nodeType getType() const = 0;
    virtual void accept(class ASTNodeVisitor& visitor) = 0;
};

// Node for declarations
struct DeclarationNode : ASTNode {
    nodeType getType() const override {return nodeType::declarationNode;}
    std::string identifier;
    void accept(ASTNodeVisitor& visitor) override;
    std::string type;
};

struct ConsoleNode : ASTNode{
    nodeType getType() const override {return nodeType::consoleNode;}
    std::vector<std::shared_ptr<ASTNode>> message;
};

struct CharNode : ASTNode {
    nodeType getType() const override {return nodeType::charNode;}
    std::string character;
    void accept(ASTNodeVisitor& visitor) override;
};

struct ForLoopNode : ASTNode {
    std::shared_ptr<ASTNode> declaration;
    std::shared_ptr<ASTNode> condition;
    std::shared_ptr<ASTNode> expression;
    std::vector<std::shared_ptr<ASTNode>> body;
    nodeType getType() const override {return nodeType::forLoopNode;}
    void accept(ASTNodeVisitor& visitor) override;
};

struct IfNode : ASTNode {
    std::shared_ptr<ASTNode> condition;
    std::vector<std::shared_ptr<ASTNode>> body;
    nodeType getType() const override {return nodeType::ifNode;}
    std::vector<std::shared_ptr<ASTNode>> elseBody;
    void accept(ASTNodeVisitor& visitor) override;
};
// Node for Struct declarations
struct StructNode : DeclarationNode {
    std::shared_ptr<ASTNode> struct_main;
    std::string identifier;
    std::vector<std::shared_ptr<ASTNode>> body;
    nodeType getType() const override {return nodeType::structNode;}
    void accept(ASTNodeVisitor& visitor) override;
};

// Node for variable declarations
struct ValueNode : DeclarationNode {
    std::shared_ptr<ASTNode> value;
    std::string type;
    std::string variable;
    nodeType getType() const override {
        if (type == "int") {return nodeType::intNode;}
        else if (type == "char") {return nodeType::charNode;}
        else if (type == "string") {return nodeType::stringNode;}
        else if (type == "float") {return nodeType::floatNode;}
        else if (type == "bool") {return nodeType::boolNode;}
    }
    // Additional properties can be added here
    void accept(ASTNodeVisitor& visitor) override;
};

struct IdentifierNode : ASTNode {
    std::string identifier;
};

struct ReturnNode : ASTNode {
    std::string returning;
    std::string identifier;
};


struct FloatNode : ASTNode {
    float Floating_Point;
    nodeType getType() const override {return nodeType::floatNode;}
    void accept(ASTNodeVisitor& visitor) override;
};

struct IntNode : ASTNode {
    int integer;
    nodeType getType() const override {return nodeType::intNode;}
    void accept(ASTNodeVisitor& visitor) override;
};

struct UsIntNode : ASTNode {
    int usinteger;
    nodeType getType() const override {return nodeType::usIntNode;}
};

struct BoolNode : ASTNode{
    bool boolean;
    nodeType getType() const override {return nodeType::boolNode;}
};

struct StringNode : ASTNode {
    std::string StringOfChars;
    nodeType getType() const override {return nodeType::stringNode;}
    void accept(ASTNodeVisitor& visitor) override;
};

struct SwitchNode : ASTNode {
    std::shared_ptr<ASTNode> condition;
    std::vector<std::shared_ptr<CaseNode>> caseBranch;
    nodeType getType() const override {return nodeType::switchNode;}
    SwitchNode() : condition(nullptr), caseBranch() {}
    void accept(ASTNodeVisitor& visitor) override;
};

struct CaseNode : ASTNode {
    std::shared_ptr<ASTNode> sucessCondition;
    std::vector<std::shared_ptr<ASTNode>> Branch;
    void accept(ASTNodeVisitor& visitor) override;
    public: nodeType getType() const override {return nodeType::caseNode;}
};

struct ConditionNode : ASTNode {
    std::string condition;
    std::shared_ptr<ASTNode> aNode;
    std::shared_ptr<ASTNode> bNode;
    nodeType getType() const override {return nodeType::conditionNode;}
    void accept(ASTNodeVisitor& visitor) override;
};

struct WhileNode : ASTNode {
    std::shared_ptr<ASTNode> condition;
    std::vector<std::shared_ptr<ASTNode>> body;
    void accept(ASTNodeVisitor& visitor) override;
    nodeType getType() const override {return nodeType::whileNode;}
};

struct JumpNode : ASTNode {
    std::string breaker;
    std::string continuer;
};

struct RandomNode : DeclarationNode {
    std::vector<int> RandomIntRange;
    std::vector<float> RandomFloatRange;
};

struct ArrayNode : DeclarationNode {
    std::string size;
    std::vector<std::shared_ptr<ASTNode>> body;
};

struct FunctionCallNode : IdentifierNode {
    std::vector<std::shared_ptr<ASTNode>> arguments;
};

struct FunctionNode : DeclarationNode {
    std::vector<std::shared_ptr<ASTNode>> arguments;
    std::vector<std::shared_ptr<ASTNode>> body;
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
    std::shared_ptr<ASTNode> parseExpression();
    std::shared_ptr<ASTNode> parseStatement();
    std::shared_ptr<ASTNode> parseArray();
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
    std::shared_ptr<ASTNode> parseFunctionArguments();

private:
    std::vector<Token> tokens;
    size_t pos = 0;

    bool lookAhead(TokenType expectedType);
    void match(TokenType expectedType);
    void match(TokenType expectedType, const std::string& expectedValue);
    std::vector<std::shared_ptr<ASTNode>> parseFunctionBody();  // Assume this function parses a function body
    std::vector<std::shared_ptr<ASTNode>> parseStructBody();
    std::vector<std::shared_ptr<ASTNode>> parseLoopBody();
    std::vector<std::shared_ptr<ASTNode>> parseArrayContents();
};

#endif; // PARSER_H
