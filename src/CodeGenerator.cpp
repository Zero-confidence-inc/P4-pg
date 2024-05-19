#include "CodeGenerator.h"
#include "string.h"

void CodeGenerator::generateCode(const std::shared_ptr<ASTNode>& root) {
    root->accept(*this);
}

void CodeGenerator::visit(FunctionNode& node) {
   
}

void CodeGenerator::visit(ValueNode& node) {
    
}

void CodeGenerator::visit(DeclarationNode& node) {
    
}

void CodeGenerator::visit(CharNode& node) {
   
}

void CodeGenerator::visit(IfNode& node) {
    
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

void CodeGenerator::visit(ConditionNode& node) {
    
}

void CodeGenerator::visit(ConsoleNode& node) {
    
}

void CodeGenerator::visit(CaseNode& node) {

}

void CodeGenerator::visit(IdentifierNode& node) {

}

void CodeGenerator::visit(ReturnNode& node) {

        return node.returning + " " + node.identifier;
    
}

void CodeGenerator::visit(IntNode& node) {

}

void CodeGenerator::visit(UsIntNode & node) {

}

void CodeGenerator::visit(BoolNode& node) {

}

void CodeGenerator::visit(JumpNode& node) {
    if (node.continuer.empty()) {
        return std::to_string(node.continuer);
    } else if (node.breaker.empty()) {
        return std::to_string(node.breaker);
    }
}
void CodeGenerator::visit(RandomNode& node) {

}

void CodeGenerator::visit(ArrayNode& node) {


return std::to_string node.type + " " + node.identifier + "[" + node.size + "] = {";

}

void CodeGenerator::visit(FunctionNode& node) {

}

void CodeGenerator::visit(FunctionCallNode& node) {
    
}

void CodeGenerator::generateFunctionCode(FunctionNode& node) {
    
}

void CodeGenerator::generateValueCode(ValueNode& node) {
    
}