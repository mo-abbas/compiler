#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

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
    Plus, Minus, Mult, Div, Mod, BitAnd, BitOr, More, MoreEqu, Less, LessEqu, NotEqu, Equ, And, Or, Not
};

/* ------------------------ Definitions ------------------------*/
// class that contains the execution results
class Result
{
public:
    string Value;
    VariableType Type;
    Result(string value = "", VariableType type = Unknown)
    {
        Value = value;
        Type = type;
    }
};

class ParentInfo
{
public:
    VariableType SwitchExpressionType;
    string BreakLabel;
    string ContinueLabel;
    int CurrentScope;
};

class Node
{
public:
    static int MaxScope;
    static int MaxRegister;
    static int MaxLabel;
    static ostream* Out;
    static ostream* ErrorOut;
    static ostream* WarningOut;

    //NodeType type;    // Not sure if it's needed right now
    int  LineNumber;
    Node(int lineNumber = -1)
    {
        LineNumber = lineNumber;
    }

    virtual ~Node(){ }

    virtual Result Execute(ParentInfo info) = 0;

    void Print(string message)
    {
        (*Out) << message << endl;
    }

    void PrintError(string message)
    {
        (*ErrorOut) << "ERROR" << (LineNumber != -1 ? " line " + to_string(LineNumber) : "") << ": " << message << endl;
    }

    void PrintWarning(string message)
    {
        (*WarningOut) << "WARNING" << (LineNumber != -1 ? " line " + to_string(LineNumber) : "") << ": " << message << endl;
    }

    string MakeRegister()
    {
        return "R" + to_string(MaxRegister++);
    }

    string MakeLabel()
    {
        return "L_" + to_string(MaxLabel++);
    }

    VariableType GetUnionType(VariableType left, VariableType right)
    {
        return max(left, right);
    }
};

class VariableNode : public Node
{
public:
    string VariableName;
    VariableNode(int lineNumber, char* variableName) : Node(lineNumber)
    {
        VariableName = variableName;
        delete variableName;
    }

    virtual Result Execute(ParentInfo info);
    Result Execute(ParentInfo info, bool checkInit);
    Result Declare(ParentInfo info, VariableType type, bool initialized, bool constant = false);
};

class IntegerNode : public Node
{
public:
    int Value;
    IntegerNode(int value)
    {
        Value = value;
    }

    virtual Result Execute(ParentInfo info);
};

class FloatNode : public Node
{
public:
    float Value;
    FloatNode(float value)
    {
        Value = value;
    }

    virtual Result Execute(ParentInfo info);
};

class BooleanNode : public Node
{
public:
    bool Value;
    BooleanNode(bool value)
    {
        Value = value;
    }

    virtual Result Execute(ParentInfo info);
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
            if (Statements[i]) delete Statements[i];
        }
    }

    StatementListNode* AddStatement(Node* node);
    virtual Result Execute(ParentInfo info);
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
        if (Statements) delete Statements;
    }

    virtual Result Execute(ParentInfo info);
};

class AssignmentNode : public Node
{
public:
    VariableNode* Variable;
    Node* Assignment;
    AssignmentNode(int lineNumber, Node* variable, Node* assignment) : Node(lineNumber)
    {
        Variable = (VariableNode*)variable;
        Assignment = assignment;
    }

    ~AssignmentNode()
    {
        if (Variable) delete Variable;
        if (Assignment) delete Assignment;
    }

    virtual Result Execute(ParentInfo info);
};

class ExpressionNode : public Node
{
public:
    OpType Operation;
    Node* Left;
    Node* Right;
    ExpressionNode(int lineNumber, OpType operation, Node* left, Node* right) : Node(lineNumber)
    {
        Operation = operation;
        Left = left;
        Right = right;
    }

    ~ExpressionNode()
    {
        if (Left) delete Left;
        if (Right) delete Right;
    }

    virtual Result Execute(ParentInfo info);
};

class UnaryExpressionNode : public Node
{
public:
    OpType Operation;
    Node* Operand;
    UnaryExpressionNode(int lineNumber, OpType operation, Node* operand) : Node(lineNumber)
    {
        Operation = operation;
        Operand = operand;
    }

    ~UnaryExpressionNode()
    {
        if (Operand) delete Operand;
    }

    virtual Result Execute(ParentInfo info);
};

class DeclarationNode : public Node
{
public:
    VariableType Type;
    VariableNode* Variable;
    Node* Expression;
    DeclarationNode(int lineNumber, VariableType type, Node* variable, Node* expression = NULL) : Node(lineNumber)
    {
        Type = type;
        Variable = (VariableNode*)variable;
        Expression = expression;
    }

