#include "gtest/gtest.h"
#include "parser.h"
#include "CodeGenerator.h"
#include <string>
#include <iostream>

TEST(CGTEST,DeclarationTest){
    auto DTN_basicDeclaration = std::make_shared<DeclarationNode>();
    DTN_basicDeclaration->type = "int";
    DTN_basicDeclaration->identifier = "x";
    CodeGenerator codeGenerator;
    std::string DTresault = codeGenerator.generateDeclartionCode(DTN_basicDeclaration);
    EXPECT_EQ(DTresault,"int x;");
}

TEST(CGTEST,ValueIntTest){
    auto VTN_basicValueInt = std::make_shared<ValueNode>();
    VTN_basicValueInt->type = "int";
    VTN_basicValueInt->identifier = "x";
    auto ITN_basicValue = std::make_shared<IntNode>();
    ITN_basicValue->integer = 12;
    VTN_basicValueInt->value = ITN_basicValue;
    CodeGenerator codeGenerator;
    std::string VTresault = codeGenerator.generateValueCode(VTN_basicValueInt);
    EXPECT_EQ(VTresault,"int x=12;");
}

TEST(CGTEST,ValueNegIntTest){
    auto VTN_basicValueInt = std::make_shared<ValueNode>();
    VTN_basicValueInt->type = "int";
    VTN_basicValueInt->identifier = "x";
    auto ITN_basicValue = std::make_shared<IntNode>();
    ITN_basicValue->integer = -12;
    VTN_basicValueInt->value = ITN_basicValue;
    CodeGenerator codeGenerator;
    std::string VTresault = codeGenerator.generateValueCode(VTN_basicValueInt);
    EXPECT_EQ(VTresault,"int x=-12;");
}

TEST(CGTEST,ValueFloatTest){
    auto VTN_basicValueFloat = std::make_shared<ValueNode>();
    VTN_basicValueFloat->type = "float";
    VTN_basicValueFloat->identifier = "x";
    auto FTN_basicValue = std::make_shared<FloatNode>();
    FTN_basicValue->Floating_Point = 7.35;
    VTN_basicValueFloat->value = FTN_basicValue;
    CodeGenerator codeGenerator;
    std::string FTresault = codeGenerator.generateValueCode(VTN_basicValueFloat);
    EXPECT_EQ(FTresault, "float x=7.350000;");
}

TEST(CGTEST,ValueCharTest){
    auto VTN_basicValueChar = std::make_shared<ValueNode>();
    VTN_basicValueChar->type = "char";
    VTN_basicValueChar->identifier = "x";
    auto CTN_basicValue = std::make_shared<CharNode>();
    CTN_basicValue->character = 'A';
    VTN_basicValueChar->value = CTN_basicValue;
    CodeGenerator codeGenerator;
    std::string CTresault = codeGenerator.generateValueCode(VTN_basicValueChar);
    EXPECT_EQ(CTresault,"char x=A;");
}

TEST(CGTEST,ValueStringTest){
    auto VTN_basicValueString = std::make_shared<ValueNode>();
    VTN_basicValueString->type = "string";
    VTN_basicValueString->identifier = "leString";
    auto STN_basicValue = std::make_shared<StringNode>();
    STN_basicValue->StringOfChars = "HELLO FRIEND";
    VTN_basicValueString->value = STN_basicValue;
    CodeGenerator codeGenerator;
    std::string STresault = codeGenerator.generateValueCode(VTN_basicValueString);
    std::string STexpect;
    STexpect += "std::string leString=";
    STexpect += '"';
    STexpect += "HELLO FRIEND";
    STexpect += '"';
    STexpect += ";";
    EXPECT_EQ(STresault,STexpect);
}

TEST(CGTEST,ValueBoolTrueTest){
    auto VTN_basicValueBool = std::make_shared<ValueNode>();
    VTN_basicValueBool->type = "bool";
    VTN_basicValueBool->identifier = "x";
    auto BTN_basicValue = std::make_shared<BoolNode>();
    BTN_basicValue->boolean = true;
    VTN_basicValueBool->value = BTN_basicValue;
    CodeGenerator codeGenerator;
    std::string BTTresault = codeGenerator.generateValueCode(VTN_basicValueBool);
    EXPECT_EQ(BTTresault,"bool x=1;");
}

