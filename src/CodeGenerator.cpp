#include "CodeGenerator.h"
#include <string>
#include <iostream>

CodeGenerator::CodeGenerator() {
    std::cout << "CodeGenerator initialized." << std::endl;
}

std::string CodeGenerator::generateCode(std::vector<std::shared_ptr<ASTNode>>& root) {
    std::cout << "Generating code for the entire program." << std::endl;
    std::string code = "#include <iostream>\n#include <string>\n#include <cstdlib>\n\n";
    code += generateBodyCode(root);
    return code;
}

std::string CodeGenerator::generateIfCode(std::shared_ptr<IfNode>& node) {
    std::cout << "Generating if statement code." << std::endl;
    std::string ifCodeOutput;
    ifCodeOutput += "if(";
    ifCodeOutput += generateConditionCode(node->condition);
    ifCodeOutput += "){";
    ifCodeOutput += generateBodyCode(node->body);
    ifCodeOutput += "}";

    if (!node->elseBody.empty()) {
        ifCodeOutput += "else{";
        ifCodeOutput += generateBodyCode(node->elseBody);
        ifCodeOutput += "}";
    }

    return ifCodeOutput;
}

std::string CodeGenerator::generateWhileCode(std::shared_ptr<WhileNode>& node) {
    std::cout << "Generating while loop code." << std::endl;
    std::string whileCodeOutput;
    whileCodeOutput += "while(";
    whileCodeOutput += generateConditionCode(node->condition);
    whileCodeOutput += "){";
    whileCodeOutput += generateBodyCode(node->body);
    whileCodeOutput += "}";
    return whileCodeOutput;
}

std::string CodeGenerator::generateReturnCode(std::shared_ptr<ReturnNode>& node){
    std::cout << "Generating return statement code." << std::endl;
    std::string returnCodeOutput;
    returnCodeOutput += "return ";
    returnCodeOutput += node->identifier;
    returnCodeOutput += ";";
    return returnCodeOutput;
}

std::string CodeGenerator::generateStructCode(std::shared_ptr<StructNode>& node) {
    std::cout << "Generating struct code." << std::endl;
    std::string leString;
    leString += "struct ";
    leString += node->identifier;
    leString += "{";
    for(int i = 0; i<node->body.size(); i++){
        auto convNode = std::dynamic_pointer_cast<DeclarationNode>(node->body[i]);
        leString += generateDeclartionCode(convNode);
    }
    leString += "};";
    return leString;
}

std::string CodeGenerator::generateSwitchCode(std::shared_ptr<SwitchNode>& node){
    std::cout << "Generating switch statement code." << std::endl;
    std::string leString;
    leString += "switch(";
    leString += generateConditionCode(node->condition);
    leString += ")";
    leString += "{";
    for (int i = 0; i < node->caseBranch.size(); i++){
        leString += "case ";
        auto convNode = std::dynamic_pointer_cast<ConditionNode>(node->caseBranch[i]->sucessCondition);
        leString += generateConditionCode(convNode) + ":";

        leString += generateBodyCode(node->caseBranch[i]->Branch);
        leString += "break;";
    }
    if(node->deNode != nullptr){
        leString += "default:";
        leString += generateBodyCode(node->deNode->Branch);
    }
    leString += "}";
    return leString;
}

std::string CodeGenerator::generateForCode(std::shared_ptr<ForLoopNode>& node) {
    std::cout << "Generating for loop code." << std::endl;
    std::string forCodeOutput;
    forCodeOutput += "for(";
    forCodeOutput += generateValueCode(node->declaration);
    forCodeOutput += generateConditionCode(node->condition) + ";";
    forCodeOutput += generateConditionCode(node->expression);
    forCodeOutput += "){";
    forCodeOutput += generateBodyCode(node->body);
    forCodeOutput += "}";
    return forCodeOutput;
}

