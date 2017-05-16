#pragma once
#include <vector>
#include "Variable.h"
using namespace std;

enum NodeType
{
    typeCon,
    typeId,
    typeOpr
};

enum CaseType
{
    Case,
    Default
};

enum OpType
{
    Plus, Minus, Mult, Div, Mod, BitAnd, BitOr, Less, More, MoreEqu, LessEqu, NotEqu, Equ, And, Or, Not
};

class Node
{
public:
    NodeType type;
    virtual void execute() = 0;
};

class VariableNode : public Node
{
public:
    VariableNode(char* variableName);
    virtual void execute();
};

class IntegerNode : public Node
{
public:
    IntegerNode(int value);
    virtual void execute();
};

class FloatNode : public Node
{
public:
    FloatNode(float value);
    virtual void execute();
};

class BooleanNode : public Node
{
public:
    BooleanNode(bool value);
    virtual void execute();
};

class ScopeNode : public Node
{
public:
    ScopeNode(Node* node);
    virtual void execute();
};

class StatementListNode : public Node
{
public:
    StatementListNode(Node* node);
    StatementListNode* AddStatement(Node* node);
    virtual void execute();
};

class AssignmentNode : public Node
{
public:
    AssignmentNode(Node* variable, Node* assignment);
    virtual void execute();
};

class ExpressionNode : public Node
{
public:
    ExpressionNode(OpType operation, Node* left, Node* right);
    virtual void execute();
};

class UnaryExpressionNode : public Node
{
public:
    UnaryExpressionNode(OpType operation, Node* operand);
    virtual void execute();
};

class DeclarationNode : public Node
{
public:
    DeclarationNode(VariableType type, Node* variable, Node* expression = NULL);
    virtual void execute();
};

class ConstantDeclarationNode : public Node
{
public:
    ConstantDeclarationNode(VariableType type, Node* variable, Node* expression);
    virtual void execute();
};

class SwitchNode : public Node
{
public:
    SwitchNode(Node* expression, Node* caseList);
    virtual void execute();
};

class CaseNode : public Node
{
public:
    CaseType Type;
    CaseNode(Node* constant, Node* scope);  // for the Case
    CaseNode(Node* scope);                  // for the default
    virtual void execute();
};

class CaseListNode : public Node
{
public:
    vector<CaseNode> children;

    CaseListNode();
    CaseListNode* AddCase(Node* caseNode);
    virtual void execute();
};

class WhileNode : public Node
{
public:
    WhileNode(Node* expression, Node* scope);
    virtual void execute();
};

class DoWhileNode : public Node
{
public:
    DoWhileNode(Node* expression, Node* scope);
    virtual void execute();
};

class ForNode : public Node
{
public:
    ForNode(Node* init, Node* condition, Node* increment, Node* scope);
    virtual void execute();
};

class ConditionNode : public Node
{
public:
    ConditionNode(Node* expression, Node* trueScope, Node* falseScope = NULL);
    virtual void execute();
};

class BreakNode : public Node
{
public:
    virtual void execute();
};

class ContinueNode : public Node
{
public:
    virtual void execute();
};