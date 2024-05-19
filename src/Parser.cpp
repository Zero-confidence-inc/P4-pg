//
// Created by Yuki on 29/04/2024.
//
#include "Parser.h"
#include <iostream>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

void Parser::parseProgram() {
    std::vector<std::shared_ptr<ASTNode>> ast;
    while (pos < tokens.size()) {
        std::cout << "Entering parseProgram at position " << pos << " with token: " << tokens[pos].value << std::endl;
        if (lookAhead(TokenType::TYPE) && tokens[++pos].value == "int?" || tokens[pos].value=="float?" || tokens[pos].value=="bool?"){
            auto random_pp = parseRandom();
            if (random_pp != nullptr){
                ast.push_back(random_pp);
            }
        }
        else{
            --pos;
            auto declaration_pp = parseDeclaration();
            if (declaration_pp != nullptr){
                ast.push_back(declaration_pp);
            }
        }
    }
    // 'ast' now contains the entire program's AST
}

std::shared_ptr<ASTNode> Parser::parseDeclaration() {
    std::cout << "Entering parseDeclaration at position " << pos << " with token: " << tokens[pos].value << std::endl;

    if (tokens[pos].type == TokenType::TYPE) {
        std::string type = tokens[pos].value;
        std::string identifier = tokens[++pos].value;
        std::cout << "Parsed type: " << type << ", identifier: " << identifier << ", current pos: " << pos << std::endl;

        if (lookAhead(TokenType::PUNCTUATION) && tokens[pos + 1].value == "(") {
            pos++; // Move to the '(' token
            auto functionNode = std::make_shared<FunctionNode>();
            functionNode->arguments = parseFunctionArguments();
            return functionNode;
        } else if (tokens[pos + 1].type == TokenType::OPERATOR && tokens[pos + 1].value == "=") {
            pos++; // Move to the '=' token
            std::cout << "Trying to make value node" << std::endl;
            auto valueNode = std::make_shared<ValueNode>();
            valueNode->type = type;
            valueNode->identifier = identifier;
            valueNode->value = parseValues();
            pos++;
            match(TokenType::PUNCTUATION, ";");
            return valueNode; //
        } else if (tokens[pos + 1].type == TokenType::TYPE && tokens[pos + 1].value == "struct") {
            pos++; // Move to the 'struct' token
            auto structNode = std::make_shared<StructNode>();
            structNode->type = type;
            structNode->identifier = identifier;
            structNode->struct_main = parseStruct();
            return structNode;
        } else if (tokens[pos + 1].type == TokenType::PUNCTUATION && tokens[pos + 1].value[0] == '[') {
            pos++; // Move to the '[' token
            auto arrayNode = std::make_shared<ArrayNode>();
            arrayNode->type = type;
            arrayNode->identifier = identifier;
            if (lookAhead(TokenType::CONST) || lookAhead(TokenType::IDENTIFIER)) {
                auto arraySize = tokens[pos + 1].value;
                pos++; // Move to the size token
                if (lookAhead(TokenType::PUNCTUATION) && tokens[pos + 1].value[0] == ']') {
                    pos += 2; // Move to the ']' token
                    arrayNode->size = arraySize;
                    if (lookAhead(TokenType::PUNCTUATION) && tokens[pos + 1].value[0] == ';') {
                        pos++; // Move to the ';' token
                        return arrayNode;
                    } else if (tokens[pos].type == TokenType::OPERATOR && tokens[pos].value[0] == '=') {
                        match(TokenType::PUNCTUATION, "[");
                        arrayNode->body = parseArrayContents();
                        match(TokenType::PUNCTUATION, "]");
                        match(TokenType::PUNCTUATION, ";");
                        return arrayNode;
                    }
                }
            }
        }
    }
    std::cout << "parseDeclaration returning nullptr" << std::endl;
    return nullptr;
}

bool Parser::lookAhead(TokenType expectedType) {
    return (pos + 1) < tokens.size() && tokens[pos + 1].type == expectedType;
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
    std::vector<std::shared_ptr<ASTNode>> contents;
    std::cout << "Entering parseFunctionBody" << std::endl;
    if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value[0] == '{') {
        pos++;
        while (tokens[pos].value[0] != '}') {
            auto declaration = parseDeclaration();
            auto random = parseRandom();
            auto jump = parseJump();
            contents.push_back(declaration);
            contents.push_back(random);
            contents.push_back(jump);
            if (lookAhead(TokenType::JUMP) && tokens[pos].value == "return") {
                auto returns = parseReturn();
                contents.push_back(returns);
            } else {
                pos++;
            }
        }
    } else {
        return {};
    }
    return contents;
}