std::string CodeGenerator::generateBodyCode(std::vector<std::shared_ptr<ASTNode>>& body) {
    std::cout << "Generating code for the body of a block." << std::endl;
    std::string completeBodyCodeOutput;
    for (int i = 0; i < body.size(); i++){
        if (body[i]->getType() == nodeType::arrayNode){
            auto convertedArrayNode = std::dynamic_pointer_cast<ArrayNode>(body[i]);
            completeBodyCodeOutput += generateArrayCode(convertedArrayNode);
        } else if(body[i]->getType() == nodeType::conditionNode){
            auto convertedConditionNode = std::dynamic_pointer_cast<ConditionNode>(body[i]);
            completeBodyCodeOutput += generateConditionCode(convertedConditionNode);
            completeBodyCodeOutput += ";";
        } else if(body[i]->getType() == nodeType::consoleNode){
            auto convertedConsoleNode = std::dynamic_pointer_cast<ConsoleNode>(body[i]);
            completeBodyCodeOutput += generateConsoleCode(convertedConsoleNode);
        } else if(body[i]->getType() == nodeType::forLoopNode){
            auto convertedForNode = std::dynamic_pointer_cast<ForLoopNode>(body[i]);
            completeBodyCodeOutput += generateForCode(convertedForNode);
        } else if(body[i]->getType() == nodeType::ifNode){
            auto convertedIfNode = std::dynamic_pointer_cast<IfNode>(body[i]);
            completeBodyCodeOutput += generateIfCode(convertedIfNode);
        } else if(body[i]->getType() == nodeType::functionNode){
            auto convertedFunctionNode = std::dynamic_pointer_cast<FunctionNode>(body[i]);
            completeBodyCodeOutput += generateFunctionCode(convertedFunctionNode);
        } else if(body[i]->getType() == nodeType::functionCallNode){
            auto convertedFunctionCallNode = std::dynamic_pointer_cast<FunctionCallNode>(body[i]);
            completeBodyCodeOutput += generateFunctionCallCode(convertedFunctionCallNode);
        } else if(body[i]->getType() == nodeType::switchNode){
            auto convertedSwitchNode = std::dynamic_pointer_cast<SwitchNode>(body[i]);
            completeBodyCodeOutput += generateSwitchCode(convertedSwitchNode);
        } else if(body[i]->getType() == nodeType::whileNode){
            auto convertedWhileNode = std::dynamic_pointer_cast<WhileNode>(body[i]);
            completeBodyCodeOutput += generateWhileCode(convertedWhileNode);
        } else if(body[i]->getType() == nodeType::declarationNode){
            auto convertedDeclarationNode = std::dynamic_pointer_cast<DeclarationNode>(body[i]);
            completeBodyCodeOutput += generateDeclartionCode(convertedDeclarationNode);
        } else if(body[i]->getType() == nodeType::valueNode){
            auto convertedValueNode = std::dynamic_pointer_cast<ValueNode>(body[i]);
            completeBodyCodeOutput += generateValueCode(convertedValueNode);
        } else if(body[i]->getType() == nodeType::jumpNode){
            auto convertedJumpNode = std::dynamic_pointer_cast<JumpNode>(body[i]);
            completeBodyCodeOutput += generateJumpCode(convertedJumpNode);
        } else if(body[i]->getType() == nodeType::returnNode){
            auto convertedReturnNode = std::dynamic_pointer_cast<ReturnNode>(body[i]);
            completeBodyCodeOutput += generateReturnCode(convertedReturnNode);
        }
    }
    return completeBodyCodeOutput;
}

std::string CodeGenerator::generateJumpCode(std::shared_ptr<JumpNode>& node){
    std::cout << "Generating jump statement code." << std::endl;
    if (node->continuer != "null"){
        return node->continuer + ";";
    } else if (node->breaker != "null"){
        return node->breaker + ";";
    }
    return "you done fucked up";
}

