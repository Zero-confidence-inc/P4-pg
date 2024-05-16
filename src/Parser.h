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
    std::string variable;
};



struct CharNode : ASTNode {
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
    std::string type;
    nodeType getType() const override {return nodeType::functionNode;}
};

// Node for variable declarations
struct VariableNode : DeclarationNode {
    nodeType getType() const override {return nodeType::variableNode;}
    std::string type;
    // Additional properties can be added here
};

struct ReturnNode : ASTNode {
    std::string returning;
    std::string identifier;
};


struct FloatNode : ASTNode {
    float Floating_Point;
    nodeType getType() const override {return nodeType::floatNode;}
};

struct IntNode : ASTNode {
    int integer;
    nodeType getType() const override {return nodeType::intNode;}
};




struct StringNode : ASTNode {
    std::string StringOfChars;
    nodeType getType() const override {return nodeType::stringNode;}
};

struct OperatorNode : ASTNode {
    std::string operatorType;
    nodeType getType() const override {return nodeType::operatorNode;}
};

struct SwitchNode : ASTNode {
    std::shared_ptr<ASTNode> condition;
    std::vector<std::shared_ptr<CaseNode>> caseBranch;
    nodeType getType() const override {return nodeType::switchNode;}
    SwitchNode() : condition(nullptr), caseBranch() {}
};

struct CaseNode : ASTNode {
    std::shared_ptr<ASTNode> sucessCondition;
    public: nodeType getType() const override {return nodeType::caseNode;}
    std::vector<std::shared_ptr<ASTNode>> Branch;
};

struct ConditionNode : ASTNode {
    std::string condition;
    std::shared_ptr<ASTNode> aNode;
    std::shared_ptr<ASTNode> bNode;
    nodeType getType() const override {return nodeType::conditionNode;}
};

struct WhileNode : ASTNode {
    std::shared_ptr<ASTNode> condition;
    std::vector<std::shared_ptr<ASTNode>> body;
    nodeType getType() const override {return nodeType::whileNode;}
};


struct randomNode : ASTNode {
    std::shared_ptr<ASTNode> randomInt;
    std::shared_ptr<ASTNode> randomFloat;
    std::shared_ptr<ASTNode> randomBool;
    std::vector<int> RandomIntRange;
    std::vector<float> RandomFloatRange;
};





struct ArrayNode : ASTNode {
    std::string type;
    std::string identifier;
    int size;
};

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);
    void parseProgram();
    std::shared_ptr<ASTNode> parseDeclaration();
    std::shared_ptr<ASTNode> parseChar();
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

    std::shared_ptr<ASTNode> parseWhileLoop();

    std::shared_ptr<ASTNode> parseRandom();

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