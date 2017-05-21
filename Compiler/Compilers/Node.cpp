#include "Node.h"

int Node::MaxScope = 0;
int Node::MaxRegister = 0;
int Node::MaxLabel = 0;
SymbolTable Node::Table = SymbolTable();
Result VariableNode::Execute(ParentInfo info, bool checkInit)
{

    Variable* variable = Table.GetVariable(VariableName, info.CurrentScope);
    if (variable == NULL)
    {
        PrintError("Variable " + VariableName + " is not defined.");
        return Result("'" + VariableName + "'");
    }

    if (checkInit)
    {
        if (!variable->Initialized)
        {
            PrintWarning("Variable " + VariableName + " is not initialized.");
        }

        variable->Used = true;
    }
    else
    {
        // if we don't check for the initialization then it is an assignment
        if (variable->Constant)
        {
            PrintError("Variable " + VariableName + " is constant and cannot be changed.");
        }

        variable->Initialized = true;
    }

    return Result("'" + VariableName + '_' + to_string(variable->ScopeId) + "'", variable->Type);
}

Result VariableNode::Execute(ParentInfo info)
{
    return Execute(info, true);
}

Result VariableNode::Declare(ParentInfo info, VariableType type, bool initialized, bool constant)
{
    if (Table.ContainsVariable(VariableName, info.CurrentScope))
    {
        PrintError("Variable " + VariableName + " is already defined.");
        return Result('"' + VariableName + '"');
    }

    if (Table.HasAccessToVariable(VariableName, info.CurrentScope))
    {
        PrintWarning("Variable " + VariableName + " is redefined.");
    }

    Table.AddVariable(VariableName, info.CurrentScope, type, initialized, LineNumber, constant);
    return Result("'" + VariableName + '_' + to_string(info.CurrentScope) + "'", type);
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
    for (unsigned int i = 0; i < Statements.size(); i++)
    {
        if (Statements[i])
        {
            Statements[i]->Execute(info);
        }
    }

    return Result();
}

Result ScopeNode::Execute(ParentInfo info)
{
    if (!info.SkipScopeInitializtion)
    {
        int newScope = ++MaxScope;
        Table.AddScope(newScope, info.CurrentScope);

        info.CurrentScope = newScope;
    }
    else
    {
        info.SkipScopeInitializtion = false;
    }

    if (Statements)
    {
        return Statements->Execute(info);
    }

    return Result();
}

Result AssignmentNode::Execute(ParentInfo info)
{
    Result variableResult = Variable->Execute(info, false);
    Result assignmentResult = Assignment->Execute(info);
    if (assignmentResult.Type != Unknown && variableResult.Type != Unknown && assignmentResult.Type != variableResult.Type)
    {
        PrintWarning("Types mismatch, expecting " + VariableTypeName[variableResult.Type] + " and found " + VariableTypeName[assignmentResult.Type]);
    }

    Print("MOV " + variableResult.Value + ", " + assignmentResult.Value);
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
        Print("ADD " + resultRegister + ", " + leftResult.Value + ", " + rightResult.Value);
        break;
    case Minus:
        Print("SUB " + resultRegister + ", " + leftResult.Value + ", " + rightResult.Value);
        break;
    case Mult:
        Print("MUL " + resultRegister + ", " + leftResult.Value + ", " + rightResult.Value);
        break;
    case Div:
        Print("DIV " + resultRegister + ", " + leftResult.Value + ", " + rightResult.Value);
        break;
    case Mod:
        Print("MOD " + resultRegister + ", " + leftResult.Value + ", " + rightResult.Value);
        break;
    case BitAnd:
        Print("ANDB " + resultRegister + ", " + leftResult.Value + ", " + rightResult.Value);
        break;
    case BitOr:
        Print("ORB " + resultRegister + ", " + leftResult.Value + ", " + rightResult.Value);
        break;
    case More:
        Print("GT " + resultRegister + ", " + leftResult.Value + ", " + rightResult.Value);
        break;
    case MoreEqu:
        Print("GTE " + resultRegister + ", " + leftResult.Value + ", " + rightResult.Value);
        break;
    case Less:
        Print("LT " + resultRegister + ", " + leftResult.Value + ", " + rightResult.Value);
        break;
    case LessEqu:
        Print("LTE " + resultRegister + ", " + leftResult.Value + ", " + rightResult.Value);
        break;
    case NotEqu:
        Print("NEQ " + resultRegister + ", " + leftResult.Value + ", " + rightResult.Value);
        break;
    case Equ:
        Print("EQ " + resultRegister + ", " + leftResult.Value + ", " + rightResult.Value);
        break;
    case And:
        Print("AND " + resultRegister + ", " + leftResult.Value + ", " + rightResult.Value);
        break;
    case Or:
        Print("OR " + resultRegister + ", " + leftResult.Value + ", " + rightResult.Value);
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
        Print("NEG " + resultRegister + ", " + operandResult.Value);
        break;
    case Not:
        Print("NOT " + resultRegister + ", " + operandResult.Value);
        break;
    }

    return Result(resultRegister, operandResult.Type);
}