std::string CodeGenerator::generateArrayCode(std::shared_ptr<ArrayNode>& node){
    std::cout << "Generating array code." << std::endl;
    std::string leString;
    if (node->type == "string"){
        leString = "std::" + node->type + " " + node->identifier + "[" + node->size + "]";
    } else{
        leString = node->type + " " + node->identifier + "[" + node->size + "]";
    }
    for (int i = 0; i < node->body.size(); i++) {
        if(i == 0){
            leString += " = [";
        } else{
            leString += ",";
        }
        if (node->body[i]->getType() == nodeType::identifierNode){
            auto newNode = std::dynamic_pointer_cast<IdentifierNode>(node->body[i]);
            leString += generateIdentifierCode(newNode);
        } else if (node->body[i]->getType() == nodeType::functionCallNode){
            auto newNode = std::dynamic_pointer_cast<FunctionCallNode>(node->body[i]);
            leString += generateFunctionCallCode(newNode);
        } else if (node->body[i]->getType() == nodeType::intNode){
            auto convertedNode = std::dynamic_pointer_cast<IntNode>(node->body[i]);
            leString += generateIntCode(convertedNode);
        } else if (node->body[i]->getType() == nodeType::charNode){
            auto convertedNode = std::dynamic_pointer_cast<CharNode>(node->body[i]);
            leString += generateCharCode(convertedNode);
        } else if (node->body[i]->getType() == nodeType::stringNode){
            auto convertedNode = std::dynamic_pointer_cast<StringNode>(node->body[i]);
            leString += generateStringCode(convertedNode);
        } else if (node->body[i]->getType() == nodeType::floatNode){
            auto convertedNode = std::dynamic_pointer_cast<FloatNode>(node->body[i]);
            leString += generateFloatCode(convertedNode);
        } else if (node->body[i]->getType() == nodeType::usIntNode){
            auto convertedNode = std::dynamic_pointer_cast<UsIntNode>(node->body[i]);
            leString += generateUSCode(convertedNode);
        } else if (node->body[i]->getType() == nodeType::boolNode){
            auto convertedNode = std::dynamic_pointer_cast<BoolNode>(node->body[i]);
            leString += generateBoolCode(convertedNode);
        }
    }
    leString += "]";
    return leString + ";";
}

std::string CodeGenerator::generateFunctionCode(std::shared_ptr<FunctionNode>& node) {
    std::cout << "Generating function code." << std::endl;
    std:: string functionCodeOutput;
    functionCodeOutput += node->type;
    functionCodeOutput += " ";
    functionCodeOutput += node->identifier;
    functionCodeOutput += "(";
    for (int i = 0; i < node->arguments.size(); i++) {
        if (i > 0 ){ functionCodeOutput += ","; }
        auto functionArugment = std::dynamic_pointer_cast<DeclarationNode>(node->arguments[i]);
        functionCodeOutput += generateDeclartionCode(functionArugment);
        functionCodeOutput.pop_back();
    }
    functionCodeOutput += "){";
    functionCodeOutput += generateBodyCode(node->body);
    functionCodeOutput += "};";
    return functionCodeOutput;
}

std::string CodeGenerator::generateIntCode(std::shared_ptr<IntNode>& node){
    std::cout << "Generating integer code." << std::endl;
    return std::to_string(node->integer);
}

std::string CodeGenerator::generateUSCode(std::shared_ptr<UsIntNode>& node){
    std::cout << "Generating unsigned integer code." << std::endl;
    return std::to_string(node->usinteger);
}

std::string CodeGenerator::generateFloatCode(std::shared_ptr<FloatNode>& node){
    std::cout << "Generating float code." << std::endl;
    return std::to_string(node->Floating_Point);
}

std::string CodeGenerator::generateBoolCode(std::shared_ptr<BoolNode>& node){
    std::cout << "Generating boolean code." << std::endl;
    return std::to_string(node->boolean);
}

std::string CodeGenerator::generateDeclartionCode(std::shared_ptr<DeclarationNode>& node){
    std::cout << "Generating declaration code." << std::endl;
    std::string leString;
    if (node->type == "string"){
        leString = "std::" + node->type + " " + node->identifier + ";";
    } else{
        leString = node->type + " " + node->identifier + ";";
    }
    return leString;
}

