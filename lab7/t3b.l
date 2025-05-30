%{
#include "t3b.tab.h"
%}

%%
[0-9]+ {yylval.ival=atoi(yytext); return NUM;}
"+" return '+';
"-" return '-';
"*" return '*';
"/" return '/';
"(" return '(';
")" return ')';
\n return NL;
[ \t]+      ; // Ignore whitespace

%%

int yywrap(){
    return 1;
}