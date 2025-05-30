%{
#include "t5_2.tab.h"
%}

%%

\n return NL;
"(" return '(';
"[" return '[';
"{" return '{';
")" return ')';
"]" return ']';
"}" return '}';
%%

int yywrap(){
    return 1;
}