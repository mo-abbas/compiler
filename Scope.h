#pragma once
#include <map>
#include "Variable.h"

typedef int ScopeID;
using namespace std;

class Scope
{
	map<string, Variable*> _variables;
	bool ParentHasAccessToVariable(string name);

public:
	ScopeID Id;
	Scope* Parent;

	Scope(ScopeID id, Scope* parent)
	{
		Id = id;
		Parent = parent;
	}

	bool AddVariable(Variable* variable);
	Variable* GetVariable(string variableName);
	bool ContainsVariable(string variableName);
	bool HasAccessToVariable(string variableName);
};