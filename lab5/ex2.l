%{
#include <stdio.h>
#include <stdlib.h>

double result = 0.0;
char op = '+'; // default to + for the first number

%}

%%
[0-9]+    {
              double num = atof(yytext);
              switch(op) {
                  case '+': result += num; break;
                  case '-': result -= num; break;
                  case '*': result *= num; break;
                  case '/': result /= num; break;
              }
          }

[+\-*/]   { op = yytext[0]; }

[\n]      { printf("Answer: %.2f\n", result); result = 0.0; op = '+'; }

[ \t]     ;   // skip whitespace

.         { printf("Invalid character: %s\n", yytext); }

%%

int main() {
    printf("Enter expression: ");
    yylex();
    return 0;
}
