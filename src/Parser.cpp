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
            if (declaration_pp != nullptr){
                ast.push_back(declaration_pp);
            }
        }
    }
    std::cout << "Parsing finalized returning AST" << std::endl;
    return ast;
}

std::shared_ptr<ASTNode> Parser::parseDeclaration() {
    std::cout << "Entering parseDeclaration at position " << pos << " with token: " << tokens[pos].value << std::endl;

    if (lookAhead(TokenType::TYPE)) {
        std::string type = tokens[++pos].value;
        std::string identifier = tokens[++pos].value;



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
                    std::cout<<"Parsed functionNode"<<std::endl;
                    return functionNode;
                }
            }
            std::cout << "parseDeclaration returning nullptr" << std::endl;
            return nullptr;
        } else if (tokens[pos + 1].type == TokenType::OPERATOR && tokens[pos + 1].value == "=") {
            pos++; // Move to the '=' token
            auto valueNode = std::make_shared<ValueNode>();
            valueNode->type = type;
            valueNode->identifier = identifier;
            valueNode->value = parseValues();

            std::cout<<"Parsed valueNode"<<std::endl;
            return valueNode; //
        } else if (tokens[pos - 1].value == "struct") {
            pos++; // Move to the 'struct' token
            auto structNode = std::make_shared<StructNode>();
            structNode->type = type;
            structNode->identifier = identifier;

            structNode->body.push_back(parseStruct());
            
            std::cout<<"Parsed structNode"<<std::endl;
            return structNode;
        } else if (tokens[pos + 1].type == TokenType::PUNCTUATION && tokens[pos + 1].value[0] == '[') {
            pos++;

            auto arrayNode = std::make_shared<ArrayNode>();
            arrayNode->type = type;
            arrayNode->identifier = identifier;

            if (lookAhead(TokenType::CONST) || lookAhead(TokenType::IDENTIFIER)) {
                auto arraySize = tokens[++pos].value;

                if (lookAhead(TokenType::PUNCTUATION) && tokens[pos + 1].value[0] == ']') {
                    pos ++; // Move to the ']' token
                    arrayNode->size = arraySize;
                    if (lookAhead(TokenType::PUNCTUATION) && tokens[pos + 1].value[0] == ';') {
                        pos++; // Move to the ';' token
                        std::cout<<"Parsed arrayNode"<<std::endl;
                        return arrayNode;
                    } else if (tokens[pos].type == TokenType::OPERATOR && tokens[pos + 1].value[0] == '=') {
                        pos++;
                        match(TokenType::PUNCTUATION, "[");
                        arrayNode->body = parseArrayContents();
                        match(TokenType::PUNCTUATION, "]");
                        match(TokenType::PUNCTUATION, ";");
                        pos--;
                        std::cout<<"Parsed arrayNode"<<std::endl;
                        return arrayNode;
                    }
                }
            }
        }else if(tokens[pos + 1].type == TokenType::PUNCTUATION && tokens[pos + 1].value[0] == ';') {
            auto rulerNode = std::make_shared<DeclarationNode>();
            rulerNode->type = type;
            rulerNode->identifier = identifier;

            std::cout<<"Parsed declarationNode"<<std::endl;
            return rulerNode;
        }

    }
    std::cout << "parseDeclaration returning nullptr" << std::endl;
    return nullptr;
}

bool Parser::lookAhead(TokenType expectedType) {

    return (pos + 1) < tokens.size() && tokens[pos + 1].type == expectedType;
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
    std::cout << "Entering parseFunctionBody at pos "<< pos <<" with token " << tokens[pos].value << std::endl;
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
            } else if (lookAhead(TokenType::JUMP) && tokens[pos+1].value == "return"){
                auto returns = parseReturn();
                contents.push_back(returns);

            }
        }
    std::cout<<"Parsed functionBody"<<std::endl;
    return contents;
}

std::shared_ptr<ASTNode> Parser::parseReturn() {
    std::cout << "Entering parseReturn at position " << pos << " with token: " << tokens[pos+1].value << std::endl;
    if (lookAhead(TokenType::JUMP) && tokens[++pos].value == "return") {
        auto returnNode = std::make_shared<ReturnNode>();
        returnNode->identifier = tokens[++pos].value;
        if(lookAhead(TokenType::PUNCTUATION)&& tokens[pos+1].value == ";"){
            pos++;
            std::cout<<"Parsed returnNode"<<std::endl;
            return returnNode;
        }
    }
    std::cout << "parseReturn returning nullptr" << std::endl;
    return nullptr;
}

