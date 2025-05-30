%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "test2.tab.h" 

char* symbolTable[200];
int symbolCount = 0;
int beginflag = 0;
int endflag = 0;
int no_of_placeholders = 0;
int no_of_variables = 0;
int no_of_commas = 0;
int validvariables = 1;

int isKeyword(char* str) {
    char keywords[][20] = {"int", "if", "else", "while", "for", "main", "begin", "end", "input", "output", "program", "VarDecl", "inc", "dec", "do", "to", "print", "char"};
    for (int i = 0; i < 18; i++ ) {
        if (strcmp(str, keywords[i]) == 0)   return 1;
    }
    return 0;
}

int isValidIdentifier(char* str) {
    if (!(str[0] >= 'a' &&  str[0] <= 'z'))   return 0;
    int underscoreCount = 0;
    for (size_t i = 1; i < strlen(str);  i++) {
        if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9') || (str[i] == '_')))   return 0;
        if (str[i] == '_') {
            underscoreCount++;
            if (underscoreCount > 1)  return 0;
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

int get_no_of_commas(char* str ) {
    int count =  0;
    while(*str) {
        if(*str==',') {
            count++;
        }
        str++;
    }

    return count;
}

void validateIntegerConstant(char* digits, char* base) {

    char* value = strdup(digits);
    char* baseStr = strdup(base);
    
    if (!value || !baseStr) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    char *baseStart = baseStr;
    while (*baseStart && isspace(*baseStart)) baseStart++;
    
    if (*baseStart == '\0') {
        free(value);
        free(baseStr);
        printf("Output: Syntax Error\n");
        exit(1);
    }

    char *endptr;
    long b = strtol(baseStart, &endptr,10);
    
    if (b != 2 && b != 8 && b != 10) {
        free(value);
        free(baseStr );
        printf("Output: Syntax Error\n");
        exit(1);
    }
    
    // Trim spaces from value
    char *valueStart = value;
    while (*valueStart && isspace(*valueStart)) valueStart++;
    char *valueEnd = valueStart + strlen(valueStart) - 1;
    while (valueEnd > valueStart && isspace(*valueEnd)) {
        *valueEnd = '\0';
        valueEnd--;
    }
    
    // Validate digits for the given base
    for (char *p =  valueStart; *p;  p++) {
        if (b == 2 && (*p != '0' && *p != '1')) {
            free( value);
            free( baseStr);
            printf("Output: Syntax Error\n");
            exit(1);
        }
        if (b == 8 && (*p < '0' || *p > '7')) {
            free( value);
            free( baseStr);
            printf( "Output: Syntax Error\n");
            exit(1);
        }

        if (b == 10 && !isdigit(*p) ) {
            free(value);
            free(baseStr);
            printf("Output: Syntax Error\n");
            exit(1);
        }
    }
    
    // Store original strings for AST
    yylval.sval = strdup(valueStart);  
    

    
    free(value);
    free(baseStr);
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

[ \t\n]+ { /* ignore whitespace */ }
"//".*    {  /*return COMMENT;*/ }
"/*"  {  BEGIN(COMMENT);/*return COMMENT_BEGIN;*/ }
<COMMENT>[^*]*     {}
<COMMENT>"*"+[^*/]*     { }
<COMMENT>"*/"    { BEGIN(INITIAL);/*return COMMENT_END;*/ }

"begin program:"    { return BEGIN_PROGRAM;}
"end program"   {    return END_PROGRAM; }
"begin VarDecl:"    {  return BEGIN_VARDECL;}
"end VarDecl"       { return END_VARDECL; }

"int" {  return INT_TYPE; }
"char"   {  return CHAR_TYPE;}

"print"     {   return PRINT;}
"scan"      { return SCAN; }

\"[^\"]*\"              { 
                          yylval.sval = strdup(yytext);
                          if (strchr(yytext, '@')) {
                              no_of_placeholders = get_no_of_placeholders(yytext);
                              if (no_of_commas = get_no_of_commas(yytext)) {
                                  
                                  return INPUT_FORMAT;
                              } else {
                                  
                                  return STRING_FORMAT;
                              }
                          } else {
                              
                              return STRING_CONST;
                          }
                        }

"if"           {  return IF; }
"else"          {  return ELSE; }
"while"         {return WHILE; }
"for"            { return FOR; }
"do"             {   return DO; }
"to"            {  return TO; }
"inc"          {  return INC; }
"dec"            {   return DEC; }
"begin"        { return BEGIN_K; }
"end"         {   return END_K; }

":="         {  return ASSIGN; }
"+="          {   return ADD_ASSIGN; }
"-="         {  return SUB_ASSIGN; }
"*="          {  return MUL_ASSIGN; }
"/="          {  return DIV_ASSIGN; }
"%="          { return MOD_ASSIGN; }

"+"       {  return PLUS; }
"-"        {    return MINUS; }
"*"      {return MULTIPLY; }
"/"      {    return DIVIDE; }
"%"     { return MODULO; }

"<"     {  return LT; }
">"      { return GT; }
"<="    { return LE; }
">="    {  return GE; }
"<>"     {  return NE; }

"("            {  return LPAREN; }
")"             { return RPAREN; }
"{"            {  return LBRACE; }
"}"            {  return RBRACE; }
"["            {  return LBRACKET; }
"]"            {   return RBRACKET; }
";"            {  return SEMICOLON; }
","             {   return COMMA; }
":"             { return COLON; }

\([ ]*[0-9]+[ ]*,[ ]*[0-9]*[ ]*\) {
                        char digits[128] = {0}, base[16] =  {0};
                         int result = sscanf(yytext, "(%[^,],%[^)])",  digits,  base);
                          
                        if (result != 2) {
                              printf("Output: Syntax Error" );  exit(1);
                          }
                          
                        char* end = digits + strlen(digits) - 1;
                         while(end > digits && isspace(*end)) *end-- =  '\0';
                          char* start = digits;
                          while(*start && isspace(*start))  start++;
                          
                          char* baseStart = base;
                          while(*baseStart && isspace(*baseStart))  baseStart++;
                          
                          // Store both value and base for parser
                          char fullVal[256];
                          snprintf(fullVal, sizeof(fullVal),  "%s,%s", start, baseStart);
                          yylval.sval = strdup(fullVal);
                          
                          return BASE_INT;
                        }

[0-9]+                  {  return INT_CONST; }
\'[^\']\' {  return CHAR_CONST; }

[a-z][a-z0-9_]*    { yylval.sval = strdup(yytext);
                        if (!isValidIdentifier(yytext)) {
                            printf("Output: Syntax Error"); exit(1);
                        } else {
                            
                            return IDENTIFIER;
                        }
                    }

.      {  return ERROR; }

%%