#include "Node.h"
#include "SymbolTable.h"

int Node::MaxScope = 0;
int Node::MaxRegister = 0;
int Node::MaxLabel = 0;
SymbolTable table;

Result VariableNode::Execute(ParentInfo info, bool checkInit)
{

    Variable* variable = table.GetVariable(VariableName, info.CurrentScope);
    if (variable == NULL)
    {
        PrintError("Variable " + VariableName + " is not defined");
        return Result("'" + VariableName + "'");
    }

    if (checkInit)
    {
        if (!variable->Initialized)
        {
            PrintWarning("Variable " + VariableName + " is not initialized");
        }
    }
    else
    {
        // if we don't check for the initialization then it is an assignment
        if (variable->Constant)
        {
            PrintError("Variable " + VariableName + " is constant and cannot be changed");
        }

        variable->Initialized = true;
    }

    return Result("'" + VariableName + "'", variable->Type);
}

Result VariableNode::Execute(ParentInfo info)
{
    return Execute(info, true);
}

Result VariableNode::Declare(ParentInfo info, VariableType type, bool initialized, bool constant)
{
    if (table.ContainsVariable(VariableName, info.CurrentScope))
    {
        PrintError("Variable " + VariableName + " is already defined");
        return Result('"' + VariableName + '"');
    }

    if (table.HasAccessToVariable(VariableName, info.CurrentScope))
    {
        PrintWarning("Variable " + VariableName + " is redefined");
    }

    table.AddVariable(VariableName, info.CurrentScope, type, initialized, constant);
    return Result("'" + VariableName + "'", type);
}

Result IntegerNode::Execute(ParentInfo info)
{
    return Result(to_string(Value), Integer);
}

Result FloatNode::Execute(ParentInfo info)
{
    return Result(to_string(Value), Float);
}

Result BooleanNode::Execute(ParentInfo info)
{
    return Result(to_string(Value), Boolean);
}

StatementListNode* StatementListNode::AddStatement(Node* node)
{
    Statements.push_back(node);
    return this;
}

Result StatementListNode::Execute(ParentInfo info)
{
    int newScope = MaxScope++;
    table.AddScope(newScope, info.CurrentScope);

    ParentInfo newInfo(info);
    newInfo.CurrentScope = newScope;

    for (unsigned int i = 0; i < Statements.size(); i++)
    {
        if (Statements[i])
        {
            Statements[i]->Execute(newInfo);
        }
    }

    return Result();
}

// TODO: remove this
Result ScopeNode::Execute(ParentInfo info)
{
    return Statements->Execute(info);
}

Result AssignmentNode::Execute(ParentInfo info)
{
    Result variableResult = Variable->Execute(info, false);
    Result assignmentResult = Assignment->Execute(info);
    if (assignmentResult.Type != Unknown && assignmentResult.Type != variableResult.Type)
    {
        PrintWarning("Types mismatch, expecting " + VariableTypeName[variableResult.Type] + " and found " + VariableTypeName[assignmentResult.Type]);
    }

    Out << "MOV " << variableResult.Value << ", " << assignmentResult.Value << endl;
    return variableResult;
}

