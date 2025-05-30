%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void yyerror(const char* s);
int yylex(void);
%}

%union{
    struct{
        int zc;
        int oc;
    }t;
}

%token ZERO ONE NL
%type <t> L B

%%
S: L NL {
    printf("Number of zeros: %d, Number of ones: %d\n",$<t.zc>1,$<t.oc>1);
    return 1;
}
L : L B {$<t.zc>$=$<t.zc>1+$<t.zc>2; $<t.oc>$=$<t.oc>1+$<t.oc>2;}
    | B {$<t.zc>$=$<t.zc>1; $<t.oc>$=$<t.oc>1;}
    ;
B: ONE {$<t.zc>$=0; $<t.oc>$=1;}
    | ZERO {$<t.zc>$=1; $<t.oc>$=0;}
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