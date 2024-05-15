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
};


bool Parser::lookAhead(TokenType expectedType) {
    return pos < tokens.size() && tokens[pos].type == expectedType;
};

void Parser::match(TokenType expectedType) {
    if (pos < tokens.size() && tokens[pos].type == expectedType) {
        pos++;
    } else {
        std::cerr << "Syntax error, expected type " << static_cast<int>(expectedType) << std::endl;
        exit(1);
    }
};

void Parser::match(TokenType expectedType, const std::string& expectedValue) {
    if (pos < tokens.size() && tokens[pos].type == expectedType && tokens[pos].value == expectedValue) {
        pos++;
    } else {
        std::cerr << "Syntax error, expected " << expectedValue << " of type " << static_cast<int>(expectedType) << std::endl;
        exit(1);
    }
};

std::vector<std::shared_ptr<ASTNode>> Parser::parseFunctionBody() {
    std::vector<std::shared_ptr<ASTNode>> contents;
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
        if (lookAhead(TokenType::JUMP) && tokens[pos].value == "return") {
            auto returns = parseReturn();
        }
    } else {
        return {};
    }
    return contents;
};

std::shared_ptr<ASTNode> Parser::parseReturn(){
    if (lookAhead(TokenType::JUMP)){
        auto returnNode = std::make_shared<ReturnNode>();
        returnNode->returning = tokens[pos].value;
        returnNode->identifier = tokens[pos].value;
        return returnNode;
    }
    return nullptr;
};



std::vector<std::shared_ptr<ASTNode>> Parser::parseStructBody() {
    std::vector<std::shared_ptr<ASTNode>> contents;
    if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value[0] == '{') {
        pos++;
        while (tokens[pos].value[0] != '}') {
            auto declaration = parseDeclaration();
            auto array = parseArray();
            auto string = parseString();
            contents.push_back(declaration);
            contents.push_back(array);
            contents.push_back(string);
        }
    } else {
        return {};
    }
    return contents;
};


std::vector<std::shared_ptr<ASTNode>> Parser::parseLoopBody() {
    std::vector<std::shared_ptr<ASTNode>> contents;
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
};


std::shared_ptr<ASTNode> Parser::parseStruct() {
    if (lookAhead(TokenType::CONTROL) && tokens[pos].value == "struct"){
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
};

std::shared_ptr<ASTNode> Parser::parseCondition() {
    if (lookAhead(TokenType::OPERATOR)){
        if (tokens[pos].value == "==" || tokens[pos].value == "!=" || tokens[pos].value == "<" 
        || tokens[pos].value == ">" || tokens[pos].value == "<=" || tokens[pos].value == ">=") {
            auto conditionNode = std::make_shared<ConditionNode>();
            conditionNode->condition = tokens[pos].value;
            return conditionNode;
        }
    }
    return nullptr;
};

//Parses the char type
std::shared_ptr<ASTNode> Parser::parseChar() {
    //Checks if the type given is actually a char, and creates a char node
    if (lookAhead(TokenType::TYPE) && tokens[pos].value == "char") {
        auto charNode = std::make_shared<CharNode>();
        pos++;
        //Skips the '=' operator, and return nullptr if the operator used isn't '='
        if(lookAhead(TokenType::OPERATOR) && tokens[pos].value[0] == '=') {
            pos++;
            //Assigns the first character of the following string as our char
            if(lookAhead(TokenType::STRING) && tokens[pos].value.size() > 0) {
                charNode->character = tokens[pos].value[0];
                pos++;
                //We only only accept this as a proper char if the following character is a ';', since that would mean the declaration has finished properly
                if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value[0] == ';') {
                    return charNode;
                }
            }
        }
    }
    return nullptr;
};


std::shared_ptr<ASTNode> Parser::parseFloat(){
    if (lookAhead(TokenType::FLOAT_CONST)){
        auto FloatingNode = std::make_shared<FloatNode>();
        FloatingNode->Floating_Point = std::stof(tokens[pos].value);
        return FloatingNode;
    }
    return nullptr;
};

std::shared_ptr<ASTNode> Parser::parseInt(){
    if (lookAhead(TokenType::CONST)){
        auto intNode = std::make_shared<IntNode>();
        intNode->integer = std::stoi(tokens[pos].value);
        return intNode;
    }
    return nullptr;
};

