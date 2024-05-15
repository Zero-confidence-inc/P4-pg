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
void SymbolTable::declareVariable(const std::string& name,const std::string& type)
{
    if(!scopes.empty())
    {
        scopes.back()[name] = type;
    }else
    {
        throw std::runtime_error("no scopes for variable declaration");
    }
}
std::string SymbolTable::lookUpVariable(const std::string& name);
{
    for(auto it=scopes.rbegin();it != scopes.rend();++it)
        {
            if(it->find(name)!=it->end())
                {
                return it->at(name);
                }
        }
    throw std::runtime_error("variable '" + name + "' NOT declared in this scope :c")
}
    void SemanticAnalyser::kowalski(const std::shared_ptr<ASTNode>& root)
    {
    symbolTable.enterScope();
    try {analyseNode(root)}
    symbolTable.exitScope();
    }

    void SemanticAnalyser::analyseNode(const std::shared_ptr<ASTNode>& node);
        {
            Switch(nodeType->getName()){
                case nodeType::functionNode:
                    kowalskiFunction(std::static_pointer_cast<FunctionNode>(node));
                    break;
                case nodeType::variableNode:
                    kowalskiVariable(std::static_pointer_cast<VariableNode>(node));
                    break;
                case nodeType::declarationNode:
                    kowalskiDeclaration(std::static_pointer_cast<DeclarationNode>(node));
                    break;
                case nodeType::charNode:
                    kowalskiChar(std::static_pointer_cast<CharNode>(node));
                    break;
                case nodeType::ifNode:
                    kowalskiIf(std::static_pointer_cast<IfStatementNode>(node));
                    break;
                case nodeType::floatNode:
                    kowalskiFloat(std::static_pointer_cast<FloatNode>(node));
                    break;
                case nodeType::stringNode:
                    kowalskiString(std::static_pointer_cast<StringNode>(node));
                    break;
                case nodeType::whileNode:
                    kowalskiWhile(std::static_pointer_cast<whileNode>(node));
                    break;
                case nodeType::forNode:
                    kowalskiFor(std::static_pointer_cast<ForLoopNode>(node));
                    break;
                case nodeType::switchNode:
                    kowalskiSwitch(std::static_pointer_cast<SwitchNode>(node));
                    break;
                case nodeType::operatorNode:
                    kowalskiOperator(std::static_pointer_cast<OperatorNode>(node));
                    break;
                case nodeType::ConditionNode:
                    kowalskiKondi(std::static_pointer_cast<ConditionNode>(node));
                    break;
                case nodeType::mathNode:
                    kowalskiMath(std::static_pointer_cast<MathNode>(node));
                    break;
                default:
                    throw std::runtime_error("unknown node type");
            }
        }
// todo: make case for each node type, define each node method,
// todo: make sure the first 4 methods are using in methods going forward, approiatly :3
// it goes through all nodes, some nodes needs to do nothing but still need a case so we don't default

void SemanticAnalyser::kowalskiFunction(const std::shared_ptr<FunctionNode>& node){

}
void SemanticAnalyser::kowalskiVariable(const std::shared_ptr<VariableNode>& node){
    // this one declares varaiable
    string name = node.identifier;
    string type = node.type;
    declareVariable(const std::string& name,const std::string& type);
}
void SemanticAnalyser::kowalskiDeclaration(const std::shared_ptr<DeclarationNode>& node){
    throw runtime_error("not fully declared variable, if i read the code correctly cuz this node is never made")
}
void SemanticAnalyser::kowalskiChar(const std::shared_ptr<CharNode>& node){   
    //no this is not declaring but just typing on raw, nice example thou in case
    //that comment was wrong my bad I just read the error in the case above so use its case
    string name = node.identifier;
    declareVariable(const std::string& name,"char");
}
void SemanticAnalyser::kowalskiIf(const std::shared_ptr<IfStatementNode>& node){
    kowalskiKondi(node.condition);
}
void SemanticAnalyser::kowalskiFloat(const std::shared_ptr<FloatNode>& node){
    string name = node.identifier;
    //should do an if to look if it is a float or an int, but right now all numbers are numbers
    declareVariable(const std::string& name, "float");
}
void SemanticAnalyser::kowalskiString(const std::shared_ptr<StringNode>& node){
    string name = node.identifier;
    declareVariable(const std::string& name, "string");
}

void SemanticAnalyser::kowalskiWhile(const std::shared_ptr<whileNode>& node){
    kowalskiKondi(node.condition);
}
void SemanticAnalyser::kowalskiFor(const std::shared_ptr< ForLoopNode>& node){
    kowalskiKondi(node.condition);
    analyseNode(node.declaration);
    KowalskiMath(node.expression);
}
void SemanticAnalyser::kowalskiSwitch(const std::shared_ptr<SwitchNode>& node){

}
void SemanticAnalyser::kowalskiOperator(const std::shared_ptr<OperatorNode>& node){
    //code case just in case to avoid an error of an unknown node type
    //you did math YAY!
    // mental assault towards human
    //todo:: math node type will be added later, aj har det på sin pc
}

void SemanticAnalyser::kowalskiKondi(const std::shared_ptr<ConditionNode>& node){
    string condition = node.condition;
    declareVariable(const std::string& name, "condition");
    string bSide = node.bNode.getName();
    //todo:: if statement to check if both sides allow || and &&
    switch(node.aNode.getName()){
        case "floatNode":
            if(bSide != "floatNode" && bSide != "intNode")
                throw runtime_error("Floats only accept integer and float comparaisons.")
            break;
        case "intNode":
            if(bSide != "intNode")
                throw runtime_error("Integers only accept integer comparaisons.")
            break;
        case "charNode":
            if(bSide != "charNode" && (bSide != "stringNode" && bNode.StringOfChars.length() == 1))
                throw runtime_error("Chars only accept chars and single letter string comparaisons.")
            break;
        case "stringNode":
            if(bSide != "stringNode" && (bSide != "charNode" && aNode.StringOfChars.length() == 1))
                throw runtime_error("Strings only accept string comparaisons and chars if the string is a single letter string.")
            break;
    }
}
void SemanticAnalyser::kowalskiMath(const std::shared_ptr<MathNode>& node){

}