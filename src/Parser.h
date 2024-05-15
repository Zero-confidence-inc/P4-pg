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
    mathNode,
    intNode
};
// Base class for all AST nodes
struct ASTNode {
    virtual ~ASTNode() {}
public:
    virtual nodeType getType() const = 0;
};

// Node for declarations
struct DeclarationNode : ASTNode {
    nodeType getType() const override {return nodeType::declarationNode;}
    std::string identifier;
};

struct MathNode : ASTNode {
    nodeType getType() const override {return nodeType::mathNode;}

};


struct CharNode : DeclarationNode {
    nodeType getType() const override {return nodeType::charNode;}
    std::string character;
};

struct ForLoopNode : ASTNode {
    std::shared_ptr<ASTNode> declaration;
    std::shared_ptr<ASTNode> condition;
    std::shared_ptr<ASTNode> expression;
    std::vector<std::shared_ptr<ASTNode>> body;
    nodeType getType() const override {return nodeType::forLoopNode;}
};

struct IfNode : ASTNode {
    std::shared_ptr<ASTNode> condition;
    std::vector<std::shared_ptr<ASTNode>> body;
    nodeType getType() const override {return nodeType::ifNode;}
    std::vector<std::shared_ptr<ASTNode>> elseBody;
};
// Node for Struct declarations
struct StructNode : DeclarationNode {
    std::string identifier;
    std::vector<std::shared_ptr<ASTNode>> body;
    nodeType getType() const override {return nodeType::structNode;}
};
// Node for function declarations
struct FunctionNode : DeclarationNode {
    std::vector<std::shared_ptr<ASTNode>> body;
    nodeType getType() const override {return nodeType::functionNode;}
};

// Node for variable declarations
struct VariableNode : DeclarationNode {
    nodeType getType() const override {return nodeType::variableNode;}
    // Additional properties can be added here
};

 /* struct IfStatementNode : ASTNode {
    std::shared_ptr<ASTNode> condition;  // Node representing the condition expression
    std::shared_ptr<ASTNode> trueBranch;  // Node representing the statements to execute if the condition is true
    std::shared_ptr<ASTNode> falseBranch;  // Node representing the statements to execute if the condition is false (optional)
    nodeType getName() const override {return nodeType::ifStatementNode}
    IfStatementNode() : condition(nullptr), trueBranch(nullptr), falseBranch(nullptr) {}
}; */
struct ReturnNode : ASTNode {
    std::string returning;
    std::string identifier;
};


struct FloatNode : DeclarationNode {
    float Floating_Point;
    nodeType getType() const override {return nodeType::floatNode;}
};

struct IntNode : ASTNode {
    int integer;
    nodeType getType() const override {return nodeType::intNode;}
};




struct StringNode : DeclarationNode {
    std::string StringOfChars;
    nodeType getType() const override {return nodeType::stringNode;}
};

struct OperatorNode : DeclarationNode {
    std::string operatorType;
    nodeType getType() const override {return nodeType::operatorNode;}
};

struct SwitchNode : ASTNode {
    std::shared_ptr<ASTNode> condition;
    std::vector<std::shared_ptr<caseNode>> caseBranch;
    nodeType getType() const override {return nodeType::switchNode;}
    SwitchNode() : condition(nullptr), caseBranch() {}
};

struct caseNode : ASTNode {
    std::shared_ptr<ASTNode> sucessCondition;
    std::shared_ptr<ASTNode> Branch;
    public: nodeType getType() const override {return nodeType::caseNode;}
};

struct ConditionNode : ASTNode {
    std::string condition;
    std::shared_ptr<ASTNode> aNode;
    std::shared_ptr<ASTNode> bNode;
    nodeType getType() const override {return nodeType::conditionNode}
};

struct WhileNode : ASTNode {
    std::shared_ptr<ASTNode> condition;
    std::vector<std::shared_ptr<ASTNode>> body;
    nodeType getType() const override {return nodeType::whileNode}
};

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);
    void parseProgram();
    std::shared_ptr<ASTNode> parseDeclaration();
    std::shared_ptr<ASTNode> parseChar();
    std::shared_ptr<ASTNode> parseFloat();
    std::shared_ptr<ASTNode> parseInt();
    std::shared_ptr<ASTNode> parseComment();
    std::shared_ptr<ASTNode> parseString();
    std::shared_ptr<ASTNode> parseCondition();
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
    std::shared_ptr<ASTNode> parseReturn();


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