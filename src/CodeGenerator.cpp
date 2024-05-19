#include "CodeGenerator.h"
#include <string>

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

}

void CodeGenerator::visit(IntNode& node) {

}

void CodeGenerator::visit(UsIntNode & node) {

}

void CodeGenerator::visit(BoolNode& node) {

}

void CodeGenerator::visit(JumpNode& node) {

}

void CodeGenerator::visit(RandomNode& node) {

}

void CodeGenerator::visit(ArrayNode& node) {

}

void CodeGenerator::visit(FunctionNode& node) {

}

void CodeGenerator::visit(FunctionCallNode& node) {
    
}


std::string CodeGenerator::generateFunctionCode(FunctionNode& node) {
    
}

std::string CodeGenerator::generateValueCode(ValueNode& node) {
    
}

std::string CodeGenerator::generateIntCode(IntNode& node){
     return std::to_string(node.integer);
}
std::string CodeGenerator::generateUSCode(UsIntNode& node){
    return std::to_string(node.usinteger);
}
std::string CodeGenerator::generateFloatCode(FloatNode& node){
    return std::to_string(node.Floating_Point);
}
std::string CodeGenerator::generateBoolCode(BoolNode& node){
    return std::to_string(node.boolean);
}
std::string CodeGenerator::generateDeclartionCode(DeclarationNode& node){
    return node.type + " " + node.identifier + ";";

}
std::string CodeGenerator::generateConsoleCode(ConsoleNode& node)
{
    std::string CodeInString = "std::cout <<" ;
    for(int i=0;i<node.message.size();i++)
    { 
        if (node.message[i].getType() == nodeType::intNode ){
        CodeInString += generateIntCode(node.message[i]);}
    }
    CodeInString += "<< std::endl;";
    return CodeInString;
}