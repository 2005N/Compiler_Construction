%{
#include<stdio.h>
#include<stdlib.h>
%}
%token INT FLOAT VOID DOUBLE CHAR SM CM ID NL
%%
stmt: e NL {printf("Valid expression\n"); return 1;}
e: INT ID tmp SM { }
    |CHAR ID tmp SM { }
    |FLOAT ID tmp SM { }
    |DOUBLE ID tmp SM { }
    |VOID ID tmp SM { }
    ;
tmp: CM ID tmp
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