#include "Scope.h"

bool Scope::AddVariable(Variable* variable)
{
    if (this->ContainsVariable(variable->Name))
    {
        return false;
    }

    _variables[variable->Name] = variable;
    return true;
}

bool Scope::ContainsVariable(string name)
{
    return _variables.find(name) != _variables.end();
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

void Scope::Print(ostream* symbolTableOut)
{
    for (map<string, Variable*>::iterator it = _variables.begin(); it != _variables.end(); it++)
    {
        it->second->Print(symbolTableOut);
    }
}

void Scope::CheckUnusedVariables(ostream* out)
{
    for (map<string, Variable*>::iterator it = _variables.begin(); it != _variables.end(); it++)
    {
        it->second->CheckUnused(out);
    }
}

Variable* Scope::GetVariable(string name)
{
    if (this->ContainsVariable(name))
    {
        return _variables[name];
    }
    
    if (Parent)
    {
        return Parent->GetVariable(name);
    }

    return NULL;
}

Scope::~Scope()
{
    for (map<string, Variable*>::iterator i = _variables.begin(); i != _variables.end(); i++)
    {
        delete i->second;
    }
}