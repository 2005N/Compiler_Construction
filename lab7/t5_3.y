%{
#include<stdio.h>
#include<stdlib.h>

void yyerror(const char* s);
int yylex(void);
%}
%token INT FLOAT VOID DOUBLE CHAR SM CM ID NL NUM EQ
%%
stmt: e NL {printf("Valid expression\n"); return 1;}
e: INT ID tmp SM { }
    |CHAR ID tmp SM { }
    |FLOAT ID tmp SM { }
    |DOUBLE ID tmp SM { }
    |VOID ID tmp SM { }
    |INT ID EQ NUM tmp SM { }
    |CHAR ID EQ NUM tmp SM { }
    |FLOAT ID EQ NUM tmp SM { }
    |DOUBLE ID EQ NUM tmp SM { }
    |VOID ID EQ NUM tmp SM { }
    ;
tmp: CM ID tmp
    | CM ID EQ NUM tmp
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