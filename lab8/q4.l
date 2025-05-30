%{
    #include "q4.tab.h"
%}

%%
1 {yylval.val=1; return BOOL;}
0 {yylval.val=0; return BOOL;}
"&&" return AND;
"||" return OR;
"!" return NOT;
"(" return LP;
")" return RP;
\n return NL;

%%

int yywrap() {return 1;}