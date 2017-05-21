#include "SymbolTable.h"

bool SymbolTable::AddScope(ScopeID id, ScopeID parentId)
{
    if (ContainsScope(id))
    {
        return false;
    }

    Scope* parentScope = NULL;
    if (parentId != -1)
    {
        parentScope = _scopes[parentId];
    }

    Scope* scope = new Scope(id, parentScope);
    _scopes[id] = scope;

    return true;
}

bool SymbolTable::ContainsScope(ScopeID id)
{
    return _scopes.find(id) != _scopes.end();
}

bool SymbolTable::AddVariable(string name, ScopeID id, VariableType type, bool initialized, int line, bool constant)
{
    Variable* variable = new Variable(name, type, id, initialized, line, constant);

    if (!ContainsScope(id))
    {
        return false;
    }

    Scope* scope = _scopes[id];
    return scope->AddVariable(variable);
}

bool SymbolTable::ContainsVariable(string name, ScopeID id)
{
    if (!ContainsScope(id))
    {
        return false;
    }

    return _scopes[id]->ContainsVariable(name);
}

bool SymbolTable::HasAccessToVariable(string name, ScopeID id)
{
    if (!ContainsScope(id))
    {
        return false;
    }

    return _scopes[id]->HasAccessToVariable(name);
}

Variable* SymbolTable::GetVariable(string name, ScopeID id)
{
    if (!ContainsScope(id))
    {
        return NULL;
    }

    return _scopes[id]->GetVariable(name);
}

void SymbolTable::Print(ostream* symbolTableOut)
{
	(*symbolTableOut) << "Name, Type, Scope, Constant"<<endl;
    for (map<ScopeID, Scope*>::iterator it = _scopes.begin(); it != _scopes.end(); it++)
    {
        it->second->Print(symbolTableOut);
    }
}

void SymbolTable::CheckUnusedVariables(ostream* out)
{
    for (map<ScopeID, Scope*>::iterator it = _scopes.begin(); it != _scopes.end(); it++)
    {
        it->second->CheckUnusedVariables(out);
    }
}

SymbolTable::~SymbolTable()
{
    for (map<ScopeID, Scope*>::iterator i = _scopes.begin(); i != _scopes.end(); i++)
    {
        delete i->second;
    }
}