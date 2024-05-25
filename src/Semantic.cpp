//
// Created by nicol on 09-05-2024.
//
#include "Parser.h"
#include "Semantic.h"
#include <iostream>
#include <string>

void SymbolTable::enterScope(){
    scopes.push_back({});
}
void FunctionTable::enterScope(){
    functionMap.push_back({});
}

void SymbolTable::exitScope(){
    if(!scopes.empty())
    {
        scopes.pop_back();
    }else
    {
        throw std::runtime_error("exiting nothing????");
    }
}
void FunctionTable::declareFunction(const std::string& name,std::vector<std::string>& arguments){
    if(!functionMap.empty()){

        functionMap.back()[name] = arguments;
    }
    else{
        throw std::runtime_error("No function could be declared");
    }
}
std::vector<std::string> FunctionTable::lookUpFunction(const std::string& functionName){
    for(auto it=functionMap.rbegin();it != functionMap.rend();++it){
        if(it->find(functionName)!=it->end()){

            return it->at(functionName);
        }
    }
    throw std::runtime_error("no function has the name: " + functionName);
}

Kowalski::Kowalski() {}

void SymbolTable::declareVariable(const std::string& name,const std::string& type){
    if(!scopes.empty())
    {
        scopes.back()[name] = type;
    }else
    {
        throw std::runtime_error("no scopes for variable declaration");
    }
}
std::string SymbolTable::lookUpVariable(const std::string& name){
    for(auto it=scopes.rbegin();it != scopes.rend();++it)
        {
            if(it->find(name)!=it->end())
                {
                return it->at(name);
                }
        }
    throw std::runtime_error("variable '" + name + "' NOT declared in this scope :c");
}
void Kowalski::Analyse(const std::vector<std::shared_ptr<ASTNode>>& root){
    symbolTable.enterScope();
    functionTable.enterScope();
    //try {
    
    
    for (int i = 0; i < root.size(); i++){
            analyseNode(root[i]);
        }/*}
    catch(std::runtime_error& withoutski){
        std::cout << withoutski.what() << "Kowalski is fucked\n";
    }*/

    symbolTable.exitScope();
}

void Kowalski::analyseNode(const std::shared_ptr<ASTNode>& node){
    switch(node->getType()){
        case nodeType::functionNode:
            kowalskiFunction(std::static_pointer_cast<FunctionNode>(node));
            std::cout<<"functionNode"<<std::endl;
            break;
        case nodeType::functionCallNode:
            kowalskiFunctionCall(std::static_pointer_cast<FunctionCallNode>(node));
            std::cout<<"functionCallNode"<<std::endl;
            break;
        case nodeType::randomNode:
            kowalskiRandom(std::static_pointer_cast<RandomNode>(node));
            std::cout<<"randomNode"<<std::endl;
            break;
        case nodeType::declarationNode:
            kowalskiDeclaration(std::static_pointer_cast<DeclarationNode>(node));
            std::cout<<"declaration"<<std::endl;
            break;
        case nodeType::charNode:
            kowalskiChar(std::static_pointer_cast<CharNode>(node));
            std::cout<<"charNode"<<std::endl;
            break;
        case nodeType::ifNode:
            kowalskiIf(std::static_pointer_cast<IfNode>(node));
            std::cout<<"ifNode"<<std::endl;
            break;
        case nodeType::floatNode:
            kowalskiFloat(std::static_pointer_cast<FloatNode>(node));
            std::cout<<"floatNode"<<std::endl;
            break;
        case nodeType::stringNode:
            kowalskiString(std::static_pointer_cast<StringNode>(node));
            std::cout<<"stringNode"<<std::endl;
            break;
        case nodeType::whileNode:
            kowalskiWhile(std::static_pointer_cast<WhileNode>(node));
            std::cout<<"whileNode"<<std::endl;
            break;
        case nodeType::forLoopNode:
            kowalskiFor(std::static_pointer_cast<ForLoopNode>(node));
            std::cout<<"forNode"<<std::endl;
            break;
        case nodeType::switchNode:
            kowalskiSwitch(std::static_pointer_cast<SwitchNode>(node));
            std::cout<<"switchNode"<<std::endl;
            break;
        case nodeType::caseNode:
            kowalskiCase(std::static_pointer_cast<CaseNode>(node));
            std::cout<<"caseNode"<<std::endl;
            break;
        case nodeType::conditionNode:
            kowalskiKondi(std::static_pointer_cast<ConditionNode>(node));
            std::cout<<"conditionNode"<<std::endl;
            break;
        case nodeType::intNode:
            kowalskiInt(std::static_pointer_cast<IntNode>(node));
            std::cout<<"intNode"<<std::endl;
            break;
        case nodeType::consoleNode:
            kowalskiConsole(std::static_pointer_cast<ConsoleNode>(node));
            std::cout<<"consoleNode"<<std::endl;
            break;
        case nodeType::arrayNode:
            kowalskiArray(std::static_pointer_cast<ArrayNode>(node));
            std::cout<<"arrayNode"<<std::endl;
            break;
        case nodeType::returnNode:
            kowalskiReturn(std::static_pointer_cast<ReturnNode>(node));
            std::cout<<"returnNode"<<std::endl;
            break;
        case nodeType::valueNode:
            kowalskiValue(std::static_pointer_cast<ValueNode>(node));
            std::cout<<"valueNode"<<std::endl;
            break;
        case nodeType::boolNode:
            kowalskiBool(std::static_pointer_cast<BoolNode>(node));
            std::cout<<"boolNode"<<std::endl;
            break;
        default:

            throw std::runtime_error("unknown node type");
    }
}
// todo: make case for each node type, define each node method,
// todo: make sure the first 4 methods are using in methods going forward, approiatly :3
// it goes through all nodes, some nodes needs to do nothing but still need a case so we don't default

