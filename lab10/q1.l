%{
#include "q1.tab.h"
#include "q1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

%%
[0-9]+      { yylval.ival = atoi(yytext); return NUM; }
"int"       { return INT; }
"char"      { return CHAR; }
"float"     { return FLOAT; }
","         { return ','; }
";"         { return ';'; }
[a-zA-Z][a-zA-Z0-9_]* { 
                yylval.sval = strdup(yytext); 
                return VAR; 
            }
"="         { return '='; }
[ \t]       { /* Ignore whitespace */ }
\n          { return NL; }
.           { printf("Unexpected character: %s\n", yytext); exit(1); }
%%

int yywrap() {
    return 1;
}