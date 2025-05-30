%{
#include "t1a.tab.h"
%}

%%

\n return NL;
"int" return INT;
"char" return CHAR;
"float" return FLOAT;
"double" return DOUBLE;
"void" return VOID;
";" return SM;
"," return CM;
[a-z]+ return ID;
%%

int yywrap(){
    return 1;
}