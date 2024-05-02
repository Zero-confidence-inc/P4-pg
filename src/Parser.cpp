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

std::shared_ptr<ASTNode> Parser::parseMathNode() {
    if (lookAhead(TokenType::OPERATOR)) {
        auto mathExprNode = std::make_shared<MathNode>();
        mathExprNode->operatorType = tokens[pos].value;
        pos++; // Consume the operator

        // Parse left operand
        mathExprNode->leftOperand = parseExpression();

        // Parse right operand
        mathExprNode->rightOperand = parseExpression();

        return mathExprNode;
    }
    return nullptr; // Not a mathematical expression
}
