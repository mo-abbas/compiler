#pragma once
#include <string>
#include <vector>
#include "Scope.h"

//#define EXECUTE_CODE

using namespace std;

class SymbolTable
{
private:
    map<ScopeID, Scope*> _scopes;

public:
    ~SymbolTable();

    bool AddScope(ScopeID id, ScopeID parentId = -1);
    bool ContainsScope(ScopeID id);

    bool AddVariable(string name, ScopeID id, VariableType type, bool initialized, bool constant = false);
    bool ContainsVariable(string name, ScopeID id);
    bool HasAccessToVariable(string name, ScopeID id);

    Variable* GetVariable(string name, ScopeID id);

#ifdef EXECUTE_CODE
    bool Update(string name, ScopeID id, void* value);
    void* Get(string name, ScopeID id);
#endif

};