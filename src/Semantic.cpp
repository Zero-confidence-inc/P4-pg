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
void SemanticAnalyser::kowalski(const std::vector<std::shared_ptr<ASTNode>>& root){
    symbolTable.enterScope();
    try {
    
    
    for (int i = 0; i < root.size(); i++){
            analyseNode(root[i]);
        }}
    catch(std::runtime_error& withoutski){
        std::cout << withoutski.what() << "Kowalski is fucked\n";
    }
    //magic??
    symbolTable.exitScope();
}

void SemanticAnalyser::analyseNode(const std::shared_ptr<ASTNode>& node){
    switch(getType2(node)){
        case nodeType::functionNode:
            kowalskiFunction(std::static_pointer_cast<FunctionNode>(node));
            break;
        case nodeType::functionCallNode:
            kowalskiFunctionCall(std::static_pointer_cast<FunctionCallNode>(node));
            break;
        case nodeType::randomNode:
            kowalskiRandom(std::static_pointer_cast<RandomNode>(node));
            break;
        case nodeType::declarationNode:
            kowalskiDeclaration(std::static_pointer_cast<DeclarationNode>(node));
            break;
        case nodeType::charNode:
            kowalskiChar(std::static_pointer_cast<CharNode>(node));
            break;
        case nodeType::ifNode:
            kowalskiIf(std::static_pointer_cast<IfNode>(node));
            break;
        case nodeType::floatNode:
            kowalskiFloat(std::static_pointer_cast<FloatNode>(node));
            break;
        case nodeType::stringNode:
            kowalskiString(std::static_pointer_cast<StringNode>(node));
            break;
        case nodeType::whileNode:
            kowalskiWhile(std::static_pointer_cast<WhileNode>(node));
            break;
        case nodeType::forLoopNode:
            kowalskiFor(std::static_pointer_cast<ForLoopNode>(node));
            break;
        case nodeType::switchNode:
            kowalskiSwitch(std::static_pointer_cast<SwitchNode>(node));
            break;
        case nodeType::caseNode:
            kowalskiCase(std::static_pointer_cast<CaseNode>(node));
            break;
        case nodeType::conditionNode:
            kowalskiKondi(std::static_pointer_cast<ConditionNode>(node));
            break;
        case nodeType::intNode:
            kowalskiInt(std::static_pointer_cast<IntNode>(node));
            break;
        case nodeType::boolNode:
            kowalskiBool(std::static_pointer_cast<BoolNode>(node));    
        default:
            throw std::runtime_error("unknown node type");
    }
}
// todo: make case for each node type, define each node method,
// todo: make sure the first 4 methods are using in methods going forward, approiatly :3
// it goes through all nodes, some nodes needs to do nothing but still need a case so we don't default

void SemanticAnalyser::kowalskiFunction(const std::shared_ptr<FunctionNode>& node){
    std::string name = node->identifier;
    std::string type = node->type;
    std::vector<std::string> functionArgumentsString;
    std::string tempType;
    symbolTable.declareVariable(name,type);
    for (int i = 0; i < node->arguments.size();i++){
        switch (node->arguments[i]->getType())
        {
        case intNode:
            functionArgumentsString.push_back("int");
            break;
        case floatNode:
            functionArgumentsString.push_back("float");
            break;
        case usIntNode:
            functionArgumentsString.push_back("usint");
            break;
        case stringNode:
            functionArgumentsString.push_back("string");
            break;
        case charNode:
            functionArgumentsString.push_back("char");
            break;
        case boolNode:
            functionArgumentsString.push_back("bool");
            break;
        default:
            break;
        };
    }
    functionTable.declareFunction(name,functionArgumentsString);
    symbolTable.enterScope();
    // checks args
    for (int i = 0; i < node->arguments.size();i++){
        analyseNode(node->arguments[i]);
    }
    
    //function body
    for (int i = 0; i <node->body.size();i++){
        analyseNode(node->body[i]);
    }
}
void SemanticAnalyser::kowalskiFunctionCall(const std::shared_ptr<FunctionCallNode> &node){
    std::string name = node->identifier;
    std::vector<std::string> currentArgument;
    std::vector<std::string> exprectedArgument;
    for (int i = 0; i < node->arguments.size();i++){
        switch (getType2(node->arguments[i])){
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
            break;
        }
    }
    exprectedArgument = functionTable.lookUpFunction(node->identifier);
    if(exprectedArgument.size() == currentArgument.size()){
        for (int i = 0; i < node->arguments.size();i++){
            if (exprectedArgument[i]!=currentArgument[i]){
                throw std::runtime_error("Arguments do not match");
            }
        }
    }
    else{
        throw std::runtime_error("too many/too few arguemnts for function called");
    }
}
void SemanticAnalyser::kowalskiDeclaration(const std::shared_ptr<DeclarationNode>& node){
    std::string name = node->identifier;
    std::string type = node->type;
    symbolTable.declareVariable(name,type);
}
void SemanticAnalyser::kowalskiRandom(const std::shared_ptr<RandomNode>& node){
    std::string name = node->identifier;
    std::string type = node->type;
    symbolTable.declareVariable(name,type);
}