Result DeclarationNode::Execute(ParentInfo info)
{
    bool initialize = Expression != NULL;
    Result variableResult = Variable->Declare(info, Type, initialize);

    Print("DEF " + VariableCode[Type] + ", " + variableResult.Value);

    if (Expression)
    {
        Result expressionResult = Expression->Execute(info);
        if (expressionResult.Type != Unknown && expressionResult.Type != Type)
        {
            PrintWarning("Types mismatch, expecting " + VariableTypeName[Type] + " and found " + VariableTypeName[expressionResult.Type]);
        }

        Print("MOV " + variableResult.Value + ", " + expressionResult.Value);
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

    Print("DEFC " + VariableCode[Type] + ", " + variableResult.Value + ", " + expressionResult.Value);

    return Result();
}

Result CaseNode::Execute(ParentInfo info)
{
    if (Type == Case)
    {
        Result constant = CaseValue->Execute(info);
        if (info.SwitchExpressionType != Unknown && constant.Type != info.SwitchExpressionType)
        {
            PrintError("switch condition and constant type mismatch.");
        }
    }

    Print(Label + ":");

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
            PrintError("switch cannot have more than one default.");
        }
		else if (children[i]->Type == Default && i != children.size() - 1)
		{
			PrintError("The default statement must appear at the end of the switch.");
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

            Print("EQ " + comparisonRegister + ", " + expressionResult.Value + ", " + constant.Value);
            Print("JNZ " + comparisonRegister + ", " + childrenLabels[i].second);
        }
        else
        {
            defaultLabel = childrenLabels[i].second;
        }
    }

    Print("JMP " + defaultLabel);

    info.BreakLabel = label;
    info.SwitchExpressionType = expressionResult.Type;
    CaseList->Execute(info);

    Print(label + ":");

    return Result();
}

Result WhileNode::Execute(ParentInfo info)
{
    string startLabel = MakeLabel();
    string endLabel = MakeLabel();

    Print(startLabel + ":");
    Result conditionResult = Condition->Execute(info);
    Print("JZ " + conditionResult.Value + ", " + endLabel);

    info.BreakLabel = endLabel;
    info.ContinueLabel = startLabel;
    if (Scope)
    {
        Scope->Execute(info);
    }

    Print("JMP " + startLabel);
    Print(endLabel + ":");

    return Result();
}

Result DoWhileNode::Execute(ParentInfo info)
{
    string startLabel = MakeLabel();
    string conditionLabel = MakeLabel();
    string endLabel = MakeLabel();

    Print(startLabel + ":");

    info.BreakLabel = endLabel;
    info.ContinueLabel = conditionLabel;
    if (Scope)
    {
        Scope->Execute(info);
    }

    Print(conditionLabel + ":");

    Result conditionResult = Condition->Execute(info);
    Print("JNZ " + conditionResult.Value + ", " + startLabel);
    Print(endLabel + ":");

    return Result();
}

Result ForNode::Execute(ParentInfo info)
{
    // Execute the for loop in the new scope
    int newScope = ++MaxScope;
    Table.AddScope(newScope, info.CurrentScope);

    info.CurrentScope = newScope;
    info.SkipScopeInitializtion = true;

    if (Initialize)
    {
        Initialize->Execute(info);
    }

    string startLabel = MakeLabel();
    string continueLabel = MakeLabel();
    string endLabel = MakeLabel();

    Print(startLabel + ":");
    if (Condition)
    {
        Result conditionResult = Condition->Execute(info);
        Print("JZ " + conditionResult.Value + ", " + endLabel);
    }

    if (Scope)
    {
        ParentInfo newInfo(info);
        newInfo.BreakLabel = endLabel;
        newInfo.ContinueLabel = continueLabel;
        Scope->Execute(newInfo);
    }

    Print(continueLabel + ":");
    if (Increment)
    {
        Increment->Execute(info);
    }

    Print("JMP " + startLabel);
    Print(endLabel + ":");

    return Result();
}

Result ConditionNode::Execute(ParentInfo info)
{
    Result conditionResult = Condition->Execute(info);
    string elseLabel = MakeLabel();

    Print("JZ " + conditionResult.Value + ", " + elseLabel);
    if (TrueScope)
    {
        TrueScope->Execute(info);
    }


    if (FalseScope)
    {
        string endLabel = MakeLabel();
        Print("JMP " + endLabel);

        Print(elseLabel + ":");
        FalseScope->Execute(info);
        Print(endLabel + ":");
    }
    else
    {
        Print(elseLabel + ":");
    }

    return Result();
}

Result BreakNode::Execute(ParentInfo info)
{
    if (info.BreakLabel == "")
    {
        PrintError("A break statement can only appear in a loop or a switch statement.");
		return Result();
    }

    Print("JMP " + info.BreakLabel);
    return Result();
}

Result ContinueNode::Execute(ParentInfo info)
{
    if (info.ContinueLabel == "")
    {
        PrintError("A continue statement can only appear in a loop.");
		return Result();
    }

    Print("JMP " + info.ContinueLabel);
    return Result();
}