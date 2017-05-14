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

class Node
{
public:
	NodeType type;
	virtual void execute() = 0;
};

class ExpressionNode : Node
{
public:
	ExpressionNode();
	virtual void execute();
};

class SwitchNode : Node
{
public:
	SwitchNode(ExpressionNode* expression, CaseListNode* cases);
	virtual void execute();
};

class CaseListNode : Node
{
public:
	vector<CaseNode> children;
	DefaultNode* def;

	CaseListNode(DefaultNode* def);
	CaseListNode* AddCase(CaseNode* caseNode);
	virtual void execute();
};

class CaseNode : Node
{
public:
	CaseNode(ConstantNode* constant, ScopeNode* scope);
	virtual void execute();
};

class DefaultNode : Node
{
public:
	DefaultNode(ScopeNode* scope);
	virtual void execute();
};


class ConstantNode : Node
{
public:
	ConstantNode(VariableType type, void* value);
	virtual void execute();
};

class DeclarationNode : Node
{
public:
	DeclarationNode(VariableType type, char* name, ExpressionNode* expression = NULL);
	virtual void execute();
};

class ConstantDeclarationNode : Node 
{
public:
	ConstantDeclarationNode(VariableType type, char* name, ExpressionNode* expression);
	virtual void execute();
};

class ScopeNode : Node
{
public:
	ScopeNode();
	virtual void execute();
};