%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char* s);
int yylex(void);
%}

%union{
    int val;
}
%token NL
%token <val> BOOL
%left OR
%left AND
%right NOT
%token LP RP
%type <val> exp

%%
stmt: exp NL { printf("output: %d\n",$1); return 1;}
;
exp: exp AND exp {$$=$1 && $3;}
    | exp OR exp {$$=$1 || $3;}
    | NOT exp   {$$=!$2;}
    | LP exp RP {$$=$2;}
    | BOOL  {$$=$1;}
    ;

%%
int main() {
    printf("Enter Boolean expression:\n");
    yyparse();
    return 0;
}

void yyerror(const char* s) {
    fprintf(stderr, "Error: %s\n", s);
    exit(1);
}
