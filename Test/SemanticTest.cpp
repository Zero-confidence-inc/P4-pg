#include "gtest/gtest.h"
#include "Parser.h"
#include "Semantic.h"

SemanticAnalyser semanticanalyser;

TEST(KowalskiTest, KowalskiFloat) {
    std::shared_ptr<FloatNode> node = std::make_shared<FloatNode>();
    node->Floating_Point = 1.2;
    EXPECT_FLOAT_EQ(1.2, node->Floating_Point);
}

TEST(KowalskiTest, KowalskiInt) {
    std::shared_ptr<IntNode> node = std::make_shared<IntNode>();
    node->integer = 1;
    EXPECT_EQ(1,node->integer);
}

TEST(KowalskiTest, KowalskiReturn) {
    std::shared_ptr<ReturnNode> node = std::make_shared<ReturnNode>();
    node->returning = "return";
    node->identifier = "xD";
    EXPECT_EQ("return",node->returning);
    EXPECT_EQ("xD",node->identifier);
}

TEST(KowalskiTest, KowalskiChar) {
    std::shared_ptr<CharNode> node = std::make_shared<CharNode>();
    node->character = "r";
    EXPECT_EQ("r",node->character);
}

TEST(KowalskiTest,KowalskiKondi){
    auto KondiNode = std::make_shared<ConditionNode>();
    auto aNode = std::make_shared<StringNode>();
    auto bNode = std::make_shared<StringNode>();
    KondiNode->aNode = aNode;
    KondiNode->bNode = bNode;
    EXPECT_NO_THROW(semanticanalyser.kowalskiKondi(KondiNode));

}

TEST(KowalskiTest, KowalskiWhile) {
    auto node = std::make_shared<WhileNode>();
    auto Anode = std::make_shared<IntNode>();
    auto Bnode = std::make_shared<IntNode>();
    Anode->integer = 4;
    Bnode->integer = 3;
    node->condition = std::make_shared<ConditionNode>();
    node->condition->aNode = Anode;
    node->condition->condition = "==";
    node->condition->bNode = Bnode;
    auto body = std::make_shared<DeclarationNode>(); //lazy why to write it
    body->identifier = "abc";
    body->type = "int";
    node->body.push_back(body);
    EXPECT_NO_THROW(semanticanalyser.kowalskiWhile(node));
}

TEST(KowalskiTest,KowalskiFor){
    auto node = std::make_shared<ForLoopNode>();
    auto DeclartionNode = std::make_shared<ValueNode>();
    DeclartionNode->type = "int";
    DeclartionNode->identifier = "abc";
    auto thyInt = std::make_shared<IntNode>();
    thyInt->integer = 0;
    node->declaration = DeclartionNode;
    auto Condi = std::make_shared<ConditionNode>();
    auto expression = std::make_shared<ConditionNode>();
    Condi->condition = "==";
    auto CondiA = std::make_shared<IdentifierNode>();
    CondiA->identifier = "abc";
    Condi->aNode = CondiA;
    Condi->bNode = std::make_shared<IntNode>();
    node->condition = Condi;
    expression->aNode = CondiA;
    expression->condition = "++";
    node->expression =expression;

    EXPECT_NO_THROW(semanticanalyser.kowalskiFor(node));

}

TEST(KowalskiTest,KowalskiIf){
    auto Node = std::make_shared<IfNode>();
    auto Condi = std::make_shared<ConditionNode>();
    Condi->aNode = std::make_shared<IntNode>();
    //Node->EXPECT_NO_THROW();
}

TEST(KowalskiTest,KowalskiStruct){
    auto node = std::make_shared<StructNode>();
    node->identifier="abc";
    node->type = "struct";
    auto decl = std::make_shared<DeclarationNode>();
    decl->type="int";decl->identifier="abc";
    auto decl2 = std::make_shared<DeclarationNode>();
    decl->type="string";decl->identifier="def";
    node->body.push_back(decl);
    node->body.push_back(decl2);
    EXPECT_ANY_THROW(semanticanalyser.kowalskiStruct(node));
}

TEST(KowalskiTest,KowalskiValue){
    auto node = std::make_shared<ValueNode>();
    node->identifier = "xd";
    node->type = "bool";
    node->value = std::make_shared<BoolNode>();
    //EXPECT_NO_THROW(semanticanalyser.kowalskiValue) den er ikke lavet semantics EW
}

TEST(KowalskiTest,KowalskiFunction_Creation_Call){

    auto node = std::make_shared<FunctionNode>();
    node->type = "bool";
    node->identifier = "hardcock";
    auto clara = std::make_shared<DeclarationNode>();
    clara->identifier = "soft";
    clara->type = "bool";
    node->arguments.push_back(clara);
    auto condi = std::make_shared<ConditionNode>();
    condi->condition = "=";
    condi->bNode = std::make_shared<BoolNode>();
    auto id =std::make_shared<IdentifierNode>();
    id->identifier = "hardcock";
    condi->aNode = id;
    node->body.push_back(condi);
    std::vector<std::shared_ptr<ASTNode>> contents;
    contents.push_back(node);
    //this is creation function after this i will add a function call to call the function we made to contents

    auto funCall = std::make_shared<FunctionCallNode>();
    funCall->identifier = "hardcock";
    funCall->arguments.push_back(std::make_shared<BoolNode>());
    contents.push_back(funCall);

    EXPECT_NO_THROW(semanticanalyser.kowalski(contents));
}

TEST (KowalskiTest,Random_N_ValueDeclartions){
    auto random = std::make_shared<RandomNode>();
    auto Value = std::make_shared<ValueNode>();
    Value->type = "int";
    Value->identifier = "NormalInt";
    auto int12 = std::make_shared<IntNode>();
    int12->integer = 12;
    Value->value = int12;
    random->identifier = "unknownIntSpooky";
    random->type = "int";
    random->RandomIntRange.push_back(0);
    random->RandomIntRange.push_back(12);



    std::vector<std::shared_ptr<ASTNode>> contents;
    contents.push_back(random);
    contents.push_back(Value);
    EXPECT_NO_THROW(semanticanalyser.kowalski(contents));

}



