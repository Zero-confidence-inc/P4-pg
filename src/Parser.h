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
    operatorNode,
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
    jumpNode
};

// Base class for all AST nodes
struct ASTNode {
    virtual ~ASTNode() = default;
    virtual nodeType getType() const = 0;
    virtual void accept(class ASTNodeVisitor& visitor) = 0;
};

// Node for declarations
struct DeclarationNode : ASTNode {
    std::string identifier;
    std::string type;
    nodeType getType() const override { return nodeType::declarationNode; }
    void accept(ASTNodeVisitor& visitor) override;
};

struct ConsoleNode : ASTNode {
    nodeType getType() const override { return nodeType::consoleNode; }
    std::vector<std::shared_ptr<ASTNode>> message;
    void accept(ASTNodeVisitor& visitor) override;
};

struct CharNode : ASTNode {
    nodeType getType() const override { return nodeType::charNode; }
    std::string character;
    void accept(ASTNodeVisitor& visitor) override;
};

struct ConditionNode : ASTNode {
    std::string condition;
    std::shared_ptr<ASTNode> aNode;
    std::shared_ptr<ASTNode> bNode;
    nodeType getType() const override { return nodeType::conditionNode; }
    void accept(ASTNodeVisitor& visitor) override;
};

struct CaseNode : ASTNode {
    std::shared_ptr<ASTNode> sucessCondition;
    std::vector<std::shared_ptr<ASTNode>> Branch;
    nodeType getType() const override { return nodeType::caseNode; }
    void accept(ASTNodeVisitor& visitor) override;
};

struct ForLoopNode : ASTNode {
    std::shared_ptr<DeclarationNode> declaration;
    std::shared_ptr<ConditionNode> condition;
    std::shared_ptr<ConditionNode> expression;
    std::vector<std::shared_ptr<ASTNode>> body;
    nodeType getType() const override { return nodeType::forLoopNode; }
    void accept(ASTNodeVisitor& visitor) override;
};

struct IfNode : ASTNode {
    std::shared_ptr<ConditionNode> condition;
    std::vector<std::shared_ptr<ASTNode>> body;
    std::vector<std::shared_ptr<ASTNode>> elseBody;
    nodeType getType() const override { return nodeType::ifNode; }
    void accept(ASTNodeVisitor& visitor) override;
};

// Node for Struct declarations
struct StructNode : DeclarationNode {
    std::shared_ptr<ASTNode> struct_main;
    std::vector<std::shared_ptr<ASTNode>> body;
    nodeType getType() const override { return nodeType::structNode; }
    void accept(ASTNodeVisitor& visitor) override;
};

// Node for variable declarations
struct ValueNode : DeclarationNode {
    std::shared_ptr<ASTNode> value;
    nodeType getType() const override { return nodeType::valueNode; }
    void accept(ASTNodeVisitor& visitor) override;
};

struct IdentifierNode : ASTNode {
    std::string identifier;
    nodeType getType() const override { return nodeType::identifierNode; }
    void accept(ASTNodeVisitor& visitor) override;
};

struct ReturnNode : ASTNode {
    std::string returning;
    std::string identifier;
    nodeType getType() const override { return nodeType::returnNode; }
    void accept(ASTNodeVisitor& visitor) override;
};

struct FloatNode : ASTNode {
    float Floating_Point;
    nodeType getType() const override { return nodeType::floatNode; }
    void accept(ASTNodeVisitor& visitor) override;
};

struct IntNode : ASTNode {
    int integer;
    nodeType getType() const override { return nodeType::intNode; }
    void accept(ASTNodeVisitor& visitor) override;
};

struct UsIntNode : ASTNode {
    int usinteger;
    nodeType getType() const override { return nodeType::usIntNode; }
    void accept(ASTNodeVisitor& visitor) override;
};

struct BoolNode : ASTNode {
    bool boolean;
    nodeType getType() const override { return nodeType::boolNode; }
    void accept(ASTNodeVisitor& visitor) override;
};

struct StringNode : ASTNode {
    std::string StringOfChars;
    nodeType getType() const override { return nodeType::stringNode; }
    void accept(ASTNodeVisitor& visitor) override;
};

struct SwitchNode : ASTNode {
    std::shared_ptr<ConditionNode> condition;
    std::vector<std::shared_ptr<CaseNode>> caseBranch;
    nodeType getType() const override { return nodeType::switchNode; }
    SwitchNode() : condition(nullptr), caseBranch() {}
    void accept(ASTNodeVisitor& visitor) override;
};

struct WhileNode : ASTNode {
    std::shared_ptr<ConditionNode> condition;
    std::vector<std::shared_ptr<ASTNode>> body;
    nodeType getType() const override { return nodeType::whileNode; }
    void accept(ASTNodeVisitor& visitor) override;
};

struct JumpNode : ASTNode {
    std::string breaker;
    std::string continuer;
    nodeType getType() const override { return nodeType::jumpNode; }
    void accept(ASTNodeVisitor& visitor) override;
};

struct RandomNode : DeclarationNode {
    std::vector<int> RandomIntRange;
    std::vector<float> RandomFloatRange;
    nodeType getType() const override { return nodeType::randomNode; }
    void accept(ASTNodeVisitor& visitor) override;
};

struct ArrayNode : DeclarationNode {
    std::string size;
    std::vector<std::shared_ptr<ASTNode>> body;
    nodeType getType() const override { return nodeType::arrayNode; }
    void accept(ASTNodeVisitor& visitor) override;
};

struct FunctionCallNode : IdentifierNode {
    std::vector<std::shared_ptr<ASTNode>> arguments;
    nodeType getType() const override { return nodeType::functionCallNode; }
    void accept(ASTNodeVisitor& visitor) override;
};

struct FunctionNode : DeclarationNode {
    std::vector<std::shared_ptr<ASTNode>> arguments;
    std::vector<std::shared_ptr<ASTNode>> body;
    nodeType getType() const override { return nodeType::functionNode; }
    void accept(ASTNodeVisitor& visitor) override;
};

class ASTNodeVisitor {
public:
    virtual void visit(DeclarationNode& node) = 0;
    virtual void visit(ConsoleNode& node) = 0;
    virtual void visit(CharNode& node) = 0;
    virtual void visit(ForLoopNode& node) = 0;
    virtual void visit(IfNode& node) = 0;
    virtual void visit(StructNode& node) = 0;
    virtual void visit(ValueNode& node) = 0;
    virtual void visit(IdentifierNode& node) = 0;
    virtual void visit(ReturnNode& node) = 0;
    virtual void visit(FloatNode& node) = 0;
    virtual void visit(IntNode& node) = 0;
    virtual void visit(UsIntNode& node) = 0;
    virtual void visit(BoolNode& node) = 0;
    virtual void visit(StringNode& node) = 0;
    virtual void visit(SwitchNode& node) = 0;
    virtual void visit(CaseNode& node) = 0;
    virtual void visit(ConditionNode& node) = 0;
    virtual void visit(WhileNode& node) = 0;
    virtual void visit(JumpNode& node) = 0;
    virtual void visit(RandomNode& node) = 0;
    virtual void visit(ArrayNode& node) = 0;
    virtual void visit(FunctionCallNode& node) = 0;
    virtual void visit(FunctionNode& node) = 0;
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
