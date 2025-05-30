%{
#include<stdio.h>
#include<stdlib.h>   

void yyerror(const char* s);
int yylex(void);
%}

%token NL

%%
stmt: exp NL {printf("Valid paranthesis\n"); return 1;}
exp: exp pair
    |
    ;
pair: '(' exp ')'
    | '[' exp ']'
    | '{' exp '}'
    ;
%%

int main(){
    printf("Enter input: ");
    yyparse();
    return 0;
}

void yyerror(const char* s){
    fprintf(stderr,"Error:%s\n",s);
    exit(1);
}