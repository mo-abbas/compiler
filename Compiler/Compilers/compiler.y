%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fstream>
#include <string>
#include <map>
#include "Variable.h"
#include "Node.h"

bool useFiles = false;
int yylex(void);
extern int yylineno;
std::map<string, string> tokenDictionary;

void yyerror(const char *s);
%}

%locations
%error-verbose

%union {
    int integerValue;           /* integer value */
    float floatValue;           /* float value   */
    bool boolValue;             /* boolean value */
    char* variableName;         /* Variable name */
    Node* nodePtr;              /* node pointer  */
};

%token <integerValue> INTEGER
%token <floatValue> FLOAT
%token <boolValue> BOOL
%token <variableName> VARIABLE
%token CONST DEC_INT DEC_FLOAT DEC_BOOL
%token DO WHILE FOR CONTINUE SWITCH CASE BREAK DEFAULT IF

%left OR
%left AND
%left '|'
%left '&'
%left EQ NE
%left GE LE '>' '<'
%left '+' '-'
%left '*' '/' '%'
%right UMINUS UPLUS '!'
%nonassoc IFX
%nonassoc ELSE

%type <nodePtr> scope statement_list statement assignment expression constant
%type <nodePtr> declaration const_declaration switch_statement case default
%type <nodePtr> case_list loop for_decl for_cond for_inc condition break continue

%%

program:
        statement_list              { $1->Execute(ParentInfo()); Node::CheckUnusedVariables(); }
        ;

scope:
          '{' '}'                   { $$ = new ScopeNode(NULL); }
        | '{' statement_list '}'    { $$ = new ScopeNode($2);   }
        ;

statement_list:
          statement                       { $$ = new StatementListNode($1);                  }
        | statement_list statement        { $$ = ((StatementListNode*)$1)->AddStatement($2); }
        ;

statement:
          ';'                       { $$ = NULL; }
        | assignment ';'            { $$ = $1;   }
        | declaration               { $$ = $1;   }
        | const_declaration         { $$ = $1;   }
        | switch_statement          { $$ = $1;   }
        | loop                      { $$ = $1;   }
        | condition                 { $$ = $1;   }
        | break                     { $$ = $1;   }
        | continue                  { $$ = $1;   }
        | error '}'                 { $$ = NULL; }
        | error ';'                 { $$ = NULL; }
        ;

assignment:
          expression                { $$ = $1; }
        | VARIABLE '=' assignment   { $$ = new AssignmentNode(@1.first_line, new VariableNode(@1.first_line, $1), $3); }
        ;

expression:
          constant                          { $$ = $1;                                                 }
        | VARIABLE                          { $$ = new VariableNode(@1.first_line, $1);                }
        | expression '+' expression         { $$ = new ExpressionNode(@1.first_line, Plus,    $1, $3); }
        | expression '-' expression         { $$ = new ExpressionNode(@1.first_line, Minus,   $1, $3); }
        | expression '*' expression         { $$ = new ExpressionNode(@1.first_line, Mult,    $1, $3); }
        | expression '/' expression         { $$ = new ExpressionNode(@1.first_line, Div,     $1, $3); }
        | expression '%' expression         { $$ = new ExpressionNode(@1.first_line, Mod,     $1, $3); }
        | expression '&' expression         { $$ = new ExpressionNode(@1.first_line, BitAnd,  $1, $3); }
        | expression '|' expression         { $$ = new ExpressionNode(@1.first_line, BitOr,   $1, $3); }
        | expression '<' expression         { $$ = new ExpressionNode(@1.first_line, Less,    $1, $3); }
        | expression '>' expression         { $$ = new ExpressionNode(@1.first_line, More,    $1, $3); }
        | expression GE expression          { $$ = new ExpressionNode(@1.first_line, MoreEqu, $1, $3); }
        | expression LE expression          { $$ = new ExpressionNode(@1.first_line, LessEqu, $1, $3); }
        | expression NE expression          { $$ = new ExpressionNode(@1.first_line, NotEqu,  $1, $3); }
        | expression EQ expression          { $$ = new ExpressionNode(@1.first_line, Equ,     $1, $3); }
        | expression AND expression         { $$ = new ExpressionNode(@1.first_line, And,     $1, $3); }
        | expression OR expression          { $$ = new ExpressionNode(@1.first_line, Or,      $1, $3); }
        | '-' expression %prec UMINUS       { $$ = new UnaryExpressionNode(@2.first_line, Minus, $2);  }
        | '!' expression                    { $$ = new UnaryExpressionNode(@2.first_line, Not, $2);    }
        | '+' expression %prec UPLUS        { $$ = $2; }
        | '(' assignment ')'                { $$ = $2; }
        ;