std::shared_ptr<ASTNode> Parser::parseReturn() {
    std::cout << "Entering parseReturn at position " << pos << " with token: " << tokens[pos].value << std::endl;
    if (lookAhead(TokenType::JUMP) && tokens[++pos].value == "return") {
        auto returnNode = std::make_shared<ReturnNode>();
        returnNode->returning = tokens[pos].value;
        returnNode->identifier = tokens[++pos].value;
        return returnNode;
    }
    return nullptr;
}

std::vector<std::shared_ptr<ASTNode>> Parser::parseStructBody() {
    std::vector<std::shared_ptr<ASTNode>> contents;
    std::cout << "Entering parseStructBody" << std::endl;
    while (tokens[++pos].value[0] != '}') {
        auto declaration = parseDeclaration();
        contents.push_back(declaration);
    }
    return contents;
}

std::shared_ptr<ASTNode> Parser::parseValues() {
    std::cout << "Entering parseValues at position " << pos << " with token: " << tokens[pos].value << std::endl;
    if (tokens[2 - pos].value == "int") {

        std::cout << "hacker voice: i'm in " << "pos: " << pos << std::endl;
        auto valueInt = std::make_shared<IntNode>();
        std::cout << "made intnode " << "pos: " << pos << std::endl;
        valueInt->integer = tokens[++pos].value[0];
        std::cout << "assigned int " << "pos: " << pos << std::endl;
        return valueInt;
    } else if (tokens[2 - pos].value == "usint") {
        auto valueUsint = std::make_shared<UsIntNode>();
        valueUsint->usinteger = tokens[pos].value[0];
        return valueUsint;
    } else if (tokens[2 - pos].value == "float") {
        auto valueFloat = std::make_shared<FloatNode>();
        valueFloat->Floating_Point = tokens[pos].value[0];
        return valueFloat;
    } else if (tokens[2 - pos].value == "char") {
        auto valueChar = std::make_shared<CharNode>();
        valueChar->character = tokens[pos].value[0];
        return valueChar;
    } else if (tokens[2 - pos].value == "string") {
        auto valueString = std::make_shared<StringNode>();
        valueString->StringOfChars = tokens[pos].value[0];
        return valueString;
    } else if (tokens[2 - pos].value == "bool") {
        auto valueBool = std::make_shared<BoolNode>();
        valueBool->boolean = tokens[pos].value[0];
        return valueBool;
    } else return nullptr;
}

std::shared_ptr<ASTNode> Parser::parseFunctionCall() {
    std::cout << "Entering parseFunctionCall at position " << pos << " with token: " << tokens[pos].value << std::endl;
    if (lookAhead(TokenType::IDENTIFIER) && tokens[++pos].value[0] == '(') {
        std::string identifier = tokens[pos].value;
        auto functionCallNode = std::make_shared<FunctionCallNode>();
        functionCallNode->identifier = identifier;
        while (tokens[pos].value[0] != ')') {
            auto argument = parseIdentifier();
            functionCallNode->arguments.push_back(argument);
            match(TokenType::PUNCTUATION, ",");
            pos++;
        }
        return functionCallNode;
    } else {
        return nullptr;
    }
}

std::vector<std::shared_ptr<ASTNode>> Parser::parseFunctionArguments() {
    std::cout << "Entering parseFunctionArguments at position " << pos << " with token: " << tokens[pos].value << std::endl;
    std::vector<std::shared_ptr<ASTNode>> arguments;
    while (tokens[pos].value[0] != ')') {
        auto argument = parseDeclaration();
        std::cout << "Parsed argument type: " << (argument ? argument->getType() : -1) << std::endl;
        arguments.push_back(argument);
        if (tokens[pos].value[0] == ',') {
            match(TokenType::PUNCTUATION, ",");
            pos++;
        }
    }
    std::cout << "parseFunctionArguments returning arguments" << std::endl;
    return arguments;
}

