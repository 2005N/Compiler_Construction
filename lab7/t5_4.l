%{
#include "t5_4.tab.h"
%}

%%

"if"        return IF;
"then"      return THEN;
"else"      return ELSE;
"(" return '(';
")" return ')';
[a-zA-Z_][a-zA-Z0-9_]*   return ID;
[\t]+   ;
\n return NL;
%%

int yywrap() { return 1; }