constant:
          INTEGER                           { $$ = new IntegerNode($1); }
        | FLOAT                             { $$ = new FloatNode($1);   }
        | BOOL                              { $$ = new BooleanNode($1); }

/* ----------------- Declarations ----------------- */
declaration:
          DEC_INT VARIABLE ';'                      { $$ = new DeclarationNode(@1.first_line, Integer, new VariableNode(@2.first_line, $2));     }
        | DEC_INT VARIABLE '=' assignment ';'       { $$ = new DeclarationNode(@1.first_line, Integer, new VariableNode(@2.first_line, $2), $4); }
        | DEC_FLOAT VARIABLE ';'                    { $$ = new DeclarationNode(@1.first_line, Float,   new VariableNode(@2.first_line, $2));     }
        | DEC_FLOAT VARIABLE '=' assignment ';'     { $$ = new DeclarationNode(@1.first_line, Float,   new VariableNode(@2.first_line, $2), $4); }
        | DEC_BOOL VARIABLE ';'                     { $$ = new DeclarationNode(@1.first_line, Boolean, new VariableNode(@2.first_line, $2));     }
        | DEC_BOOL VARIABLE '=' assignment ';'      { $$ = new DeclarationNode(@1.first_line, Boolean, new VariableNode(@2.first_line, $2), $4); }
        ;

const_declaration:
          CONST DEC_INT VARIABLE '=' assignment ';'     { $$ = new ConstantDeclarationNode(@1.first_line, Integer, new VariableNode(@3.first_line, $3), $5); }
        | CONST DEC_FLOAT VARIABLE '=' assignment ';'   { $$ = new ConstantDeclarationNode(@1.first_line, Float,   new VariableNode(@3.first_line, $3), $5); }
        | CONST DEC_BOOL VARIABLE '=' assignment ';'    { $$ = new ConstantDeclarationNode(@1.first_line, Boolean, new VariableNode(@3.first_line, $3), $5); }
        ;

/* ----------------- Switch ----------------- */
switch_statement:
          SWITCH '(' assignment ')' '{' case_list '}'   { $$ = new SwitchNode(@1.first_line, $3, $6); }
          ;

case:
          CASE constant ':' scope        { $$ = new CaseNode(@1.first_line, $2, $4); }
          ;
default:
          DEFAULT ':' scope              { $$ = new CaseNode(@1.first_line, $3);     }
          ;

case_list:
        /* no case */                    { $$ = new CaseListNode();               }
        | case_list case                 { $$ = ((CaseListNode*)$1)->AddCase($2); }
        | case_list default              { $$ = ((CaseListNode*)$1)->AddCase($2); }
        ;

/* ----------------- Loops ----------------- */
loop:
          WHILE '(' assignment ')' scope                             { $$ = new WhileNode(@1.first_line, $3, $5);       }
        | DO scope WHILE '(' assignment ')' ';'                      { $$ = new DoWhileNode(@1.first_line, $5, $2);     }
        | FOR '(' for_decl for_cond for_inc ')' scope                { $$ = new ForNode(@1.first_line, $3, $4, $5, $7); }
        ;

