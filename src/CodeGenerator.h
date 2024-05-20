#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include "parser.h"
#include <iostream>
#include <memory>

class ASTNodeVisitor {
public:
    virtual void visit(FunctionNode& node) = 0;
    virtual void visit(ValueNode& node) = 0;
    virtual void visit(DeclarationNode& node) = 0;
    virtual void visit(CharNode& node) = 0;
    virtual void visit(IfNode& node) = 0;
    virtual void visit(FloatNode& node) = 0;
    virtual void visit(StringNode& node) = 0;
    virtual void visit(WhileNode& node) = 0;
    virtual void visit(ForLoopNode& node) = 0;
    virtual void visit(SwitchNode& node) = 0;
    virtual void visit(ConditionNode& node) = 0;
    virtual void visit(ConsoleNode& node) = 0;
    virtual void visit(CaseNode& node) = 0;
    virtual void visit(IdentifierNode& node) = 0;
    virtual void visit(ReturnNode& node) = 0;
    virtual void visit(IntNode& node) = 0;
    virtual void visit(UsIntNode& node) = 0;
    virtual void visit(BoolNode & node) = 0;
    virtual void visit(JumpNode& node) = 0;
    virtual void visit(RandomNode& node) = 0;
    virtual void visit(ArrayNode& node) = 0;
    virtual void visit(FunctionNode& node) = 0;
    virtual void visit(FunctionCallNode& node) = 0;
    // Add other node types as needed...
};

class CodeGenerator : public ASTNodeVisitor {
public:
    void generateCode(const std::shared_ptr<ASTNode>& root);

    void visit(FunctionNode& node) override;
    void visit(ValueNode& node) override;
    void visit(DeclarationNode& node) override;
    void visit(CharNode& node) override;
    void visit(IfNode& node) override;
    void visit(FloatNode& node) override;
    void visit(StringNode& node) override;
    void visit(WhileNode& node) override;
    void visit(ForLoopNode& node) override;
    void visit(SwitchNode& node) override;
    void visit(ConditionNode& node) override;
    void visit(ConsoleNode& node) override;
    void visit(CaseNode& node) override;
    void visit(IdentifierNode& node) override;
    void visit(ReturnNode& node) override;
    void visit(IntNode& node) override;
    void visit(UsIntNode& node) override;
    void visit(BoolNode & node) override;
    void visit(JumpNode& node) override;
    void visit(RandomNode& node) override;
    void visit(ArrayNode& node) override;
    void visit(FunctionNode& node) override;
    void visit(FunctionCallNode& node) override;
    // Add other node types as needed...

private:
    // Helper methods for code generation
    std::string generateFunctionCode(FunctionNode& node);
    std::string generateValueCode(ValueNode& node);
    std::string generateIntCode(IntNode& node);
    std::string generateUSCode(UsIntNode& node);
    std::string generateFloatCode(FloatNode& node);
    std::string generateBoolCode(BoolNode& node);
    std::string generateConsoleCode(ConsoleNode& node);
    std::string generateDeclartionCode(DeclarationNode& node);
    std::string generateValueCode(ValueNode& node);
    std::string generateFunctionCallCode(FunctionCallNode& node);
    std::string generateConditionCode(std::shared_ptr<ConditionNode>& node);
    std::string generateCharCode(CharNode& node);
    std::string generateStringCode(StringNode& node);
    std::string generateIdentifierCode(IdentifierNode& node);
    std::string generateRandomCode(RandomNode& node);
    std::string generateIfCode(std::shared_ptr<IfNode>& node);
    std::string generateBodyCode(std::vector<std::shared_ptr<ASTNode>>& body);
    // Add other helper methods as needed...
};

#endif // CODEGENERATOR_H
