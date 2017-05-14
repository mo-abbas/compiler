%{
#include <stdlib.h>
#include "Node.h"
#include "compiler.tab.h"
void yyerror(char *);
%}

%%

[0-9]+\.[0-9]+(e[+-]?[0-9]+)? {
				yylval.fValue = atof(yytext);
				return FLOAT;
			}

[0-9]+		{
                yylval.iValue = atoi(yytext);
                return INTEGER;
            }

"true"		{
				yylval.bValue = true;
				return BOOL;
			}

"false"		{
				yylval.bValue = false;
				return BOOL;
			}


[-()<>=+*/;{}.] {
                return *yytext;
            }

"\n"			return ';';	/* A statement could end with a new line instead of a semi-colon */

"&&"			return AND;
"||"			return OR;
"!"				return NOT;

">="            return GE;
"<="            return LE;
"=="            return EQ;
"!="            return NE;
"while"         return WHILE;
"if"            return IF;
"else"          return ELSE;
"print"         return PRINT;

[A-Za-z_][A-Za-z_0-9]+ { 
                yylval.variableName = yytext;
                return VARIABLE;
            }

[ \t\r]+	    ;       /* ignore whitespace except endline */

.               yyerror("Unknown character");
%%
int yywrap(void) {
    return 1;
}