for_decl:
          declaration       { $$ = $1;   }
        | ';'               { $$ = NULL; }
        ;

for_cond:
          assignment ';'    { $$ = $1;   }
        | ';'               { $$ = NULL; }
        ;

for_inc:
          assignment        { $$ = $1;   }
        |                   { $$ = NULL; }
        ;

/* ----------------- Conditions ----------------- */
condition:
          IF '(' assignment ')' scope %prec IFX      { $$ = new ConditionNode(@1.first_line, $3, $5);     }
        | IF '(' assignment ')' scope ELSE scope     { $$ = new ConditionNode(@1.first_line, $3, $5, $7); }
        ;

/* ----------------- Miscellaneous ----------------- */
break:
        BREAK ';'       { $$ = new BreakNode(@1.first_line);    }

continue:
        CONTINUE ';'    { $$ = new ContinueNode(@1.first_line); }

%%

void yyerror(const char *s) {
    std::string message(s);
    if (message.length() > 0)
    {
        message[0] = toupper(message[0]);
    }

    for (auto i = tokenDictionary.begin(); i != tokenDictionary.end(); i++)
    {
        size_t location = message.find(i->first);
        if (location != std::string::npos)
        {
            message.replace(location, i->first.size(), i->second);
        }
    }

    (*Node::ErrorOut) << "ERROR line " << yylineno << ": " << message << ".\n";
}

int main(int argc, char* argv[]) {
    std::ostream* symbolTableOut = &cout;

    if (argc == 5)
    {
        useFiles = true;
        Node::Out = new std::ofstream(argv[1]);
        Node::ErrorOut = new std::ofstream(argv[2]);
        Node::WarningOut = new std::ofstream(argv[3]);
        symbolTableOut = new std::ofstream(argv[4]);
    }

    tokenDictionary[" INTEGER"] = " integer value";
    tokenDictionary[" FLOAT"] = " float value";
    tokenDictionary[" BOOL"] = " boolean value";
    tokenDictionary[" VARIABLE"] = " variable";
    tokenDictionary[" CONST"] = " 'const'";
    tokenDictionary[" DEC_INT"] = " 'int'";
    tokenDictionary[" DEC_FLOAT"] = " 'float'";
    tokenDictionary[" DEC_BOOL"] = " 'bool'";
    tokenDictionary[" DO"] = " 'do'";
    tokenDictionary[" WHILE"] = " 'while'";
    tokenDictionary[" FOR"] = " 'for'";
    tokenDictionary[" CONTINUE"] = " 'continue'";
    tokenDictionary[" SWITCH"] = " 'switch'";
    tokenDictionary[" CASE"] = " 'case'";
    tokenDictionary[" BREAK"] = " 'break'";
    tokenDictionary[" DEFAULT"] = " 'default'";
    tokenDictionary[" IF"] = " 'if'";
    tokenDictionary[" OR"] = " '||'";
    tokenDictionary[" AND"] = " '&&'";
    tokenDictionary[" EQ"] = " '=='";
    tokenDictionary[" NE"] = " '!='";
    tokenDictionary[" GE"] = " '>='";
    tokenDictionary[" LE"] = " '<='";
    tokenDictionary[" UMINUS"] = " '-'";
    tokenDictionary[" UPLUS"] = " '+'";
    tokenDictionary[" ELSE"] = " 'else'";
    tokenDictionary[" $end"] = " eof";
    yyparse();
 
    Node::Table.Print(symbolTableOut);

    if (useFiles)
    {
        Node::Out->flush();
        Node::ErrorOut->flush();
        Node::WarningOut->flush();
        symbolTableOut->flush();

        delete Node::Out;
        delete Node::ErrorOut;
        delete Node::WarningOut;
        delete symbolTableOut;
    }

    return 0;
}

ostream* Node::Out = &cout;
ostream* Node::ErrorOut = &cerr;
ostream* Node::WarningOut = &cerr;