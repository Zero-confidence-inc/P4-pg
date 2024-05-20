#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include "parser.h"
#include <iostream>
#include <memory>

class CodeGenerator{
public:
    void generateCode(const std::shared_ptr<ASTNode>& root);
    std::string generateFunctionCode(std::shared_ptr<FunctionNode>& node);
    std::string generateValueCode(std::shared_ptr<ValueNode>& node);
    std::string generateIntCode(std::shared_ptr<IntNode>& node);
    std::string generateUSCode(std::shared_ptr<UsIntNode>& node);
    std::string generateFloatCode(std::shared_ptr<FloatNode>& node);
    std::string generateBoolCode(std::shared_ptr<BoolNode>& node);
    std::string generateConsoleCode(std::shared_ptr<ConsoleNode>& node);
    std::string generateDeclartionCode(std::shared_ptr<DeclarationNode>& node);
    std::string generateFunctionCallCode(std::shared_ptr<FunctionCallNode>& node);
    std::string generateConditionCode(std::shared_ptr<ConditionNode>& node);
    std::string generateCharCode(std::shared_ptr<CharNode>& node);
    std::string generateStringCode(std::shared_ptr<StringNode>& node);
    std::string generateIdentifierCode(std::shared_ptr<IdentifierNode>& node);
    std::string generateRandomCode(RandomNode& node);
    std::string generateIfCode(std::shared_ptr<IfNode>& node);
    std::string generateWhileCode(std::shared_ptr<WhileNode>& node);
    std::string generateForCode(std::shared_ptr<ForLoopNode>& node);
    std::string generateSwitchCode(std::shared_ptr<SwitchNode>& node);
    std::string generateStructCode(std::shared_ptr<StructNode>& node);
    std::string generateBodyCode(std::vector<std::shared_ptr<ASTNode>>& body);
    // Add other helper methods as needed...

private:

};

#endif