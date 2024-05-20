//
// Created by Yuki on 29/04/2024.
//
#include "Parser.h"
#include <iostream>
#include <string>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

void Parser::parseProgram() {
    std::vector<std::shared_ptr<ASTNode>> ast;
    while (pos < tokens.size()) {
        std::cout << "Entering parseProgram at position " << pos << " with token: " << tokens[pos+1].value << std::endl;
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
    std::cout << "Entering parseDeclaration at position " << pos << " with token: " << tokens[pos+1].value << std::endl;

    if (lookAhead(TokenType::TYPE)) {
        std::string type = tokens[++pos].value;
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

            std::cout << "pos = " << pos << std::endl;
            return valueNode; //
        } else if (tokens[pos - 1].value == "struct") {
            pos++; // Move to the 'struct' token
            auto structNode = std::make_shared<StructNode>();
            structNode->type = type;
            structNode->identifier = identifier;
            structNode->struct_main = parseStruct();
            return structNode;
        } else if (tokens[pos + 1].type == TokenType::PUNCTUATION && tokens[pos + 1].value[0] == '[') {
            pos++;
            std::cout << "array found pos = " << pos << std::endl;

            auto arrayNode = std::make_shared<ArrayNode>();
            arrayNode->type = type;
            arrayNode->identifier = identifier;

            if (lookAhead(TokenType::CONST) || lookAhead(TokenType::IDENTIFIER)) {
                std::cout << "const/ident found, pos = " << pos << std::endl;
                auto arraySize = tokens[++pos].value;

                if (lookAhead(TokenType::PUNCTUATION) && tokens[pos + 1].value[0] == ']') {
                    pos ++; // Move to the ']' token
                    arrayNode->size = arraySize;
                    if (lookAhead(TokenType::PUNCTUATION) && tokens[pos + 1].value[0] == ';') {
                        pos++; // Move to the ';' token
                        return arrayNode;
                    } else if (tokens[pos].type == TokenType::OPERATOR && tokens[pos + 1].value[0] == '=') {
                        pos++;
                        match(TokenType::PUNCTUATION, "[");
                        arrayNode->body = parseArrayContents();
                        match(TokenType::PUNCTUATION, "]");
                        match(TokenType::PUNCTUATION, ";");
                        pos--;
                        return arrayNode;
                    }
                }
            }
        }else if(tokens[pos + 1].type == TokenType::PUNCTUATION && tokens[pos + 1].value[0] == ';') {
            auto rulerNode = std::make_shared<DeclarationNode>();
            rulerNode->type = type;
            rulerNode->identifier = identifier;
            return rulerNode;
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
    std::cout << "Entering parseReturn at position " << pos << " with token: " << tokens[pos+1].value << std::endl;
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
    std::cout << "Entering parseValues at position " << pos << " with token: " << tokens[pos+1].value << std::endl;
    if (tokens[pos - 2].value == "int") {
        std::cout << "hacker voice: i'm in " << "pos: " << pos << std::endl;
        auto valueInt = std::make_shared<IntNode>();
        std::cout << "made intnode " << "pos: " << pos << std::endl;
        valueInt->integer = tokens[++pos].value[0];
        std::cout << "assigned int " << "pos: " << pos << std::endl;
        return valueInt;
    } else if (tokens[pos - 2].value == "usint") {
        auto valueUsint = std::make_shared<UsIntNode>();
        valueUsint->usinteger = tokens[pos].value[0];
        return valueUsint;
    } else if (tokens[pos - 2].value == "float") {
        auto valueFloat = std::make_shared<FloatNode>();
        valueFloat->Floating_Point = tokens[pos].value[0];
        return valueFloat;
    } else if (tokens[pos - 2].value == "char") {
        auto valueChar = std::make_shared<CharNode>();
        valueChar->character = tokens[pos].value[0];
        return valueChar;
    } else if (tokens[pos - 2].value == "string") {
        auto valueString = std::make_shared<StringNode>();
        valueString->StringOfChars = tokens[pos].value[0];
        return valueString;
    } else if (tokens[pos - 2].value == "bool") {
        auto valueBool = std::make_shared<BoolNode>();
        valueBool->boolean = tokens[pos].value[0];
        return valueBool;
    } else return nullptr;
}

std::shared_ptr<ASTNode> Parser::parseFunctionCall() {
    std::cout << "Entering parseFunctionCall at position " << pos << " with token: " << tokens[pos+1].value << std::endl;
    if (lookAhead(TokenType::IDENTIFIER) && tokens[pos+2].value[0] == '(') {
        std::string identifier = tokens[++pos].value;
        auto functionCallNode = std::make_shared<FunctionCallNode>();
        functionCallNode->identifier = identifier;
        while (tokens[++pos].value == "," || tokens[++pos].value == "(") {
            auto argument = parseIdentifier();
            functionCallNode->arguments.push_back(argument);
        }
        return functionCallNode;
    } else {
        return nullptr;
    }
}

std::vector<std::shared_ptr<ASTNode>> Parser::parseFunctionArguments() {
    std::vector<std::shared_ptr<ASTNode>> arguments;
    std::cout << "Entering parseFunctionArguments" << std::endl;

    while (true) {
        if (lookAhead(TokenType::TYPE)) {
            std::string type = tokens[++pos].value;
            std::string identifier = tokens[++pos].value;
            auto declaration = std::make_shared<DeclarationNode>();
            declaration->type = type;
            declaration->identifier = identifier;
            arguments.push_back(declaration);
            std::cout << "Parsed argument type: " << type << ", identifier: " << identifier << std::endl;
        }
        if (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value == ")") {
            std::cout << "Ending parseFunctionArguments with closing parenthesis at position " << pos << std::endl;
            break;
        }

    }
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
            auto ifStatement = parseIfStatement();
            auto whileLoop = parseWhileLoop();
            contents.push_back(declaration);
            contents.push_back(forLoop);
            contents.push_back(switchCase);
            contents.push_back(ifStatement);
            contents.push_back(whileLoop);
        }
    } else {
        return {};
    }
    return contents;
}

