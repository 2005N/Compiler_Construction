%{
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
void yyerror(const char* s);
int yylex(void);
%}

%union {
    int ival;
}

%token <ival> NUM
%type <ival> expr stmt

%token NL 
%left '+' '-'
%left '*' '/'
%right '^'
%right UMINUS

%%
stmt: expr NL {printf("%d\n",$1); return 1;}
expr: expr '+' expr {$$ = $1 + $3;}
| expr '-' expr {$$ = $1 - $3;}
| expr '*' expr {$$ = $1 * $3;}
| expr '/' expr {$$ = $1 / $3;}
| '(' expr ')' {$$ = $2;}
| expr '^' expr {$$=pow($1,$3);}
| '-' expr %prec UMINUS {$$ = -$2;}
| NUM {$$ = $1;}
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