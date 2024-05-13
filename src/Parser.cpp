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

std::vector<std::shared_ptr<ASTNode>> Parser::parseLoopBody() {
    std::vector<std::shared_ptr<ASTNode>> contents;
    if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value[0] == '{') {
        pos++;
        while (tokens[pos].value[0] != '}') {
            auto contentsNode = parseDeclaration();
            contents.push_back(contentsNode);
        }
    } else {
        return {};
    }
    return contents;
}


std::shared_ptr<ASTNode> Parser::parseCondition() {
    if (lookAhead(TokenType::OPERATOR)){
        if (tokens[pos].value == "==" || tokens[pos].value == "!=" || tokens[pos].value == "<" 
        || tokens[pos].value == ">" || tokens[pos].value == "<=" || tokens[pos].value == ">=") {
            auto conditionNode = std::make_shared<ConditionNode>();
            conditionNode->condition = tokens[pos].value;
            return conditionNode;
        }
        return nullptr;
    }
    return nullptr;
}

std::shared_ptr<ASTNode> Parser::parseMath() {
    // Dummy implementation for now
    return {};

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
                } else {
                    return nullptr; //Missing ';'
                }
            } else {
                return nullptr; //Missing or empty string
            }
        } else {
            return nullptr; //Missing operator '='
        }
    }
    return nullptr; //Missing "char"
}


std::shared_ptr<ASTNode> Parser::parseFloat(){
    if (lookAhead(TokenType::FLOAT_CONST)){
        auto FloatingNode = std::make_shared<FloatNode>();
        FloatingNode->Floating_Point = std::stof(tokens[pos].value);
        return FloatingNode;
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
                    auto expressionNode = parseMath();
                    //skip ')' and parses the body of the loop, thereafter it assigns the, declaration, condition, expression and body.
                    if (lookAhead(TokenType::PUNCTUATION) && tokens[pos].value[0] == ')') {
                        pos++;
                        auto bodyNode = parseLoopBody();
                        forLoopNode->declaration = declarationNode;
                        forLoopNode->condition = conditionNode;
                        forLoopNode->expression = expressionNode;
                        forLoopNode->body = bodyNode;
                        return forLoopNode;
                    } else {
                        return nullptr; //Missing ')'
                    }
                } else {
                    return nullptr; //Missing ';'
                }
            } else {
                return nullptr; //Missing ';'
            }
        } else {
            return nullptr; //Missing '('
        }
    } else {
        return nullptr; //Missing "for"
    }
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
        swNode->condition = parseCondition();

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