std::vector<std::shared_ptr<ASTNode>> Parser::parseLoopBody() {
    std::vector<std::shared_ptr<ASTNode>> contents;
    std::cout << "Entering parseLoopBody" << std::endl;
    if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value[0] == '{') {
        pos++;
        while (tokens[pos].value[0] != '}') {
            auto declaration = parseDeclaration();
            auto forLoop = parseForLoop();
            auto switchCase = parseSwitch();
            auto array = parseArray();
            auto ifStatement = parseIfStatement();
            auto whileLoop = parseWhileLoop();
            contents.push_back(declaration);
            contents.push_back(forLoop);
            contents.push_back(switchCase);
            contents.push_back(array);
            contents.push_back(ifStatement);
            contents.push_back(whileLoop);
        }
    } else {
        return {};
    }
    return contents;
}

std::shared_ptr<ASTNode> Parser::parseStruct() {
    std::cout << "Entering parseStruct at position " << pos << " with token: " << tokens[pos].value << std::endl;
    if (lookAhead(TokenType::TYPE) && tokens[pos].value == "struct") {
        pos++;
        auto identify = tokens[pos].value;
        if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value == "{") {
            auto structNode = std::make_shared<StructNode>();
            structNode->identifier = identify;
            structNode->body = parseStructBody();
            match(TokenType::PUNCTUATION, "{");
            match(TokenType::PUNCTUATION, "}");
            return structNode;
        }
    }
    std::cout << "parseStruct returning nullptr" << std::endl;
    return nullptr;
}

std::shared_ptr<ASTNode> Parser::parseIdentifier() {
    std::cout << "Entering parseIdentifier at position " << pos << " with token: " << tokens[pos].value << std::endl;
    std::string identifier = tokens[++pos].value;
    if (lookAhead(TokenType::IDENTIFIER)) {
        auto identifierNode = std::make_shared<IdentifierNode>();
        identifierNode->identifier = identifier;
        return identifierNode;
    } else {
        return nullptr;
    }
}

std::shared_ptr<ASTNode> Parser::parseCondition() {
    std::cout << "Entering parseCondition at position " << pos << " with token: " << tokens[pos].value << std::endl;
    if (lookAhead(TokenType::CONST) || lookAhead(TokenType::FLOAT_CONST) || lookAhead(TokenType::STRING)
        || lookAhead(TokenType::IDENTIFIER) || lookAhead(TokenType::BOOL)) {
        pos++;
        auto conditionNode = std::make_shared<ConditionNode>();
        if (tokens[pos].type == TokenType::IDENTIFIER) {
            auto bNode = std::make_shared<IdentifierNode>();
            bNode->identifier = tokens[pos].value;
            conditionNode->bNode = bNode;
        } else if (tokens[pos].type == TokenType::CONST) {
            conditionNode->bNode = std::make_shared<IntNode>();
        } else if (tokens[pos].type == TokenType::FLOAT_CONST) {
            conditionNode->bNode = std::make_shared<FloatNode>();
        } else if (tokens[pos].type == TokenType::STRING) {
            conditionNode->bNode = std::make_shared<StringNode>();
        } else if (tokens[pos].type == TokenType::BOOL) {
            conditionNode->bNode = std::make_shared<BoolNode>();
        }
        pos++;
        if (tokens[pos].type == TokenType::OPERATOR) {
            conditionNode->condition = tokens[pos].value;
        } else {
            return conditionNode;
        }
        if (lookAhead(TokenType::OPERATOR)) {
            pos++;
            conditionNode->bNode = parseCondition();
        } else if (lookAhead(TokenType::CONST) || lookAhead(TokenType::FLOAT_CONST) || lookAhead(TokenType::STRING)
                   || lookAhead(TokenType::IDENTIFIER) || lookAhead(TokenType::BOOL)) {
            pos++;
            if (tokens[pos].type == TokenType::IDENTIFIER) {
                auto bNode = std::make_shared<IdentifierNode>();
                bNode->identifier = tokens[pos].value;
                conditionNode->bNode = bNode;
            } else if (tokens[pos].type == TokenType::CONST) {
                conditionNode->bNode = std::make_shared<IntNode>();
            } else if (tokens[pos].type == TokenType::FLOAT_CONST) {
                conditionNode->bNode = std::make_shared<FloatNode>();
            } else if (tokens[pos].type == TokenType::STRING) {
                conditionNode->bNode = std::make_shared<StringNode>();
            } else if (tokens[pos].type == TokenType::BOOL) {
                conditionNode->bNode = std::make_shared<BoolNode>();
            }
        }
        return conditionNode;
    }
    std::cout << "parseCondition returning nullptr" << std::endl;
    return nullptr;
}

