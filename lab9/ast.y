%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"  // Ensure this is included before %union

ASTNode* rootNode = NULL;

extern int yylex();
extern int yyparse();
extern FILE* yyin;
void yyerror(const char* s);
%}
%code requires {
    #include "ast.h"  // ✅ Ensures ASTNode is known in parser.tab.h
}
%union {
    int ival;
    char sval;
    ASTNode* ast;  // This should work if ast.h is included properly
}


%token NL
%token <ival> NUMBER
%token <sval> VAR

%left '+' '-' '='
%left '*' '/'

%type <ast> expr 

%%

stmt : expr NL { printf("Parsing successful!\n");
        printAST($1);
        
 return 0; }
     ;

expr: expr '=' expr         { $$ = createOperatorNode(NODE_EQ, $1, $3); }
    |  expr '+' expr         { $$ = createOperatorNode(NODE_ADD, $1, $3); }
    | expr '-' expr          { $$ = createOperatorNode(NODE_SUB, $1, $3); }
    | expr '*' expr       { $$ = createOperatorNode(NODE_MUL, $1, $3); }
    | expr '/' expr       { $$ = createOperatorNode(NODE_DIV, $1, $3); }
    | NUMBER                  { $$ = createNumberNode($1); }
    | VAR                   { $$ = createVarNode($1);}
    | '(' expr ')'          { $$ = $2; }
    ;

%%

int main() {
    printf("Enter input string: ");
    yyparse();
    printf("\n");

    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    exit(EXIT_FAILURE);
}