std::vector<std::shared_ptr<ASTNode>> Parser::parseStructBody() {
    std::vector<std::shared_ptr<ASTNode>> contents;
    std::cout << "Entering parseStructBody" << std::endl;
    while (tokens[++pos].value[0] != '}') {
        auto declaration = parseDeclaration();
        contents.push_back(declaration);
    }

    std::cout<<"Parsed structBody"<<std::endl;
    return contents;
}

std::shared_ptr<ASTNode> Parser::parseValues() {
    std::cout << "Entering parseValues at position " << pos << " with token: " << tokens[pos+1].value << std::endl;
    if (tokens[pos - 2].value == "int" && tokens[pos+1].type != TokenType::IDENTIFIER) {

        auto valueInt = std::make_shared<IntNode>();
        valueInt->integer = std::stoi(tokens[++pos].value);
        pos++;
        match(TokenType::PUNCTUATION,";");
        pos--;
        return valueInt;
    } else if (tokens[pos - 2].value == "usint"&& tokens[pos+1].type != TokenType::IDENTIFIER) {

        auto valueUsint = std::make_shared<UsIntNode>();
        valueUsint->usinteger = std::stoi(tokens[++pos].value);
        pos++;
        match(TokenType::PUNCTUATION,";");
        pos--;
        std::cout<<"Parsed usintNode"<<std::endl;
        return valueUsint;
    } else if (tokens[pos - 2].value == "float" && tokens[pos+1].type != TokenType::IDENTIFIER) {

        auto valueFloat = std::make_shared<FloatNode>();
        valueFloat->Floating_Point = std::stof(tokens[++pos].value);
        pos++;
        match(TokenType::PUNCTUATION,";");
        pos--;
        std::cout<<"Parsed floatNode"<<std::endl;
        return valueFloat;
    } else if (tokens[pos - 2].value == "char"&& tokens[pos+1].type != TokenType::IDENTIFIER) {

        auto valueChar = std::make_shared<CharNode>();
        valueChar->character = tokens[++pos].value[0];
        pos++;
        match(TokenType::PUNCTUATION,";");
        pos--;
        std::cout<<"Parsed charNode"<<std::endl;
        return valueChar;
    } else if (tokens[pos - 2].value == "string"&& tokens[pos+1].type != TokenType::IDENTIFIER) {

        auto valueString = std::make_shared<StringNode>();
        valueString->StringOfChars = tokens[++pos].value;
        pos++;
        match(TokenType::PUNCTUATION,";");
        pos--;
        std::cout<<"Parsed stringNode"<<std::endl;
        return valueString;
    } else if (tokens[pos - 2].value == "bool"&& tokens[pos+1].type != TokenType::IDENTIFIER) {

        auto valueBool = std::make_shared<BoolNode>();
        if (tokens[++pos].value == "true")
            valueBool->boolean = true;
        if (tokens[pos].value == "false")
            valueBool->boolean = false;
        pos++;
        match(TokenType::PUNCTUATION,";");
        pos--;
        std::cout<<"Parsed boolNode"<<std::endl;
        return valueBool;
    } else if (tokens[pos+1].type == TokenType::IDENTIFIER){

        if(tokens[pos+2].value == "("){
            //auto valueFunctionCall = std::make_shared<FunctionCallNode>(); //parse functionCall apperently returns astnode so this did not work
            auto valueFunctionCall = parseFunctionCall();
            std::cout<<"Parsed functionCallNode"<<std::endl;
            return valueFunctionCall;

        }else{
            auto identifier = std::make_shared<IdentifierNode>();
            identifier->identifier = tokens[++pos].value;
            pos++;
            match(TokenType::PUNCTUATION,";");
            pos--;
            return identifier;
        }
        auto valueIdentifier = std::make_shared<IdentifierNode>();
        valueIdentifier->identifier = tokens[pos].value;
        std::cout<<"Parsed identifierNode"<<std::endl;
        return valueIdentifier;
    } else {
        std::cout << "parseRValues returning nullptr" << std::endl;
        return nullptr;}
}

