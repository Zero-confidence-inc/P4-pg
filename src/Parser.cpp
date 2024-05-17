//
// Created by Yuki on 29/04/2024.
//
#include "Parser.h"

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

void Parser::parseProgram() {
    std::vector<std::shared_ptr<ASTNode>> ast;
    while (pos < tokens.size()) {
        if (lookAhead(TokenType::TYPE) && tokens[++pos].value == "int?" || tokens[pos].value=="float?" || tokens[pos].value=="bool?"){
            auto random_pp = parseRandom();
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
    if (lookAhead(TokenType::TYPE)){
        std::string type = tokens[++pos].value;
        std::string identifier = tokens[++pos].value;
        if (lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value == "{"){
            auto functionNode = std::make_shared<FunctionNode>();
            functionNode->type = type;
            functionNode->identifier = identifier;
            functionNode->body = parseFunctionBody();
            match(TokenType::PUNCTUATION, "{");
            match(TokenType::PUNCTUATION, "}");
            return functionNode;
        }
        else if (lookAhead(TokenType::OPERATOR) && tokens[++pos].value == "="){
            auto valueNode = std::make_shared<ValueNode>();
            valueNode->type = type;
            valueNode->identifier = identifier;
            valueNode->value = parseValues();
            match(TokenType::PUNCTUATION, ";");
            return valueNode;
        }
        else if (lookAhead(TokenType::TYPE) && tokens[++pos].value == "struct"){
            auto structNode = std::make_shared<StructNode>();
            structNode->type = type;
            structNode->identifier = identifier;
            structNode->struct_main = parseStruct();
            return structNode;
        }
        else if(lookAhead(TokenType::PUNCTUATION) && tokens[++pos].value == "["){
            auto arrayNode = std::make_shared<ArrayNode>();
        }
    }
    return nullptr; // Return nullptr if no valid declaration is found
};


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

std::shared_ptr<ASTNode> Parser::parseValues(){
    if (tokens[2-pos].value == "int"){
        auto valueInt = std::make_shared<IntNode>();
        valueInt->integer = tokens[pos].value[0];
        return valueInt;
    }
    else if (tokens[2-pos].value == "usint"){
        auto valueUsint = std::make_shared<UsIntNode>();
        valueUsint->usinteger = tokens[pos].value[0];
        return valueUsint;
    }
    else if (tokens[2-pos].value == "float"){
        auto valueFloat = std::make_shared<FloatNode>();
        valueFloat->Floating_Point = tokens[pos].value[0];
        return valueFloat;
    }
    else if (tokens[2-pos].value == "char"){
        auto valueChar = std::make_shared<CharNode>();
        valueChar->character = tokens[pos].value[0];
        return valueChar;
    }
    else if (tokens[2-pos].value == "string"){
        auto valueString = std::make_shared<StringNode>();
        valueString->StringOfChars = tokens[pos].value[0];
        return valueString;
    }
    else if (tokens[2-pos].value == "bool"){
        auto valueBool = std::make_shared<BoolNode>();
        valueBool->boolean = tokens[pos].value[0];
        return valueBool;
    }
    else return nullptr;
}

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
    if (lookAhead(TokenType::TYPE) && tokens[pos].value == "struct"){
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

std::shared_ptr<ASTNode> Parser::parseIdentifier() {
    std::string identifier = tokens[++pos].value;
    if(lookAhead(TokenType::IDENTIFIER)) {
        auto identifierNode = std::make_shared<IdentifierNode>();
        identifierNode->identifier = identifier;
    }
}

std::shared_ptr<ASTNode> Parser::parseCondition() {
    if (tokens[pos].type == TokenType::CONST || tokens[pos].type == TokenType::FLOAT_CONST || tokens[pos].type == TokenType::STRING){
        auto conditionNode = std::make_shared<ConditionNode>();
        switch(tokens[pos].type) {
            case TokenType::CONST:
                conditionNode->aNode = std::make_shared<IntNode>();
                break;
            case TokenType::FLOAT_CONST:
                conditionNode->aNode = std::make_shared<FloatNode>();
                break;
            case TokenType::STRING:
                conditionNode->aNode = std::make_shared<StringNode>();
                break;
            case TokenType::IDENTIFIER:
                auto aNode = std::make_shared<ValueNode>();
                aNode->identifier = tokens[pos].value;
                conditionNode->aNode = aNode;
        }
        pos++;
        if(tokens[pos].type == TokenType::OPERATOR){
            conditionNode->condition = tokens[pos].value;
            pos++;
        } else {
            return conditionNode;
        }
        if(lookAhead(TokenType::OPERATOR)){
            conditionNode->bNode = parseCondition();
        } else {
            switch(tokens[pos].type) {
            case TokenType::CONST:
                conditionNode->bNode = std::make_shared<IntNode>();
                break;
            case TokenType::FLOAT_CONST:
                conditionNode->bNode = std::make_shared<FloatNode>();
                break;
            case TokenType::STRING:
                conditionNode->bNode = std::make_shared<StringNode>();
                break;
            case TokenType::IDENTIFIER:
                auto bNode = std::make_shared<ValueNode>();
                bNode-identifier = tokens[pos].value;
                conditionNode->bNode->identifier = tokens[pos].value;
            }
        }
        return conditionNode;
    }
    return nullptr;
}

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

std::shared_ptr<ASTNode> Parser::parseBool(){
    if (lookAhead(TokenType::BOOL)){
        auto Boolnode = std::make_shared<BoolNode>();
        if (tokens[pos].value == "true"){
            Boolnode->boolean = true;
        } else if (tokens[pos].value == "false"){
            Boolnode->boolean = false;
        }
        return Boolnode;
    }
    return nullptr;
};
/*
std::shared_ptr<ASTNode> Parser::parseComment(){
    if (lookAhead(TokenType::COMMENTS)){
        auto Commentnode = std::make_shared<CommentNode>();
        Commentnode->Comment=tokens[pos].value;
        return Commentnode;
    };
    return nullptr;
}; */

std::shared_ptr<ASTNode> Parser::parseString(){
    if (lookAhead(TokenType::STRING)){
        auto stringNode = std::make_shared<StringNode>();
        stringNode->StringOfChars=tokens[pos].value;
        return stringNode;
    }
    return nullptr;
};

std::shared_ptr<ASTNode> Parser::parseUsInt(){
    if (lookAhead(TokenType::CONST)){
        auto usIntNode = std::make_shared<UsIntNode>();
        usIntNode->usinteger=std::stoi(tokens[pos].value);
        return usIntNode;
    }
}


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

std::shared_ptr<ASTNode> Parser::parseJump(){
    if (lookAhead(TokenType::JUMP) && tokens[++pos].value == "break"){
        auto breakNode = std::make_shared<JumpNode>();
        breakNode->breaker = tokens[pos].value;
        breakNode->continuer = "null";
        pos--;
        return breakNode;
    }
    else if (lookAhead(TokenType::JUMP) && tokens[++pos].value == "continue"){
        auto continueNode = std::make_shared<JumpNode>();
        continueNode->continuer = tokens[pos].value;
        continueNode->breaker = "null";
        pos--;
        return continueNode;
    }
    else{
        return nullptr;
    }
}


std::shared_ptr<ASTNode> Parser::parseSwitch() {
    if (lookAhead(TokenType::CONTROL) && tokens[++pos].value == "switch"){
        pos++;
        auto swNode = std::make_shared<SwitchNode>();
        swNode->condition = parseCondition();

        while (lookAhead(TokenType::CONTROL) && tokens[++pos].value == "case"){
            auto cNode = std::make_shared<CaseNode>();
            cNode->sucessCondition = parseCondition();
            pos++;
            cNode->Branch.push_back(parseDeclaration());

            swNode->caseBranch.push_back(cNode);
        }

        return swNode;
    }
    return nullptr;
};

std::shared_ptr<ASTNode> Parser::parseArray() {
    if (lookAhead(TokenType::TYPE)) {
        auto type = tokens[pos].value;

        if (lookAhead(TokenType::IDENTIFIER)) {
            auto identifier = tokens[pos].value;

            if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value == "[") {
                pos++;

                // Parse int, float, identifier, char, string, bool, function
                if (lookAhead(TokenType::CONST) || (lookAhead(TokenType::FLOAT_CONST)) || (lookAhead(TokenType::IDENTIFIER)) ||
                    (lookAhead(TokenType::TYPE)) || (lookAhead(TokenType::CONTROL)))  {

                    auto arraySize = std::stoi(tokens[pos].value);

                    if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value == "]") {
                        pos++;

                        // Ensure semicolon at the end
                        if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value == ";") {
                            pos++;

                            auto arrayNode = std::make_shared<ArrayNode>();
                            arrayNode->type = type;
                            arrayNode->identifier = identifier;
                            arrayNode->size = arraySize;

                            return arrayNode;
                        }
                    }
                }
            }
        }
    }

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
                if (lookAhead(TokenType::CONTROL) && tokens[pos].value == "else" && tokens[++pos].value == "if") {
                    pos++;
                    auto elseIfBodyNode = parseLoopBody();
                    ifNode->body = elseIfBodyNode;
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
        auto whileNode = std::make_shared<WhileNode>();
        pos++;
        //skips '(' and parses the condition
        if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value[0] == '(') {
            pos++;
            auto conditionNode = parseCondition();
            //skip ')' and parses the body of the if statement, thereafter it assigns the condition and body.
            if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value[0] == ')') {
                pos++;
                auto bodyNode = parseLoopBody();
                whileNode->condition = conditionNode;
                whileNode->body = bodyNode;
                return whileNode;
            }
        }
    }
    return nullptr;
};

