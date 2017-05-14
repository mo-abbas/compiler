#include "SymbolTable.h"

bool SymbolTable::AddScope(ScopeID id, ScopeID parentId)
{
    if (_scopes[id] != NULL)
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

bool SymbolTable::Add(string name, ScopeID id, VariableType type, bool constant)
{
    Variable* variable = new Variable(name, type, constant);

    if (!ContainsScope(id))
    {
        return false;
    }

    Scope* scope = _scopes[id];
    return scope->AddVariable(variable);
}

bool SymbolTable::ContainsScope(ScopeID id)
{
    return _scopes[id] != NULL;
}