std::string CodeGenerator::generateConsoleCode(std::shared_ptr<ConsoleNode>& node){
    std::cout << "Generating console output code." << std::endl;
    std::string CodeInString;
    if(node->Cin ){
    CodeInString =+ "std::cin >>";
    }else{
    CodeInString =+ "std::cout <<";
    }
    for(int i = 0; i < node->message.size(); i++) {
        if (i > 0){ CodeInString += "+"; }
        if (node->message[i]->getType() == nodeType::intNode){
            auto convertedNode = std::dynamic_pointer_cast<IntNode>(node->message[i]);
            CodeInString += generateIntCode(convertedNode);
        } else if (node->message[i]->getType() == nodeType::charNode){
            auto convertedNode = std::dynamic_pointer_cast<CharNode>(node->message[i]);
            CodeInString += generateCharCode(convertedNode);
        } else if (node->message[i]->getType() == nodeType::stringNode){
            auto convertedNode = std::dynamic_pointer_cast<StringNode>(node->message[i]);
            CodeInString += generateStringCode(convertedNode);
        } else if (node->message[i]->getType() == nodeType::floatNode){
            auto convertedNode = std::dynamic_pointer_cast<FloatNode>(node->message[i]);
            CodeInString += generateFloatCode(convertedNode);
        } else if (node->message[i]->getType() == nodeType::identifierNode){
            auto convertedNode = std::dynamic_pointer_cast<IdentifierNode>(node->message[i]);
            CodeInString += generateIdentifierCode(convertedNode);
        } else if (node->message[i]->getType() == nodeType::usIntNode){
            auto convertedNode = std::dynamic_pointer_cast<UsIntNode>(node->message[i]);
            CodeInString += generateUSCode(convertedNode);
        } else if (node->message[i]->getType() == nodeType::boolNode){
            auto convertedNode = std::dynamic_pointer_cast<BoolNode>(node->message[i]);
            CodeInString += generateBoolCode(convertedNode);
        }
    }
    if(node->Cin ){
        CodeInString += ";";
        //CodeInString += ">> std::endl;";
    }else{
        CodeInString += "<< std::endl;";
    }

    return CodeInString;
}

std::string CodeGenerator::generateValueCode(std::shared_ptr<ValueNode>& node){
    std::string leString;

    if (node->type == "string"){
        leString = "std::" + node->type + " " + node->identifier + "=";
    }
    else if (node->type == "usint"){
        leString = "int "  + node->identifier + "=";
    }
    else{
        leString = node->type + " " + node->identifier + "=";
    }

    if (node->value->getType() == nodeType::intNode){
        auto convertedNode = std::dynamic_pointer_cast<IntNode>(node->value);
        leString += generateIntCode(convertedNode);
    } else if (node->value->getType() == nodeType::charNode){
        auto convertedNode = std::dynamic_pointer_cast<CharNode>(node->value);
        leString += generateCharCode(convertedNode);
    } else if (node->value->getType() == nodeType::stringNode){
        auto convertedNode = std::dynamic_pointer_cast<StringNode>(node->value);
        leString += generateStringCode(convertedNode);
    } else if (node->value->getType() == nodeType::floatNode){
        auto convertedNode = std::dynamic_pointer_cast<FloatNode>(node->value);
        leString += generateFloatCode(convertedNode);
    } else if (node->value->getType() == nodeType::usIntNode){
        auto convertedNode = std::dynamic_pointer_cast<UsIntNode>(node->value);
        leString += generateUSCode(convertedNode);
    } else if (node->value->getType() == nodeType::boolNode){
        auto convertedNode = std::dynamic_pointer_cast<BoolNode>(node->value);
        leString += generateBoolCode(convertedNode);
    } else if (node->value->getType() == nodeType::identifierNode){
        auto convertedNode = std::dynamic_pointer_cast<IdentifierNode>(node->value);
        leString += generateIdentifierCode(convertedNode);
    } else if (node->value->getType() == nodeType::functionCallNode){
        auto convertedNode = std::dynamic_pointer_cast<FunctionCallNode>(node->value);
        leString += generateFunctionCallCode(convertedNode);
        return leString;
    }

    return leString + ";";
}

