//
// Created by nicol on 09-05-2024.
//
#include "Semantic.h
#include <iostream>

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
    void SemanticAnalyser::kowalski(const std::shared_ptr<ASTNode>& Root)
    {
    symbolTable.enterScope();
    try {analyseNode(Root)}
    symbolTable.exitScope();
    }

    void SemanticAnalyser::analyseNode(const std::shared_ptr<ASTNode>& node);
        {
            Switch(Node->getType()){
                case nodetype::Function:
                    kowalskiFunction(std::static_pointer_cast<FunctionNode>(node));
                    break;
                case
                default:
                    throw std::runtime_error("unknown node type");
            }
        }
// todo: make case for each node type, define each node method,
// todo: make sure the first 4 methods are using in methods going forward, approiatly :3