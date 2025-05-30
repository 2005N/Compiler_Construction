%{
#include <stdio.h>
#include <string.h>

int in_paragraph = 0;

void start_paragraph() {
    if (!in_paragraph) {
        printf("<p>");
        in_paragraph = 1;
    }
}

void end_paragraph() {
    if (in_paragraph) {
        printf("</p>\n");
        in_paragraph = 0;
    }
}
%}

%option noyywrap

%x BOLD ITALIC

%%
^#{1} [^\n]+      {
                    end_paragraph();
                    printf("<h1>%s</h1>\n", yytext + 2);
                 }

^#{2} [^\n]+      {
                    end_paragraph();
                    printf("<h2>%s</h2>\n", yytext + 3);
                 }

^#{3} [^\n]+      {
                    end_paragraph();
                    printf("<h3>%s</h3>\n", yytext + 4);
                 }

"**"              { start_paragraph(); printf("<b>"); BEGIN(BOLD); }

<BOLD>"**"        { printf("</b>"); BEGIN(INITIAL); }
<BOLD>.|\n        { ECHO; }

"*"               { start_paragraph(); printf("<i>"); BEGIN(ITALIC); }

<ITALIC>"*"       { printf("</i>"); BEGIN(INITIAL); }
<ITALIC>.|\n      { ECHO; }

^[ \t]*\n         { end_paragraph(); } // Empty line ends paragraph

[^\n]+            { start_paragraph(); ECHO; }

\n                { printf("\n"); }

.                 { start_paragraph(); ECHO; }

%%

int main() {
    yylex();
    end_paragraph(); // close any open paragraph at EOF
    return 0;
}