Result ExpressionNode::Execute(ParentInfo info)
{
    Result leftResult = Left->Execute(info);
    Result rightResult = Right->Execute(info);
    string resultRegister = MakeRegister();

    switch (Operation)
    {
    case Plus:
        Out << "ADD " << resultRegister << ", " << leftResult.Value << ", " << rightResult.Value << endl;
        break;
    case Minus:
        Out << "SUB " << resultRegister << ", " << leftResult.Value << ", " << rightResult.Value << endl;
        break;
    case Mult:
        Out << "MUL " << resultRegister << ", " << leftResult.Value << ", " << rightResult.Value << endl;
        break;
    case Div:
        Out << "DIV " << resultRegister << ", " << leftResult.Value << ", " << rightResult.Value << endl;
        break;
    case Mod:
        Out << "MOD " << resultRegister << ", " << leftResult.Value << ", " << rightResult.Value << endl;
        break;
    case BitAnd:
        Out << "ANDB " << resultRegister << ", " << leftResult.Value << ", " << rightResult.Value << endl;
        break;
    case BitOr:
        Out << "ORB " << resultRegister << ", " << leftResult.Value << ", " << rightResult.Value << endl;
        break;
    case More:
        Out << "GT " << resultRegister << ", " << leftResult.Value << ", " << rightResult.Value << endl;
        break;
    case MoreEqu:
        Out << "GTE " << resultRegister << ", " << leftResult.Value << ", " << rightResult.Value << endl;
        break;
    case Less:
        Out << "LT " << resultRegister << ", " << leftResult.Value << ", " << rightResult.Value << endl;
        break;
    case LessEqu:
        Out << "LTE " << resultRegister << ", " << leftResult.Value << ", " << rightResult.Value << endl;
        break;
    case NotEqu:
        Out << "NEQ " << resultRegister << ", " << leftResult.Value << ", " << rightResult.Value << endl;
        break;
    case Equ:
        Out << "EQ " << resultRegister << ", " << leftResult.Value << ", " << rightResult.Value << endl;
        break;
    case And:
        Out << "AND " << resultRegister << ", " << leftResult.Value << ", " << rightResult.Value << endl;
        break;
    case Or:
        Out << "OR " << resultRegister << ", " << leftResult.Value << ", " << rightResult.Value << endl;
        break;
    }

    return Result(resultRegister, GetUnionType(leftResult.Type, rightResult.Type));
}

Result UnaryExpressionNode::Execute(ParentInfo info)
{
    Result operandResult = Operand->Execute(info);
    string resultRegister = MakeRegister();

    switch (Operation)
    {
    case Minus:
        Out << "NEG " << resultRegister << ", " << operandResult.Value << endl;
        break;
    case Not:
        Out << "NOT " << resultRegister << ", " << operandResult.Value << endl;
        break;
    }

    return Result(resultRegister, operandResult.Type);
}

Result DeclarationNode::Execute(ParentInfo info)
{
    bool initialize = Expression != NULL;
    Result variableResult = Variable->Declare(info, Type, initialize);

    Out << "DEF " << VariableCode[Type] << ", " << variableResult.Value << endl;

    if (Expression)
    {
        Result expressionResult = Expression->Execute(info);
        if (expressionResult.Type != Unknown && expressionResult.Type != Type)
        {
            PrintWarning("Types mismatch, expecting " + VariableTypeName[Type] + " and found " + VariableTypeName[expressionResult.Type]);
        }

        Out << "MOV " << variableResult.Value << ", " << expressionResult.Value << endl;
    }

    return Result();
}

Result ConstantDeclarationNode::Execute(ParentInfo info)
{
    Result variableResult = Variable->Declare(info, Type, true, true);
    Result expressionResult = Expression->Execute(info);

    if (expressionResult.Type != Unknown && expressionResult.Type != Type)
    {
        PrintWarning("Types mismatch, expecting " + VariableTypeName[Type] + " and found " + VariableTypeName[expressionResult.Type]);
    }

    Out << "DEFC " << VariableCode[Type] << ", " << variableResult.Value << ", " << expressionResult.Value << endl;

    return Result();
}

Result CaseNode::Execute(ParentInfo info)
{
    if (Type == Case)
    {
        Result constant = CaseValue->Execute(info);
        if (info.SwitchExpressionType != Unknown && constant.Type != info.SwitchExpressionType)
        {
            PrintError("switch condition and constant type mismatch");
        }
    }

    Out << Label << ":" << endl;

    if (Scope)
    {
        return Scope->Execute(info);
    }

    return Result();
}

CaseListNode* CaseListNode::AddCase(Node* node)
{
    children.push_back((CaseNode*)node);
    if (LineNumber == -1)
    {
        LineNumber = node->LineNumber;
    }
    else
    {
        LineNumber = min(LineNumber, node->LineNumber);
    }

    return this;
}

vector<pair<Node*, string>> CaseListNode::GetLabels()
{
    vector<pair<Node*, string>> constLabelPairs;

    for (unsigned int i = 0; i < children.size(); i++)
    {
        string label = MakeLabel();
        children[i]->Label = label;
        constLabelPairs.push_back(make_pair(children[i]->CaseValue, label));
    }

    return constLabelPairs;
}

Result CaseListNode::Execute(ParentInfo info)
{
    int defaultCount = 0;

    for (unsigned int i = 0; i < children.size(); i++)
    {
        if (children[i]->Type == Default && ++defaultCount > 1)
        {
            PrintError("switch cannot have more than one default");
        }

        children[i]->Execute(info);
    }

    return Result();
}

