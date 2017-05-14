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
    else if (this->ParentHasAccessToVariable(name))
    {
        return Parent->GetVariable(name);
    }
    
    return NULL;
}