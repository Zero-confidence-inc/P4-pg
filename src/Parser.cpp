//
// Created by Yuki on 29/04/2024.
//
#include "Parser.h"
#include <cctype>

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
//Parse the Int Type
std::shared_ptr<ASTNode> Parser::parseInt() {

    //Create int node
    if (lookAhead(TokenType::TYPE) && tokens[pos].value == "int") {
        auto IntNode = std::make_shared<IntNode>();
        pos++;
        // Check if '=' operator is used, if not, skip till end
        if (lookAhead(TokenType::OPERATOR) && tokens[pos].value[0] == '=') {
            pos++
        } else {
            return nullptr; //If no '=' is found
        }
        if (lookAhead(TokenType::STRING) && tokens[pos].value.size() > 0 && isdigit(tokens[pos])) {
            IntNode->integer = tokens[pos].value[0];
            pos++;
        } else {
            return nullptr; //if no Integer is found
        }
        if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value[0] == ';') {
            return IntNode; //If everything matches at the end, then it will return the IntNode
        }
    }
    return nullptr;
    }
}