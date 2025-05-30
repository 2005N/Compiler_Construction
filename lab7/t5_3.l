%{
#include "t5_3.tab.h"
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
"=" return EQ;
[a-z]+ return ID;
[0-9]+ return NUM;
%%

int yywrap(){
    return 1;
}