void SemanticAnalyser::kowalskiChar(const std::shared_ptr<CharNode>& node){
    //no this is not declaring but just typing on raw, nice example thou in case
    //that comment was wrong my bad I just read the error in the case above so use its case
    //okay 3rd comment about this lets redo
    
}
void SemanticAnalyser::kowalskiInt(const std::shared_ptr<IntNode>& node){
    
}
void SemanticAnalyser::kowalskiIf(const std::shared_ptr<IfNode>& node){
    if (getType2(node->condition) != nodeType::conditionNode){
        throw std::runtime_error("Not a condition");
    }else {
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
}
void SemanticAnalyser::kowalskiFloat(const std::shared_ptr<FloatNode>& node){
    
}
void SemanticAnalyser::kowalskiString(const std::shared_ptr<StringNode>& node){
    
}

void SemanticAnalyser::kowalskiWhile(const std::shared_ptr<WhileNode>& node){
    if (node->condition->getType() != nodeType::whileNode){
        throw std::runtime_error("Not a condition");
    }else {
        symbolTable.enterScope();
        kowalskiKondi(node->condition);
        for (int i = 0; i < node->body.size(); i++){
            analyseNode(node->body[i]);
        }
        symbolTable.exitScope();
    }
}
void SemanticAnalyser::kowalskiFor(const std::shared_ptr<ForLoopNode>& node){
    if (node->condition->getType() != nodeType::conditionNode){
        throw std::runtime_error("Not a condition");
    }else {
        symbolTable.enterScope();
        kowalskiDeclaration(node->declaration);
        kowalskiKondi(node->condition);
        kowalskiKondi(node->expression);
        for (int i = 0; i < node->body.size(); i++){
            
            analyseNode(node->body[i]);
        }
        symbolTable.exitScope();
    }
}
void SemanticAnalyser::kowalskiSwitch(const std::shared_ptr<SwitchNode>& node){
    if (node->condition->getType() != nodeType::switchNode){
        throw std::runtime_error("Not a condition");
    }else {
        
        kowalskiKondi(node->condition);
        for (int i = 0; i < node->caseBranch.size(); i++){
            analyseNode(node->caseBranch[i]);
        }
    }
}
void SemanticAnalyser::kowalskiCase(const std::shared_ptr<CaseNode>& node)
{
    symbolTable.enterScope();
for (int i = 0; i < node->Branch.size(); i++){
            analyseNode(node->Branch[i]);
        }
    symbolTable.exitScope();
}


void SemanticAnalyser::kowalskiKondi(const std::shared_ptr<ConditionNode>& node){
    std::string condition = node->condition;
    nodeType aSide = getType2(node->aNode);
    //todo:: if statement to check if both sides allow || and &&
    if (getType2(node->bNode) == nodeType::floatNode){
        if(aSide != nodeType::floatNode && aSide != nodeType::intNode)
            throw std::runtime_error("Floats only accept integer and float comparaisons.");
    } else if (getType2(node->bNode) == nodeType::intNode){
        if(aSide != nodeType::intNode)
            throw std::runtime_error("Integers only accept integer comparaisons.");  
    } else if (getType2(node->bNode) == nodeType::charNode){
        auto convertedNode = std::dynamic_pointer_cast<StringNode>(node->bNode);
        if(aSide != nodeType::charNode && (aSide != nodeType::stringNode && convertedNode->StringOfChars.length() == 1))
            throw std::runtime_error("Chars only accept chars and single letter string comparaisons.");
    } else if (getType2(node->bNode) == nodeType::stringNode){
        auto convertedNode = std::dynamic_pointer_cast<StringNode>(node->bNode);
        if(aSide != nodeType::stringNode && (aSide != nodeType::charNode && convertedNode->StringOfChars.length() == 1))
            throw std::runtime_error("Strings only accept string comparaisons and chars if the string is a single letter string.");
    } else if (getType2(node->bNode) == nodeType::conditionNode){
        if(aSide != nodeType::stringNode && aSide != nodeType::charNode && aSide != nodeType::intNode && aSide!= nodeType::floatNode)
            throw std::runtime_error("Illegal condition");
        auto convertedNode = std::dynamic_pointer_cast<ConditionNode>(node->bNode);
        kowalskiKondi(convertedNode);
    } else if (node->bNode == nullptr){
        if (node->condition == "=" || "==" || "<" || ">" || "<=" || ">=" || "+=" || "-=" || "!=" || "+" || "-"){
            throw std::runtime_error("No comparison to be made");
        }
    }
}

void SemanticAnalyser::kowalskiConsole(const std::shared_ptr<ConsoleNode>& node) {
        for (int i = 0; i < node->message.size(); i++){
            analyseNode(node->message[i]);
        }
}

void SemanticAnalyser::kowalskiStruct(const std::shared_ptr<StructNode>& node) {
    if(node->struct_main->getType() != nodeType::structNode) {
        throw std::runtime_error("Not a struct");
    } else {
        for (int i = 0; i < node->body.size(); i++){
            analyseNode(node->body[i]);
        }
    }
}

void SemanticAnalyser::kowalskiArray(const std::shared_ptr<ArrayNode>& node) {
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

void SemanticAnalyser::kowalskiReturn(const std::shared_ptr<ReturnNode>& node) {
}

nodeType SemanticAnalyser::getType2(const std::shared_ptr<ASTNode>& node){
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