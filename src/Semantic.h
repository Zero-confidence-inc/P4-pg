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
    std::string lookUpVariable(const std::string& name);
private:
    std::vector<std::map<std::string,std::string>> scopes;

};
class SemanticAnalyser{
public:
    void kowalski(const std::shared_ptr<ASTNode>& root);
private:
    SymbolTable symbolTable;
    void analyseNode(const std::shared_ptr<ASTNode>& node);
    void kowalskiFunction(const std::shared_ptr<FunctionNode>& node);
    void kowalskiDeclaration(const std::shared_ptr<DeclarationNode>& node);
    void kowalskiChar(const std::shared_ptr<CharNode>& node);
    void kowalskiIf(const std::shared_ptr<IfNode>& node);
    void kowalskiFloat(const std::shared_ptr<FloatNode>& node);
    void kowalskiString(const std::shared_ptr<StringNode>& node);
    void kowalskiInt(const std::shared_ptr<IntNode>& node);
    void kowalskiBool(const std::shared_ptr<BoolNode>& node);
    void kowalskiWhile(const std::shared_ptr<WhileNode>& node);
    void kowalskiFor(const std::shared_ptr< ForLoopNode>& node);
    void kowalskiSwitch(const std::shared_ptr<SwitchNode>& node);
    void kowalskiKondi(const std::shared_ptr<ConditionNode>& node);
};






#endif //VCS_XML_SEMANTIC_H