std::string CodeGenerator::generateFunctionCallCode(std::shared_ptr<FunctionCallNode>& Node){
    std::cout << "Generating function call code." << std::endl;
    std::string leString = Node->identifier + "(";
    for (int i = 0; i < Node->arguments.size(); i++){
        if (i != 0) { leString += ","; }
        if (Node->arguments[i]->getType() == nodeType::intNode){
            auto convertedNode = std::dynamic_pointer_cast<IntNode>(Node->arguments[i]);
            leString += generateIntCode(convertedNode);
        } else if (Node->arguments[i]->getType() == nodeType::charNode){
            auto convertedNode = std::dynamic_pointer_cast<CharNode>(Node->arguments[i]);
            leString += generateCharCode(convertedNode);
        } else if (Node->arguments[i]->getType() == nodeType::stringNode){
            auto convertedNode = std::dynamic_pointer_cast<StringNode>(Node->arguments[i]);
            leString += generateStringCode(convertedNode);
        } else if (Node->arguments[i]->getType() == nodeType::floatNode){
            auto convertedNode = std::dynamic_pointer_cast<FloatNode>(Node->arguments[i]);
            leString += generateFloatCode(convertedNode);
        } else if (Node->arguments[i]->getType() == nodeType::identifierNode){
            auto convertedNode = std::dynamic_pointer_cast<IdentifierNode>(Node->arguments[i]);
            leString += generateIdentifierCode(convertedNode);
        } else if (Node->arguments[i]->getType() == nodeType::usIntNode){
            auto convertedNode = std::dynamic_pointer_cast<UsIntNode>(Node->arguments[i]);
            leString += generateUSCode(convertedNode);
        } else if (Node->arguments[i]->getType() == nodeType::boolNode){
            auto convertedNode = std::dynamic_pointer_cast<BoolNode>(Node->arguments[i]);
            leString += generateBoolCode(convertedNode);
        }
    }
    return leString + ");";
}

std::string CodeGenerator::generateConditionCode(std::shared_ptr<ConditionNode>& node){
    std::cout << "Generating condition code." << std::endl;
    std::string leString = "";
    if (node->aNode->getType() == nodeType::intNode){
        auto convertedNode = std::dynamic_pointer_cast<IntNode>(node->aNode);
        leString = generateIntCode(convertedNode);
    } else if (node->aNode->getType() == nodeType::charNode){
        auto convertedNode = std::dynamic_pointer_cast<CharNode>(node->aNode);
        leString = generateCharCode(convertedNode);
    } else if (node->aNode->getType() == nodeType::stringNode){
        auto convertedNode = std::dynamic_pointer_cast<StringNode>(node->aNode);
        leString = generateStringCode(convertedNode);
    } else if (node->aNode->getType() == nodeType::floatNode){
        auto convertedNode = std::dynamic_pointer_cast<FloatNode>(node->aNode);
        leString = generateFloatCode(convertedNode);
    } else if (node->aNode->getType() == nodeType::identifierNode){
        auto convertedNode = std::dynamic_pointer_cast<IdentifierNode>(node->aNode);
        leString = generateIdentifierCode(convertedNode);
    } else if (node->aNode->getType() == nodeType::usIntNode){
        auto convertedNode = std::dynamic_pointer_cast<UsIntNode>(node->aNode);
        leString = generateUSCode(convertedNode);
    } else if (node->aNode->getType() == nodeType::boolNode){
        auto convertedNode = std::dynamic_pointer_cast<BoolNode>(node->aNode);
        leString = generateBoolCode(convertedNode);
    } else if (node->aNode->getType() == nodeType::functionCallNode){
        auto convertedNode = std::dynamic_pointer_cast<FunctionCallNode>(node->aNode);
        leString = generateFunctionCallCode(convertedNode);
    }
    leString += node->condition;

    if (node->condition.empty()){
        return leString;
    }
    if (node->bNode != nullptr){
        if (node->bNode->getType() == nodeType::conditionNode){
            auto condinode = std::dynamic_pointer_cast<ConditionNode>(node->bNode);
            leString += generateConditionCode(condinode);
        } else if (node->bNode->getType() == nodeType::intNode){
            auto convertedNode = std::dynamic_pointer_cast<IntNode>(node->bNode);
            leString += generateIntCode(convertedNode);
        } else if (node->bNode->getType() == nodeType::charNode){
            auto convertedNode = std::dynamic_pointer_cast<CharNode>(node->bNode);
            leString += generateCharCode(convertedNode);
        } else if (node->bNode->getType() == nodeType::stringNode){
            auto convertedNode = std::dynamic_pointer_cast<StringNode>(node->bNode);
            leString += generateStringCode(convertedNode);
        } else if (node->bNode->getType() == nodeType::floatNode){
            auto convertedNode = std::dynamic_pointer_cast<FloatNode>(node->bNode);
            leString += generateFloatCode(convertedNode);
        } else if (node->bNode->getType() == nodeType::identifierNode){
            auto convertedNode = std::dynamic_pointer_cast<IdentifierNode>(node->bNode);
            leString += generateIdentifierCode(convertedNode);
        } else if (node->bNode->getType() == nodeType::usIntNode){
            auto convertedNode = std::dynamic_pointer_cast<UsIntNode>(node->bNode);
            leString += generateUSCode(convertedNode);
        } else if (node->bNode->getType() == nodeType::boolNode){
            auto convertedNode = std::dynamic_pointer_cast<BoolNode>(node->bNode);
            leString += generateBoolCode(convertedNode);
        } else if (node->bNode->getType() == nodeType::functionCallNode){
            auto convertedNode = std::dynamic_pointer_cast<FunctionCallNode>(node->bNode);
            leString += generateFunctionCallCode(convertedNode);
        }
    }
    return leString;
}

