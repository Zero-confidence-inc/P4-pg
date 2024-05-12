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
                    return nullptr; //Missing semicolon
                }
            } else {
                return nullptr; //Missing or empty string
            }
        } else {
            return nullptr; //Missing operator '='
        }
    }
    return nullptr;
}

};

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

std::shared_ptr<ASTnode> Parser::parseIf()
{
//the irony of using if in if,
if (lookAhead(TokenType::CONTROL) {
    bool result = false;




    if(tokens[pos].value == "if")
    {
        auto conditionNode = std::make_shared<IfStatementNode>();
        match(TokenType::PUNCTUATION, "(");
        conditionNode->condition = tokens[pos].value;
        match(TokenType::PUNCTUATION, ")");
        match(TokenType::PUNCTUATION, "{");
        conditionNode->trueBranch = tokens[pos].value;
        match(TokenType::PUNCTUATION, "}");
        return conditionNode;
    }
    else if(tokens[pos].value == "else if")
    {
        auto conditionNode = std::make_shared<IfStatementNode>();
        match(TokenType::PUNCTUATION, "(");
        conditionNode->condition = tokens[pos].value;
        match(TokenType::PUNCTUATION, ")");
        match(TokenType::PUNCTUATION, "{");
        conditionNode->trueBranch = tokens[pos].value;
        match(TokenType::PUNCTUATION, "}");
        return conditionNode;

    }
    else if(tokens[pos].value == "else")
    {
        auto conditionNode = std::make_shared<IfStatementNode>();
        match(TokenType::PUNCTUATION, "(");
        conditionNode->condition = tokens[pos].value;
        match(TokenType::PUNCTUATION, ")");
        match(TokenType::PUNCTUATION, "{");
        conditionNode->falseBranch = tokens[pos].value;
        match(TokenType::PUNCTUATION, "}");
        return conditionNode;
    }
    return nullptr;
}

}

