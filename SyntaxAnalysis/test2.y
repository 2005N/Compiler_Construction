%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern int yylex();
extern FILE *yyin;
extern int no_of_placeholders;
extern int no_of_variables;
extern int no_of_commas;
extern int validvariables;

void yyerror(const char* s);
%}

%token BEGIN_PROGRAM END_PROGRAM BEGIN_VARDECL END_VARDECL BEGIN_K END_K
%token INT_TYPE CHAR_TYPE
%token COLON SEMICOLON COMMA
%token PRINT SCAN STRING_FORMAT INPUT_FORMAT
%token IF ELSE WHILE FOR DO TO INC DEC
%token ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
%token PLUS MINUS MULTIPLY DIVIDE MODULO
%token LT GT LE GE NE
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token INT_CONST CHAR_CONST STRING_CONST BASE_INT
%token IDENTIFIER ERROR

%start program

%%

program : BEGIN_PROGRAM vardecl_section statements END_PROGRAM
        ;

vardecl_section : BEGIN_VARDECL var_declarations END_VARDECL
                ;

var_declarations : /* empty */
                 | var_declaration var_declarations
                 ;

var_declaration : LPAREN IDENTIFIER COMMA type RPAREN SEMICOLON
                | LPAREN IDENTIFIER LBRACKET INT_CONST RBRACKET COMMA type RPAREN SEMICOLON
                ;

type : INT_TYPE
     | CHAR_TYPE
     ;

statements : /* empty */
           | BEGIN_K statement statements END_K 
           | statement statements
           ;

statement : assignment SEMICOLON
          | print_statement SEMICOLON
          | scan_statement SEMICOLON
          | if_statement SEMICOLON
          | while_statement SEMICOLON
          | for_statement SEMICOLON
          | inc_statement SEMICOLON
          | dec_statement SEMICOLON
          | error SEMICOLON { yyerrok; }
          ;


assignment : IDENTIFIER ASSIGN expression
           | IDENTIFIER ADD_ASSIGN expression
           | IDENTIFIER SUB_ASSIGN expression
           | IDENTIFIER MUL_ASSIGN expression
           | IDENTIFIER DIV_ASSIGN expression
           | IDENTIFIER MOD_ASSIGN expression
           | IDENTIFIER LBRACKET expression RBRACKET ASSIGN expression
           ;

print_statement : PRINT LPAREN STRING_CONST RPAREN
                | PRINT LPAREN STRING_CONST print_vars RPAREN {
                    if (no_of_placeholders > 0) {
                        fprintf(stderr, "Error: String constant contains @ but placeholders not expected\n");
                        YYERROR;
                    }
                  }
                | PRINT LPAREN STRING_FORMAT RPAREN {
                    if (no_of_placeholders > 0) {
                        fprintf(stderr, "Error: Format string contains @ but no variables provided\n");
                        YYERROR;
                    }
                  }
                | PRINT LPAREN STRING_FORMAT print_vars RPAREN {
                    if (no_of_placeholders != no_of_variables || !validvariables) {
                        fprintf(stderr, "Error: Number of placeholders (%d) does not match number of variables (%d)\n", 
                                no_of_placeholders, no_of_variables);
                        YYERROR;
                    }
                    no_of_placeholders = 0;
                    no_of_variables = 0;
                    validvariables = 1;
                  }
                ;

print_vars : COMMA IDENTIFIER { no_of_variables++; }
           | COMMA IDENTIFIER print_vars { no_of_variables++; }
           ;

scan_statement : SCAN LPAREN STRING_CONST RPAREN
               | SCAN LPAREN STRING_CONST scan_vars RPAREN {
                   if (no_of_placeholders > 0) {
                       fprintf(stderr, "Error: String constant contains @ but placeholders not expected\n");
                       YYERROR;
                   }
                 }
               | SCAN LPAREN INPUT_FORMAT RPAREN {
                   if (no_of_placeholders > 0) {
                       fprintf(stderr, "Error: Input format contains @ but no variables provided\n");
                       YYERROR;
                   }
                 }
               | SCAN LPAREN INPUT_FORMAT scan_vars RPAREN {
                   if (no_of_placeholders != no_of_variables || !validvariables || 
                       (no_of_commas != no_of_placeholders-1 && no_of_placeholders != 0)) {
                       fprintf(stderr, "Error: Invalid scan statement\n");
                       YYERROR;
                   }
                   no_of_placeholders = 0;
                   no_of_variables = 0;
                   no_of_commas = 0;
                   validvariables = 1;
                 }
               ;

scan_vars : COMMA IDENTIFIER { no_of_variables++; }
          | COMMA IDENTIFIER scan_vars { no_of_variables++; }
          ;

if_statement : IF LPAREN condition RPAREN statements
             | IF LPAREN condition RPAREN statements ELSE statements
             ;

while_statement : WHILE LPAREN condition RPAREN DO statements
                ;

for_statement : FOR IDENTIFIER ASSIGN expression TO expression inc_statement DO statements
              | FOR IDENTIFIER ASSIGN expression TO expression dec_statement DO statements
              ;

inc_statement : INC expression
              ;

dec_statement : DEC expression
              ;

condition : expression relational_op expression
          ;

relational_op : LT
              | GT
              | LE
              | GE
              | NE
              ;

expression : term
           | expression PLUS term
           | expression MINUS term
           ;

term : factor
     | term MULTIPLY factor
     | term DIVIDE factor
     | term MODULO factor
     ;

factor : IDENTIFIER
       | IDENTIFIER LBRACKET expression RBRACKET
       //| INT_CONST
       | CHAR_CONST
       | STRING_CONST
       | LPAREN expression RPAREN
       | BASE_INT
       ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "%s\n", s);
    exit(1);
}

int main(int argc, char** argv) {
    FILE* input_file = fopen("input.txt", "r");
    if (!input_file) {
        fprintf(stderr, "Cannot open file input.txt\n");
        return 1;
    }

    yyin = input_file;
    
    yyparse();
    
    printf("\nParsing completed. No syntax errors found.\n");
    
    fclose(input_file);
    return 0;
}