%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "q1.h"

extern int yylex();
extern int yyparse();
extern FILE* yyin;
void yyerror(const char* s);
%}

%union {
    int ival;
    char* sval;
}

%token <ival> NUM
%token <sval> VAR
%token INT CHAR FLOAT NL
%%

stmt : expr { 
                printSymbolTable();
                return 0; 
            }
     ;

expr: INT VAR tmp1 ';' expr          { insertSymbol($2, "int"); }
    | CHAR VAR tmp2 ';' expr          { insertSymbol($2, "char"); }
    | FLOAT VAR tmp3 ';' expr        { insertSymbol($2, "float"); }
    | {}
    ;

tmp1: ',' VAR tmp1              { insertSymbol($2, "int"); }
    | /* empty */               { }
    ;

tmp2: ',' VAR tmp2              { insertSymbol($2, "char"); }
    | /* empty */               { }
    ;

tmp3: ',' VAR tmp3              { insertSymbol($2, "float"); }
    | /* empty */               { }
    ;

%%

int main() {
    // Initialize symbol table
    initSymbolTable();
    
    printf("Enter input string: ");
    yyparse();
    printf("\n");

    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    exit(EXIT_FAILURE);
}