TEST(CGTEST,ValueBoolFalseTest){
    auto VTN_basicValueBool = std::make_shared<ValueNode>();
    VTN_basicValueBool->type = "bool";
    VTN_basicValueBool->identifier = "x";
    auto BTN_basicValue = std::make_shared<BoolNode>();
    BTN_basicValue->boolean = false;
    VTN_basicValueBool->value = BTN_basicValue;
    CodeGenerator codeGenerator;
    std::string BTFresault = codeGenerator.generateValueCode(VTN_basicValueBool);
    EXPECT_EQ(BTFresault,"bool x=0;");
}

TEST(CGTEST,ValueUsIntTest){
    auto VTN_basicValueUsInt = std::make_shared<ValueNode>();
    VTN_basicValueUsInt->type = "usint";
    VTN_basicValueUsInt->identifier = "x";
    auto UTN_basicValue = std::make_shared<UsIntNode>();
    UTN_basicValue->usinteger = 12;
    VTN_basicValueUsInt->value = UTN_basicValue;
    CodeGenerator codeGenerator;
    std::string UTresault = codeGenerator.generateValueCode(VTN_basicValueUsInt);
    EXPECT_EQ(UTresault,"int x=12;");
}

TEST(CGTEST,CondiTest){
    auto finalCondiNode = std::make_shared<ConditionNode>();
    auto firstArgument = std::make_shared<IdentifierNode>();
    firstArgument->identifier = "ABC";
    finalCondiNode->aNode = firstArgument;
    finalCondiNode->condition = "+=";
    auto midCondinode = std::make_shared<ConditionNode>();
    auto secondArgument = std::make_shared<FloatNode>();
    secondArgument->Floating_Point = 5.6;
    midCondinode->condition = "+";
    auto thirdArgument = std::make_shared<IntNode>();
    thirdArgument->integer = 10;
    midCondinode->aNode = secondArgument;
    midCondinode->bNode = thirdArgument;
    finalCondiNode->bNode = midCondinode;
    CodeGenerator codeGenerator;
    std::string CondiResault = codeGenerator.generateConditionCode(finalCondiNode);
    EXPECT_EQ(CondiResault,"ABC+=5.600000+10");
}

TEST(CGTEST,ConsoleTest){
    auto ConsoleTest = std::make_shared<ConsoleNode>();
    auto Consolemsg = std::make_shared<StringNode>();
    auto ConsoleOutputIntTest = std::make_shared<IntNode>();
    ConsoleOutputIntTest->integer = 12;
    int ConsoleExpectInt = ConsoleOutputIntTest->integer;
    Consolemsg->StringOfChars = "x is an int, it is:";
    ConsoleTest->message.push_back(Consolemsg);
    ConsoleTest->message.push_back(ConsoleOutputIntTest);
    CodeGenerator codeGenerator;
    std::string ConsoleResault = codeGenerator.generateConsoleCode(ConsoleTest);
    std:: string ConsoleExpect = "std::cout <<";
    ConsoleExpect += '"';
    ConsoleExpect += "x is an int, it is:";
    ConsoleExpect += '"';
    ConsoleExpect += "+";
    ConsoleExpect += std::to_string(ConsoleExpectInt);
    ConsoleExpect += "<< std::endl;";
    EXPECT_EQ(ConsoleResault,ConsoleExpect);
}

TEST(CGTEST,WhileTest){
    auto WhileTestOutput = std::make_shared<WhileNode>();
    auto WhileCondition = std::make_shared<ConditionNode>();
    auto WhileaNode = std::make_shared<IdentifierNode>();
    auto WhilebNode = std::make_shared<IntNode>();
    WhileaNode->identifier = "a";
    WhilebNode->integer = 12;
    WhileCondition->aNode = WhileaNode;
    WhileCondition->condition = "==";
    WhileCondition->bNode = WhilebNode;
    WhileTestOutput->condition = WhileCondition;
    auto WhileElement = std::make_shared<DeclarationNode>();
    WhileElement->type = "int";
    WhileElement->identifier = "x";
    WhileTestOutput->body.push_back(WhileElement);
    CodeGenerator codeGenerator;
    std::string WTresault = codeGenerator.generateWhileCode(WhileTestOutput);
    EXPECT_EQ(WTresault,"while(a==12){int x;}");
}