void Kowalski::kowalskiFunction(const std::shared_ptr<FunctionNode>& node) {
    std::string name = node->identifier;
    std::string type = node->type;
    std::vector<std::string> functionArgumentsString;

    // Register function in symbol table
    symbolTable.declareVariable(name, type);

    // Register function arguments
    for (const auto& arg : node->arguments) {
        functionArgumentsString.push_back(arg->type);
    }
    functionTable.declareFunction(name, functionArgumentsString);

    // Enter new scope for function body
    symbolTable.enterScope();

    // Process function arguments within the new scope
    for (const auto& arg : node->arguments) {
        analyseNode(arg);
    }

    // Process function body
    for (const auto& stmt : node->body) {
        analyseNode(stmt);
    }

    // Exit scope after processing the function body
    symbolTable.exitScope();
}
void Kowalski::kowalskiFunctionCall(const std::shared_ptr<FunctionCallNode>& node) {
    std::string name = node->identifier;
    std::vector<std::string> currentArgument;
    std::vector<std::string> expectedArgument;

    // Determine the types of current arguments
    for (const auto& arg : node->arguments) {
        switch (getType2(arg)) {
            case intNode:
                currentArgument.push_back("int");
                break;
            case floatNode:
                currentArgument.push_back("float");
                break;
            case usIntNode:
                currentArgument.push_back("usint");
                break;
            case stringNode:
                currentArgument.push_back("string");
                break;
            case charNode:
                currentArgument.push_back("char");
                break;
            case boolNode:
                currentArgument.push_back("bool");
                break;
            default:
                throw std::runtime_error("Unknown argument type in function call");
        }
    }

    // Look up the expected function arguments
    expectedArgument = functionTable.lookUpFunction(name);

    // Check if the number of arguments match
    if (expectedArgument.size() != currentArgument.size()) {
        std::cout << "arg 1:" << std::to_string(expectedArgument.size()) << " and arg 2:" << std::to_string(currentArgument.size()) << std::endl;
        throw std::runtime_error("too many/too few arguments for function called");
    }

    // Check if each argument type matches
    for (size_t i = 0; i < expectedArgument.size(); ++i) {
        if (expectedArgument[i] != currentArgument[i]) {
            throw std::runtime_error("Arguments do not match");
        }
    }
}
void Kowalski::kowalskiDeclaration(const std::shared_ptr<DeclarationNode>& node){
    std::string name = node->identifier;
    std::string type = node->type;
    symbolTable.declareVariable(name,type);
}
void Kowalski::kowalskiRandom(const std::shared_ptr<RandomNode>& node){
    std::string name = node->identifier;
    std::string type = node->type;
    symbolTable.declareVariable(name,type);
}


void Kowalski::kowalskiChar(const std::shared_ptr<CharNode>& node){
    //no this is not declaring but just typing on raw, nice example thou in case
    //that comment was wrong my bad I just read the error in the case above so use its case
    //okay 3rd comment about this lets redo
    
}
void Kowalski::kowalskiInt(const std::shared_ptr<IntNode>& node){
    
}
void Kowalski::kowalskiBool(const std::shared_ptr<BoolNode>& node){

}