// Parses the char type
std::shared_ptr<ASTNode> Parser::parseChar() {
    std::cout << "Entering parseChar at position " << pos << " with token: " << tokens[pos].value << std::endl;
    // Checks if the type given is actually a char, and creates a char node
    if (lookAhead(TokenType::TYPE) && tokens[pos].value == "char") {
        auto charNode = std::make_shared<CharNode>();
        pos++;
        // Skips the '=' operator, and return nullptr if the operator used isn't '='
        if (lookAhead(TokenType::OPERATOR) && tokens[pos].value[0] == '=') {
            pos++;
            // Assigns the first character of the following string as our char
            if (lookAhead(TokenType::STRING) && tokens[pos].value.size() > 0) {
                charNode->character = tokens[pos].value[0];
                pos++;
                // We only only accept this as a proper char if the following character is a ';', since that would mean the declaration has finished properly
                if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value[0] == ';') {
                    return charNode;
                }
            }
        }
    }
    std::cout << "parseChar returning nullptr" << std::endl;
    return nullptr;
}

std::shared_ptr<ASTNode> Parser::parseFloat() {
    std::cout << "Entering parseFloat at position " << pos << " with token: " << tokens[pos].value << std::endl;
    if (lookAhead(TokenType::FLOAT_CONST)) {
        auto FloatingNode = std::make_shared<FloatNode>();
        FloatingNode->Floating_Point = std::stof(tokens[pos].value);
        return FloatingNode;
    }
    std::cout << "parseFloat returning nullptr" << std::endl;
    return nullptr;
}

std::shared_ptr<ASTNode> Parser::parseInt() {
    std::cout << "Entering parseInt at position " << pos << " with token: " << tokens[pos].value << std::endl;
    if (lookAhead(TokenType::CONST)) {
        auto intNode = std::make_shared<IntNode>();
        intNode->integer = std::stoi(tokens[++pos].value);
        return intNode;
    }
    std::cout << "parseInt returning nullptr" << std::endl;
    return nullptr;
}

std::shared_ptr<ASTNode> Parser::parseBool() {
    std::cout << "Entering parseBool at position " << pos << " with token: " << tokens[pos].value << std::endl;
    if (lookAhead(TokenType::BOOL)) {
        auto Boolnode = std::make_shared<BoolNode>();
        if (tokens[++pos].value == "true") {
            Boolnode->boolean = true;
        } else if (tokens[pos].value == "false") {
            Boolnode->boolean = false;
        }
        return Boolnode;
    }
    std::cout << "parseBool returning nullptr" << std::endl;
    return nullptr;
}

std::shared_ptr<ASTNode> Parser::parseString() {
    std::cout << "Entering parseString at position " << pos << " with token: " << tokens[pos].value << std::endl;
    if (lookAhead(TokenType::STRING)) {
        auto stringNode = std::make_shared<StringNode>();
        stringNode->StringOfChars = tokens[pos].value;
        return stringNode;
    }
    std::cout << "parseString returning nullptr" << std::endl;
    return nullptr;
}

std::shared_ptr<ASTNode> Parser::parseUsInt() {
    std::cout << "Entering parseUsInt at position " << pos << " with token: " << tokens[pos].value << std::endl;
    if (lookAhead(TokenType::CONST)) {
        auto usIntNode = std::make_shared<UsIntNode>();
        usIntNode->usinteger = std::stoi(tokens[pos].value);
        return usIntNode;
    }
    std::cout << "parseUsInt returning nullptr" << std::endl;
    return nullptr;
}