std::shared_ptr<ASTNode> Parser::parseStruct() {
    std::cout << "Entering parseStruct at position " << pos << " with token: " << tokens[pos+1].value << std::endl;
    if (lookAhead(TokenType::TYPE) && tokens[++pos].value == "struct") {
        std::cout << "pos = " << pos << std::endl;
        auto identify = tokens[++pos].value;
        std::cout << "pos = " << pos << std::endl;
        if (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value == "{") {
            std::cout << "pos = " << pos << std::endl;
            auto structNode = std::make_shared<StructNode>();
            structNode->identifier = identify;
            structNode->body = parseStructBody();
            match(TokenType::PUNCTUATION, "}");
            pos--;
            std::cout << "pos = " << pos << std::endl;
            return structNode;
        }
    }
    std::cout << "parseStruct returning nullptr" << std::endl;
    return nullptr;
}

std::shared_ptr<ASTNode> Parser::parseIdentifier() {
    std::cout << "Entering parseIdentifier at position " << pos << " with token: " << tokens[pos+1].value << std::endl;

    if (lookAhead(TokenType::IDENTIFIER)) {
        std::string identifier = tokens[++pos].value;
        auto identifierNode = std::make_shared<IdentifierNode>();
        identifierNode->identifier = identifier;
        return identifierNode;
    } else {
        return nullptr;
    }
}

std::shared_ptr<ASTNode> Parser::parseCondition() {
    std::cout << "Entering parseCondition at position " << pos << " with token: " << tokens[pos+1].value << std::endl;
    if (lookAhead(TokenType::CONST) || lookAhead(TokenType::FLOAT_CONST) || lookAhead(TokenType::STRING)
        || lookAhead(TokenType::IDENTIFIER) || lookAhead(TokenType::BOOL)) {

        auto conditionNode = std::make_shared<ConditionNode>();
        if (lookAhead(TokenType::IDENTIFIER)) {
            conditionNode->aNode = parseIdentifier();
        } else if (lookAhead(TokenType::CONST)) {
            conditionNode->aNode = parseInt();
        } else if (lookAhead(TokenType::FLOAT_CONST)) {
            conditionNode->aNode = parseFloat();
        } else if (lookAhead(TokenType::STRING)) {
            conditionNode->aNode = parseString();
        } else if (lookAhead(TokenType::BOOL)) {
            conditionNode->aNode = parseBool();
        }
        std::cout << "pos = " << pos <<std::endl;
        if (lookAhead(TokenType::OPERATOR)) {
            conditionNode->condition = tokens[++pos].value;
            std::cout << "pos = " << pos <<std::endl;
        } else {
            return conditionNode;
        }
        if (tokens[pos+2].type == TokenType::OPERATOR) {
            conditionNode->bNode = parseCondition();
        } else if (lookAhead(TokenType::CONST) || lookAhead(TokenType::FLOAT_CONST) || lookAhead(TokenType::STRING)
                   || lookAhead(TokenType::IDENTIFIER) || lookAhead(TokenType::BOOL)) {

            if (lookAhead(TokenType::IDENTIFIER)) {
                conditionNode->bNode = parseIdentifier();
            } else if (lookAhead(TokenType::CONST)) {
                conditionNode->bNode = parseInt();
            } else if (lookAhead(TokenType::FLOAT_CONST)) {
                conditionNode->bNode = parseFloat();
            } else if (lookAhead(TokenType::STRING)) {
                conditionNode->bNode = parseString();
            } else if (lookAhead(TokenType::BOOL)) {
                conditionNode->bNode = parseBool();
            }
        }
        return conditionNode;
    }
    std::cout << "parseCondition returning nullptr" << std::endl;
    return nullptr;
}

