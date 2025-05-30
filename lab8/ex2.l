%{
#include "ex2.tab.h"
%}
%%
0 { return ZERO; }
1 { return ONE; }
\n { return NL; }
[ \t] ; /* ignore whitespace */
. { printf("Invalid character"); }
%%


int yywrap(){
    return 1;
}