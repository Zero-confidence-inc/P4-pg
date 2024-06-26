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

class FunctionTable{
public:
    void enterScope();
    void declareFunction(const std::string& name,std::vector<std::string>& arguments);
    std::vector<std::string> lookUpFunction(const std::string& functionName);
private:
    std::vector<std::map<std::string,std::vector<std::string>>> functionMap;
};

class Kowalski{
public:
    Kowalski();
    void Analyse(const std::vector<std::shared_ptr<ASTNode>>& root);
    void analyseNode(const std::shared_ptr<ASTNode>& node);
    void kowalskiFunction(const std::shared_ptr<FunctionNode>& node);
    void kowalskiIdentifier(const std::shared_ptr<IdentifierNode>& node);
    void kowalskiDeclaration(const std::shared_ptr<DeclarationNode>& node);
    void kowalskiChar(const std::shared_ptr<CharNode>& node);
    void kowalskiIf(const std::shared_ptr<IfNode>& node);
    void kowalskiFloat(const std::shared_ptr<FloatNode>& node);
    void kowalskiString(const std::shared_ptr<StringNode>& node);
    void kowalskiInt(const std::shared_ptr<IntNode>& node);
    void kowalskiBool(const std::shared_ptr<BoolNode>& node);
    void kowalskiWhile(const std::shared_ptr<WhileNode>& node);
    void kowalskiFor(const std::shared_ptr<ForLoopNode>& node);
    void kowalskiSwitch(const std::shared_ptr<SwitchNode>& node);
    void kowalskiCase(const std::shared_ptr<CaseNode>& node);
    void kowalskiKondi(const std::shared_ptr<ConditionNode>& node);
    void kowalskiConsole(const std::shared_ptr<ConsoleNode>& node);
    void kowalskiStruct(const std::shared_ptr<StructNode>& node);
    void kowalskiArray(const std::shared_ptr<ArrayNode>& node);
    void kowalskiReturn(const std::shared_ptr<ReturnNode>& node);
    nodeType getType2(const std::shared_ptr<ASTNode>& node);
    void kowalskiFunctionCall(const std::shared_ptr<FunctionCallNode>& node);
    void kowalskiRandom(const std::shared_ptr<RandomNode>& node);
    void kowalskiValue(const std::shared_ptr<ValueNode>& node);
private:
    SymbolTable symbolTable;
    FunctionTable functionTable;
};






#endif //VCS_XML_SEMANTIC_H
