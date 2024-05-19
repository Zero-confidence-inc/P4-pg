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
std::string CodeGenerator::generateConsoleCode(ConsoleNode& node){
    std::string CodeInString = "std::cout <<" ;
    for(int i=0;i<node.message.size();i++){
            CodeInString += node.message[i]->getValue();
        }
    
    CodeInString += "<< std::endl;";
    return CodeInString;
}
std::string CodeGenerator::generateValueCode(ValueNode& node){
    return node.type + " " + node.identifier + "=" + node.value->getValue()+";";
}
std::string CodeGenerator::generateFunctionCallCode(FunctionCallNode& Node){
    std::string leString = Node.identifier+"(";
    for (int i = 0;i<Node.arguments.size();i++){
        if (i<0) {leString +=",";}
        leString += Node.arguments[i]->getValue();
    }
    return leString +");";
}
std::string CodeGenerator::generateConditionCode(std::shared_ptr<ConditionNode>& node){
    std::string leString = node->aNode->getValue() + node->condition;
    if (node->condition==""){return leString;}
    if (node->bNode->getType() == nodeType::conditionNode){

        return leString += generateConditionCode(node->bNode);

    }
    return leString+node->bNode->getValue();
}

std::string CodeGenerator::generateCharCode(CharNode& node) {
    return node.character;
}

std::string CodeGenerator::generateStringCode(StringNode& node) {
    return node.StringOfChars;
}

std::string CodeGenerator::generateIdentifierCode(IdentifierNode& node) {
    return node.identifier;
}

std::string CodeGenerator::generateRandomCode(RandomNode& node) {
    std::string randomCodeOutput;
    std::string randomID = node.identifier;

    if (node.type == "int?"){
            randomCodeOutput += "int";
            randomCodeOutput += randomID;
            randomCodeOutput += "=";
        if (node.RandomIntRange.size()>0){
                randomCodeOutput += "rand()%(" + std::to_string(node.RandomIntRange[1]) + "-" + std::to_string(node.RandomIntRange[0]) + "+ 1) + " + std::to_string(node.RandomIntRange[0]) + ";";
                return randomCodeOutput;
        }
        else{
            randomCodeOutput += "rand();";
            return randomCodeOutput;
        }
    }
    else if (node.type == "float?"){
        randomCodeOutput += "float";
        randomCodeOutput += randomID;
        randomCodeOutput += "=";
        if (node.RandomFloatRange.size()>0){
            randomCodeOutput += "randomFloat;";
            randomCodeOutput += "randomFloat = (float range =" + std::to_string(node.RandomFloatRange[1]) + "-" + std::to_string(node.RandomFloatRange[0]) + "+ 1; float num = rand() % range +" + std::to_string(node.RandomFloatRange[0]) + ";)";
        }
        else{
            randomCodeOutput += "randomFloat;";
            randomCodeOutput += "randomFloat = (float)rand();";
            return randomCodeOutput;
        }
    }
    else if (node.type == "bool?"){
        randomCodeOutput += "bool";
        randomCodeOutput += randomID;
        randomCodeOutput += "=";
        randomCodeOutput += "int randomBool = rand(); if (randomBool%2==0){" + randomID + "= true); else {" + randomID + "= false);";
        return randomCodeOutput;
    }
}

