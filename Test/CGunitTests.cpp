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
   // STexpect += '"';
    STexpect += "HELLO FRIEND";
   // STexpect += '"';
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
   // ConsoleExpect += '"';
    ConsoleExpect += "x is an int, it is:";
   // ConsoleExpect += '"';
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

TEST(CGTEST,ForTests){
    auto forTestNode = std::make_shared<ForLoopNode>();
    auto forDeclartionNode = std::make_shared<ValueNode>();
    forDeclartionNode->identifier = "i";
    forDeclartionNode->type = "int";
    auto forDeclarationIntNode = std::make_shared<IntNode>();
    forDeclarationIntNode->integer = 0;
    forDeclartionNode->value = forDeclarationIntNode;
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
    EXPECT_EQ(FTresault,"for(int i=0;i<10;i++){int x=10;}");
}

TEST(CGTEST,IfTest){
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

TEST(CGTEST,IfElseTest){
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

TEST(CGTEST,StructTest){
    auto structTestOutput = std::make_shared<StructNode>();
    structTestOutput->type = "struct";
    structTestOutput->identifier = "ABC";
    auto structBody1 = std::make_shared<DeclarationNode>();
    structBody1->type = "int";
    structBody1->identifier = "a";
    auto structBody2 = std::make_shared<DeclarationNode>();
    structBody2->type = "string";
    structBody2->identifier = "b";
    structTestOutput->body.push_back(structBody1);
    structTestOutput->body.push_back(structBody2);
    CodeGenerator codeGenerator;
    std::string STresault = codeGenerator.generateStructCode(structTestOutput);
    std::string STexpect = "struct ABC{int a;std::string b;};";
    EXPECT_EQ(STresault,STexpect);
}

TEST(CGTEST,IDTest){
    auto IdTestOutput = std::make_shared<IdentifierNode>();
    IdTestOutput->identifier = "a";
    CodeGenerator codeGenerator;
    std::string IDresault = codeGenerator.generateIdentifierCode(IdTestOutput);
    EXPECT_EQ(IDresault,"a");
}

TEST(CGTEST,ReturnTest){
    auto ReturnTestOutput = std::make_shared<ReturnNode>();
    ReturnTestOutput->identifier = "a";;
    CodeGenerator codeGenerator;
    std::string RTresault = codeGenerator.generateReturnCode(ReturnTestOutput);
    EXPECT_EQ(RTresault,"return a;");
}

TEST(CGTEST,RandomIntUnboundTest){
    auto RandomIntUnboundOutput = std::make_shared<RandomNode>();
    RandomIntUnboundOutput->type = "int?";
    RandomIntUnboundOutput->identifier = "x";
    CodeGenerator codeGenerator;
    std::string RIUTresault = codeGenerator.generateRandomCode(RandomIntUnboundOutput);
    EXPECT_EQ(RIUTresault,"int x=rand();");
}

TEST(CGTEST,RandomIntBoundTest){
    auto RandomIntBoundOutput = std::make_shared<RandomNode>();
    RandomIntBoundOutput->type = "int?";
    RandomIntBoundOutput->identifier = "x";
    RandomIntBoundOutput->RandomIntRange.push_back(1);
    RandomIntBoundOutput->RandomIntRange.push_back(10);
    CodeGenerator codeGenerator;
    std::string RIBTresault = codeGenerator.generateRandomCode(RandomIntBoundOutput);
    EXPECT_EQ(RIBTresault,"int x=rand()%(10-1+1)+1;");
}

TEST(CGTEST,RandomFloatUnboundTest){
    auto RandomFloatUnboundOutput = std::make_shared<RandomNode>();
    RandomFloatUnboundOutput->type = "float?";
    RandomFloatUnboundOutput->identifier = "x";
    CodeGenerator codeGenerator;
    std::string RFUTresault = codeGenerator.generateRandomCode(RandomFloatUnboundOutput);
    EXPECT_EQ(RFUTresault,"float x=randomFloat; randomFloat = (float)rand();");
}

TEST(CGTEST,RandomFloatBoundTest){
    auto RandomFloatBoundOutput = std::make_shared<RandomNode>();
    RandomFloatBoundOutput->type = "float?";
    RandomFloatBoundOutput->identifier = "x";
    RandomFloatBoundOutput->RandomFloatRange.push_back(3.5);
    RandomFloatBoundOutput->RandomFloatRange.push_back(10.8);
    CodeGenerator codeGenerator;
    std::string RFBTresault = codeGenerator.generateRandomCode(RandomFloatBoundOutput);
    EXPECT_EQ(RFBTresault,"float x=randomFloat; randomFloat = (float range =10.800000-3.500000+ 1; float num = rand() % range +3.500000;)");
}

TEST(CGTEST,RandomBoolTest){
    auto RandomBoolOutput = std::make_shared<RandomNode>();
    RandomBoolOutput->type = "bool?";
    RandomBoolOutput->identifier = "x";
    CodeGenerator codeGenerator;
    std::string RBTresault = codeGenerator.generateRandomCode(RandomBoolOutput);
    EXPECT_EQ(RBTresault,"bool x; int randomBool = rand(); if (randomBool%2==0){x= true); else {x= false);");
}

TEST(CGTEST,ArrayTest){
    auto ArrayOutput = std::make_shared<ArrayNode>();
    ArrayOutput->type = "int";
    ArrayOutput->identifier = "x";
    ArrayOutput->size = "5";
    auto ArrayBody1 = std::make_shared<IntNode>();
    auto ArrayBody2 = std::make_shared<IntNode>();
    ArrayBody1->integer = 2;
    ArrayBody2->integer = 15;
    ArrayOutput->body.push_back(ArrayBody1);
    ArrayOutput->body.push_back(ArrayBody2);
    CodeGenerator codeGenerator;
    std::string ATresault = codeGenerator.generateArrayCode(ArrayOutput);
    EXPECT_EQ(ATresault,"int x[5] = [2,15];");
}

TEST(CGTEST,JumpBreakTest){
    auto JumpOutput = std::make_shared<JumpNode>();
    JumpOutput->breaker = "break";
    JumpOutput->continuer = "null";
    CodeGenerator codeGenerator;
    std::string JBTresault = codeGenerator.generateJumpCode(JumpOutput);
    EXPECT_EQ(JBTresault,"break;");
}

TEST(CGTEST,JumpContinueTest){
    auto JumpOutput = std::make_shared<JumpNode>();
    JumpOutput->breaker = "null";
    JumpOutput->continuer = "continue";
    CodeGenerator codeGenerator;
    std::string JCTresault = codeGenerator.generateJumpCode(JumpOutput);
    EXPECT_EQ(JCTresault,"continue;");
}

TEST(CGTEST,SwitchCaseTest){
    auto SwitchAndCaseOutput = std::make_shared<SwitchNode>();
    auto SACCondition = std::make_shared<ConditionNode>();
    auto SACCID = std::make_shared<IdentifierNode>();
    SACCID->identifier = "x";
    SACCondition->aNode = SACCID;
    SwitchAndCaseOutput->condition = SACCondition;

    auto SACCN1 = std::make_shared<CaseNode>();
    auto SACCN1C = std::make_shared<ConditionNode>();
    auto SACCN1CAN = std::make_shared<IntNode>();
    SACCN1CAN->integer = 1;
    SACCN1C->aNode = SACCN1CAN;
    SACCN1->sucessCondition = SACCN1C;
    auto SACCN1B = std::make_shared<ValueNode>();
    SACCN1B->type = "int";
    SACCN1B->identifier = "X1";
    auto SACCN1BV = std::make_shared<IntNode>();
    SACCN1BV->integer=12;
    SACCN1B->value = SACCN1BV;
    SACCN1->Branch.push_back(SACCN1B);
    SwitchAndCaseOutput->caseBranch.push_back(SACCN1);

    auto SACCN2 = std::make_shared<CaseNode>();
    auto SACCN2C = std::make_shared<ConditionNode>();
    auto SACCN2CAN = std::make_shared<IntNode>();
    SACCN2CAN->integer = 2;
    SACCN2C->aNode = SACCN2CAN;
    SACCN2->sucessCondition = SACCN2C;
    auto SACCN2B = std::make_shared<ValueNode>();
    SACCN2B->type = "float";
    SACCN2B->identifier = "X2";
    auto SACCN2BV = std::make_shared<FloatNode>();
    SACCN2BV->Floating_Point = 5.6;
    SACCN2B->value = SACCN2BV;
    SACCN2->Branch.push_back(SACCN2B);
    SwitchAndCaseOutput->caseBranch.push_back(SACCN2);

    CodeGenerator codeGenerator;
    std::string SACTresault = codeGenerator.generateSwitchCode(SwitchAndCaseOutput);
    EXPECT_EQ(SACTresault,"switch(x){case 1:int X1=12;break;case 2:float X2=5.600000;break;}");
}

TEST(CGTEST,FunctionTest){
    auto FunctionOutput = std::make_shared<FunctionNode>();
    FunctionOutput->type = "int";
    FunctionOutput->identifier = "calc";
    auto FunctionArgumentA = std::make_shared<DeclarationNode>();
    FunctionArgumentA->type = "int";
    FunctionArgumentA->identifier = "a";
    FunctionOutput->arguments.push_back(FunctionArgumentA);
    auto FunctionArgumentB = std::make_shared<DeclarationNode>();
    FunctionArgumentB->type = "int";
    FunctionArgumentB->identifier = "b";
    FunctionOutput->arguments.push_back(FunctionArgumentB);

    auto FunctionBodyFunc1 = std::make_shared<DeclarationNode>();
    FunctionBodyFunc1->type = "int";
    FunctionBodyFunc1->identifier = "c";
    FunctionOutput->body.push_back(FunctionBodyFunc1);

    auto FunctionBodyFunc2 = std::make_shared<ConditionNode>();
    auto FunctionBodyFunc2_3 = std::make_shared<IdentifierNode>();
    FunctionBodyFunc2_3->identifier = "c";
    FunctionBodyFunc2->aNode = FunctionBodyFunc2_3;
    FunctionBodyFunc2->condition = "=";
    auto FunctionBodyFunc2_5 = std::make_shared<ConditionNode>();
    auto FunctionBodyFunc2_5_1 = std::make_shared<IdentifierNode>();
    FunctionBodyFunc2_5_1->identifier = "a";
    FunctionBodyFunc2_5->aNode = FunctionBodyFunc2_5_1;
    FunctionBodyFunc2_5->condition = "+";
    auto FunctionBodyFunc2_5_2 = std::make_shared<IdentifierNode>();
    FunctionBodyFunc2_5_2->identifier = "b";
    FunctionBodyFunc2_5->bNode = FunctionBodyFunc2_5_2;
    FunctionBodyFunc2->bNode = FunctionBodyFunc2_5;
    FunctionOutput->body.push_back(FunctionBodyFunc2);

    auto FunctionBodyFunc3 = std::make_shared<ReturnNode>();
    FunctionBodyFunc3->identifier = "c";
    FunctionOutput->body.push_back(FunctionBodyFunc3);

    CodeGenerator codeGenerator;
    std::string FTresault = codeGenerator.generateFunctionCode(FunctionOutput);
    EXPECT_EQ(FTresault,"int calc(int a,int b){int c;c=a+b;return c;};");
}

TEST(CGTEST,FunctionCallTest){
    auto FunctionCallOutput = std::make_shared<FunctionCallNode>();
    FunctionCallOutput->identifier = "calc";
    auto FunctionCallArg1 = std::make_shared<IntNode>();
    FunctionCallArg1->integer = 12;
    FunctionCallOutput->arguments.push_back(FunctionCallArg1);
    auto FunctionCallArg2 = std::make_shared<IntNode>();
    FunctionCallArg2->integer = 8;
    FunctionCallOutput->arguments.push_back(FunctionCallArg2);
    CodeGenerator codeGenerator;
    std::string FCTresault = codeGenerator.generateFunctionCallCode(FunctionCallOutput);
    EXPECT_EQ(FCTresault,"calc(12,8);");
}