    ~DeclarationNode()
    {
        if (Variable) delete Variable;
        if (Expression) delete Expression;
    }

    virtual Result Execute(ParentInfo info);
};

class ConstantDeclarationNode : public Node
{
public:
    VariableType Type;
    VariableNode* Variable;
    Node* Expression;
    ConstantDeclarationNode(int lineNumber, VariableType type, Node* variable, Node* expression) : Node(lineNumber)
    {
        Type = type;
        Variable = (VariableNode*)variable;
        Expression = expression;
    }

    ~ConstantDeclarationNode()
    {
        if (Variable) delete Variable;
    }

    virtual Result Execute(ParentInfo info);
};

class CaseNode : public Node
{
public:
    CaseType Type;
    Node* CaseValue;
    Node* Scope;
    string Label;
    CaseNode(int lineNumber, Node* constant, Node* scope) : Node(lineNumber) // for the Case
    {
        Type = Case;
        CaseValue = constant;
        Scope = scope;
    }

    CaseNode(int lineNumber, Node* scope) : Node(lineNumber)  // for the default
    {
        Type = Default;
        Scope = scope;
    }

    ~CaseNode()
    {
        if (CaseValue) delete CaseValue;
        if (Scope) delete Scope;
    }

    virtual Result Execute(ParentInfo info);
};

class CaseListNode : public Node
{
public:
    vector<CaseNode*> children;
    CaseListNode() : Node(-1)
    {
    }

    ~CaseListNode()
    {
        for (unsigned int i = 0; i < children.size(); i++)
        {
            if (children[i]) delete children[i];
        }
    }

    CaseListNode* AddCase(Node* caseNode);
    vector<pair<Node*, string>> GetLabels();
    virtual Result Execute(ParentInfo info);
};

class SwitchNode : public Node
{
public:
    Node* SwitchExpression;
    CaseListNode* CaseList;
    SwitchNode(int lineNumber, Node* expression, Node* caseList) : Node(lineNumber)
    {
        SwitchExpression = expression;
        CaseList = (CaseListNode*)caseList;
    }

    ~SwitchNode()
    {
        if (SwitchExpression) delete SwitchExpression;
        if (CaseList) delete CaseList;
    }

    virtual Result Execute(ParentInfo info);
};

class WhileNode : public Node
{
public:
    Node* Condition;
    Node* Scope;
    WhileNode(int lineNumber, Node* expression, Node* scope) : Node(lineNumber)
    {
        Condition = expression;
        Scope = scope;
    }

    ~WhileNode()
    {
        if (Condition) delete Condition;
        if (Scope) delete Scope;
    }

    virtual Result Execute(ParentInfo info);
};

class DoWhileNode : public Node
{
public:
    Node* Condition;
    Node* Scope;
    DoWhileNode(int lineNumber, Node* expression, Node* scope) : Node(lineNumber)
    {
        Condition = expression;
        Scope = scope;
    }

    ~DoWhileNode()
    {
        if (Condition) delete Condition;
        if (Scope) delete Scope;
    }

    virtual Result Execute(ParentInfo info);
};

class ForNode : public Node
{
public:
    Node* Initialize;
    Node* Condition;
    Node* Increment;
    Node* Scope;
    ForNode(int lineNumber, Node* init, Node* condition, Node* increment, Node* scope) : Node(lineNumber)
    {
        Initialize = init;
        Condition = condition;
        Increment = increment;
        Scope = scope;
    }

    ~ForNode()
    {
        if (Initialize) delete Initialize;
        if (Condition) delete Condition;
        if (Increment) delete Increment;
        if (Scope) delete Scope;
    }

    virtual Result Execute(ParentInfo info);
};

class ConditionNode : public Node
{
public:
    Node* Condition;
    Node* TrueScope;
    Node* FalseScope;
    ConditionNode(int lineNumber, Node* expression, Node* trueScope, Node* falseScope = NULL) : Node(lineNumber)
    {
        Condition = expression;
        TrueScope = trueScope;
        FalseScope = falseScope;
    }

    ~ConditionNode()
    {
        if (Condition) delete Condition;
        if (TrueScope) delete TrueScope;
        if (FalseScope) delete FalseScope;
    }

    virtual Result Execute(ParentInfo info);
};

class BreakNode : public Node
{
public:
    BreakNode(int lineNumber) : Node(lineNumber)
    {
    }

    virtual Result Execute(ParentInfo info);
};

class ContinueNode : public Node
{
public:
    ContinueNode(int lineNumber) : Node(lineNumber)
    {
    }

    virtual Result Execute(ParentInfo info);
};