// Parses the char type
std::shared_ptr<ASTNode> Parser::parseChar() {
    std::cout << "Entering parseChar at position " << pos << " with token: " << tokens[pos+1].value << std::endl;

    if (lookAhead(TokenType::STRING)) {
        std::string tokenValue = tokens[++pos].value;
        // Check if the token is a single character enclosed in single quotes
        if (tokenValue.length() == 3 && tokenValue[0] == '\'' && tokenValue[2] == '\'') {
            auto charNode = std::make_shared<CharNode>();
            charNode->character = tokenValue[1]; // Extract the character between the quotes
            pos++;
            return charNode;
        }
    }

    std::cout << "parseChar returning nullptr" << std::endl;
    return nullptr;
}

std::shared_ptr<ASTNode> Parser::parseFloat() {
    std::cout << "Entering parseFloat at position " << pos << " with token: " << tokens[pos+1].value << std::endl;
    if (lookAhead(TokenType::FLOAT_CONST)) {
        auto FloatingNode = std::make_shared<FloatNode>();
        FloatingNode->Floating_Point = std::stof(tokens[++pos].value);
        return FloatingNode;
    }
    std::cout << "parseFloat returning nullptr" << std::endl;
    return nullptr;
}

std::shared_ptr<ASTNode> Parser::parseInt() {
    std::cout << "Entering parseInt at position " << pos << " with token: " << tokens[pos+1].value << std::endl;
    if (lookAhead(TokenType::CONST)) {
        auto intNode = std::make_shared<IntNode>();
        intNode->integer = std::stoi(tokens[++pos].value);
        return intNode;
    }
    std::cout << "parseInt returning nullptr" << std::endl;
    return nullptr;
}

std::shared_ptr<ASTNode> Parser::parseBool() {
    std::cout << "Entering parseBool at position " << pos << " with token: " << tokens[pos+1].value << std::endl;
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
    std::cout << "Entering parseString at position " << pos << " with token: " << tokens[pos+1].value << std::endl;
    if (lookAhead(TokenType::STRING)) {
        auto stringNode = std::make_shared<StringNode>();
        stringNode->StringOfChars = tokens[pos].value;
        return stringNode;
    }
    std::cout << "parseString returning nullptr" << std::endl;
    return nullptr;
}

std::shared_ptr<ASTNode> Parser::parseUsInt() {
    std::cout << "Entering parseUsInt at position " << pos << " with token: " << tokens[pos+1].value << std::endl;
    if (lookAhead(TokenType::CONST)) {
        auto usIntNode = std::make_shared<UsIntNode>();
        usIntNode->usinteger = std::stoi(tokens[++pos].value);
        return usIntNode;
    }
    std::cout << "parseUsInt returning nullptr" << std::endl;
    return nullptr;
}