// Parses a for loop
std::shared_ptr<ASTNode> Parser::parseForLoop() {
    std::cout << "Entering parseForLoop at position " << pos << " with token: " << tokens[pos].value << std::endl;
    // Check to see if the loop token "for" is given
    if (lookAhead(TokenType::LOOP) && tokens[pos].value == "for") {
        auto forLoopNode = std::make_shared<ForLoopNode>();
        pos++;
        // Skips '(' and parses the declaration
        if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value[0] == '(') {
            pos++;
            auto declarationNode = parseDeclaration();
            // Skips the first ';' and parses the condition
            if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value[0] == ';') {
                pos++;
                auto conditionNode = parseCondition();
                // Skips the second ';' and parses the expression
                if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value[0] == ';') {
                    pos++;
                    auto expressionNode = parseCondition();
                    // Skip ')' and parses the body of the loop, thereafter it assigns the, declaration, condition, expression and body.
                    if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value[0] == ')') {
                        pos++;
                        auto bodyNode = parseLoopBody();
                        forLoopNode->declaration = std::dynamic_pointer_cast<DeclarationNode>(declarationNode);
                        forLoopNode->condition = std::dynamic_pointer_cast<ConditionNode>(conditionNode);
                        forLoopNode->expression = std::dynamic_pointer_cast<ConditionNode>(expressionNode);
                        forLoopNode->body = bodyNode;
                        return forLoopNode;
                    }
                }
            }
        }
    }
    std::cout << "parseForLoop returning nullptr" << std::endl;
    return nullptr;
}

std::shared_ptr<ASTNode> Parser::parseJump() {
    std::cout << "Entering parseJump at position " << pos << " with token: " << tokens[pos].value << std::endl;
    if (lookAhead(TokenType::JUMP) && tokens[++pos].value == "break") {
        auto breakNode = std::make_shared<JumpNode>();
        breakNode->breaker = tokens[pos].value;
        breakNode->continuer = "null";
        pos--;
        return breakNode;
    } else if (lookAhead(TokenType::JUMP) && tokens[++pos].value == "continue") {
        auto continueNode = std::make_shared<JumpNode>();
        continueNode->continuer = tokens[pos].value;
        continueNode->breaker = "null";
        pos--;
        return continueNode;
    } else {
        return nullptr;
    }
}

std::shared_ptr<ASTNode> Parser::parseSwitch() {
    std::cout << "Entering parseSwitch at position " << pos << " with token: " << tokens[pos].value << std::endl;
    if (lookAhead(TokenType::CONTROL) && tokens[++pos].value == "switch") {
        auto swNode = std::make_shared<SwitchNode>();
        if (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value[0] == '(') {
            pos++;
            swNode->condition = std::dynamic_pointer_cast<ConditionNode>(parseCondition());
            if (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value[0] == ')') {
                while (lookAhead(TokenType::CONTROL) && tokens[++pos].value == "case") {
                    auto cNode = std::make_shared<CaseNode>();
                    if (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value[0] == '(') {
                        pos++;
                        cNode->sucessCondition = parseCondition();
                        if (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value[0] == ')') {
                            if (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value[0] == ':') {
                                pos++;
                                cNode->Branch.push_back(parseDeclaration());
                                swNode->caseBranch.push_back(cNode);
                            } else {
                                return nullptr;
                            }
                        } else {
                            return nullptr;
                        }
                    }
                }
                return swNode;
            }
        }
    }
    std::cout << "parseSwitch returning nullptr" << std::endl;
    return nullptr;
}

std::shared_ptr<ASTNode> Parser::parseArray() {
    std::cout << "Entering parseArray at position " << pos << " with token: " << tokens[pos].value << std::endl;
    if (lookAhead(TokenType::TYPE)) {
        auto type = tokens[++pos].value;
        if (lookAhead(TokenType::IDENTIFIER)) {
            auto identifier = tokens[++pos].value;
        }
    }
    std::cout << "parseArray returning nullptr" << std::endl;
    return nullptr;
}

std::vector<std::shared_ptr<ASTNode>> Parser::parseArrayContents() {
    std::cout << "Entering parseArrayContents at position " << pos << " with token: " << tokens[pos].value << std::endl;
    if (tokens[pos].type == TokenType::CONST || tokens[pos].type == TokenType::FLOAT_CONST || tokens[pos].type == TokenType::STRING || tokens[pos].type == TokenType::BOOL) {
        std::vector<std::shared_ptr<ASTNode>> contents;
        auto arrayContentInput = parseValues();
        contents.push_back(arrayContentInput);
        while (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value[0] == ',') {
            arrayContentInput = parseValues();
            contents.push_back(arrayContentInput);
        }
        return contents;
    } else if (tokens[pos].type == TokenType::IDENTIFIER) {
        pos++;
        if (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value[0] == '[') {
            std::vector<std::shared_ptr<ASTNode>> contents;
            contents.push_back(parseArray());
            while (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value[0] == ',') {
                contents.push_back(parseArray());
            }
            return contents;
        }
        pos--;
        if (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value[0] == '(') {
            std::vector<std::shared_ptr<ASTNode>> contents;
            contents.push_back(parseFunctionCall());
            while (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value[0] == ',') {
                contents.push_back(parseFunctionCall());
            }
            return contents;
        }
        pos--;
        if (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value[0] == ',' || tokens[pos].value[0] == ']' && tokens[pos].type == TokenType::PUNCTUATION) {
            std::vector<std::shared_ptr<ASTNode>> contents;
            contents.push_back(parseIdentifier());
            while (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value[0] == ',') {
                contents.push_back(parseIdentifier());
            }
            return contents;
        }
        pos--;
    } else {
        exit(1);
    }
    std::cout << "parseArrayContents returning nullptr" << std::endl;
    return {};
}

