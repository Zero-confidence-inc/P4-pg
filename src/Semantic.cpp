//
// Created by nicol on 09-05-2024.
//
#include "Semantic.h
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
            Switch(Node->getType()){
                case nodetype::Function:
                    kowalskiFunction(std::static_pointer_cast<FunctionNode>(node));
                    break;
                case nodetype::Variable:
                    kowalskiVariable(std::static_pointer_cast<VariableNode>(node));
                    break;
                case nodetype::Declaration:
                    kowalskiDeclaration(std::static_pointer_cast<DeclarationNode>(node));
                    break;
                case nodetype::Char:
                    kowalskiChar(std::static_pointer_cast<CharNode>(node));
                    break;
                case nodetype::IfStatement:
                    kowalskiIf(std::static_pointer_cast<IfStatementNode>(node));
                    break;
                case nodetype::Float:
                    kowalskiFloat(std::static_pointer_cast<FloatNode>(node));
                    break;
                case nodetype::String:
                    kowalskiString(std::static_pointer_cast<StringNode>(node));
                    break;
                default:
                    throw std::runtime_error("unknown node type");
            }
        }
// todo: make case for each node type, define each node method,
// todo: make sure the first 4 methods are using in methods going forward, approiatly :3

void SemanticAnalyser::kowalskiFunction(const std::shared_ptr<FunctionNode>& node)
    {

    }
void SemanticAnalyser::kowalskiVariable(const std::shared_ptr<VariableNode>& node) // this one declares varaiable
    {
        string name = node.identifier;
        string type = node.type;
        declareVariable(const std::string& name,const std::string& type);
    }
void SemanticAnalyser::kowalskiDeclaration(const std::shared_ptr<DeclarationNode>& node)
    {
        throw runtime_error("not fully declared variable, if i read the code correctly cuz this node is ever made")
    }
void SemanticAnalyser::kowalskiChar(const std::shared_ptr<CharNode>& node)
    {
        string name = node.identifier;
        string character = node.character;
        declareVariable(const std::string& name, const std::string& character);
    }
void SemanticAnalyser::kowalskiIf(const std::shared_ptr<IfStatementNode>& node)
    {

    }
void SemanticAnalyser::kowalskiFloat(const std::shared_ptr<FloatNode>& node)
    {

    }
void SemanticAnalyser::kowalskiString(const std::shared_ptr<StringNode>& node)
    {

    }

void SemanticAnalyser::kowalskiWhile(const std::shared_ptr<whileNode>& node);
{

}
void SemanticAnalyser::kowalskiFor(const std::shared_ptr< ForLoopNode>& node);
{

}
void SemanticAnalyser::kowalskiSwitch(const std::shared_ptr<SwitchNode>& node);
{

}
void SemanticAnalyser::kowalskiOperator(const std::shared_ptr<OperatorNode>& node);
{
    //you did math YAY!
    // mental assault towards human
}
void SemanticAnalyser::kowalskiKondi(const std::shared_ptr<ConditionNode>& node);
{

}