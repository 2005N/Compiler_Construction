%{
#include<stdio.h>
#include<stdlib.h> 
void yyerror(const char* s);
int yylex(void);   
%}

%union{
    int count;
}
%token ZERO ONE NL
%type <count> L B

%%

S: L NL {printf("Number in decimal: %d\n",$1); return 1;}
;
L: L B {$$=2*$1+$2;}
| B {$$=$1;}
;
B: ZERO {$$=0;}
| ONE {$$=1;}
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