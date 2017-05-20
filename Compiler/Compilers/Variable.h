#pragma once
#include <string>
using namespace std;

enum VariableType{
    Unknown,
    Boolean,
    Integer,
    Float,
};

static string VariableTypeName[] = { "Unknown", "bool", "int", "float" };
static string VariableCode[] = { "unknown", "BOOL", "INT", "FLOAT" };

class Variable
{
public:
    string Name;
    VariableType Type;
    bool Constant;
    bool Initialized;
    int ScopeId;

    Variable(string name, VariableType type, int scopeId, bool initialized, bool constant = false)
    {
        Name = name;
        Type = type;
        ScopeId = scopeId;
        Initialized = initialized;
        Constant = constant;
    }
};