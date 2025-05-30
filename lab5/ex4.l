%{
#include <stdio.h>

int nesting = 0;  // Comment nesting level
%}

%x COMMENT
%option noyywrap

%%
"/*"            {
                  nesting = 1;
                  BEGIN(COMMENT);
                }

<COMMENT>"/*"   { nesting++; }

<COMMENT>"*/"   {
                  nesting--;
                  if (nesting == 0) BEGIN(INITIAL);
                }

<COMMENT>.|\n   ;  // Ignore everything inside comments

.|\n            { ECHO; }  // Output everything else
%%

int main() {
    yylex();
    return 0;
}