std::shared_ptr<ASTNode> Parser::parseFunctionCall() {
    std::cout << "Entering parseFunctionCall at position " << pos << " with token: " << tokens[pos+1].value << std::endl;
    if (lookAhead(TokenType::IDENTIFIER) && tokens[pos+2].value[0] == '(') {
        std::string identifier = tokens[++pos].value;
        auto functionCallNode = std::make_shared<FunctionCallNode>();
        functionCallNode->identifier = identifier;
        while (tokens[pos].value != ")") {
            pos++;

            if (lookAhead(TokenType::IDENTIFIER)) {
                auto argument = parseIdentifier();
                functionCallNode->arguments.push_back(argument);
            }else if (lookAhead(TokenType::CONST)){
                auto argument = parseInt();
                functionCallNode->arguments.push_back(argument);
            }else if (lookAhead(TokenType::FLOAT_CONST)){
                auto argument = parseFloat();
                functionCallNode->arguments.push_back(argument);
            }else if (lookAhead(TokenType::BOOL)){
                auto argument = parseBool();
                functionCallNode->arguments.push_back(argument);
            }else if (lookAhead(TokenType::STRING)){
                auto argument = parseString();
                functionCallNode->arguments.push_back(argument);
            }
        }
        if(lookAhead(TokenType::PUNCTUATION) && tokens[pos+1].value == ";"){
            pos++;
            std::cout<<"Parsed functionCallNode"<<std::endl;

            return functionCallNode;
        }

    }
std::cout << "parseFunctionCall returning nullptr" << std::endl;
return nullptr;
}

std::vector<std::shared_ptr<DeclarationNode>> Parser::parseFunctionArguments() {
    std::vector<std::shared_ptr<DeclarationNode>> arguments;
    std::cout << "Entering parseFunctionArguments at position " << pos <<" with token: " <<tokens[pos].value << std::endl;

    while (true) {
        if (lookAhead(TokenType::TYPE)) {
            std::string type = tokens[++pos].value;
            std::string identifier = tokens[++pos].value;
            auto declaration = std::make_shared<DeclarationNode>();
            declaration->type = type;
            declaration->identifier = identifier;
            arguments.push_back(declaration);

        } else if (lookAhead(TokenType::PUNCTUATION) && tokens[pos+1].value == ","){
            pos++;

        }else if (lookAhead(TokenType::PUNCTUATION) && tokens[pos+1].value == ")") {
            pos++;
            std::cout << "Ending parseFunctionArguments with closing parenthesis at position " << pos << std::endl;
            break;
        }

    }
    std::cout<<"Parsed functionArguments"<<std::endl;
    return arguments;
}

std::vector<std::shared_ptr<ASTNode>> Parser::parseLoopBody() {
    std::vector<std::shared_ptr<ASTNode>> contents;
    std::cout << "Entering parseLoopBody" << std::endl;
    if (lookAhead(TokenType::PUNCTUATION) && tokens[pos+1].value == "{") {
        pos++;
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
            } else if(lookAhead(TokenType::LOOP)){
                if(tokens[pos+1].value == "for"){
                    auto forStatement = parseForLoop();
                    std::cout<<"pos/token " << pos << "/" << tokens[pos].value<<std::endl;
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

                //std::cout<< "you shall not pass" <<std::endl;
                if(tokens[pos+2].value == "=" || tokens[pos+2].value == "+="||tokens[pos+2].value == "-="
                    ||tokens[pos+2].value == "++"||tokens[pos+2].value == "--") {
                    auto condi = parseCondition();

                    contents.push_back(condi);
                }else if(tokens[pos+2].value == "("){
                    auto funCall = parseFunctionCall();
                    contents.push_back(funCall);
                }
            }
        }
    }
    std::cout<<"Parsed parsed loopbody"<<std::endl;
    return contents;
}

