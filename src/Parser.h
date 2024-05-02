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
    std::string identifier;
    std::string character;
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

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);
    void parseProgram();
    std::shared_ptr<ASTNode> parseDeclaration();
    std::shared_ptr<ASTNode> parseChar();

private:
    std::vector<Token> tokens;
    size_t pos = 0;

    bool lookAhead(TokenType expectedType);
    void match(TokenType expectedType);
    void match(TokenType expectedType, const std::string& expectedValue);
    std::vector<std::shared_ptr<ASTNode>> parseFunctionBody();  // Assume this function parses a function body
};

#endif // PARSER_H