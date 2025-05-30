%{
#include "ast.tab.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
%}

%%

[0-9]+  { yylval.ival = atoi(yytext); return NUMBER; }
[a-z]   {yylval.sval=yytext[0]; return VAR;}
"+"     { return '+'; }
"-"     { return '-'; }
"*"     { return '*'; }
"/"     { return '/'; }
"("     { return '('; }
")"     { return ')'; }
"="     {return '=';}
[ \t]  { /* Ignore whitespace */ }
.       { printf("Unexpected character: %s\n", yytext); exit(1); }
\n return NL; 
%%

int yywrap() {
    return 1;
}

