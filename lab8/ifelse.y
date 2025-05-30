%{
#include<stdio.h>
#include<stdlib.h>

int yylex(void);
void yyerror(const char* s);
%}

%token IF ELSE ID NUM NL
%nonassoc IFX
%nonassoc ELSE

%%
sentence: stmt NL {printf("Valid if"); return 1;}
;
stmt: IF expr stmt %prec IFX
    | IF expr stmt ELSE stmt
    | ID '=' expr ';'
    | '{' stmt_list '}'
    ;
stmt_list: stmt
        | stmt_list stmt
        ;
expr: NUM
    | ID
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