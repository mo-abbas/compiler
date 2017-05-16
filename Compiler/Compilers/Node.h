#pragma once
#include <vector>
#include <string>
#include "Variable.h"
using namespace std;

//enum NodeType
//{
//    typeCon,
//    typeId,
//    typeOpr
//};

enum CaseType
{
    Case,
    Default
};

enum OpType
{
    Plus, Minus, Mult, Div, Mod, BitAnd, BitOr, Less, More, MoreEqu, LessEqu, NotEqu, Equ, And, Or, Not
};

/* ------------------------ Definitions ------------------------*/
class Node
{
public:
    //NodeType type;    // Not sure if it's needed right now
    virtual void execute() = 0;
    virtual ~Node();
};

class VariableNode : public Node
{
public:
    string VariableName;
    VariableNode(char* variableName)
    {
        VariableName = variableName;
    }

    virtual void execute();
};

class IntegerNode : public Node
{
public:
    int Value;
    IntegerNode(int value)
    {
        Value = value;
    }

    virtual void execute();
};

class FloatNode : public Node
{
public:
    float Value;
    FloatNode(float value)
    {
        Value = value;
    }

    virtual void execute();
};

class BooleanNode : public Node
{
public:
    bool Value;
    BooleanNode(bool value)
    {
        Value = value;
    }

    virtual void execute();
};



class StatementListNode : public Node
{
public:
    vector<Node*> Statements;
    StatementListNode(Node* statement)
    {
        Statements.push_back(statement);
    }

    ~StatementListNode()
    {
        for (unsigned int i = 0; i < Statements.size(); i++)
        {
            if(Statements[i]) delete Statements[i];
        }
    }

    StatementListNode* AddStatement(Node* node);
    virtual void execute();
};

class ScopeNode : public Node
{
public:
    StatementListNode* Statements;
    ScopeNode(Node* node)
    {
        Statements = (StatementListNode*)node;
    }

    ~ScopeNode()
    {
        if(Statements) delete Statements;
    }

    virtual void execute();
};

class AssignmentNode : public Node
{
public:
    VariableNode* Variable;
    Node* Assignment;
    AssignmentNode(Node* variable, Node* assignment)
    {
        Variable = (VariableNode*)variable;
        Assignment = assignment;
    }

    ~AssignmentNode()
    {
        if(Variable) delete Variable;
        if(Assignment) delete Assignment;
    }

    virtual void execute();
};

class ExpressionNode : public Node
{
public:
    OpType Operation;
    Node* Left;
    Node* Right;
    ExpressionNode(OpType operation, Node* left, Node* right)
    {
        Operation = operation;
        Left = left;
        Right = right;
    }

    ~ExpressionNode()
    {
        if(Left) delete Left;
        if(Right) delete Right;
    }

    virtual void execute();
};

class UnaryExpressionNode : public Node
{
public:
    OpType Operation;
    Node* Operand;
    UnaryExpressionNode(OpType operation, Node* operand)
    {
        Operation = operation;
        Operand = operand;
    }

    ~UnaryExpressionNode()
    {
        if(Operand) delete Operand;
    }

    virtual void execute();
};

class DeclarationNode : public Node
{
public:
    VariableType Type;
    VariableNode* Variable;
    Node* Expression;
    DeclarationNode(VariableType type, Node* variable, Node* expression = NULL)
    {
        Type = type;
        Variable = (VariableNode*)variable;
        Expression = expression;
    }

    ~DeclarationNode()
    {
        if(Variable) delete Variable;
        if(Expression) delete Expression;
    }

    virtual void execute();
};

class ConstantDeclarationNode : public Node
{
public:
    VariableType Type;
    VariableNode* Variable;
    Node* Expression;
    ConstantDeclarationNode(VariableType type, Node* variable, Node* expression)
    {
        Type = type;
        Variable = (VariableNode*)variable;
        Expression = expression;
    }

    ~ConstantDeclarationNode()
    {
        if(Variable) delete Variable;
    }

    virtual void execute();
};

class CaseNode : public Node
{
public:
    CaseType Type;
    Node* CaseValue;
    Node* Scope;
    CaseNode(Node* constant, Node* scope)  // for the Case
    {
        Type = Case;
        CaseValue = constant;
        Scope = scope;
    }

    CaseNode(Node* scope)   // for the default
    {
        Type = Default;
        Scope = scope;
    }

    ~CaseNode()
    {
        if(CaseValue) delete CaseValue;
        if(Scope) delete Scope;
    }

    virtual void execute();
};

class CaseListNode : public Node
{
public:
    vector<CaseNode*> children;
    ~CaseListNode()
    {
        for (unsigned int i = 0; i < children.size(); i++)
        {
            if(children[i]) delete children[i];
        }
    }

    CaseListNode* AddCase(Node* caseNode);
    virtual void execute();
};

class SwitchNode : public Node
{
public:
    Node* SwitchExpression;
    CaseListNode* CaseList;
    SwitchNode(Node* expression, Node* caseList)
    {
        SwitchExpression = expression;
        CaseList = (CaseListNode*)caseList;
    }

    ~SwitchNode()
    {
        if (SwitchExpression) delete SwitchExpression;
        if (CaseList) delete CaseList;
    }

    virtual void execute();
};


class WhileNode : public Node
{
public:
    Node* Condition;
    Node* Scope;
    WhileNode(Node* expression, Node* scope)
    {
        Condition = expression;
        Scope = scope;
    }

    ~WhileNode()
    {
        if(Condition) delete Condition;
        if(Scope) delete Scope;
    }

    virtual void execute();
};

class DoWhileNode : public Node
{
public:
    Node* Condition;
    Node* Scope;
    DoWhileNode(Node* expression, Node* scope)
    {
        Condition = expression;
        Scope = scope;
    }

    ~DoWhileNode()
    {
        if(Condition) delete Condition;
        if(Scope) delete Scope;
    }

    virtual void execute();
};

class ForNode : public Node
{
public:
    Node* Initialize;
    Node* Condition;
    Node* Increment;
    Node* Scope;

    ForNode(Node* init, Node* condition, Node* increment, Node* scope)
    {
        Initialize = init;
        Condition = condition;
        Increment = increment;
        Scope = scope;
    }

    ~ForNode()
    {
        if(Initialize) delete Initialize;
        if(Condition) delete Condition;
        if(Increment) delete Increment;
        if(Scope) delete Scope;
    }

    virtual void execute();
};

class ConditionNode : public Node
{
public:
    Node* Condition;
    Node* TrueScope;
    Node* FalseScope;
    ConditionNode(Node* expression, Node* trueScope, Node* falseScope = NULL)
    {
        Condition = expression;
        TrueScope = trueScope;
        FalseScope = falseScope;
    }

    ~ConditionNode()
    {
        if(Condition) delete Condition;
        if(TrueScope) delete TrueScope;
        if(FalseScope) delete FalseScope;
    }

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