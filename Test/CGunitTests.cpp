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
    EXPECT_EQ(CTresault,'char x=A');
}