#include "CodeGenerator.h"

void CodeGenerator::generateCode(const std::shared_ptr<ASTNode>& root) {
    root->accept(*this);
}

void CodeGenerator::visit(FunctionNode& node) {
   
}

void CodeGenerator::visit(VariableNode& node) {
    
}

void CodeGenerator::visit(DeclarationNode& node) {
    
}

void CodeGenerator::visit(CharNode& node) {
   
}

void CodeGenerator::visit(IfStatementNode& node) {
    
}

void CodeGenerator::visit(FloatNode& node) {
    
}

void CodeGenerator::visit(StringNode& node) {
    
}

void CodeGenerator::visit(WhileNode& node) {
    
}

void CodeGenerator::visit(ForLoopNode& node) {
    
}

void CodeGenerator::visit(SwitchNode& node) {
    
}

void CodeGenerator::visit(OperatorNode& node) {
    
}

void CodeGenerator::visit(ConditionNode& node) {
    
}

void CodeGenerator::visit(MathNode& node) {
    
}

void CodeGenerator::generateFunctionCode(FunctionNode& node) {
    
}

void CodeGenerator::generateVariableCode(VariableNode& node) {
    
}