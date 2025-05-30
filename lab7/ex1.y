%{
#include<stdio.h>
#include<stdlib.h>
%}
%token NL PL ST OB CB ID
%%
stmt: e NL {printf("Valid Expression\n"); return 1;};
e : e PL t { }
| t { }
;
t : t ST f { }
| f { }
;
f : OB e CB { }
| ID { }
;
%%
int main() {
printf("Enter Expression: ");
yyparse();
return 0;
}
void yyerror(const char *s) {
fprintf(stderr, "Error: %s\n", s);
exit(1);
}