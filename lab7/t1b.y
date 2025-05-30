%{
#include<stdio.h>
#include<stdlib.h>
%}
%token INT FLOAT VOID DOUBLE CHAR LONG SM CM ID NL
%%
stmt: e NL {printf("Valid expression\n"); return 1;}
e: INT ID '(' tmp ')' SM
 |LONG ID '(' tmp ')' SM
 |FLOAT ID '(' tmp ')' SM
 |DOUBLE ID '(' tmp ')' SM
 |VOID ID '(' tmp ')' SM
 |CHAR ID '(' tmp ')' SM
 ;

tmp: INT ID tp
    |LONG ID tp
    |FLOAT ID tp
    |DOUBLE ID tp
    |CHAR ID tp
    |
    ;
tp: CM INT ID tp
    | CM LONG ID tp
    | CM FLOAT ID tp
    | CM DOUBLE ID tp
    | CM CHAR ID tp
    |
    ;
%%

int main(){
    printf("Enter expression: ");
    yyparse();
    return 0;
}

void yyerror(const char* s){
    fprintf(stderr,"Error:%s\n",s);
    exit(1);
}