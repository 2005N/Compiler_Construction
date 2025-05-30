%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "parser.tab.h" 

char* symbolTable[200];
int symbolCount = 0;
int beginflag = 0;
int endflag = 0;
int no_of_placeholders = 0;
int no_of_variables = 0;
int no_of_commas = 0;
int validvariables = 1;

// Values to pass to parser
char* idVal;
int intVal;
char charVal;
char* strVal;
char* baseIntVal;

int isKeyword(char* str) {
    char keywords[][20] = {"int", "if", "else", "while", "for", "main", "begin", "end", "input", "output", "program", "VarDecl", "inc", "dec", "do", "to", "print", "char"};
    for (int i = 0; i < 18; i++) {
        if (strcmp(str, keywords[i]) == 0) return 1;
    }
    return 0;
}

int isValidIdentifier(char* str) {
    if (!(str[0] >= 'a' && str[0] <= 'z')) return 0;
    int underscoreCount = 0;
    for (size_t i = 1; i < strlen(str); i++) {
        if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9') || (str[i] == '_'))) return 0;
        if (str[i] == '_') {
            underscoreCount++;
            if (underscoreCount > 1) return 0;
        }
    }
    return 1;
}

int get_no_of_placeholders(char* str) {
    int count = 0;
    while(*str) {
        if(*str=='@') {
            count++;
        }
        str++;
    }
    return count;
}

int get_no_of_commas(char* str) {
    int count = 0;
    while(*str) {
        if(*str==',') {
            count++;
        }
        str++;
    }
    return count;
}

void validateIntegerConstant(char* digits, char* base) {
    if (!digits || !base) {
        fprintf(stderr, "Error: Null pointer passed to validateIntegerConstant\n");
        return;
    }

    char tempDigits[128] = {0};
    char tempBase[16] = {0};
    
    strncpy(tempDigits, digits, 127);
    strncpy(tempBase, base, 15);
    
    char *start = tempBase;
    while (*start && isspace(*start)) start++;
    
    if (*start == '\0') {
        printf("Syntax Error: Empty base\n");
        return; // Don't exit
    }
    
    char *endptr;
    long b = strtol(start, &endptr, 10);
    
    if (b != 2 && b != 8 && b != 10) {
        printf("Syntax Error: Invalid base %ld\n", b);
        return; // Don't exit
    }
    
    for (int i = 0; tempDigits[i] != '\0' && i < 128; i++) {
        if (b == 2 && (tempDigits[i] != '0' && tempDigits[i] != '1')) {
            printf("Syntax Error: Invalid digit for binary\n");
            return; // Don't exit
        }
        if (b == 8 && (tempDigits[i] < '0' || tempDigits[i] > '7')) {
            printf("Syntax Error: Invalid digit for octal\n");
            return; // Don't exit
        }
        if (b == 10 && !isdigit(tempDigits[i])) {
            printf("Syntax Error: Invalid digit for decimal\n");
            return; // Don't exit
        }
    }
    
    //printf("(%s, %s)    Integer constant\n", digits, base);
    baseIntVal = strdup(digits); // Store the value for use in parser
    if (!baseIntVal) {
        fprintf(stderr, "Memory allocation failed\n");
        //exit(1);
        validvariables = 0;
        return;
    }
}

int isDeclared(char* name) {
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i], name) == 0) return 1;
    }
    return 0;
}

void addToSymbolTable(char* name) {
    if (!isDeclared(name) && symbolCount < 200) {
        symbolTable[symbolCount++] = strdup(name);
    }
}
%}

%option noyywrap

%s COMMENT

%%

[ \t\n]+                { /* ignore whitespace */ }
"//".*                  { /* printf("%s        ",yytext);  printf("Single-line comment\n"); */ }
"/*"                    { /*printf("%s        ",yytext); BEGIN(COMMENT); printf("Multi-line comment begins\n"); */ }
<COMMENT>[^*]*          { /* printf("%s        ",yytext); printf("Multi-line comment \n"); */}
<COMMENT>"*"+[^*/]*     { /*printf("%s        ",yytext); printf("Multi-line comment \n"); */}
<COMMENT>"*/"           { /*printf("%s        ",yytext); BEGIN(INITIAL); printf("Multi-line comment ends\n"); */ }

"begin program:"        { /*printf("%s   Program begin\n", yytext);*/ return BEGIN_PROGRAM; }
"end program"           { /*printf("%s   Program end\n", yytext);*/ return END_PROGRAM; }
"begin VarDecl:"        { /*printf("%s   Variable declaration begin\n", yytext);*/ return BEGIN_VARDECL; }
"end VarDecl"           { /*printf("%s   Variable declaration end\n", yytext);*/ return END_VARDECL; }

"int"                   { /*printf("%s   Type\n", yytext);*/ return INT_TYPE; }
"char"                  { /*printf("%s   Type\n", yytext);*/ return CHAR_TYPE; }

"print"                 { /*printf("%s   Keyword\n", yytext);*/ return PRINT; }
"scan"                  { /*printf("%s   Keyword\n", yytext);*/ return SCAN; }

