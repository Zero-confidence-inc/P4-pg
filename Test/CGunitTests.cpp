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
TEST(CGTEST,ValueTest){
    auto VTN_basicValue = std::make_shared<ValueNode>();
    VTN_basicValue->type = "int";
    VTN_basicValue->identifier = "x";
    auto ITN_basicValue = std::make_shared<IntNode>();
    ITN_basicValue->integer = 12;
    VTN_basicValue->value = ITN_basicValue;
    EXPECT_EQ(VTN_basicValue,"int x = 12;");
}