Result SwitchNode::Execute(ParentInfo info)
{
    vector<pair<Node*, string>> childrenLabels = CaseList->GetLabels();
    Result expressionResult = SwitchExpression->Execute(info);

    string label = MakeLabel();
    string defaultLabel = label;
    string comparisonRegister = MakeRegister();

    for (unsigned int i = 0; i < childrenLabels.size(); i++)
    {
        if (childrenLabels[i].first)
        {
            Result constant = childrenLabels[i].first->Execute(info);

            Out << "EQ " << comparisonRegister << ", " << expressionResult.Value << ", " << constant.Value << endl;
            Out << "JNZ " << comparisonRegister << ", " << childrenLabels[i].second << endl;
        }
        else
        {
            defaultLabel = childrenLabels[i].second;
        }
    }

    Out << "JMP " << defaultLabel << endl;

    info.BreakLabel = label;
    info.SwitchExpressionType = expressionResult.Type;
    CaseList->Execute(info);

    Out << label << ":" << endl;

    return Result();
}

Result WhileNode::Execute(ParentInfo info)
{
    string startLabel = MakeLabel();
    string endLabel = MakeLabel();

    Out << startLabel << ":" << endl;
    Result conditionResult = Condition->Execute(info);
    Out << "JZ " << conditionResult.Value << ", " << endLabel << endl;

    info.BreakLabel = endLabel;
    info.ContinueLabel = startLabel;
    if (Scope)
    {
        Scope->Execute(info);
    }

    Out << "JMP " << startLabel << endl;
    Out << endLabel << ":" << endl;

    return Result();
}

Result DoWhileNode::Execute(ParentInfo info)
{
    string startLabel = MakeLabel();
    string conditionLabel = MakeLabel();
    string endLabel = MakeLabel();

    Out << startLabel << ":" << endl;

    info.BreakLabel = endLabel;
    info.ContinueLabel = conditionLabel;
    if (Scope)
    {
        Scope->Execute(info);
    }

    Out << conditionLabel << ":" << endl;

    Result conditionResult = Condition->Execute(info);
    Out << "JNZ " << conditionResult.Value << ", " << startLabel << endl;
    Out << endLabel << ":" << endl;

    return Result();
}

Result ForNode::Execute(ParentInfo info)
{
    if (Initialize)
    {
        Initialize->Execute(info);
    }

    string startLabel = MakeLabel();
    string continueLabel = MakeLabel();
    string endLabel = MakeLabel();

    Out << startLabel << ":" << endl;
    if (Condition)
    {
        Result conditionResult = Condition->Execute(info);
        Out << "JZ " << conditionResult.Value << ", " << endLabel << endl;
    }

    if (Scope)
    {
        ParentInfo newInfo(info);
        newInfo.BreakLabel = endLabel;
        newInfo.ContinueLabel = continueLabel;
        Scope->Execute(newInfo);
    }

    Out << continueLabel << ":" << endl;
    if (Increment)
    {
        Increment->Execute(info);
    }

    Out << "JMP " << startLabel << endl;
    Out << endLabel << ":" << endl;

    return Result();
}

Result ConditionNode::Execute(ParentInfo info)
{
    Result conditionResult = Condition->Execute(info);
    string elseLabel = MakeLabel();

    Out << "JZ " << conditionResult.Value << ", " << elseLabel << endl;
    if (TrueScope)
    {
        TrueScope->Execute(info);
    }


    if (FalseScope)
    {
        string endLabel = MakeLabel();
        Out << "JMP " << endLabel << endl;

        Out << elseLabel << ":" << endl;
        FalseScope->Execute(info);
        Out << endLabel << ":" << endl;
    }
    else
    {
        Out << elseLabel << ":" << endl;
    }

    return Result();
}

Result BreakNode::Execute(ParentInfo info)
{
    if (info.BreakLabel == "")
    {
        PrintError("A break statement can only appear in a loop or a switch statement");
    }

    Out << "JMP " << info.BreakLabel << endl;
    return Result();
}

Result ContinueNode::Execute(ParentInfo info)
{
    if (info.ContinueLabel == "")
    {
        PrintError("A continue statement can only appear in a loop");
    }

    Out << "JMP " << info.ContinueLabel << endl;
    return Result();
}