std::shared_ptr<ASTNode> Parser::parseStruct() {
    if (lookAhead(TokenType::TYPE) && tokens[++pos].value == "struct") {
        auto identify = tokens[++pos].value;
        if (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value == "{") {
            auto structNode = std::make_shared<StructNode>();
            structNode->body = parseStructBody();
            match(TokenType::PUNCTUATION, "}");
            pos--;
            std::cout<<"Parsed structNode"<<std::endl;
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
        std::cout<<"Parsed identifierNode"<<std::endl;
        return identifierNode;
    } else {
        std::cout << "parseIdentifier returning nullptr" << std::endl;
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

        if (lookAhead(TokenType::OPERATOR)) {
            conditionNode->condition = tokens[++pos].value;

        } else {
            std::cout<<"Parsed conditionNode"<<std::endl;
            return conditionNode;
        }
        if (tokens[pos+2].type == TokenType::OPERATOR) {
            conditionNode->bNode = parseCondition();
        } else if (lookAhead(TokenType::CONST) || lookAhead(TokenType::FLOAT_CONST) || lookAhead(TokenType::STRING)
                   || lookAhead(TokenType::IDENTIFIER) || lookAhead(TokenType::BOOL) || lookAhead(TokenType::PUNCTUATION) && tokens[pos+1].value == ";") {

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
            } else if (lookAhead(TokenType::STRING)) {
                conditionNode->bNode = parseString();
            } else if (lookAhead(TokenType::BOOL)) {
                conditionNode->bNode = parseBool();
            }
            if(lookAhead(TokenType::PUNCTUATION) && tokens[pos+1].value == ";"){
                pos++;
                std::cout<<"Parsed conditionNode"<<std::endl;
                return conditionNode;
            }
        }
        std::cout<<"Parsed conditionNode"<<std::endl;
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
            std::cout<<"Parsed charNode"<<std::endl;
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
        std::cout<<"Parsed floatNode"<<std::endl;
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
        std::cout<<"Parsed intNode"<<std::endl;
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
        std::cout<<"Parsed boolNode"<<std::endl;
        return Boolnode;
    }
    std::cout << "parseBool returning nullptr" << std::endl;
    return nullptr;
}