std::string CodeGenerator::generateCharCode(std::shared_ptr<CharNode>& node) {
    std::cout << "Generating char code." << std::endl;
    return node->character;
}

std::string CodeGenerator::generateStringCode(std::shared_ptr<StringNode>& node) {
    std::cout << "Generating string code." << std::endl;
    //if (node->StringOfChars == "\"\"") {
      //  return "\"\"";
    //}
    return node->StringOfChars; //no need to add extra " cuz its already
}

std::string CodeGenerator::generateIdentifierCode(std::shared_ptr<IdentifierNode>& node) {
    std::cout << "Generating identifier code." << std::endl;
    return node->identifier;
}

std::string CodeGenerator::generateRandomCode(std::shared_ptr<RandomNode>& node) {
    std::cout << "Generating random code." << std::endl;
    std::string randomCodeOutput;
    std::string randomID = node->identifier;

    if (node->type == "int?") {
        randomCodeOutput += "int ";
        randomCodeOutput += randomID;
        randomCodeOutput += "=";
        if (node->RandomIntRange.size() > 0) {
            randomCodeOutput +=
                    "rand()%(" + std::to_string(node->RandomIntRange[1]) + "-" + std::to_string(node->RandomIntRange[0]) +
                    "+1)+" + std::to_string(node->RandomIntRange[0]) + ";";
            return randomCodeOutput;
        } else {
            randomCodeOutput += "rand();";
            return randomCodeOutput;
        }
    } else if (node->type == "float?") {
        randomCodeOutput += "float ";
        randomCodeOutput += randomID;
        randomCodeOutput += "=";
        if (node->RandomFloatRange.size() > 0) {
            randomCodeOutput += "randomFloat; ";
            randomCodeOutput += "randomFloat = (float range =" + std::to_string(node->RandomFloatRange[1]) + "-" +
                                std::to_string(node->RandomFloatRange[0]) + "+ 1; float num = rand() % range +" +
                                std::to_string(node->RandomFloatRange[0]) + ";)";
            return randomCodeOutput;
        } else {
            randomCodeOutput += "randomFloat;";
            randomCodeOutput += " randomFloat = (float)rand();";
            return randomCodeOutput;
        }
    } else if (node->type == "bool?") {
        randomCodeOutput += "bool ";
        randomCodeOutput += randomID;
        randomCodeOutput += "; ";
        randomCodeOutput += "int randomBool = rand(); if (randomBool%2==0){" + randomID + "= true); else {" + randomID +
                            "= false);";
        return randomCodeOutput;
    }
    std::cout << "randomCodeOutput returned empty string" << std::endl;
    return randomCodeOutput;
}