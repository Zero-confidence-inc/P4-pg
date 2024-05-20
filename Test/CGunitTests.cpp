#include "gtest/gtest.h"
#include "parser.h"
#include "CodeGenerator.h"
#include <string>

TEST(CGTEST,DeclarationTest){
    auto DeclarationTestNode = std::make_shared<DeclarationNode>();
    DeclarationTestNode->type = "int";
    DeclarationTestNode->identifier = "x";
    CodeGenerator codeGenerator;
    std::string DTresault = codeGenerator.generateDeclartionCode(DeclarationTestNode);
    EXPECT_EQ(DTresault,"int x;");
}