std::shared_ptr<ASTNode> Parser::parseIfStatement() {
    std::cout << "Entering parseIfStatement at position " << pos << " with token: " << tokens[pos].value << std::endl;
    // Check to see if the loop token "if" is given
    if (lookAhead(TokenType::CONTROL) && tokens[pos].value == "if") {
        auto ifNode = std::make_shared<IfNode>();
        pos++;
        // Skips '(' and parses the condition
        if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value[0] == '(') {
            pos++;
            auto conditionNode = parseCondition();
            // Skip ')' and parses the body of the if statement, thereafter it assigns the condition and body.
            if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value[0] == ')') {
                pos++;
                auto bodyNode = parseLoopBody();
                ifNode->condition = std::dynamic_pointer_cast<ConditionNode>(conditionNode);
                ifNode->body = bodyNode;
                if (lookAhead(TokenType::CONTROL) && tokens[pos].value == "else") {
                    pos++;
                    auto elseBodyNode = parseLoopBody();
                    ifNode->elseBody = elseBodyNode;
                }
                if (lookAhead(TokenType::CONTROL) && tokens[pos].value == "else" && tokens[++pos].value == "if") {
                    pos++;
                    auto elseIfBodyNode = parseLoopBody();
                    ifNode->body = elseIfBodyNode;
                }
                return ifNode;
            }
        }
    }
    std::cout << "parseIfStatement returning nullptr" << std::endl;
    return nullptr;
}

std::shared_ptr<ASTNode> Parser::parseWhileLoop() {
    std::cout << "Entering parseWhileLoop at position " << pos << " with token: " << tokens[pos].value << std::endl;
    // Check to see if the loop token "while" is given
    if (lookAhead(TokenType::CONTROL) && tokens[pos].value == "while") {
        auto whileNode = std::make_shared<WhileNode>();
        pos++;
        // Skips '(' and parses the condition
        if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value[0] == '(') {
            pos++;
            auto conditionNode = parseCondition();
            // Skip ')' and parses the body of the if statement, thereafter it assigns the condition and body.
            if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value[0] == ')') {
                pos++;
                auto bodyNode = parseLoopBody();
                whileNode->condition = std::dynamic_pointer_cast<ConditionNode>(conditionNode);
                whileNode->body = bodyNode;
                return whileNode;
            }
        }
    }
    std::cout << "parseWhileLoop returning nullptr" << std::endl;
    return nullptr;
}

std::shared_ptr<ASTNode> Parser::parseConsole() {
    std::cout << "Entering parseConsole at position " << pos << " with token: " << tokens[pos].value << std::endl;
    if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].getType() == TokenType::CONSOLE) {
        auto consoleNode = std::make_shared<ConsoleNode>();
        pos++;
        while (tokens[pos].value != ")") {
            if (lookAhead(TokenType::CONST)) {
                consoleNode->message.push_back(parseInt());
            } else if (lookAhead(TokenType::FLOAT_CONST)) {
                consoleNode->message.push_back(parseFloat());
            } else if (lookAhead(TokenType::STRING)) {
                consoleNode->message.push_back(parseString());
            } else if (lookAhead(TokenType::IDENTIFIER)) {
                consoleNode->message.push_back(parseIdentifier());
            }
            pos++;
        }
        return consoleNode;
    }
    std::cout << "parseConsole returning nullptr" << std::endl;
    return nullptr;
}

