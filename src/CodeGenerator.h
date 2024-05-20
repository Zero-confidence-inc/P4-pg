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
    std::string generateFunctionCode(std::shared_ptr<FunctionNode>& node);
    std::string generateValueCode(std::shared_ptr<ValueNode>& node);
    std::string generateIntCode(std::shared_ptr<IntNode>& node);
    std::string generateUSCode(std::shared_ptr<UsIntNode>& node);
    std::string generateFloatCode(std::shared_ptr<FloatNode>& node);
    std::string generateBoolCode(std::shared_ptr<BoolNode>& node);
    std::string generateConsoleCode(std::shared_ptr<ConsoleNode>& node);
    std::string generateDeclartionCode(std::shared_ptr<DeclarationNode>& node);
    std::string generateValueCode(std::shared_ptr<ValueNode>& node);
    std::string generateFunctionCallCode(std::shared_ptr<FunctionCallNode>& node);
    std::string generateConditionCode(std::shared_ptr<ConditionNode>& node);
    std::string generateCharCode(std::shared_ptr<CharNode>& node);
    std::string generateStringCode(std::shared_ptr<StringNode>& node);
    std::string generateIdentifierCode(std::shared_ptr<IdentifierNode>& node);
    std::string generateRandomCode(RandomNode& node);
    // Add other helper methods as needed...
};

#endif // CODEGENERATOR_H