TEST(CGTEST,forTests){
    auto forTestNode = std::make_shared<ForLoopNode>();
    auto forDeclartionNode = std::make_shared<DeclarationNode>();
    forDeclartionNode->identifier = "i";
    forDeclartionNode->type = "int";
    auto forCountNode = std::make_shared<ConditionNode>();
    auto forCountIdNode = std::make_shared<IdentifierNode>();
    forCountIdNode->identifier = "i";
    forCountNode->aNode = forCountIdNode;
    forCountNode->condition = "<";
    auto forCountIntNode = std::make_shared<IntNode>();
    forCountIntNode->integer = 10;
    forCountNode->bNode = forCountIntNode;
    auto forIncreaseNode = std::make_shared<ConditionNode>();
    forIncreaseNode->aNode = forCountIdNode;
    forIncreaseNode->condition = "++";
    forTestNode->declaration = forDeclartionNode;
    forTestNode->condition = forCountNode;
    forTestNode->expression = forIncreaseNode;
    auto forBodyElementNode = std::make_shared<ValueNode>();
    forBodyElementNode->type = "int";
    forBodyElementNode->identifier = "x";
    forBodyElementNode->value = forCountIntNode;
    forTestNode->body.push_back(forBodyElementNode);
    CodeGenerator codeGenerator;
    std::string FTresault = codeGenerator.generateForCode(forTestNode);
    EXPECT_EQ(FTresault,"for(int i;i<10;i++){int x=10;}");
}

TEST(CGTEST,ifTest){
    auto ifTestNode = std::make_shared<IfNode>();
    auto ifConditionNode = std::make_shared<ConditionNode>();
    auto ifXNode = std::make_shared<IdentifierNode>();
    auto ifYNode = std::make_shared<IntNode>();
    ifXNode->identifier = "a";
    ifYNode->integer = 12;
    ifConditionNode->aNode = ifXNode;
    ifConditionNode->condition = "==";
    ifConditionNode->bNode = ifYNode;
    ifTestNode->condition = ifConditionNode;
    auto ifBody = std::make_shared<ValueNode>();
    ifBody->type = "int";
    ifBody->identifier = "b";
    ifBody->value = ifYNode;
    ifTestNode->body.push_back(ifBody);
    CodeGenerator codeGenerator;
    std::string ITresault = codeGenerator.generateIfCode(ifTestNode);
    EXPECT_EQ(ITresault,"if(a==12){int b=12;}");
}

TEST(CGTEST,ifElseTest){
    auto ifElseTest = std::make_shared<IfNode>();
    auto ifConditionNode = std::make_shared<ConditionNode>();
    auto ifXNode = std::make_shared<IdentifierNode>();
    auto ifYNode = std::make_shared<IntNode>();
    ifXNode->identifier = "a";
    ifYNode->integer = 12;
    ifConditionNode->aNode = ifXNode;
    ifConditionNode->condition = "==";
    ifConditionNode->bNode = ifYNode;
    ifElseTest->condition = ifConditionNode;
    auto IfBody = std::make_shared<ValueNode>();
    IfBody->type = "int";
    IfBody->identifier = "b";
    IfBody->value = ifYNode;
    ifElseTest->body.push_back(IfBody);
    auto IfElseBody = std::make_shared<ValueNode>();
    IfElseBody->type = "int";
    IfElseBody->identifier = "b";
    auto IfElseBodyValue = std::make_shared<IntNode>();
    IfElseBodyValue->integer = 14;
    IfElseBody->value = IfElseBodyValue;
    ifElseTest->elseBody.push_back(IfElseBody);
    CodeGenerator codeGenerator;
    std::string IETresault = codeGenerator.generateIfCode(ifElseTest);
    EXPECT_EQ(IETresault,"if(a==12){int b=12;}else{int b=14;}");
}
