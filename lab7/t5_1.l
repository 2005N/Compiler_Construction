%{
#include "t5_1.tab.h"    
#include <string.h>
#include <stdlib.h>
%}

%%
[ab]+ {yylval.sval=strdup(yytext); return STR;}
\n {return NL;}
%%

int yywrap(){return 1;}