std::shared_ptr<ASTNode> Parser::parseConsole(){
    if(lookAhead(TokenType::PUNCTUATION) && tokens[pos].getType() == TokenType::CONSOLE){
        auto consoleNode = std::make_shared<ConsoleNode>();
        pos++;
        while(tokens[pos].value != ")"){
            if (lookAhead(TokenType::CONST)){
                consoleNode->message.push_back(parseInt());
            } else if (lookAhead(TokenType::FLOAT_CONST)){
                consoleNode->message.push_back(parseFloat());
            } else if (lookAhead(TokenType::STRING)){
                consoleNode->message.push_back(parseString());
            } else if (lookAhead(TokenType::IDENTIFIER)){
                consoleNode->message.push_back(parseIdentifier());
            }
            pos++;
        }
        return consoleNode;
    }
    return nullptr;
}


//Rewrite logic to fit parser.h
std::shared_ptr<ASTNode> Parser::parseRandom(){
    auto randomNode = std::make_shared<RandomNode>();
    std::string type = tokens[++pos].value;
    std::string identifier = tokens[++pos].value;
    randomNode->type = type;
    randomNode->identifier = identifier;
    if (lookAhead(TokenType::TYPE) && tokens[pos].value=="int?"){ //Random Int
        auto randomIntNode = std::make_shared<randomNode>();
        pos++;
        if (lookAhead(TokenType::CONST)){
            int RandomIntRangeLowBound = tokens[pos].value[0];
            randomNode->RandomIntRange.push_back(RandomIntRangeLowBound);
            pos++;
            if (tokens[pos].value==".."){
                pos++;
                if (lookAhead(TokenType::CONST) && tokens[pos].value[0]>RandomIntRangeLowBound){
                    int RandomIntRangeHighBound = tokens[pos].value[0];
                    randomNode->RandomIntRange.push_back(RandomIntRangeHighBound);
                    pos--;
                    pos--;
                    pos--;
                    return randomNode;
                }
            }
        }
    }
    else if(lookAhead(TokenType::TYPE) && tokens[pos].value=="float?"){ //Random Float
        pos++;
        if (lookAhead(TokenType::CONST)){
            float RandomFloatRangeLowBound = tokens[pos].value[0];
            randomNode->RandomFloatRange.push_back(RandomFloatRangeLowBound);
            pos++;
            if (tokens[pos].value==".."){
                pos++;
                if (lookAhead(TokenType::CONST) && tokens[pos].value[0]>RandomFloatRangeLowBound){
                    float RandomFLoatRangeHighBound = tokens[pos].value[0];
                    randomNode->RandomFloatRange.push_back(RandomFLoatRangeHighBound);
                    pos--;
                    pos--;
                    pos--;
                    return randomNode;
                }
            }
        }
    }
    else if(lookAhead(TokenType::TYPE) && tokens[pos].value=="bool?"){//Random bool
        return randomNode;
    }
    else return nullptr;
};