// Rewrite logic to fit parser.h
std::shared_ptr<ASTNode> Parser::parseRandom() {
    std::cout << "Entering parseRandom at position " << pos << " with token: " << tokens[pos].value << std::endl;
    auto randomNode = std::make_shared<RandomNode>();
    std::string type = tokens[++pos].value;
    std::string identifier = tokens[++pos].value;
    randomNode->type = type;
    randomNode->identifier = identifier;
    if (lookAhead(TokenType::TYPE) && tokens[pos].value == "int?") { // Random Int
        auto randomIntNode = std::make_shared<RandomNode>();
        pos++;
        if (tokens[++pos].value[0] == '?') {
            if (lookAhead(TokenType::CONST)) {
                int RandomIntRangeLowBound = tokens[pos].value[0];
                randomNode->RandomIntRange.push_back(RandomIntRangeLowBound);
                pos++;
                if (tokens[pos].value == "." && tokens[++pos].value == ".") {
                    pos++;
                    if (lookAhead(TokenType::CONST) && tokens[pos].value[0] > RandomIntRangeLowBound) {
                        int RandomIntRangeHighBound = tokens[pos].value[0];
                        randomNode->RandomIntRange.push_back(RandomIntRangeHighBound);
                        pos -= 3;
                        return randomNode;
                    }
                }
            }
        }
    } else if (lookAhead(TokenType::TYPE) && tokens[pos].value == "float?") { // Random Float
        pos++;
        if (tokens[++pos].value[0] == '?') {
            if (lookAhead(TokenType::CONST)) {
                float RandomFloatRangeLowBound = tokens[pos].value[0];
                randomNode->RandomFloatRange.push_back(RandomFloatRangeLowBound);
                pos++;
                if (tokens[pos].value == "." && tokens[++pos].value == ".") {
                    pos++;
                    if (lookAhead(TokenType::CONST) && tokens[pos].value[0] > RandomFloatRangeLowBound) {
                        float RandomFloatRangeHighBound = tokens[pos].value[0];
                        randomNode->RandomFloatRange.push_back(RandomFloatRangeHighBound);
                        pos--;
                        pos--;
                        pos--;
                        return randomNode;
                    }
                }
            }
        }
    } else if (lookAhead(TokenType::TYPE) && tokens[pos].value == "bool?") { // Random bool
        return randomNode;
    }
    std::cout << "parseRandom returning nullptr" << std::endl;
    return nullptr;
}

void DeclarationNode::accept(ASTNodeVisitor& visitor) { visitor.visit(*this); }
void CharNode::accept(ASTNodeVisitor& visitor) { visitor.visit(*this); }
void ForLoopNode::accept(ASTNodeVisitor& visitor) { visitor.visit(*this); }
void IfNode::accept(ASTNodeVisitor& visitor) { visitor.visit(*this); }
void StructNode::accept(ASTNodeVisitor& visitor) { visitor.visit(*this); }
void FunctionNode::accept(ASTNodeVisitor& visitor) { visitor.visit(*this); }
void ValueNode::accept(ASTNodeVisitor& visitor) { visitor.visit(*this); }
void FloatNode::accept(ASTNodeVisitor& visitor) { visitor.visit(*this); }
void IntNode::accept(ASTNodeVisitor& visitor) { visitor.visit(*this); }
void StringNode::accept(ASTNodeVisitor& visitor) { visitor.visit(*this); }
void SwitchNode::accept(ASTNodeVisitor& visitor) { visitor.visit(*this); }
void CaseNode::accept(ASTNodeVisitor& visitor) { visitor.visit(*this); }
void ConditionNode::accept(ASTNodeVisitor& visitor) { visitor.visit(*this); }
void WhileNode::accept(ASTNodeVisitor& visitor) { visitor.visit(*this); }
void ConsoleNode::accept(ASTNodeVisitor& visitor) { visitor.visit(*this); }
void ReturnNode::accept(ASTNodeVisitor& visitor) { visitor.visit(*this); }
void RandomNode::accept(ASTNodeVisitor& visitor) { visitor.visit(*this); }
void ArrayNode::accept(ASTNodeVisitor& visitor) { visitor.visit(*this); }
void IdentifierNode::accept(ASTNodeVisitor& visitor) { visitor.visit(*this); }
void FunctionCallNode::accept(ASTNodeVisitor& visitor) { visitor.visit(*this); }
void BoolNode::accept(ASTNodeVisitor& visitor) { visitor.visit(*this); }
void UsIntNode::accept(ASTNodeVisitor& visitor) { visitor.visit(*this); }
void JumpNode::accept(ASTNodeVisitor& visitor) { visitor.visit(*this); }
