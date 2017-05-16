%{
#include <string>
#include <stdlib.h>
#include "Node.h"
#include "compiler.tab.h"
void yyerror(char *);
%}

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

[-()<>=+*/;{}.!&|%]               { return *yytext; }

[0-9]+\.[0-9]+(e[+-]?[0-9]+)?    { yylval.floatValue = (float)atof(yytext); return FLOAT; }
[0-9]+                           { yylval.integerValue = atoi(yytext); return INTEGER; }


[A-Za-z_][A-Za-z_0-9]+           { yylval.variableName = yytext; return VARIABLE; }

[ \t\n\r]+                       ;       /* ignore whitespace */

.                               {
                                    std::string message = "Unknown symbol on line: ";
                                    message += std::to_string(yylineno);
                                    yyerror((char*)message.c_str());
                                }
%%
int yywrap(void) {
    return 1;
}
