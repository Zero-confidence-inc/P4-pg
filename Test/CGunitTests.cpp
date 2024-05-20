#include "gtest/gtest.h"
#include "parser.h"
#include "CodeGenerator.h"
#include <string>

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


    auto CondiNode = std::make_shared<ConditionNode>();
    auto aNode = std::make_shared<IdentifierNode>();
    aNode->identifier = "abc";
    CondiNode->aNode = aNode;
    CondiNode->condition = "+="

    auto CondiNode2 = std::make_shared<ConditionNode>();
    auto bNode = std::make_shared<FloatNode>();
    bNode->const_Float = "5";
    CondiNode->aNode = aNode;
    CondiNode->condition = "+"
    auto cNode = std::make_shared<IntNode>();
    bNode->integer = "10";
    CondiNode->bNode = CondiNode2;

    std::string CondiResault = codeGenerator.generateValueCode(VTN_basicValueBool);
    EXPECT_EQ(CondiResault,"abc+=5+10;");
}

