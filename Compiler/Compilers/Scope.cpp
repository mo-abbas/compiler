#include "Scope.h"

bool Scope::AddVariable(Variable* variable)
{
    if (this->HasAccessToVariable(variable->Name))
    {
        return false;
    }

    _variables[variable->Name] = variable;
    return true;
}

bool Scope::ContainsVariable(string name)
{
    return _variables[name] != NULL;
}

bool Scope::ParentHasAccessToVariable(string name)
{
    if (Parent != NULL)
    {
        return Parent->HasAccessToVariable(name);
    }

    return false;
}

bool Scope::HasAccessToVariable(string name)
{
    return this->ContainsVariable(name) || this->ParentHasAccessToVariable(name);
}

Variable* Scope::GetVariable(string name)
{
    if (this->ContainsVariable(name))
    {
        return _variables[name];
    }
    
    return Parent->GetVariable(name);
}

Scope::~Scope()
{
    for (map<string, Variable*>::iterator i = _variables.begin(); i != _variables.end(); i++)
    {
        delete i->second;
    }
}