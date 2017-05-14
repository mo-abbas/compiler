#pragma once
#include <string>
using namespace std;

enum VariableType{
	INT,
	FLOAT,
	BOOL
};

class Variable
{
public:
	string Name;
	VariableType Type;
	bool Constant;

	Variable(string name, VariableType type, bool constant = false)
	{
		Name = name;
		Type = type;
		Constant = constant;
	}
};