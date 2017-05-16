%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string>
#include "Variable.h"
#include "Node.h"

int yylex(void);
void yyerror(char *s);

%}

%union {
    int integerValue;           /* integer value */
    float floatValue;           /* float value   */
    bool boolValue;             /* boolean value */
    char* variableName;         /* Variable name */
    Node *nodePtr;              /* node pointer  */
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

%type <nodePtr> scope statement_list statement assignment expression
%type <nodePtr> constant declaration const_declaration switch_statement
%type <nodePtr> case default case_list loop condition break continue

%%

program:
        statement_list              { $1->execute(); exit(0); }
        ;

scope:
          '{' '}'                   { $$ = NULL; }
        | '{' statement_list '}'    { $$ = new ScopeNode($2); }
        ;

statement_list:
          statement                 { $$ = new StatementListNode($1);                  }
        | statement_list statement  { $$ = ((StatementListNode*)$1)->AddStatement($2); }
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
        ;

assignment:
          expression                { $$ = $1; }
        | VARIABLE '=' assignment   { $$ = new AssignmentNode(new VariableNode($1), $3); }
        ;

expression:
          constant                          { $$ = $1;                                  }
        | VARIABLE                          { $$ = new VariableNode($1);                }
        | expression '+' expression         { $$ = new ExpressionNode(Plus,    $1, $3); }
        | expression '-' expression         { $$ = new ExpressionNode(Minus,   $1, $3); }
        | expression '*' expression         { $$ = new ExpressionNode(Mult,    $1, $3); }
        | expression '/' expression         { $$ = new ExpressionNode(Div,     $1, $3); }
        | expression '%' expression         { $$ = new ExpressionNode(Mod,     $1, $3); }
        | expression '&' expression         { $$ = new ExpressionNode(BitAnd,  $1, $3); }
        | expression '|' expression         { $$ = new ExpressionNode(BitOr,   $1, $3); }
        | expression '<' expression         { $$ = new ExpressionNode(Less,    $1, $3); }
        | expression '>' expression         { $$ = new ExpressionNode(More,    $1, $3); }
        | expression GE expression          { $$ = new ExpressionNode(MoreEqu, $1, $3); }
        | expression LE expression          { $$ = new ExpressionNode(LessEqu, $1, $3); }
        | expression NE expression          { $$ = new ExpressionNode(NotEqu,  $1, $3); }
        | expression EQ expression          { $$ = new ExpressionNode(Equ,     $1, $3); }
        | expression AND expression         { $$ = new ExpressionNode(And,     $1, $3); }
        | expression OR expression          { $$ = new ExpressionNode(Or,      $1, $3); }
        | '-' expression %prec UMINUS       { $$ = new UnaryExpressionNode(Minus, $2);  }
        | '!' expression                    { $$ = new UnaryExpressionNode(Not, $2);    }
        | '+' expression %prec UPLUS        { $$ = $2; }
        | '(' expression ')'                { $$ = $2; }
        ;

constant:
          INTEGER                           { $$ = new IntegerNode($1); }
        | FLOAT                             { $$ = new FloatNode($1);   }
        | BOOL                              { $$ = new BooleanNode($1); }

/* ----------------- Declarations ----------------- */
declaration:
          DEC_INT VARIABLE ';'                      { $$ = new DeclarationNode(Integer, new VariableNode($2));     }
        | DEC_INT VARIABLE '=' expression ';'       { $$ = new DeclarationNode(Integer, new VariableNode($2), $4); }
        | DEC_FLOAT VARIABLE ';'                    { $$ = new DeclarationNode(Float,   new VariableNode($2));     }
        | DEC_FLOAT VARIABLE '=' expression ';'     { $$ = new DeclarationNode(Float,   new VariableNode($2), $4); }
        | DEC_BOOL VARIABLE ';'                     { $$ = new DeclarationNode(Boolean, new VariableNode($2));     }
        | DEC_BOOL VARIABLE '=' expression ';'      { $$ = new DeclarationNode(Boolean, new VariableNode($2), $4); }
        ;

const_declaration:
          CONST DEC_INT VARIABLE '=' expression ';'     { $$ = new ConstantDeclarationNode(Integer, new VariableNode($3), $5); }
        | CONST DEC_FLOAT VARIABLE '=' expression ';'   { $$ = new ConstantDeclarationNode(Float,   new VariableNode($3), $5); }
        | CONST DEC_BOOL VARIABLE '=' expression ';'    { $$ = new ConstantDeclarationNode(Boolean, new VariableNode($3), $5); }
        ;

/* ----------------- Switch ----------------- */
switch_statement:
          SWITCH '(' expression ')' '{' case_list '}'   { $$ = new SwitchNode($3, $6); }
          ;

case:
          CASE constant ':' scope        { $$ = new CaseNode($2, $4); }
          ;
default:
          DEFAULT ':' scope              { $$ = new CaseNode($3);     }
          ;

case_list:
        /* no case */                    { $$ = new CaseListNode();               }
        | case_list case                 { $$ = ((CaseListNode*)$1)->AddCase($2); }
        | case_list default              { $$ = ((CaseListNode*)$1)->AddCase($2); }
        ;

/* ----------------- Loops ----------------- */
loop:
          WHILE '(' expression ')' scope                             { $$ = new WhileNode($3, $5);       }
        | DO scope WHILE '(' expression ')'                          { $$ = new DoWhileNode($5, $2);     }
        | FOR '(' declaration expression ';' assignment ')' scope    { $$ = new ForNode($3, $4, $6, $8); }
        ;

/* ----------------- Conditions ----------------- */
condition:
          IF '(' expression ')' scope %prec IFX      { $$ = new ConditionNode($3, $5); }
        | IF '(' expression ')' scope ELSE scope     { $$ = new ConditionNode($3, $5, $7);   }
        ;

/* ----------------- Miscellaneous ----------------- */
break:
        BREAK ';'       { $$ = new BreakNode(); }

continue:
        CONTINUE ';'    { $$ = new ContinueNode(); }

%%

void yyerror(const char *s) {
    fprintf(stdout, "%s\n", s);
}

int main() {
    yyparse();
    return 0;
}