std::shared_ptr<ASTNode> Parser::parseComment(){
    if (lookAhead(TokenType::COMMENTS)){
        auto Commentnode = std::make_shared<CommentNode>();
        Commentnode->Comment=tokens[pos].value;
        return Commentnode;
    };
    return nullptr;
};

std::shared_ptr<ASTNode> Parser::parseString(){
    if (lookAhead(TokenType::STRING)){
        auto Stringnode = std::make_shared<StringNode>();
        Stringnode->StringOfChars=tokens[pos].value;
        return Stringnode;
    }
    return nullptr;
};


//Parses a for loop
std::shared_ptr<ASTNode> Parser::parseForLoop() {
    //Check to see if the loop token "for" is given
    if (lookAhead(TokenType::LOOP) && tokens[pos].value == "for") {
        auto forLoopNode = std::make_shared<ForLoopNode>();
        pos++;
        //skips '(' and parses the declaration
        if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value[0] == '(') {
            pos++;
            auto declarationNode = parseDeclaration();
            //skips the first ';' and parses the condition
            if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value[0] == ';') {
                pos++;
                auto conditionNode = parseCondition();
                //skips the second ';' and parses the expression
                if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value[0] == ';') {
                    pos++;
                    auto expressionNode = parseCondition();
                    //skip ')' and parses the body of the loop, thereafter it assigns the, declaration, condition, expression and body.
                    if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value[0] == ')') {
                        pos++;
                        auto bodyNode = parseLoopBody();
                        forLoopNode->declaration = declarationNode;
                        forLoopNode->condition = conditionNode;
                        forLoopNode->expression = expressionNode;
                        forLoopNode->body = bodyNode;
                        return forLoopNode;
                    }
                }
            }
        }
    }
    return nullptr;
};

//Operators 
std::shared_ptr<ASTNode> Parser::parseOperator() {
    if(lookAhead(TokenType::OPERATOR)){
        auto opeNode = std::make_shared<OperatorNode>();
        opeNode->operatorType = tokens[pos].value;
        return opeNode;
    }
    return nullptr;
};

std::shared_ptr<ASTNode> Parser::parseSwitch() {
    if(lookAhead(TokenType::CONTROL) && tokens[pos].value == "switch"){
        pos++;
        auto swNode = std::make_shared<SwitchNode>();
        swNode->condition = parseCondition();

        while (lookAhead(TokenType::CONTROL) && tokens[pos].value == "case"){
            auto cNode = std::make_shared<caseNode>();
            cNode->sucessCondition = parseCondition();
            pos++;
            cNode->Branch = parseCondition();

            swNode->caseBranch.push_back(cNode);
        }

        return swNode;
    }
    return nullptr;
};

std::shared_ptr<ASTNode> Parser::parseArray(){
    //placeholder for now
    return nullptr;
};

std::shared_ptr<ASTNode> Parser::parseIfStatement(){
    //Check to see if the loop token "if" is given
    if (lookAhead(TokenType::CONTROL) && tokens[pos].value == "if") {
        auto ifNode = std::make_shared<IfNode>();
        pos++;
        //skips '(' and parses the condition
        if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value[0] == '(') {
            pos++;
            auto conditionNode = parseCondition();
            //skip ')' and parses the body of the if statement, thereafter it assigns the condition and body.
            if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value[0] == ')') {
                pos++;
                auto bodyNode = parseLoopBody();
                ifNode->condition = conditionNode;
                ifNode->body = bodyNode;
                if (lookAhead(TokenType::CONTROL) && tokens[pos].value == "else") {
                    pos++;
                    auto elseBodyNode = parseLoopBody();
                    ifNode->elseBody = elseBodyNode;
                }
                return ifNode;
            }
        }
    }
    return nullptr;
};

std::shared_ptr<ASTNode> Parser::parseWhileLoop(){
    //Check to see if the loop token "while" is given
    if (lookAhead(TokenType::CONTROL) && tokens[pos].value == "while") {
        auto ifNode = std::make_shared<IfNode>();
        pos++;
        //skips '(' and parses the condition
        if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value[0] == '(') {
            pos++;
            auto conditionNode = parseCondition();
            //skip ')' and parses the body of the if statement, thereafter it assigns the condition and body.
            if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value[0] == ')') {
                pos++;
                auto bodyNode = parseLoopBody();
                ifNode->condition = conditionNode;
                ifNode->body = bodyNode;
                return ifNode;
            }
        }
    }
    return nullptr;
};
