%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string>
#include "Variable.h"
#include "Node.h"
#include "printGraph.c"

int yylex(void);
void yyerror(char *s);

enum OpType
{
    Plus, Minus, Mult, Div, Mod, BitAnd, BitOr, Less, More, MoreEqu, LessEqu, NotEqu, Equ, And, Or, Not
};

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

%left OR
%left AND
%left EQ NE
%left GE LE '>' '<'
%left '+' '-'
%left '*' '/' '%'
%right NOT
%right UMINUS UPLUS

%type <nodePtr> scope statement_list statement assignment expression declaration 
%type <nodePtr> const_declaration switch_statement case default case_list iterations

%%

program:
        statement_list              { $1->execute(); exit(0); }
        ;

scope:
          '{' '}'                   { $$ = new ScopeNode(NULL); }
        | '{' statement_list '}'    { $$ = new ScopeNode($2); }
        ;

statement_list:
          statement                 { $$ = new StatementListNode($1); }
        | statement_list statement  { $$ = $1->AddStatement($2); }
        ;

statement:
          ';'                       { $$ = NULL; }
        | expression ';'            { $$ = $1; }
        | assignment ';'            { $$ = $1; }
        | iterations                { $$ = $1; }
        | condition                 { $$ = $1; }
        ;

assignment:
          expression                { $$ = $1; }
        | VARIABLE '=' assignment   { $$ = new AssignmentNode(new VariableNode($1), $3); }
        ;

expression:
          INTEGER                           { $$ = new IntegerNode($1);                 }
        | FLOAT                             { $$ = new FloatNode($2);                   }
        | BOOL                              { $$ = new BooleanNode($3);                 }
        | VARIABLE                          { $$ = new VariableNode($4);                }
        | expression '+' expression         { $$ = new ExpressionNode(Plus, $1, $3);    }
        | expression '-' expression         { $$ = new ExpressionNode(Minus, $1, $3);   }
        | expression '*' expression         { $$ = new ExpressionNode(Mult, $1, $3);    }
        | expression '/' expression         { $$ = new ExpressionNode(Div, $1, $3);     }
        | expression '%' expression         { $$ = new ExpressionNode(Mod, $1, $3);     }
        | expression '&' expression         { $$ = new ExpressionNode(BitAnd, $1, $3);  }
        | expression '|' expression         { $$ = new ExpressionNode(BitOr, $1, $3);   }
        | expression '<' expression         { $$ = new ExpressionNode(Less, $1, $3);    }
        | expression '>' expression         { $$ = new ExpressionNode(More, $1, $3);    }
        | expression GE expression          { $$ = new ExpressionNode(MoreEqu, $1, $3); }
        | expression LE expression          { $$ = new ExpressionNode(LessEqu, $1, $3); }
        | expression NE expression          { $$ = new ExpressionNode(NotEqu, $1, $3);  }
        | expression EQ expression          { $$ = new ExpressionNode(Equ, $1, $3);     }
        | expression AND expression         { $$ = new ExpressionNode(And, $1, $3);     }
        | expression OR expression          { $$ = new ExpressionNode(Or, $1, $3);      }
        | '-' expression %prec UMINUS       { $$ = new UnaryExpressionNode(Minus, $2);  }
        | '!' expression                    { $$ = new UnaryExpressionNode(Not, $2);    }
        | '+' expression %prec UPLUS        { $$ = $2; }
        | '(' expression ')'                { $$ = $2; }
        ;

/* ----------------- Declarations ----------------- */
declaration:
          INT variableName ';'                  { $$ = new DeclarationNode(Integer, $2);     }
        | INT variableName '=' expression ';'   { $$ = new DeclarationNode(Integer, $2, $4); }
        | FLOAT variableName ';'                { $$ = new DeclarationNode(Float, $2);       }
        | FLOAT variableName '=' expression ';' { $$ = new DeclarationNode(Float, $2, $4);   }
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
          SWITCH '(' expression ')' '{' case_list '}'           { $$ = SwitchNode($3, $6); }
        | SWITCH '(' expression ')' '{' case_list default '}'   { $$ = SwitchNode($3, $6); }
          ;

case:
          CASE constant ':' scope        { $$ = new CaseNode($2, $4); }
          ;
default:
          DEFAULT ':' scope              { $$ = new DefaultNode($3); }
          ;

case_list:
        /* no case */                    { $$ = new CaseListNode(NULL); }
        | case_list case                 { $$ = $2.AddCase($1); }
        ;

/* ----------------- Loops ----------------- */
iterations:
         WHILE '(' expression ')' scope
       | DO scope WHILE '(' expression ')'
       | FOR '(' declaration expression ';' expression ')' scope
       ;

/* ----------------- Conditions ----------------- */
condition:
         IF '(' expression ')' scope %prec IFX      { $$ = new ConditionNode($3, $5, NULL); }
       | IF '(' expression ')' scope ELSE scope     { $$ = new ConditionNode($3, $5, $7);   }

%%

void yyerror(const char *s) {
    fprintf(stdout, "%s\n", s);
}

int main() {
    yyparse();
    return 0;
}
