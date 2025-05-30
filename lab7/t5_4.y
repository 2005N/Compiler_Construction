%{
#include<stdio.h>
#include<stdlib.h>

void yyerror(const char* s);
int yylex(void);
%}

%token IF THEN ELSE ID NL

%%
exp: stmt NL {printf("Valid"); return 1;}
stmt: match
    | unmatch
    ;
match: IF '(' ID ')' THEN match ELSE match
    | ID
    ;
unmatch: IF '(' ID ')' THEN stmt
        | IF '(' ID ')' THEN match ELSE unmatch
        ;
%%

int main(){
    printf("Enter input: ");
    yyparse();
    return 0;
}

void yyerror(const char* s){
    fprintf(stderr,"Error: %s\n",s);
    exit(1);
}