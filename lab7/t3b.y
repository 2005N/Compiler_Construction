%{
#include<stdio.h>
#include<stdlib.h>  
double ans;  
%}

%union{
    int ival;
    double dval;
}

%token NL 
%token <ival> NUM
%type <dval> stmt expr term mulex

%left '+' '-'
%left '*' '/'

%%
stmt: expr NL {ans = $1; printf("answer: %lf\n",ans); return 1;}
;
expr: expr '+' mulex    {$$=$1+$3;}
    | expr '-' mulex    {$$=$1-$3;}
    | mulex     {$$=$1;}
    ;
mulex: mulex '*' term   {$$=$1*$3;}
    | mulex '/' term    {$$=$1/$3;}
    | term      {$$=$1;}
    ;
term: '(' expr ')'  {$$=$2;}
    | NUM {$$=(double)$1;}
    ;

%%

int main(){
    printf("Enter expression: ");
    yyparse();
    return 0;
}

void yyerror(const char* s){
    fprintf(stderr,"Error: %s\n",s);
    exit(1);
}