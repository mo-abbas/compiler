%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string>
#include "Variable.h"
#include "Node.h"
#include "printGraph.c"

/* prototypes */
nodeType *opr(int oper, int nops, ...);
nodeType *id(int i);
nodeType *con(int value);
void freeNode(nodeType *p);
int ex(nodeType *p);
int yylex(void);

void yyerror(char *s);
int sym[26];                    /* symbol table */
%}

%union {
    int integerValue;           /* integer value */
    float floatValue;           /* float value   */
    bool boolValue;             /* boolean value */
    char* variableName;         /* Variable name */
    Node *nodePtr;              /* node pointer  */
};

%token <integerValue> INT
%token <floatValue> FLOAT
%token <boolValue> BOOL
%token <variableName> VARIABLE
%token CONST
%token DO WHILE FOR CONTINUE SWITCH CASE BREAK DEFAULT IF
%nonassoc IFX
%nonassoc ELSE

%left AND OR
%left GE LE EQ NE '>' '<'
%left '+' '-'
%left '*' '/'
%right NOT
%right UMINUS UPLUS

%type <nodePtr> declaration const_declaration switch_statement case default case_list

%%

program:
        statement_list          { exit(0); }
        ;


statement:
          ';'                                               { $$ = opr(';', 2, NULL, NULL); }
        | expression ';'                                    { $$ = $1; }
        | VARIABLE '=' expression ';'                       { $$ = opr('=', 2, id($1), $3); }
        | WHILE '(' expression ')' statement                { $$ = opr(WHILE, 2, $3, $5); }
        | IF '(' expression ')' statement %prec IFX         { $$ = opr(IF, 2, $3, $5); }
        | IF '(' expression ')' statement ELSE statement    { $$ = opr(IF, 3, $3, $5, $7); }
        | '{' statement_list '}'                            { $$ = $2; }
        ;

statement_list:
          statement                  { $$ = $1; }
        | statement_list statement   { $$ = opr(';', 2, $1, $2); }
        ;

expression:
          INTEGER                           { $$ = con($1); }
        | VARIABLE                          { $$ = id($1); }
        | '-' expression %prec UMINUS       { $$ = opr(UMINUS, 1, $2); }
        | '+' expression %prec UPLUS        { $$ = $2; }
        | expression '+' expression         { $$ = opr('+', 2, $1, $3); }
        | expression '-' expression         { $$ = opr('-', 2, $1, $3); }
        | expression '*' expression         { $$ = opr('*', 2, $1, $3); }
        | expression '/' expression         { $$ = opr('/', 2, $1, $3); }
        | expression '<' expression         { $$ = opr('<', 2, $1, $3); }
        | expression '>' expression         { $$ = opr('>', 2, $1, $3); }
        | expression GE expression          { $$ = opr(GE, 2, $1, $3); }
        | expression LE expression          { $$ = opr(LE, 2, $1, $3); }
        | expression NE expression          { $$ = opr(NE, 2, $1, $3); }
        | expression EQ expression          { $$ = opr(EQ, 2, $1, $3); }
        | '(' expression ')'                { $$ = $2; }
        ;

/* ----------------- Declarations ----------------- */
declaration: 
          INT variableName ';'                  { $$ = new DeclarationNode(Integer, $2);     }
        | INT variableName '=' expression ';'   { $$ = new DeclarationNode(Integer, $2, $4); }
        | FLOAT variableName ';'                { $$ = new DeclarationNode(Float, $2);         }
        | FLOAT variableName '=' expression ';' { $$ = new DeclarationNode(Float, $2, $4);     }
        | BOOL variableName ';'                 { $$ = new DeclarationNode(Boolean, $2);     }
        | BOOL variableName '=' expression ';'  { $$ = new DeclarationNode(Boolean, $2, $4); }
        ;

const_declaration:
        | CONST INT variableName '=' expression ';'     { $$ = new ConstantDeclarationNode(Integer, $3, $5); }
        | CONST FLOAT variableName '=' expression ';'   { $$ = new ConstantDeclarationNode(Float,   $3, $5); }
        | CONST BOOL variableName '=' expression ';'    { $$ = new ConstantDeclarationNode(Boolean, $3, $5); }
        ;

/* ----------------- Switch ----------------- */
switch_statement:
          SWITCH '(' expression ')' '{' case_list '}'    { $$ = SwitchNode($3, $6); }
          ;

case:
          CASE constant ':' scope        { $$ = new CaseNode($2, $4); }
          ;
default:
          DEFAULT ':' scope              { $$ = new DefaultNode($3); }
          ;

case_list:
        /* no default */                { $$ = new CaseListNode(NULL); }
        | default                       { $$ = new CaseListNode($1); }
        | case case_list                { $$ = $2.AddCase($1); }
        ;

%%

void yyerror(const char *s) {
    fprintf(stdout, "%s\n", s);
}

int main() {
    yyparse();
    return 0;
}
