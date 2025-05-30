%{
#include "t5.tab.h"
%}
%%
0 { return ZERO; }
1 { return ONE; }
"." {return '.';}
\n { return NL; }
[ \t] ; /* ignore whitespace */
. { printf("Invalid character"); }
%%


int yywrap(){
    return 1;
}