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
    bool Used;
    int Line;

    Variable(string name, VariableType type, int scopeId, bool initialized, int line, bool constant = false)
    {
        Name = name;
        Type = type;
        ScopeId = scopeId;
        Initialized = initialized;
        Constant = constant;
        Used = false;
        Line = line;
    }
    
    void Print(ostream* symbolTableOut)
    {
        (*symbolTableOut) << boolalpha;
        (*symbolTableOut) <<Name <<
            "," << VariableCode[Type] <<
            "," << ScopeId <<
            "," << Constant << endl;
    }

    void CheckUnused(ostream* out)
    {
        if (!Used)
        {
            (*out) << "WARNING line " << Line << ": Variable '" << Name << "' is not used" << endl;
        }
    }
};