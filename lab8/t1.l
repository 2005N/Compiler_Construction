%{
#include "t1.tab.h"
%}

%%
[0-9]+ {yylval.ival=atoi(yytext); return NUM;}
\n return NL;
"+" return '+';
"-" return '-';
"*" return '*';
"/" return '/';
"(" return '(';
")" return ')';
"^" return '^';
%%

int yywrap(){
    return 1;
}