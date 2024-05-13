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
};

// Node for declarations
struct DeclarationNode : ASTNode {
    std::string type;
    std::string identifier;
};

struct CharNode : ASTNode {
    std::string character;
};

struct ForLoopNode : ASTNode {
    std::shared_ptr<ASTNode> declaration;
    std::shared_ptr<ASTNode> condition;
    std::shared_ptr<ASTNode> expression;
    std::vector<std::shared_ptr<ASTNode>> body;
};

// Node for function declarations
struct FunctionNode : DeclarationNode {
    std::vector<std::shared_ptr<ASTNode>> body;
};

// Node for variable declarations
struct VariableNode : DeclarationNode {
    // Additional properties can be added here
};

struct IfStatementNode : ASTNode {
    std::shared_ptr<ASTNode> condition;  // Node representing the condition expression
    std::shared_ptr<ASTNode> trueBranch;  // Node representing the statements to execute if the condition is true
    std::shared_ptr<ASTNode> falseBranch;  // Node representing the statements to execute if the condition is false (optional)

    IfStatementNode() : condition(nullptr), trueBranch(nullptr), falseBranch(nullptr) {}
};

struct FloatNode : ASTNode {
    float Floating_Point;
};

struct CommentNode : ASTNode {
    std::string Comment;
};

struct StringNode : ASTNode {
    std::string StringOfChars;
};

struct OperatorNode : ASTNode {
    std::string operatorType; 
};

struct SwitchNode : ASTNode {
    std::shared_ptr<ASTNode> condition;
    std::vector<std::shared_ptr<caseNode>> caseBranch;

    SwitchNode() : condition(nullptr), caseBranch() {}
};

struct caseNode : ASTNode {
    std::shared_ptr<ASTNode> sucessCondition;
    std::shared_ptr<ASTNode> Branch;
};

struct ConditionNode : ASTNode {
    std::string condition;
};

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);
    void parseProgram();
    std::shared_ptr<ASTNode> parseDeclaration();

    std::shared_ptr<ASTNode> parseChar();

    std::shared_ptr<ASTNode> parseFloat();
    std::shared_ptr<ASTNode> parseComment();
    std::shared_ptr<ASTNode> parseString();
    std::shared_ptr<ASTNode> parseCondition();
    std::shared_ptr<ASTNode> parseMath();
    std::shared_ptr<ASTNode> parseForLoop();

    std::shared_ptr<ASTNode> parseDeclaration();
    std::shared_ptr<ASTNode> parseOperator();
    std::shared_ptr<ASTNode> parseSwitch();
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
    std::vector<std::shared_ptr<ASTNode>> parseLoopBody();
};

#endif // PARSER_H
