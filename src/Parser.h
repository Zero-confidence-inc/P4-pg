//
// Created by Yuki on 29/04/2024.
//
#ifndef PARSER_H
#define PARSER_H

#include "Token.h"
#include <vector>
#include <memory>
#include <iostream>

// Base class for all AST nodes
struct ASTNode {
    virtual ~ASTNode() {}
    virtual void accept(class ASTNodeVisitor& visitor) = 0;
};

// Node for declarations
struct DeclarationNode : ASTNode {
    std::string type;
    std::string identifier;
    void accept(ASTNodeVisitor& visitor) override;
};


struct CharNode : ASTNode {
    std::string character;
    void accept(ASTNodeVisitor& visitor) override;
};

struct ForLoopNode : ASTNode {
    std::shared_ptr<ASTNode> declaration;
    std::shared_ptr<ASTNode> condition;
    std::shared_ptr<ASTNode> expression;
    std::vector<std::shared_ptr<ASTNode>> body;
    void accept(ASTNodeVisitor& visitor) override;
};

struct IfNode : ASTNode {
    std::shared_ptr<ASTNode> condition;
    std::vector<std::shared_ptr<ASTNode>> body;
    void accept(ASTNodeVisitor& visitor) override;
};
// Node for Struct declarations
struct StructNode : DeclarationNode {
    std::vector<std::shared_ptr<ASTNode>> body;
    void accept(ASTNodeVisitor& visitor) override;
};
// Node for function declarations
struct FunctionNode : DeclarationNode {
    std::vector<std::shared_ptr<ASTNode>> body;
    void accept(ASTNodeVisitor& visitor) override;
};

// Node for variable declarations
struct VariableNode : DeclarationNode {
    // Additional properties can be added here
    void accept(ASTNodeVisitor& visitor) override;
};

struct IfStatementNode : ASTNode {
    std::shared_ptr<ASTNode> condition;  // Node representing the condition expression
    std::shared_ptr<ASTNode> trueBranch;  // Node representing the statements to execute if the condition is true
    std::shared_ptr<ASTNode> falseBranch;  // Node representing the statements to execute if the condition is false (optional)

    IfStatementNode() : condition(nullptr), trueBranch(nullptr), falseBranch(nullptr) {}
    void accept(ASTNodeVisitor& visitor) override;
};

struct FloatNode : ASTNode {
    float Floating_Point;
    void accept(ASTNodeVisitor& visitor) override;
};

struct IntNode : ASTNode {
    int integer;
    void accept(ASTNodeVisitor& visitor) override;
};

struct CommentNode : ASTNode {
    std::string Comment;
    void accept(ASTNodeVisitor& visitor) override;
};

struct StringNode : ASTNode {
    std::string StringOfChars;
    void accept(ASTNodeVisitor& visitor) override;
};

struct OperatorNode : ASTNode {
    std::string operatorType; 
    void accept(ASTNodeVisitor& visitor) override;
};

struct SwitchNode : ASTNode {
    std::shared_ptr<ASTNode> condition;
    std::vector<std::shared_ptr<caseNode>> caseBranch;

    SwitchNode() : condition(nullptr), caseBranch() {}
    void accept(ASTNodeVisitor& visitor) override;
};

struct caseNode : ASTNode {
    std::shared_ptr<ASTNode> sucessCondition;
    std::shared_ptr<ASTNode> Branch;
    void accept(ASTNodeVisitor& visitor) override;
};

struct ConditionNode : ASTNode {
    std::string condition;
    void accept(ASTNodeVisitor& visitor) override;
};

struct whileNode : ASTNode {
    std::shared_ptr<ASTNode> condition;
    std::vector<std::shared_ptr<ASTNode>> body;
    void accept(ASTNodeVisitor& visitor) override;
};

struct MathNode : ASTNode {
    std::string operatorType; //Operator representing the mathematical expression
    std:: shared_ptr<ASTNode> leftOperand;
    std:: shared_ptr<ASTNode> rightOperand;

    MathNode() : operatorType(""), leftOperand(nullptr), rightOperand(nullptr) {}
    void accept(ASTNodeVisitor& visitor) override;
};

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);
    void parseProgram();
    std::shared_ptr<ASTNode> parseDeclaration();
    std::shared_ptr<ASTNode> parseMathNode();
    std::shared_ptr<ASTNode> parseChar();
    std::shared_ptr<ASTNode> parseFloat();
    std::shared_ptr<ASTNode> parseInt();
    std::shared_ptr<ASTNode> parseComment();
    std::shared_ptr<ASTNode> parseString();
    std::shared_ptr<ASTNode> parseCondition();
    std::shared_ptr<ASTNode> parseMath();
    std::shared_ptr<ASTNode> parseForLoop();
    std::shared_ptr<ASTNode> parseOperator();
    std::shared_ptr<ASTNode> parseSwitch();
    std::shared_ptr<ASTNode> parseStruct();
    std::shared_ptr<ASTNode> parseSwitchStatement();
    std::shared_ptr<ASTNode> parseExpression();
    std::shared_ptr<ASTNode> parseStatement();
    std::shared_ptr<ASTNode> parseArray();
    std::shared_ptr<ASTNode> parseIfStatement();
    std::shared_ptr<ASTNode> parseWhileLoop();


private:
    std::vector<Token> tokens;
    size_t pos = 0;

    bool lookAhead(TokenType expectedType);
    void match(TokenType expectedType);
    void match(TokenType expectedType, const std::string& expectedValue);
    std::vector<std::shared_ptr<ASTNode>> parseFunctionBody();  // Assume this function parses a function body
    std::vector<std::shared_ptr<ASTNode>> parseStructBody();
    std::vector<std::shared_ptr<ASTNode>> parseLoopBody();
};

#endif // PARSER_H