%{
#include "t1b.tab.h"
%}

%%

\n return NL;
"int" return INT;
"char" return CHAR;
"float" return FLOAT;
"double" return DOUBLE;
"void" return VOID;
"long" return LONG;
";" return SM;
"," return CM;
"(" return '(';
")" return ')';
[a-z]+ return ID;
%%

int yywrap(){
    return 1;
}