#pragma once
#include <string>
using namespace std;

enum VariableType{
    Unknown,
    Boolean,
    Integer,
    Float,
};

static string VariableTypeName[] = { "Unknown", "Boolean", "Integer", "Float" };
static string VariableCode[] = { "unknown", "BOOL", "INT", "FLOAT" };

class Variable
{
public:
    string Name;
    VariableType Type;
    bool Constant;
    bool Initialized;

    Variable(string name, VariableType type, bool initialized, bool constant = false)
    {
        Name = name;
        Type = type;
        Constant = constant;
        Initialized = initialized;
    }
};