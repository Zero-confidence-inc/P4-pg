//
// Created by Yuki on 29/04/2024.
//
#include "Parser.h"

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

void Parser::parseProgram() {
    std::vector<std::shared_ptr<ASTNode>> ast;
    while (pos < tokens.size()) {
        auto declaration = parseDeclaration();
        if (declaration != nullptr) {
            ast.push_back(declaration);
        }
    }
    // 'ast' now contains the entire program's AST
}

std::shared_ptr<ASTNode> Parser::parseDeclaration() {
    if (lookAhead(TokenType::TYPE)) {
        std::string type = tokens[pos++].value;
        std::string identifier = tokens[pos++].value;

        if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value == "{") {
            auto functionNode = std::make_shared<FunctionNode>();
            functionNode->type = type;
            functionNode->identifier = identifier;
            functionNode->body = parseFunctionBody();
            match(TokenType::PUNCTUATION, "{");
            match(TokenType::PUNCTUATION, "}");
            return functionNode;
        } else if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value == ";") {
            auto variableNode = std::make_shared<VariableNode>();
            variableNode->type = type;
            variableNode->identifier = identifier;
            match(TokenType::PUNCTUATION, ";");
            return variableNode;
        }
    }
    return nullptr; // Return nullptr if no valid declaration is found
}


bool Parser::lookAhead(TokenType expectedType) {
    return pos < tokens.size() && tokens[pos].type == expectedType;
}

void Parser::match(TokenType expectedType) {
    if (pos < tokens.size() && tokens[pos].type == expectedType) {
        pos++;
    } else {
        std::cerr << "Syntax error, expected type " << static_cast<int>(expectedType) << std::endl;
        exit(1);
    }
}

void Parser::match(TokenType expectedType, const std::string& expectedValue) {
    if (pos < tokens.size() && tokens[pos].type == expectedType && tokens[pos].value == expectedValue) {
        pos++;
    } else {
        std::cerr << "Syntax error, expected " << expectedValue << " of type " << static_cast<int>(expectedType) << std::endl;
        exit(1);
    }
}

std::vector<std::shared_ptr<ASTNode>> Parser::parseFunctionBody() {
    // Dummy implementation for now
    return {};
}

//Operators 
std::shared_ptr<ASTNode> Parser::parseOperator() {
    if(lookAhead(TokenType::OPERATOR)){
        auto opeNode = std::make_shared<OperatorNode>();
        opeNode->operatorType = tokens[pos].value;
        return opeNode;
    }
    return nullptr;
}

//Switch
std::shared_ptr<ASTNode> Parser::parseSwitchStatement() {
    if(lookAhead(TokenType::CONTROL) && tokens[pos].value == "switch"){
        return parseSwitch();
    }
    return nullptr;
}

std::shared_ptr<ASTNode> Parser::parseSwitch() {
    if(lookAhead(TokenType::CONTROL) && tokens[pos].value == "switch"){
        pos++;
        auto swNode = std::make_shared<SwitchNode>();
        swNode->condition = parseExpression();

        while (lookAhead(TokenType::CONTROL) && tokens[pos].value == "case"){
            auto cNode = std::make_shared<caseNode>();
            cNode->sucessCondition = parseStatement();
            pos++;
            cNode->Branch = parseStatement();

            swNode->caseBranch.push_back(cNode);
        }

        return swNode;
    }
    return nullptr;
}

std::shared_ptr<ASTNode> Parser::parseStatement(){
    //placeholder for now
    return nullptr;
}

std::shared_ptr<ASTNode> Parser::parseExpression(){
    //placeholder for now
    return nullptr;
}