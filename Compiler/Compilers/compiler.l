%{
#include <string>
#include <stdlib.h>
#include "Node.h"
#include "compiler.tab.h"

#define YY_USER_ACTION yylloc.first_line = yylineno;

void yyerror(const char *);
%}

%option yylineno

%%

"const"         return CONST;
"int"           return DEC_INT;
"float"         return DEC_FLOAT;
"bool"          return DEC_BOOL;

"do"            return DO;
"while"         return WHILE;
"for"           return FOR;
"continue"      return CONTINUE;

"switch"        return SWITCH;
"case"          return CASE;
"break"         return BREAK;
"default"       return DEFAULT;

"if"            return IF;
"else"          return ELSE;

"true"          { yylval.boolValue = true; return BOOL; }
"false"         { yylval.boolValue = false; return BOOL; }

"&&"            return AND;
"||"            return OR;

">="            return GE;
"<="            return LE;
"=="            return EQ;
"!="            return NE;

[-()<>=+*/;{}.!&|%:]             { return yytext[0]; }

[0-9]+\.[0-9]+(e[+-]?[0-9]+)?    { yylval.floatValue = (float)atof(yytext); return FLOAT; }
[0-9]+                           { yylval.integerValue = atoi(yytext); return INTEGER; }


[A-Za-z_][A-Za-z_0-9]*           {
                                    char* name = new char[strlen(yytext) + 1];
                                    strcpy(name, yytext);
                                    yylval.variableName = name;
                                    return VARIABLE;
                                 }

[ \t\n\r]+                       ;

[^ \t\n\r]                       { yyerror("Unknown symbol"); } // .+ sometimes matches the ignored spaces in the previous rule

%%
int yywrap(void) {
    return 1;
}
