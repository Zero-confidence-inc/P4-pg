//
// Created by Yuki on 29/04/2024.
//
#include "Parser.h"
#include <iostream>
#include <string>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

std::vector<std::shared_ptr<ASTNode>> Parser::parseProgram() {
    std::vector<std::shared_ptr<ASTNode>> ast;
    while (pos < tokens.size()-1) {
        std::cout << "Entering parseProgram at position " << pos << " with token: " << tokens[pos+1].value << std::endl;
        if (lookAhead(TokenType::TYPE) && tokens[pos+1].value == "int?" || tokens[pos].value=="float?" || tokens[pos].value=="bool?"){
            auto random_pp = parseRandom();
            if (random_pp != nullptr){
                ast.push_back(random_pp);
            }
        }
        else{
            auto declaration_pp = parseDeclaration();
            std::cout << "declaration made current pos = " << pos <<std::endl;
            if (declaration_pp != nullptr){
                ast.push_back(declaration_pp);
            }
        }
    }
    // 'ast' now contains the entire program's AST
    return ast;
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
            functionNode->type = type;
            functionNode->identifier = identifier;
            functionNode->arguments = parseFunctionArguments();
            if(lookAhead(TokenType::PUNCTUATION) && tokens[pos+1].value == "{"){
                pos++;
                functionNode->body = parseFunctionBody();
                if(lookAhead(TokenType::PUNCTUATION) && tokens[pos+1].value == "}"){
                    pos++;
                    return functionNode;
                }
            }
            return nullptr;
        } else if (tokens[pos + 1].type == TokenType::OPERATOR && tokens[pos + 1].value == "=") {
            pos++; // Move to the '=' token
            std::cout << "Trying to make value node" << std::endl;
            auto valueNode = std::make_shared<ValueNode>();
            valueNode->type = type;
            valueNode->identifier = identifier;
            valueNode->value = parseValues();

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
        while (tokens[pos+1].value != "}") {
            if(lookAhead(TokenType::TYPE) && tokens[pos+1].value[tokens[pos+1].value.size()-1] == '?'){
                auto random = parseRandom();
                contents.push_back(random);
            } else if (lookAhead(TokenType::TYPE)){
                auto declaration = parseDeclaration();
                contents.push_back(declaration);

            } else if (lookAhead(TokenType::CONTROL)) {
                if (tokens[pos + 1].value == "if") {
                    auto ifStatement = parseIfStatement();
                    contents.push_back(ifStatement);
                } else if (tokens[pos + 1].value == "switch") {
                    auto switchStatement = parseSwitch();
                    contents.push_back(switchStatement);
                }
            }else if(lookAhead(TokenType::LOOP)){
                if(tokens[pos+1].value == "for"){
                    auto forStatement = parseForLoop();
                    contents.push_back(forStatement);
                }else if(tokens[pos+1].value == "while"){
                    auto whileStatement = parseWhileLoop();
                    contents.push_back(whileStatement);
                }
            } else if (lookAhead(TokenType::JUMP) && tokens[pos].value == "return") {
                auto returns = parseReturn();
                contents.push_back(returns);
            }




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
        auto valueInt = std::make_shared<IntNode>();
        std::cout << "made intnode " << "pos: " << pos << std::endl;
        valueInt->integer = std::stoi(tokens[++pos].value);
        std::cout << "assigned int " << "pos: " << pos << std::endl;
        pos++;
        match(TokenType::PUNCTUATION,";");
        pos--;
        return valueInt;
    } else if (tokens[pos - 2].value == "usint") {
        auto valueUsint = std::make_shared<UsIntNode>();
        valueUsint->usinteger = std::stoi(tokens[++pos].value);
        pos++;
        match(TokenType::PUNCTUATION,";");
        pos--;
        return valueUsint;
    } else if (tokens[pos - 2].value == "float") {
        auto valueFloat = std::make_shared<FloatNode>();
        valueFloat->Floating_Point = std::stof(tokens[++pos].value);
        pos++;
        match(TokenType::PUNCTUATION,";");
        pos--;
        return valueFloat;
    } else if (tokens[pos - 2].value == "char") {
        auto valueChar = std::make_shared<CharNode>();
        valueChar->character = tokens[++pos].value[0];
        pos++;
        match(TokenType::PUNCTUATION,";");
        pos--;
        return valueChar;
    } else if (tokens[pos - 2].value == "string") {
        auto valueString = std::make_shared<StringNode>();
        valueString->StringOfChars = tokens[++pos].value;
        pos++;
        match(TokenType::PUNCTUATION,";");
        pos--;
        return valueString;
    } else if (tokens[pos - 2].value == "bool") {
        auto valueBool = std::make_shared<BoolNode>();
        if (tokens[++pos].value == "true")
            valueBool->boolean = true;
        if (tokens[pos].value == "false")
            valueBool->boolean = false;
        pos++;
        match(TokenType::PUNCTUATION,";");
        pos--;
        return valueBool;
    } else if (tokens[++pos].type == TokenType::IDENTIFIER){
        if(lookAhead(TokenType::PUNCTUATION) && tokens[pos+1].value == "("){
            //auto valueFunctionCall = std::make_shared<FunctionCallNode>(); //parse functioncall apperently returns astnode so this did not work
            pos--;
            auto valueFunctionCall = parseFunctionCall();
            return valueFunctionCall;
        }
        auto valueIdentifier = std::make_shared<IdentifierNode>();
        valueIdentifier->identifier = tokens[pos].value;
        return valueIdentifier;
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

std::vector<std::shared_ptr<DeclarationNode>> Parser::parseFunctionArguments() {
    std::vector<std::shared_ptr<DeclarationNode>> arguments;
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
        } else if (lookAhead(TokenType::PUNCTUATION) && tokens[pos+1].value == ")") {
            pos++;
            std::cout << "Ending parseFunctionArguments with closing parenthesis at position " << pos << std::endl;
            break;
        }

    }
    return arguments;
}

