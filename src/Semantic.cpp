//
// Created by nicol on 09-05-2024.
//
#include "Semantic.h"
#include "Parser.h"
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
void SemanticAnalyser::kowalski(const std::shared_ptr<ASTNode>& root){
    symbolTable.enterScope();
    try {analyseNode(root);}
    catch(std::string watchoutski){
        printf("watchoutski");
    }
    //magic??
    symbolTable.exitScope();
}

void SemanticAnalyser::analyseNode(const std::shared_ptr<ASTNode>& node){
    switch(node->getType()){
        case nodeType::functionNode:
            kowalskiFunction(std::static_pointer_cast<FunctionNode>(node));
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
        case nodeType::conditionNode:
            kowalskiKondi(std::static_pointer_cast<ConditionNode>(node));
            break;
        case nodeType::intNode:
            kowalskiInt(std::static_pointer_cast<IntNode>(node));
            break;
        case nodeType::boolNode:
            kowalskiBool(std::static_pointer_cast<BoolNode>(node));    
            //todo:: make a bool, enum in node type, ASTtype-> getType()
        default:
            throw std::runtime_error("unknown node type");
    }
}
// todo: make case for each node type, define each node method,
// todo: make sure the first 4 methods are using in methods going forward, approiatly :3
// it goes through all nodes, some nodes needs to do nothing but still need a case so we don't default

void SemanticAnalyser::kowalskiFunction(const std::shared_ptr<FunctionNode>& node){

}

void SemanticAnalyser::kowalskiDeclaration(const std::shared_ptr<DeclarationNode>& node){
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
    if (node->condition->getType() != nodeType::conditionNode){
        throw std::runtime_error("Not a condition");
    }else {
        kowalskiKondi(node->condition);
        for (int i = 0; i < node->body.size(); i++){
            analyseNode(node->body);
        }
        for (int i = 0; i < node->elseBody.size(); i++){
            analyseNode(node->elseBody);
        }
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
        kowalskiKondi(node->condition);
        for (int i = 0; i < node->body.size(); i++){
            analyseNode(node->body);
        }
    }
}
void SemanticAnalyser::kowalskiFor(const std::shared_ptr<ForLoopNode>& node){
    if (node->condition->getType() != nodeType::conditionNode){
        throw std::runtime_error("Not a condition");
    }else {
        kowalskiDeclaration(node->declaration);
        kowalskiKondi(node->condition);
        kowalskiKondi(node->expression);
        for (int i = 0; i < node->body.size(); i++){
            analyseNode(node->body);
        }
    }
}
void SemanticAnalyser::kowalskiSwitch(const std::shared_ptr<SwitchNode>& node){
    if (node->condition->getType() != nodeType::switchNode){
        throw std::runtime_error("Not a condition");
    }else {
        kowalskiKondi(node->condition);
        for (int i = 0; i < node->caseBranch.size(); i++){
            analyseNode(node->caseBranch);
        }
    }
}


void SemanticAnalyser::kowalskiKondi(const std::shared_ptr<ConditionNode>& node){
    std::string condition = node->condition;
    nodeType aSide = node->aNode->getType();
    //todo:: if statement to check if both sides allow || and &&
    switch(node->bNode->getType()){
        case nodeType::floatNode:
            if(aSide != nodeType::floatNode && aSide != nodeType::intNode)
                throw std::runtime_error("Floats only accept integer and float comparaisons.");
            break;
        case nodeType::intNode:
            if(aSide != nodeType::intNode)
                throw std::runtime_error("Integers only accept integer comparaisons.");
            break;
        case nodeType::charNode:
            if(aSide != nodeType::charNode && (aSide != nodeType::stringNode && node->aNode->StringOfChars.length() == 1))
                throw std::runtime_error("Chars only accept chars and single letter string comparaisons.");
            break;
        case nodeType::stringNode:
            if(aSide != nodeType::stringNode && (aSide != nodeType::charNode && node->aNode->StringOfChars.length() == 1))
                throw std::runtime_error("Strings only accept string comparaisons and chars if the string is a single letter string.");
            break;
        
        case nodeType::conditionNode:
            if(aSide != nodeType::stringNode && aSide != nodeType::charNode && aSide != nodeType::intNode && aSide!= nodeType::floatNode){
                throw std::runtime_error("Illegal condition");
                break;
            }
            kowalskiKondi(node->bNode);
            break;
        default:
            throw std::runtime_error("Illegel condition");
            break;
    }
}

void SemanticAnalyser::kowalskiConsole(const std::shared_ptr<ConsoleNode>& node) {
    if (node->message->getType() != nodeType::consoleNode){
    }else {
        for (int i = 0; i < node->message.size(); i++){
            analyseNode(node->message[i]);
        }
    }
}

void SemanticAnalyser::kowalskiStruct(const std::shared_ptr<StructNode>& node) {
    if(node->struct_main->getType() != nodeType::structNode) {
        throw std::runtime_error("Not a struct");
    } else {
        kowalskiDeclaration(node->struct_main);
        kowalskiIdentifier(node->identifier);
        for (int i = 0; i < node->body.size(); i++){
            analyseNode(node->body[i]);
        }
    }
}

void SemanticAnalyser::kowalskiArray(const std::shared_ptr<ArrayNode>& node) {
    if(node->size->getType() != nodeType::arrayNode){
        throw std::runtime_error("Not an array");
    } else {
        std::string size = node->size;
        for (int i = 0; i < node->body.size(); i++){
            analyseNode(node->body[i]);
        }
    }
}

void SemanticAnalyser::kowalskiReturn(const std::shared_ptr<ReturnNode>& node) {
    if(node->returning->getType() != nodeType::returnNode) {
        throw std::runtime_error("Not a return");
    } else {
        std::string returning = node->returning;
        kowalskiIdentifier(node->identifier);
    }
}