//
// Created by nicol on 09-05-2024.
//


#ifndef VCS_XML_SEMANTIC_H
#define VCS_XML_SEMANTIC_H
#include "Parser.h"
#include <map>
#include <string>
#include <memory>
#include <vector>

class SymbolTable{
public:
    void enterScope();
    void exitScope();
    void declareVariable(const std::string& name,const std::string& type);
    std::string LookUpVariable(const std::string& name);
private:
    std::vector<std::map<std::string,std::string>> scopes;

};
class SemanticAnalyser{
public:
    void kowalski(const std::shared_ptr<ASTNode>& Root);
private:
    SymbolTable symbolTable;
    void analyseNode(const std::shared_ptr<ASTNode>& Node);
    void kowalskiFunction(const std::shared_ptr<FunctionNode>& node);
    void kowalskiVariable(const std::shared_ptr<VariableNode>& node);
    void kowalskiDeclaration(const std::shared_ptr<DeclarationNode>& node);

};






#endif //VCS_XML_SEMANTIC_H
