%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_palindrome(const char* str) {
    int len = strlen(str);
    for(int i = 0; i < len / 2; ++i) {
        if(str[i] != str[len - i - 1])
            return 0;
    }
    return 1;
}
%}

%union {
    char* sval;
}

%token NL
%token <sval> STR
%type <sval> exp

%%

stmt: exp NL {
    if (is_palindrome($1))
        printf("palindrome\n");
    else
        printf("not a palindrome\n");
    free($1);
    return 1;
}
;

exp: STR { $$ = $1; };

%%

int main() {
    printf("Enter expression: ");
    yyparse();

    return 0;
}

void yyerror(const char* s) {
    fprintf(stderr, "Error: %s\n", s);
}
