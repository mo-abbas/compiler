#pragma once
#include <string>
using namespace std;

enum VariableType{
    Integer,
    Float,
    Boolean
};

class Variable
{
public:
    string Name;
    VariableType Type;
    bool Constant;
    bool Initialized;

    Variable(string name, VariableType type, bool constant = false)
    {
        Name = name;
        Type = type;
        Constant = constant;
        Initialized = false;
    }
};