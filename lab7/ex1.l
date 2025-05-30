%{
#include "ex1.tab.h"
%}
%%
[a-z]+ return ID;
"+" return PL;
"*" return ST;
"(" return OB;
")" return CB;
\n return NL;
%%

int yywrap(){
    return 1;
}