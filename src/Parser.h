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
    std::string variable;
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

struct IfNode : ASTNode {
    std::shared_ptr<ASTNode> condition;
    std::vector<std::shared_ptr<ASTNode>> body;
    std::vector<std::shared_ptr<ASTNode>> elseBody;
};
// Node for Struct declarations
struct StructNode : DeclarationNode {
    std::string identifier;
    std::vector<std::shared_ptr<ASTNode>> body;
};
// Node for function declarations
struct FunctionNode : DeclarationNode {
    std::vector<std::shared_ptr<ASTNode>> body;
};

// Node for variable declarations
struct VariableNode : DeclarationNode {
};

struct ReturnNode : ASTNode {
    std::string returning;
    std::string identifier;
};

struct FloatNode : ASTNode {
    float Floating_Point;
};

struct IntNode : ASTNode {
    int integer;
};

struct StringNode : ASTNode {
    std::string StringOfChars;
};

struct SwitchNode : ASTNode {
    std::shared_ptr<ASTNode> condition;
    std::vector<std::shared_ptr<caseNode>> caseBranch;

    SwitchNode() : condition(nullptr), caseBranch() {}
};

struct caseNode : ASTNode {
    std::shared_ptr<ASTNode> sucessCondition;
    std::vector<std::shared_ptr<ASTNode>> Branch;
};

struct ConditionNode : ASTNode {
    std::string condition;
};

struct WhileNode : ASTNode {
    std::shared_ptr<ASTNode> condition;
    std::vector<std::shared_ptr<ASTNode>> body;
};


struct RandomNode : ASTNode {
    std::shared_ptr<ASTNode> random;
    std::string identifier;
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