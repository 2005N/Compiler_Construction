%{
#include <stdio.h>
#include <string.h>
int s_comment = 0;
int m_comment = 0;
char line_buffer[1024];
int buffer_index = 0;

void flush_line() {
    line_buffer[buffer_index] = '\0';
    // Check if line is not empty
    int non_empty = 0;
    for (int i = 0; line_buffer[i]; i++) {
        if (line_buffer[i] != ' ' && line_buffer[i] != '\t' && line_buffer[i] != '\n')
            non_empty = 1;
    }
    if (non_empty) {
        fprintf(yyout, "%s\n", line_buffer);
    }
    buffer_index = 0; // reset for next line
}
%}
%s COMMENT
%%
"//".*              { s_comment++; /* skip single-line comment */ }
"/*"              { BEGIN(COMMENT); } // Start multi-line comment
<COMMENT>"*/"     { m_comment++; BEGIN(0); } // End multi-line comment
<COMMENT>.|\n     { /* Consume comment chars, do nothing */ }
\n                { flush_line(); } // On newline, flush if non-empty
.                 { if (buffer_index < sizeof(line_buffer) - 1) line_buffer[buffer_index++] = *yytext; }
%%

int main() {
    yyin = fopen("input.c", "r");
    yyout = fopen("output.txt", "w");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