std::shared_ptr<ASTNode> Parser::parseString() {
    std::cout << "Entering parseString at position " << pos << " with token: " << tokens[pos+1].value << std::endl;
    if (lookAhead(TokenType::STRING)) {
        auto stringNode = std::make_shared<StringNode>();
        stringNode->StringOfChars = tokens[++pos].value;

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
        std::cout<<"Parsed usintNode"<<std::endl;
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


        // Skips '(' and parses the declaration
        if (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value[0] == '(') {

            auto declarationNode = parseDeclaration();
            // Skips the first ';' and parses the condition
                auto conditionNode = parseCondition();
                // Skips the second ';' and parses the expression
                pos--;
                if (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value[0] == ';') {

                    auto expressionNode = parseCondition();
                    // Skip ')' and parses the body of the loop, thereafter it assigns the, declaration, condition, expression and body.
                    if (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value[0] == ')') {

                        auto bodyNode = parseLoopBody();
                        forLoopNode->declaration = std::dynamic_pointer_cast<ValueNode>(declarationNode);
                        forLoopNode->condition = std::dynamic_pointer_cast<ConditionNode>(conditionNode);
                        forLoopNode->expression = std::dynamic_pointer_cast<ConditionNode>(expressionNode);
                        forLoopNode->body = bodyNode;
                        std::cout<<"Parsed forLoopNode"<<std::endl;
                        if(lookAhead(TokenType::PUNCTUATION)&& tokens[pos+1].value == "}"){
                            pos++;
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
    if (lookAhead(TokenType::JUMP)) {
        if (tokens[pos + 1].value == "break") {
            pos++;
            auto jumpNode = std::make_shared<JumpNode>();
            jumpNode->breaker = tokens[pos].value;
            jumpNode->continuer = "null";
            std::cout<<"Parsed jumpNode"<<std::endl;
            return jumpNode;
        } else if (tokens[pos + 1].value == "continue") {
            pos++;
            auto jumpNode = std::make_shared<JumpNode>();
            jumpNode->continuer = tokens[pos].value;
            jumpNode->breaker = "null";
            std::cout<<"Parsed jumpNode"<<std::endl;
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
                std::cout<<"Parsed switchNode"<<std::endl;
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
        std::cout<<"Parsed arrayContents"<<std::endl;
        return contents;
    } else if (tokens[pos].type == TokenType::IDENTIFIER) {
        pos++;
        if (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value[0] == '[') {
            std::vector<std::shared_ptr<ASTNode>> contents;
            contents.push_back(parseDeclaration());
            while (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value[0] == ',') {
                contents.push_back(parseDeclaration());
            }
            std::cout<<"Parsed arrayContents"<<std::endl;
            return contents;
        }
        pos--;
        if (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value[0] == '(') {
            std::vector<std::shared_ptr<ASTNode>> contents;
            contents.push_back(parseFunctionCall());
            while (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value[0] == ',') {
                contents.push_back(parseFunctionCall());
            }
            std::cout<<"Parsed arrayContents"<<std::endl;
            return contents;
        }
        pos--;
        if (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value[0] == ',' || tokens[pos].value[0] == ']' && tokens[pos].type == TokenType::PUNCTUATION) {
            std::vector<std::shared_ptr<ASTNode>> contents;
            contents.push_back(parseIdentifier());
            while (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value[0] == ',') {
                contents.push_back(parseIdentifier());
            }
            std::cout<<"Parsed arrayContents"<<std::endl;
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
            pos++;
            auto conditionNode = parseCondition();
            std::cout << "finished condition " << pos << " with token: " << tokens[pos+1].value << std::endl;
            // Skip ')' and parses the body of the if statement, thereafter it assigns the condition and body.
            if (lookAhead(TokenType::PUNCTUATION) && tokens[pos+1].value[0] == ')') {
                pos+=2;
                match(TokenType::PUNCTUATION,"{");
                pos-=2;
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
                if (lookAhead(TokenType::CONTROL) && tokens[pos+1].value == "else" && tokens[pos+2].value == "if") {
                    pos++;
                    auto elseIfBodyNode = parseLoopBody();
                    ifNode->body = elseIfBodyNode;
                }
                std::cout<<"Parsed ifNode"<<std::endl;
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
    if (lookAhead(TokenType::LOOP) && tokens[pos+1].value == "while") {
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
                    auto bodyNode = parseLoopBody();

                    whileNode->condition = std::dynamic_pointer_cast<ConditionNode>(conditionNode);
                    whileNode->body = bodyNode;
                    pos++;
                    match(TokenType::PUNCTUATION,"}");
                    --pos;
                    std::cout<<"Parsed whileNode"<<std::endl;
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

        while (tokens[++pos].value != ")") {
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
        }
        std::cout<<"Parsed consoleNode"<<std::endl;
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

        if (tokens[++pos].value[0] == '?') {

            if (lookAhead(TokenType::CONST)) {

                int RandomIntRangeLowBound = std::stoi(tokens[++pos].value);

                randomNode->RandomIntRange.push_back(RandomIntRangeLowBound);

                if (tokens[++pos].value == "." && tokens[++pos].value == ".") {

                    if (lookAhead(TokenType::CONST) && std::stoi(tokens[++pos].value) > RandomIntRangeLowBound) {

                        int RandomIntRangeHighBound = std::stoi(tokens[pos].value);
                        randomNode->RandomIntRange.push_back(RandomIntRangeHighBound);

                        pos++;
                        match(TokenType::PUNCTUATION,"?");
                        pos--;
                        std::cout<<"Parsed randomNode"<<std::endl;
                        return randomNode;
                    }
                }
            }
        }
    } else if (lookAhead(TokenType::TYPE) && tokens[pos+1].value == "float?") { // Random Float

        pos += 2;
        if (tokens[++pos].value == "?") {

            if (lookAhead(TokenType::CONST)|| lookAhead(TokenType::FLOAT_CONST)) {

                float RandomFloatRangeLowBound = std::stof(tokens[++pos].value);

                randomNode->RandomFloatRange.push_back(RandomFloatRangeLowBound);
                pos++;
                if (tokens[pos].value == "." && tokens[++pos].value == ".") {

                    if (lookAhead(TokenType::CONST) && std::stof(tokens[pos+1].value) > RandomFloatRangeLowBound
                    ||lookAhead(TokenType::FLOAT_CONST) && std::stof(tokens[pos+1].value) > RandomFloatRangeLowBound) {

                        float RandomFloatRangeHighBound = std::stof(tokens[++pos].value);
                        randomNode->RandomFloatRange.push_back(RandomFloatRangeHighBound);

                        std::cout<<"Parsed randomNode"<<std::endl;
                        return randomNode;
                    }
                }
            }
        }
    } else if (lookAhead(TokenType::TYPE) && tokens[pos+1].value == "bool?") { // Random bool
        pos++;
        std::cout<<"Parsed randomNode"<<std::endl;
        return randomNode;
    }
    std::cout << "parseRandom returning nullptr" << std::endl;
    return nullptr;
}
