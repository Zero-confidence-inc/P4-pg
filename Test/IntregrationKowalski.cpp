#include "gtest/gtest.h"
#include "Parser.h"
#include "Semantic.h"

Kowalski kowalski2;

TEST(KowalskiTest, KowalskiIntregrationToSocitetyTest){
    std::vector<std::shared_ptr<ASTNode>> root;
    auto func = std::make_shared<FunctionNode>();
    func->type = "bool";
    func->identifier = "cryptoMine";
    auto argument1 = std::make_shared<DeclarationNode>();
    argument1->identifier = "hard";
    argument1->type = "bool";
    auto argument2 = std::make_shared<DeclarationNode>();
    argument2->type = "string";
    argument2->identifier = "vString";
    func->arguments.push_back(argument1);
    func->arguments.push_back(argument2);
    auto WHILE = std::make_shared<WhileNode>();
    auto whileCondi = std::make_shared<ConditionNode>();
    auto id1 = std::make_shared<IdentifierNode>();
    id1->identifier = "hard";
    whileCondi->aNode = id1;
    WHILE->condition = whileCondi;
    auto ifN = std::make_shared<IfNode>();
    auto ifCondi = std::make_shared<ConditionNode>();
    ifCondi->condition="==";
    auto id2 = std::make_shared<IdentifierNode>();
    id2->identifier = "vString";
    auto aNode = id2;
    ifN->condition = ifCondi;
    ifCondi->aNode = id2;
    ifCondi->bNode = std::make_shared<StringNode>();
    auto forN = std::make_shared<ForLoopNode>();
    auto id3 = std::make_shared<IdentifierNode>();
    id3->identifier = "i";
    auto ForCondi = std::make_shared<ConditionNode>();
    ForCondi->aNode = id3;
    ForCondi->bNode = std::make_shared<IntNode>();
    forN->condition = ForCondi;
    auto forEX = std::make_shared<ConditionNode>();
    forEX->aNode = id3;
    forEX->condition = "++";
    forN->expression = forEX;
    auto DDDD = std::make_shared<ValueNode>();
    DDDD->identifier = "i";
    DDDD->type = "float";
    DDDD->value = std::make_shared<FloatNode>();
    forN->declaration = DDDD;
    auto funCall = std::make_shared<FunctionCallNode>();
    funCall->identifier = "cryptoMine";
    funCall->arguments.push_back(std::make_shared<BoolNode>());
    funCall->arguments.push_back(id2);


    forN->body.push_back(funCall);
    ifN->body.push_back(forN);
    WHILE->body.push_back(ifN);
    func->body.push_back(WHILE);
    root.push_back(func);
    EXPECT_NO_THROW(kowalski2.Analyse(root));

}