std::vector<std::shared_ptr<ASTNode>> Parser::parseLoopBody() {
    std::vector<std::shared_ptr<ASTNode>> contents;
    std::cout << "Entering parseLoopBody" << std::endl;
    std::cout << "current pos is " << pos << " infiltration starting shortly" << std::endl;
    if (lookAhead(TokenType::PUNCTUATION) && tokens[pos+1].value[0] == '{') {
        pos++;
        std::cout << "first if infiltrated current pos = " << pos << std::endl;
        while (tokens[pos+1].value != "}") {
            if(lookAhead(TokenType::TYPE) && tokens[pos+1].value[tokens[pos+1].value.size()-1] == '?'){
                auto random = parseRandom();
                contents.push_back(random);
            } else if (lookAhead(TokenType::TYPE)){
                auto declaration = parseDeclaration();
                contents.push_back(declaration);
            } else if (lookAhead(TokenType::CONTROL)) {
                if (tokens[pos + 1].value == "if") {
                    auto ifStatement = parseIfStatement();
                    contents.push_back(ifStatement);
                } else if (tokens[pos + 1].value == "switch") {
                    auto switchStatement = parseSwitch();
                    contents.push_back(switchStatement);
                }
            }else if(lookAhead(TokenType::LOOP)){
                if(tokens[pos+1].value == "for"){
                    auto forStatement = parseForLoop();
                    contents.push_back(forStatement);
                }else if(tokens[pos+1].value == "while"){
                    auto whileStatement = parseWhileLoop();
                    contents.push_back(whileStatement);
                }
            } else if (lookAhead(TokenType::JUMP))
            {
                if(tokens[pos+1].value == "return") {
                    auto returns = parseReturn();
                    contents.push_back(returns);
                } else {
                   auto jump = parseJump();
                   contents.push_back(jump);
                }
            }else if (lookAhead(TokenType::IDENTIFIER)){
                if(tokens[pos+2].value == "=" || tokens[pos+2].value == "+=" ||tokens[pos+2].value == "-=") {
                    auto condi = parseCondition();
                    contents.push_back(condi);
                }
            }
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
            if (tokens[pos+2].type == TokenType::PUNCTUATION && tokens[pos+2].value == "("){
                conditionNode->aNode = parseFunctionCall();
            } else {
                conditionNode->aNode = parseIdentifier();
            }
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

                if (tokens[pos+2].type == TokenType::PUNCTUATION && tokens[pos+2].value == "("){
                    conditionNode->bNode = parseFunctionCall();
                } else {
                    conditionNode->bNode = parseIdentifier();
                }
            } else if (lookAhead(TokenType::CONST)) {
                conditionNode->bNode = parseInt();
            } else if (lookAhead(TokenType::FLOAT_CONST)) {
                conditionNode->bNode = parseFloat();
                std::cout<< "made it though float pos = " << pos <<std::endl;
            } else if (lookAhead(TokenType::STRING)) {
                conditionNode->bNode = parseString();
            } else if (lookAhead(TokenType::BOOL)) {
                conditionNode->bNode = parseBool();
            }
            std::cout << " current pos = " << pos <<std::endl;
            if(lookAhead(TokenType::PUNCTUATION) && tokens[pos+1].value == ";"){
                pos++;
                return conditionNode;
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
                std::cout << "made it back with pos = " << pos << std::endl;
                // Skips the second ';' and parses the expression
                pos--;
                if (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value[0] == ';') {
                    std::cout << "made it to last con" <<std::endl;
                    std::cout << "recon on second semi complete" << std::endl;
                    auto expressionNode = parseCondition();
                    // Skip ')' and parses the body of the loop, thereafter it assigns the, declaration, condition, expression and body.
                    if (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value[0] == ')') {

                        std::cout << "recon on end-bracket complete" << std::endl;
                        auto bodyNode = parseLoopBody();
                        forLoopNode->declaration = std::dynamic_pointer_cast<ValueNode>(declarationNode);
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
        if (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value == "(") {
            pos++;
            swNode->condition = std::dynamic_pointer_cast<ConditionNode>(parseCondition());
            if (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value == ")") {
                while (lookAhead(TokenType::CONTROL) && tokens[++pos].value == "case") {
                    auto cNode = std::make_shared<CaseNode>();
                    if (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value == "(") {
                        pos++;
                        cNode->sucessCondition = parseCondition();
                        if (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value == ")") {
                            if (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value == ":") {
                                pos++;
                                cNode->Branch.push_back(parseDeclaration());
                                swNode->caseBranch.push_back(cNode);
                            } else {
                                return nullptr;
                            }
                        } else {
                            return nullptr;
                        }
                    } else {
                        return nullptr;
                    }
                }
                if (lookAhead(TokenType::CONTROL) && tokens[++pos].value == "default"){
                    auto dNode = std::make_shared<DefaultNode>();
                    if(lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value == ":"){
                        pos++;
                        dNode->Branch.push_back(parseDeclaration());
                        swNode->deNode = dNode;
                    } else{
                        return nullptr;
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
                pos+=2;
                match(TokenType::PUNCTUATION,"{");
                pos-=2;
                std::cout << "out of condition brackets pos = " << pos << std::endl;
                auto bodyNode = parseLoopBody();
                ifNode->condition = std::dynamic_pointer_cast<ConditionNode>(conditionNode);
                ifNode->body = bodyNode;
                pos++;
                match(TokenType::PUNCTUATION,"}");
                pos--;
                if (lookAhead(TokenType::CONTROL) && tokens[pos+1].value == "else") {
                    pos++;
                    auto elseBodyNode = parseLoopBody();
                    ifNode->elseBody = elseBodyNode;
                }
                if (lookAhead(TokenType::CONTROL) && tokens[pos+1].value == "else" && tokens[pos+1].value == "if") {
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
                if (tokens[pos+2].value == "("){
                    consoleNode->message.push_back(parseFunctionCall());
                } else {
                    consoleNode->message.push_back(parseIdentifier());
                }
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