void Kowalski::kowalskiIf(const std::shared_ptr<IfNode>& node){
        kowalskiKondi(node->condition);

        symbolTable.enterScope();
        for (int i = 0; i < node->body.size(); i++){
            analyseNode(node->body[i]);

        }
        symbolTable.exitScope();
        symbolTable.enterScope();
        for (int i = 0; i < node->elseBody.size(); i++){
            analyseNode(node->elseBody[i]);
        }
        symbolTable.exitScope();

}
void Kowalski::kowalskiFloat(const std::shared_ptr<FloatNode>& node){

}
void Kowalski::kowalskiString(const std::shared_ptr<StringNode>& node){
    
}

void Kowalski::kowalskiWhile(const std::shared_ptr<WhileNode>& node){

        kowalskiKondi(node->condition);
        symbolTable.enterScope();
        for (int i = 0; i < node->body.size(); i++){
            analyseNode(node->body[i]);
        }
        symbolTable.exitScope();
    }

void Kowalski::kowalskiFor(const std::shared_ptr<ForLoopNode>& node){
        symbolTable.enterScope();
        kowalskiDeclaration(node->declaration);
        kowalskiKondi(node->condition);
        kowalskiKondi(node->expression);
        for (int i = 0; i < node->body.size(); i++){
            
            analyseNode(node->body[i]);
        }
        symbolTable.exitScope();
    }

void Kowalski::kowalskiSwitch(const std::shared_ptr<SwitchNode>& node){
    if (node->condition->getType() != nodeType::conditionNode){
        throw std::runtime_error("Not a condition");
    }else {
        kowalskiKondi(node->condition);
        for (int i = 0; i < node->caseBranch.size(); i++){
            analyseNode(node->caseBranch[i]);
        }
        if (node->deNode != nullptr){
            analyseNode(node->deNode);
        }
    }
}
void Kowalski::kowalskiCase(const std::shared_ptr<CaseNode>& node)
{
    symbolTable.enterScope();
for (int i = 0; i < node->Branch.size(); i++){
            analyseNode(node->Branch[i]);
        }
    symbolTable.exitScope();
}

