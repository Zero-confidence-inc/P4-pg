#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include "parser.h"
#include <iostream>
#include <memory>

class ASTNodeVisitor {
public:
    virtual void visit(FunctionNode& node) = 0;
    virtual void visit(VariableNode& node) = 0;
    virtual void visit(DeclarationNode& node) = 0;
    virtual void visit(CharNode& node) = 0;
    virtual void visit(IfStatementNode& node) = 0;
    virtual void visit(FloatNode& node) = 0;
    virtual void visit(StringNode& node) = 0;
    virtual void visit(WhileNode& node) = 0;
    virtual void visit(ForLoopNode& node) = 0;
    virtual void visit(SwitchNode& node) = 0;
    virtual void visit(OperatorNode& node) = 0;
    virtual void visit(ConditionNode& node) = 0;
    virtual void visit(MathNode& node) = 0;
    // Add other node types as needed...
};

class CodeGenerator : public ASTNodeVisitor {
public:
    void generateCode(const std::shared_ptr<ASTNode>& root);

    void visit(FunctionNode& node) override;
    void visit(VariableNode& node) override;
    void visit(DeclarationNode& node) override;
    void visit(CharNode& node) override;
    void visit(IfStatementNode& node) override;
    void visit(FloatNode& node) override;
    void visit(StringNode& node) override;
    void visit(WhileNode& node) override;
    void visit(ForLoopNode& node) override;
    void visit(SwitchNode& node) override;
    void visit(OperatorNode& node) override;
    void visit(ConditionNode& node) override;
    void visit(MathNode& node) override;
    // Add other node types as needed...

private:
    // Helper methods for code generation
    void generateFunctionCode(FunctionNode& node);
    void generateVariableCode(VariableNode& node);
    // Add other helper methods as needed...
};

#endif // CODEGENERATOR_H