// Parses a for loop
std::shared_ptr<ASTNode> Parser::parseForLoop() {
    std::cout << "Entering parseForLoop at position " << pos << " with token: " << tokens[pos+1].value << std::endl;
    // Check to see if the loop token "for" is given
    if (lookAhead(TokenType::LOOP) && tokens[++pos].value == "for") {
        auto forLoopNode = std::make_shared<ForLoopNode>();

        std::cout << "recon on for complete" << std::endl;
        // Skips '(' and parses the declaration
        if (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value[0] == '(') {

            std::cout << "recon on bracket complete" << std::endl;
            auto declarationNode = parseDeclaration();
            std::cout << "made it back" << std::endl;
            // Skips the first ';' and parses the condition
            std::cout << "current pos = " << pos << std::endl;
                auto conditionNode = parseCondition();
                std::cout << "made it back" << std::endl;
                // Skips the second ';' and parses the expression
                if (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value[0] == ';') {

                    std::cout << "recon on second semi complete" << std::endl;
                    auto expressionNode = parseCondition();
                    // Skip ')' and parses the body of the loop, thereafter it assigns the, declaration, condition, expression and body.
                    if (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value[0] == ')') {

                        std::cout << "recon on end-bracket complete" << std::endl;
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

    std::cout << "parseForLoop returning nullptr" << std::endl;
    return nullptr;
}

std::shared_ptr<ASTNode> Parser::parseJump() {
    if (lookAhead(TokenType::JUMP)) {
        if (tokens[pos + 1].value == "break") {
            pos++;
            auto jumpNode = std::make_shared<JumpNode>();
            jumpNode->breaker = tokens[pos].value;
            jumpNode->continuer = "null";
            return jumpNode;
        } else if (tokens[pos + 1].value == "continue") {
            pos++;
            auto jumpNode = std::make_shared<JumpNode>();
            jumpNode->continuer = tokens[pos].value;
            jumpNode->breaker = "null";
            return jumpNode;
        }
    }
    return nullptr;
}

std::shared_ptr<ASTNode> Parser::parseSwitch() {
    std::cout << "Entering parseSwitch at position " << pos << " with token: " << tokens[pos+1].value << std::endl;
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

//std::shared_ptr<ASTNode> Parser::parseArray() {
  //  std::cout << "Entering parseArray at position " << pos << " with token: " << tokens[pos+1].value << std::endl;
    //if (lookAhead(TokenType::TYPE)) {
      //  auto type = tokens[++pos].value;
        //if (lookAhead(TokenType::IDENTIFIER)) {
          //  auto identifier = tokens[++pos].value;
       // }
    //}
   // std::cout << "parseArray returning nullptr" << std::endl;
  //  return nullptr;
//}

std::vector<std::shared_ptr<ASTNode>> Parser::parseArrayContents() {
    std::cout << "Entering parseArrayContents at position " << pos << " with token: " << tokens[pos+1].value << std::endl;
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
            contents.push_back(parseDeclaration());
            while (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value[0] == ',') {
                contents.push_back(parseDeclaration());
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
    std::cout << "Entering parseIfStatement at position " << pos << " with token: " << tokens[pos+1].value << std::endl;
    // Check to see if the loop token "if" is given
    if (lookAhead(TokenType::CONTROL) && tokens[pos+1].value == "if") {
        pos++;
        auto ifNode = std::make_shared<IfNode>();
        // Skips '(' and parses the condition
        if (lookAhead(TokenType::PUNCTUATION) && tokens[pos+1].value[0] == '(') {
            std::cout << "pos = " << pos << std::endl;
            pos++;
            auto conditionNode = parseCondition();
            // Skip ')' and parses the body of the if statement, thereafter it assigns the condition and body.
            if (lookAhead(TokenType::PUNCTUATION) && tokens[pos+1].value[0] == ')') {
                pos += 2;
                match(TokenType::PUNCTUATION,"{");
                std::cout << "out of condition brackets pos = " << pos << std::endl;
                auto bodyNode = parseLoopBody();
                ifNode->condition = std::dynamic_pointer_cast<ConditionNode>(conditionNode);
                ifNode->body = bodyNode;
                match(TokenType::PUNCTUATION,"}");
                pos--;
                if (lookAhead(TokenType::CONTROL) && tokens[pos].value == "else") {
                    pos++;
                    auto elseBodyNode = parseLoopBody();
                    ifNode->elseBody = elseBodyNode;
                }
                if (lookAhead(TokenType::CONTROL) && tokens[pos].value == "else" && tokens[pos+1].value == "if") {
                    pos++;
                    auto elseIfBodyNode = parseLoopBody();
                    ifNode->body = elseIfBodyNode;
                }
                std::cout << "pos = " << pos << std::endl;
                return ifNode;
            }
        }
    }
    std::cout << "parseIfStatement returning nullptr" << std::endl;
    return nullptr;
}

std::shared_ptr<ASTNode> Parser::parseWhileLoop() {
    std::cout << "Entering parseWhileLoop at position " << pos << " with token: " << tokens[pos+1].value << std::endl;
    // Check to see if the loop token "while" is given
    if (lookAhead(TokenType::CONTROL) && tokens[pos+1].value == "while") {
        pos++;
        auto whileNode = std::make_shared<WhileNode>();
        // Skips '(' and parses the condition
        if (lookAhead(TokenType::PUNCTUATION) && tokens[pos+1].value[0] == '(') {
            pos++;
            auto conditionNode = parseCondition();
            // Skip ')' and parses the body of the if statement, thereafter it assigns the condition and body.
            if (lookAhead(TokenType::PUNCTUATION) && tokens[pos+1].value[0] == ')') {
                pos++;
                if (lookAhead(TokenType::PUNCTUATION) && tokens[pos+1].value[0] == '{') {
                    pos++;
                    auto bodyNode = parseLoopBody();
                    whileNode->condition = std::dynamic_pointer_cast<ConditionNode>(conditionNode);
                    whileNode->body = bodyNode;
                    std::cout << "pos = " << pos << std::endl;
                    match(TokenType::PUNCTUATION,"}");
                    --pos;
                    return whileNode;
                }
            }
        }
    }
    std::cout << "parseWhileLoop returning nullptr" << std::endl;
    return nullptr;
}

std::shared_ptr<ASTNode> Parser::parseConsole() {
    std::cout << "Entering parseConsole at position " << pos << " with token: " << tokens[pos+1].value << std::endl;
    if (lookAhead(TokenType::CONSOLE)) {
        pos++;
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
    std::cout << "Entering parseRandom at position " << pos << " with token: " << tokens[pos+1].value << std::endl;
    auto randomNode = std::make_shared<RandomNode>();
    std::string type = tokens[pos+1].value;
    std::string identifier = tokens[pos+2].value;
    randomNode->type = type;
    randomNode->identifier = identifier;

    if (lookAhead(TokenType::TYPE) && tokens[pos+1].value == "int?") { // Random Int
        pos +=2;
        auto randomIntNode = std::make_shared<RandomNode>();

        std::cout << "pos = " << pos << std::endl;
        if (tokens[++pos].value[0] == '?') {
            std::cout << " before const pos = " << pos << std::endl;
            if (lookAhead(TokenType::CONST)) {
                std::cout << "after const seen pos = " << pos << std::endl;
                int RandomIntRangeLowBound = std::stoi(tokens[++pos].value);
                std::cout << "pos = " << pos << " lowbound =" << RandomIntRangeLowBound << std::endl;
                randomNode->RandomIntRange.push_back(RandomIntRangeLowBound);
                std::cout << "survived pos = " << pos << std::endl;
                if (tokens[++pos].value == "." && tokens[++pos].value == ".") {
                    std::cout << ".. recognicred pos = " << pos << std::endl;
                    if (lookAhead(TokenType::CONST) && std::stoi(tokens[++pos].value) > RandomIntRangeLowBound) {
                        std::cout << "pos = " << pos << std::endl;
                        int RandomIntRangeHighBound = std::stoi(tokens[pos].value);
                        randomNode->RandomIntRange.push_back(RandomIntRangeHighBound);
                        std::cout << "pos = " << pos << std::endl;
                        pos++;
                        match(TokenType::PUNCTUATION,"?");
                        pos--;
                        return randomNode;
                    }
                }
            }
        }
    } else if (lookAhead(TokenType::TYPE) && tokens[pos+1].value == "float?") { // Random Float
        std::cout << "pos1 = " << pos << std::endl;
        pos += 2;
        if (tokens[++pos].value == "?") {
            std::cout << "pos2 = " << pos << std::endl;
            if (lookAhead(TokenType::CONST)|| lookAhead(TokenType::FLOAT_CONST)) {
                std::cout << "pos3 = " << pos << std::endl;
                float RandomFloatRangeLowBound = std::stof(tokens[++pos].value);
                std::cout << "pos4 = " << pos << " lowb =" << RandomFloatRangeLowBound<< std::endl;
                randomNode->RandomFloatRange.push_back(RandomFloatRangeLowBound);
                pos++;
                if (tokens[pos].value == "." && tokens[++pos].value == ".") {
                    std::cout << "pos4 = " << pos << std::endl;
                    std::cout << "pos5 = " << pos << std::endl;
                    if (lookAhead(TokenType::CONST) && std::stof(tokens[pos+1].value) > RandomFloatRangeLowBound
                    ||lookAhead(TokenType::FLOAT_CONST) && std::stof(tokens[pos+1].value) > RandomFloatRangeLowBound) {
                        std::cout << "pos6 = " << pos << std::endl;
                        float RandomFloatRangeHighBound = std::stof(tokens[++pos].value);
                        randomNode->RandomFloatRange.push_back(RandomFloatRangeHighBound);
                        std::cout << "pos7 = " << pos << std::endl;
                        return randomNode;
                    }
                }
            }
        }
    } else if (lookAhead(TokenType::TYPE) && tokens[pos+1].value == "bool?") { // Random bool
        pos++;
        return randomNode;
    }
    std::cout << "parseRandom returning nullptr" << std::endl;
    return nullptr;
}