void Kowalski::kowalskiKondi(const std::shared_ptr<ConditionNode>& node){
    std::string condition = node->condition;
    nodeType aSide = getType2(node->aNode);
    if (condition == "+=" || condition == "-=" || condition == "--" || condition == "++" || condition == "="){
        if (node->aNode->getType() != nodeType::identifierNode){
            throw std::runtime_error("Trying to reassign a non identifier");
        } else if (condition == "+=" || condition == "-=" || condition == "="){
            if (node->bNode == nullptr)
                throw std::runtime_error("Trying to reassign nothing");
            if (getType2(node->aNode) == nodeType::intNode && getType2(node->bNode) != nodeType::intNode)
                throw std::runtime_error("Trying to assign a non int to an int");
            if (getType2(node->aNode) == nodeType::floatNode && getType2(node->bNode) != nodeType::intNode && getType2(node->bNode) != nodeType::floatNode)
                throw std::runtime_error("Trying to assign a non int or float to a float");
            if (getType2(node->aNode) == nodeType::charNode && getType2(node->bNode) != nodeType::charNode)
                throw std::runtime_error("Trying to assign a non char to a char");
            if (getType2(node->aNode) == nodeType::stringNode && getType2(node->bNode) != nodeType::stringNode && getType2(node->bNode) != nodeType::charNode)
                throw std::runtime_error("Trying to assign non string or char to a char");
            if (getType2(node->aNode) == nodeType::boolNode && getType2(node->bNode) != nodeType::boolNode)
                throw std::runtime_error("Trying to assign non bool to a bool");
        } else if (condition == "--" || condition == "++"){
            if (node->bNode != nullptr)
                throw std::runtime_error("Trying to assign after \"++\" or \"--\"");
            if (getType2(node->aNode) == nodeType::charNode)
                throw std::runtime_error("Trying to increment or decrement a char");
            if (getType2(node->aNode) == nodeType::stringNode)
                throw std::runtime_error("Trying to increment or decrement a string");
            if (getType2(node->aNode) == nodeType::boolNode)
                throw std::runtime_error("Trying to increment or decrement a bool");
            if (node->aNode->getType() == nodeType::functionCallNode)
                throw std::runtime_error("Trying to increment or decrement a function");
        }
    } else if (condition == "==" || condition == "!="){
        if (node->bNode == nullptr)
            throw std::runtime_error("Trying to compare nothing");
        if (getType2(node->aNode) == nodeType::intNode && getType2(node->bNode) != nodeType::intNode && getType2(node->bNode) != nodeType::floatNode)
            throw std::runtime_error("Trying to compare int to non int or non float");
        if (getType2(node->aNode) == nodeType::floatNode && getType2(node->bNode) != nodeType::intNode && getType2(node->bNode) != nodeType::floatNode)
            throw std::runtime_error("Trying to compare float to non int or non float");
        if (getType2(node->aNode) == nodeType::charNode && getType2(node->bNode) != nodeType::charNode && getType2(node->bNode) != nodeType::stringNode)
            throw std::runtime_error("Trying to compare char to non char or non string");
        if (getType2(node->aNode) == nodeType::stringNode && getType2(node->bNode) != nodeType::charNode && getType2(node->bNode) != nodeType::stringNode)
            throw std::runtime_error("Trying to compare string to non char or non string");
        if (getType2(node->aNode) == nodeType::boolNode && getType2(node->bNode) != nodeType::boolNode)
            throw std::runtime_error("Trying to compare bool to non bool");
    } else if (condition == "<=" || condition == ">=" || condition == "<" || condition == ">" || condition == "+" || condition == "-"){
        if (node->bNode == nullptr){
            if (condition == "+" || condition == "-") {throw std::runtime_error("Trying to do math on nothing");}
            else {throw std::runtime_error("Trying to compare nothing");}
        }
        if(condition == "+" || condition == "-"){
            if(node->aNode->getType() == nodeType::functionCallNode || node->bNode->getType() == nodeType::functionCallNode)
                throw std::runtime_error("Trying to +/- a function");
        }
        if (getType2(node->aNode) == nodeType::boolNode)
            throw std::runtime_error("Bools can only be compared or reassigned");
        if (getType2(node->aNode) == nodeType::charNode)
            throw std::runtime_error("chars can only be compared or reassigned");
        if (getType2(node->aNode) == nodeType::intNode && getType2(node->bNode) != nodeType::intNode){
            if(condition == "+" || "-") {throw std::runtime_error("Trying to add or subtract a non int from an int");}
            else if (getType2(node->bNode) != nodeType::floatNode) {throw std::runtime_error("Trying to do a non int or float operation on an int");}
        }
        if (getType2(node->aNode) == nodeType::floatNode && getType2(node->bNode) != nodeType::intNode && getType2(node->bNode) != nodeType::floatNode)
            throw std::runtime_error("Trying to do an operation on a float that is not followed by an int or a float");
        if (getType2(node->aNode) == nodeType::stringNode && getType2(node->bNode) != nodeType::stringNode && getType2(node->bNode) != nodeType::charNode)
            throw std::runtime_error("Trying to do an operation on a string that is not allowed");
        if (getType2(node->aNode) == nodeType::stringNode && condition != "+")
            throw std::runtime_error("Trying to do an operation on a string that is not appending");
    }
}

void Kowalski::kowalskiConsole(const std::shared_ptr<ConsoleNode>& node) {
        for (int i = 0; i < node->message.size(); i++){
            analyseNode(node->message[i]);
        }
}

void Kowalski::kowalskiStruct(const std::shared_ptr<StructNode>& node) {
    if(node->getType() != nodeType::structNode) {
        throw std::runtime_error("Not a struct");
    } else {
        for (int i = 0; i < node->body.size(); i++){
            analyseNode(node->body[i]);
        }
    }
}


void Kowalski::kowalskiArray(const std::shared_ptr<ArrayNode>& node) {
    std::string size = node->size;
    if(isalpha(size[0])){
        std::string type = symbolTable.lookUpVariable(size);
        if (type != "int") {
            throw std::runtime_error("The array size is not an integer");
        }
    }
    for (int i = 0; i < node->body.size(); i++){
        analyseNode(node->body[i]);
    }
}

void Kowalski::kowalskiReturn(const std::shared_ptr<ReturnNode>& node) {
}
void Kowalski::kowalskiValue(const std::shared_ptr<ValueNode>& node){

}

nodeType Kowalski::getType2(const std::shared_ptr<ASTNode>& node){
        if (node->getType() == nodeType::identifierNode){
            auto idNode = std::dynamic_pointer_cast<IdentifierNode>(node);
            std::string type = symbolTable.lookUpVariable(idNode->identifier);
            if (type == "int") {return nodeType::intNode;}
            else if (type == "char") {return nodeType::charNode;}
            else if (type == "string") {return nodeType::stringNode;}
            else if (type == "float") {return nodeType::floatNode;}
            else if (type == "bool") {return nodeType::boolNode;}
            else exit(1);
        }
        
        return node->getType();
}