\"[^\"]*\"              { 
                          strVal = strdup(yytext);
                          if (strchr(yytext, '@')) {
                              no_of_placeholders = get_no_of_placeholders(yytext);
                              if ((no_of_commas = get_no_of_commas(yytext))) {
                                  //printf("%s   Input format\n", yytext);
                                  return INPUT_FORMAT;
                              } else {
                                  //printf("%s   String format\n", yytext);
                                  return STRING_FORMAT;
                              }
                          } else {
                              //printf("%s   String constant\n", yytext);
                              return STRING_CONST;
                          }
                        }

"if"                    { /*printf("%s   Keyword\n", yytext);*/ return IF; }
"else"                  { /*printf("%s   Keyword\n", yytext);*/ return ELSE; }
"while"                 { /*printf("%s   Keyword\n", yytext);*/ return WHILE; }
"for"                   {/* printf("%s   Keyword\n", yytext);*/ return FOR; }
"do"                    { /*printf("%s   Keyword\n", yytext);*/ return DO; }
"to"                    { /*printf("%s   Keyword\n", yytext);*/ return TO; }
"inc"                   { /*printf("%s   Keyword\n", yytext);*/ return INC; }
"dec"                   { /*printf("%s   Keyword\n", yytext);*/ return DEC; }
"begin"                 { /*printf("%s   Keyword\n", yytext);*/ return BEGIN_K; }
"end"                   { /*printf("%s   Keyword\n", yytext);*/ return END_K; }

":="                    { /*printf("%s   Assignment operator\n", yytext);*/ return ASSIGN; }
"+="                    { /*printf("%s   Assignment operator\n", yytext);*/ return ADD_ASSIGN; }
"-="                    { /*printf("%s   Assignment operator\n", yytext);*/ return SUB_ASSIGN; }
"*="                    { /*printf("%s   Assignment operator\n", yytext);*/ return MUL_ASSIGN; }
"/="                    { /*printf("%s   Assignment operator\n", yytext);*/ return DIV_ASSIGN; }
"%="                    { /*printf("%s   Assignment operator\n", yytext);*/ return MOD_ASSIGN; }

"+"                     { /*printf("%s   Arithmetic operator\n", yytext);*/ return PLUS; }
"-"                     { /*printf("%s   Arithmetic operator\n", yytext);*/ return MINUS; }
"*"                     { /*printf("%s   Arithmetic operator\n", yytext);*/ return MULTIPLY; }
"/"                     { /*printf("%s   Arithmetic operator\n", yytext);*/ return DIVIDE; }
"%"                     { /*printf("%s   Arithmetic operator\n", yytext);*/ return MODULO; }

"<"                     { /*printf("%s   Relational operator\n", yytext);*/ return LT; }
">"                     { /*printf("%s   Relational operator\n", yytext);*/ return GT; }
"<="                    { /*printf("%s   Relational operator\n", yytext);*/ return LE; }
">="                    { /*printf("%s   Relational operator\n", yytext);*/ return GE; }
"<>"                    { /*printf("%s   Relational operator\n", yytext);*/ return NE; }

"("                     { /*printf("%s   Separator\n", yytext);*/ return LPAREN; }
")"                     { /*printf("%s   Separator\n", yytext);*/ return RPAREN; }
"{"                     { /*printf("%s   Separator\n", yytext);*/ return LBRACE; }
"}"                     { /*printf("%s   Separator\n", yytext);*/ return RBRACE; }
"["                     { /*printf("%s   Separator\n", yytext);*/ return LBRACKET; }
"]"                     { /*printf("%s   Separator\n", yytext);*/ return RBRACKET; }
";"                     { /*printf("%s   Separator\n", yytext);*/ return SEMICOLON; }
","                     { /*printf("%s   Separator\n", yytext);*/ return COMMA; }
":"                     { /*printf("%s   Separator\n", yytext);*/ return COLON; }

\([ ]*[0-9]+[ ]*,[ ]*[0-9]*[ ]*\) {
    char digits[128] = {0}, base[16] = {0};
    int result = sscanf(yytext, "(%[^,],%[^)])", digits, base);
    
    if (result != 2) {
        printf("Syntax Error"); //exit(1);
    }
    
    // Clean up spaces
    char* end = digits + strlen(digits) - 1;
    while(end > digits && isspace(*end)) *end-- = '\0';
    char* start = digits;
    while(*start && isspace(*start)) start++;
    
    char* baseStart = base;
    while(*baseStart && isspace(*baseStart)) baseStart++;
    
    // Store full format so we can directly use it in the parser
    baseIntVal = strdup(yytext);
    
    return BASE_INT;
}
[0-9]+                  { 
                          //printf("%s   Integer constant\n", yytext);
                          yylval.num = atoi(yytext); 
                          return INT_CONST; 
                        }
\'[^\']\' { 
                          //printf("%s   Character constant\n", yytext);
                          charVal = yytext[1]; 
                          return CHAR_CONST; 
                        }

[a-z][a-z0-9_]*         {
                          if (!isValidIdentifier(yytext)) {
                              printf("Syntax Error"); //exit(1);
                          } else {
                              //printf("%s   Identifier\n", yytext);
                              yylval.id = strdup(yytext);
                              addToSymbolTable(yylval.id );
                              return IDENTIFIER;
                          }
                        }

.                       { printf("ERROR: Invalid token '%s'\n", yytext); return ERROR; }

%%