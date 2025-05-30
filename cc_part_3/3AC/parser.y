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

// Import the values from lexer
extern char* idVal;
extern int intVal;
extern char charVal;
extern char* strVal;
extern char* baseIntVal;
extern char* baseVal;  // Added to store the base value too

void yyerror(const char* s);

// 3AC Generation code
int qind = 0;
struct quadruple {
    char operator[10];
    char operand1[20];
    char operand2[20];
    char result[20];
    int is_label;     // Flag to indicate if this is a label
    int is_if;        // Flag to indicate if this is an if statement
    int is_goto;      // Flag to indicate if this is a goto statement
} quad[100];

void addQuadruple(char op1[], char op[], char op2[], char result[]) {
    if (qind >= 100) {
        fprintf(stderr, "Quadruple array overflow\n");
        return;
    }
    
    if (op) strcpy(quad[qind].operator, op);
    else quad[qind].operator[0] = '\0';
    
    if (op1) strcpy(quad[qind].operand1, op1);
    else quad[qind].operand1[0] = '\0';
    
    if (op2) strcpy(quad[qind].operand2, op2);
    else quad[qind].operand2[0] = '\0';
    
    if (result) strcpy(quad[qind].result, result);
    else quad[qind].result[0] = '\0';
    
    quad[qind].is_label = 0;
    quad[qind].is_if = 0;
    quad[qind].is_goto = 0;
    
    qind++;
}

// Add a label to the quadruple table
void addLabel(char *label) {
    strcpy(quad[qind].result, label);
    quad[qind].operator[0] = '\0';
    quad[qind].operand1[0] = '\0';
    quad[qind].operand2[0] = '\0';
    quad[qind].is_label = 1;
    quad[qind].is_if = 0;
    quad[qind].is_goto = 0;
    qind++;
}

// Add a goto statement to the quadruple table
void addGoto(char *label) {
    strcpy(quad[qind].result, "goto");
    strcpy(quad[qind].operand1, label);
    quad[qind].operator[0] = '\0';
    quad[qind].operand2[0] = '\0';
    quad[qind].is_label = 0;
    quad[qind].is_if = 0;
    quad[qind].is_goto = 1;
    qind++;
}

void addIf(char *cond, char *label) {
    strcpy(quad[qind].result, "if");
    strcpy(quad[qind].operand1, cond);
    strcpy(quad[qind].operator, "==");
    strcpy(quad[qind].operand2, "0");
    quad[qind].is_label = 0;
    quad[qind].is_if = 1;
    quad[qind].is_goto = 0;
    
    qind++;
    
    // Add the goto part
    strcpy(quad[qind].result, "goto");
    strcpy(quad[qind].operand1, label);
    quad[qind].operator[0] = '\0';
    quad[qind].operand2[0] = '\0';
    quad[qind].is_label = 0;
    quad[qind].is_if = 0;
    quad[qind].is_goto = 1;
    
    qind++;
}

void display_Quad() {
    if (qind <= 0) {
        printf("Error: No quadruple to display\n");
        return;
    }
    
    int idx = qind - 1;
    
    if (quad[idx].is_label) {
        printf("%s:\n", quad[idx].result);
    } else if (quad[idx].is_if) {
        printf("if %s %s %s goto %s\n", 
               quad[idx].operand1, 
               quad[idx].operator, 
               quad[idx].operand2, 
               quad[idx+1].operand1);
    } else if (quad[idx].is_goto) {
        printf("goto %s\n", quad[idx].operand1);
    } else {
        // Normal quadruple with assignment
        if (quad[idx].operator[0]) {
            printf("%s := %s %s %s\n", 
                  quad[idx].result, 
                  quad[idx].operand1, 
                  quad[idx].operator, 
                  quad[idx].operand2);
        } else if (quad[idx].operand1[0]) { // Check if operand1 exists
            printf("%s := %s\n", 
                  quad[idx].result, 
                  quad[idx].operand1);
        }
    }
}

// Function to print entire quad table with proper formatting
void print_Quad_Table() {
    printf("\n..............3AC Code.............\n");
    for (int i = 0; i < qind; i++) {
        if (quad[i].is_label) {
            printf("%s:\n", quad[i].result);
        } else if (quad[i].is_if) {
            printf("if %s %s %s goto %s\n", 
                   quad[i].operand1, 
                   quad[i].operator, 
                   quad[i].operand2, 
                   quad[i+1].operand1);
            i++; // Skip the goto part since we've included it
        } else if (quad[i].is_goto) {
            printf("goto %s\n", quad[i].operand1);
        } else {
            // Normal quadruple with assignment
            if (quad[i].operator[0]) {
                printf("%s := %s %s %s\n", 
                      quad[i].result, 
                      quad[i].operand1, 
                      quad[i].operator, 
                      quad[i].operand2);
            } else if (quad[i].operand1[0]) { // Check if operand1 exists
                printf("%s := %s\n", 
                      quad[i].result, 
                      quad[i].operand1);
            }
        }
    }
}
int temp_count = 1;
// Function to generate temporary variable names
char* newTemp() {
    char *temp = malloc(10); // Dynamically allocate
    sprintf(temp, "t%d", temp_count++);
    return temp;
}

// For handling labels in control structures
int label_count = 1;
char* newLabel() {
    char *label = malloc(10); // Dynamically allocate
    sprintf(label, "L%d", label_count++);
    return label;
}

// Stack implementation for expression handling
int tos = -1;
struct stack {
    char c[20];
} stk[100];

void push(char *c) {
    strcpy(stk[++tos].c, c);
}

char* pop() {
    if (tos < 0) {
        fprintf(stderr, "Stack underflow error\n");
        // Return a safe default value instead of crashing
        return "";
    }
    return stk[tos--].c;
}

%}

%union {
    char *id;
    int num;
    char chr;
    char *str;
    
    // For 3AC code generation
    struct {
        char place[20];    // Place to store the result
        char *true_label;  // For boolean expressions
        char *false_label; // For boolean expressions
        char *next_label;  // For control flow
        int quad_index;    // Index in quad array
        
        // Additional fields for for-loop
        char *loop_var;    // Loop variable
        char *upper;       // Upper bound
        char *step;        // Step value
        char *loop_start;  // Loop start label
        char *loop_end;    // Loop end label
    } attr;
}

%token BEGIN_PROGRAM END_PROGRAM BEGIN_VARDECL END_VARDECL BEGIN_K END_K
%token INT_TYPE CHAR_TYPE
%token COLON SEMICOLON COMMA
%token PRINT SCAN 
%token IF ELSE WHILE FOR DO TO INC DEC
%token ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
%token PLUS MINUS MULTIPLY DIVIDE MODULO
%token LT GT LE GE NE
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token <num> INT_CONST
%token <chr> CHAR_CONST
%token <str> STRING_CONST STRING_FORMAT INPUT_FORMAT BASE_INT
%token <id> IDENTIFIER
%token ERROR

%type <attr> expression term factor condition
%type <attr> if_statement while_statement for_statement print_statement scan_statement
%type <attr> inc_statement dec_statement
%type <id> relational_op

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
                  {
                      // Generate 3AC for array declaration
                      char size[10];
                      sprintf(size, "%d", $4);
                      addQuadruple("array", size, "", $2);
                  }
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
           {
               // Generate 3AC for simple assignment
               addQuadruple($3.place, "", "", $1);
           }
           | IDENTIFIER ADD_ASSIGN expression
           {
               // Generate 3AC for += operator
               char *temp = newTemp();
               addQuadruple($1, "+", $3.place, temp);
               addQuadruple(temp, "", "", $1);
           }
           | IDENTIFIER SUB_ASSIGN expression
           {
               // Generate 3AC for -= operator
               char *temp = newTemp();
               addQuadruple($1, "-", $3.place, temp);
               addQuadruple(temp, "", "", $1);
           }
           | IDENTIFIER MUL_ASSIGN expression
           {
               // Generate 3AC for *= operator
               char *temp = newTemp();
               addQuadruple($1, "*", $3.place, temp);
               addQuadruple(temp, "", "", $1);
           }
           | IDENTIFIER DIV_ASSIGN expression
           {
               // Generate 3AC for /= operator
               char *temp = newTemp();
               addQuadruple($1, "/", $3.place, temp);
               addQuadruple(temp, "", "", $1);
           }
           | IDENTIFIER MOD_ASSIGN expression
           {
               // Generate 3AC for %= operator
               char *temp = newTemp();
               addQuadruple($1, "%", $3.place, temp);
               addQuadruple(temp, "", "", $1);
           }
           | IDENTIFIER LBRACKET expression RBRACKET ASSIGN expression
           {
               // Generate 3AC for array assignment
               char index_str[20];
               sprintf(index_str, "%s[%s]", $1, $3.place);
               addQuadruple($6.place, "", "", index_str);
           }
           ;

print_statement : PRINT LPAREN STRING_CONST RPAREN
                {
                    // Generate 3AC for print with string constant
                    addQuadruple("print", $3, "", "_");
                    $$.place[0] = '\0'; // Initialize place
                }
                | PRINT LPAREN STRING_CONST print_vars RPAREN 
                {
                    if (no_of_placeholders > 0) {
                        fprintf(stderr, "Error: String constant contains @ but placeholders not expected\n");
                        YYERROR;
                    }
                    // Generate 3AC for print with multiple variables
                    addQuadruple("print", $3, "", "_");
                    $$.place[0] = '\0'; // Initialize place
                }
                | PRINT LPAREN STRING_FORMAT RPAREN 
                {
                    if (no_of_placeholders > 0) {
                        fprintf(stderr, "Error: Format string contains @ but no variables provided\n");
                        YYERROR;
                    }
                    // Generate 3AC for print with format string
                    addQuadruple("printf", $3, "", "_");
                    $$.place[0] = '\0'; // Initialize place
                }
                | PRINT LPAREN STRING_FORMAT print_vars RPAREN 
                {
                    if (no_of_placeholders != no_of_variables || !validvariables) {
                        fprintf(stderr, "Error: Number of placeholders (%d) does not match number of variables (%d)\n", 
                                no_of_placeholders, no_of_variables);
                        YYERROR;
                    }
                    no_of_placeholders = 0;
                    no_of_variables = 0;
                    validvariables = 1;
                    // Generate 3AC for printf with variables
                    addQuadruple("printf", $3, "", "_");
                    $$.place[0] = '\0'; // Initialize place
                }
                ;

print_vars : COMMA IDENTIFIER 
           { 
               no_of_variables++; 
               // Generate 3AC for print variable
               addQuadruple("param", $2, "", "_");
           }
           | COMMA IDENTIFIER print_vars 
           { 
               no_of_variables++; 
               // Generate 3AC for print variable
               addQuadruple("param", $2, "", "_");
           }
           ;

scan_statement : SCAN LPAREN STRING_CONST RPAREN
               {
                   // Generate 3AC for scan
                   addQuadruple("scan", $3, "", "_");
                   $$.place[0] = '\0'; // Initialize place
               }
               | SCAN LPAREN STRING_CONST scan_vars RPAREN 
               {
                   if (no_of_placeholders > 0) {
                       fprintf(stderr, "Error: String constant contains @ but placeholders not expected\n");
                       YYERROR;
                   }
                   // Generate 3AC for scan with multiple variables
                   addQuadruple("scan", $3, "", "_");
                   $$.place[0] = '\0'; // Initialize place
               }
               | SCAN LPAREN INPUT_FORMAT RPAREN 
               {
                   if (no_of_placeholders > 0) {
                       fprintf(stderr, "Error: Input format contains @ but no variables provided\n");
                       YYERROR;
                   }
                   // Generate 3AC for scan with format
                   addQuadruple("scanf", $3, "", "_");
                   $$.place[0] = '\0'; // Initialize place
               }
               | SCAN LPAREN INPUT_FORMAT scan_vars RPAREN 
               {
                   if (no_of_placeholders != no_of_variables || !validvariables || 
                       (no_of_commas != no_of_placeholders-1 && no_of_placeholders != 0)) {
                       fprintf(stderr, "Error: Invalid scan statement\n");
                       YYERROR;
                   }
                   no_of_placeholders = 0;
                   no_of_variables = 0;
                   no_of_commas = 0;
                   validvariables = 1;
                   // Generate 3AC for scanf with variables
                   addQuadruple("scanf", $3, "", "_");
                   $$.place[0] = '\0'; // Initialize place
               }
               ;

scan_vars : COMMA IDENTIFIER 
          { 
              no_of_variables++; 
              // Generate 3AC for scan variable
              addQuadruple("read", "", "", $2);
          }
          | COMMA IDENTIFIER scan_vars 
          { 
              no_of_variables++; 
              // Generate 3AC for scan variable
              addQuadruple("read", "", "", $2);
          }
          ;

if_statement : IF LPAREN condition RPAREN 
             {
                 // Create labels before processing statements
                 char *else_label = newLabel();
                 char *end_label = newLabel();
                 
                 // If condition is false, jump to else_label
                 addIf($3.place, else_label);
                 
                 // Save these labels for later use
                 $<attr>$.true_label = strdup(else_label);
                 $<attr>$.false_label = strdup(end_label);
             }
             statements
             {
                 // After if-body, jump to end
                 addGoto($<attr>5.false_label);
                 
                 // Add the else label
                 addLabel($<attr>5.true_label);
             }
             ELSE statements
             {
                 // Add the end label after both branches are processed
                 addLabel($<attr>5.false_label);
             }
             | IF LPAREN condition RPAREN
             {
                 // Create a single end label for the simple if
                 char *end_label = newLabel();
                 
                 // If condition is false, jump to end_label
                 addIf($3.place, end_label);
                 
                 // Save this label for later use
                 $<attr>$.next_label = strdup(end_label);
             }
             statements
             {
                 // Add the end label after if body
                 addLabel($<attr>5.next_label);
             }
             ;

while_statement : WHILE 
                {
                    // Create labels for the while loop
                    char *loop_start = newLabel();
                    char *loop_end = newLabel();
                    
                    // Add the loop start label BEFORE evaluating condition
                    addLabel(loop_start);
                    
                    // Save labels for later use
                    $<attr>$.loop_start = strdup(loop_start);
                    $<attr>$.loop_end = strdup(loop_end);
                }
                LPAREN condition RPAREN DO
                {
                    // If condition is false, goto loop_end
                    // This places the condition check BEFORE the loop body
                    addIf($4.place, $<attr>2.loop_end);
                }
                statements 
                {
                    // Jump back to loop start for next iteration
                    addGoto($<attr>2.loop_start);
                    
                    // Add the loop end label
                    addLabel($<attr>2.loop_end);
                }
                ;


for_statement : FOR IDENTIFIER ASSIGN expression 
              {
                  // Initialize loop variable
                  addQuadruple($4.place, "", "", $2);
                  
                  // Create labels
                  char *loop_start = newLabel();
                  char *loop_end = newLabel();
                  
                  // Add loop start label
                  addLabel(loop_start);
                  
                  // Save loop variable and labels
                  $<attr>$.loop_var = strdup($2);
                  $<attr>$.loop_start = strdup(loop_start);
                  $<attr>$.loop_end = strdup(loop_end);
              }
              TO expression 
              {
                  char *upper = newTemp();
                  addQuadruple($7.place, "", "", upper);
                  $<attr>$.upper = strdup(upper);
                  
                  // Generate condition - check if loop var <= upper bound (negated from > for addIf)
                  char *cond_temp = newTemp();
                  addQuadruple($<attr>5.loop_var, "<=", $<attr>$.upper, cond_temp);
                  
                  // Use the proper addIf function to create a combined if-goto
                  addIf(cond_temp, $<attr>5.loop_end);
              }
              inc_statement DO statements 
              {
                  // Apply increment
                  char *temp = newTemp();
                  addQuadruple($<attr>5.loop_var, "+", $9.step, temp);
                  addQuadruple(temp, "", "", $<attr>5.loop_var);
                  
                  // Loop back to start
                  addGoto($<attr>5.loop_start);
                  
                  // Add end label
                  addLabel($<attr>5.loop_end);
              }
              | FOR IDENTIFIER ASSIGN expression 
              {
                  // Initialize loop variable
                  addQuadruple($4.place, "", "", $2);
                  
                  // Create labels
                  char *loop_start = newLabel();
                  char *loop_end = newLabel();
                  
                  // Add loop start label
                  addLabel(loop_start);
                  
                  // Save loop variable and labels
                  $<attr>$.loop_var = strdup($2);
                  $<attr>$.loop_start = strdup(loop_start);
                  $<attr>$.loop_end = strdup(loop_end);
              }
              TO expression 
              {
                  // Store upper bound in a temp
                  char *upper = newTemp();
                  addQuadruple($7.place, "", "", upper);
                  $<attr>$.upper = strdup(upper);
                  
                  // Generate condition - check if loop var > upper bound
                  char *cond_temp = newTemp();
                  addQuadruple($<attr>5.loop_var, ">", $<attr>$.upper, cond_temp);
                  
                  // Exit loop if condition is true (loop var > upper bound)
                  addQuadruple(cond_temp, "==", "1", "if");
                  addGoto($<attr>5.loop_end);
              }
              dec_statement DO statements 
              {
                  // Apply decrement
                  char *temp = newTemp();
                  addQuadruple($<attr>5.loop_var, "-", $9.place, temp);
                  addQuadruple(temp, "", "", $<attr>5.loop_var);
                  
                  // Loop back to start
                  addGoto($<attr>5.loop_start);
                  
                  // Add end label
                  addLabel($<attr>5.loop_end);
              }
              ;

dec_statement : DEC expression
              {
                  // Store the decrement value in place
                  strcpy($$.place, $2.place);
                  
                  // Also store in step for for-loop
                  $$.step = strdup($2.place);
              }
              ;

inc_statement : INC expression
              {
                  // Store the increment value in place
                  strcpy($$.place, $2.place);
                  
                  // Also store in step for for-loop
                  $$.step = strdup($2.place);
              }
              ;



condition : expression relational_op expression
          {
              // Generate 3AC for condition
              char *temp = newTemp();
              addQuadruple($1.place, $2, $3.place, temp);
              strcpy($$.place, temp);
          }
          ;

relational_op : LT  { $$ = strdup("<"); }
              | GT  { $$ = strdup(">"); }
              | LE  { $$ = strdup("<="); }
              | GE  { $$ = strdup(">="); }
              | NE  { $$ = strdup("<>"); }
              ;

expression : term
           {
               strcpy($$.place, $1.place);
           }
           | expression PLUS term
           {
               char *temp = newTemp();
               addQuadruple($1.place, "+", $3.place, temp);
               strcpy($$.place, temp);
           }
           | expression MINUS term
           {
               char *temp = newTemp();
               addQuadruple($1.place, "-", $3.place, temp);
               strcpy($$.place, temp);
           }
           ;

term : factor
     {
         strcpy($$.place, $1.place);
     }
     | term MULTIPLY factor
     {
         char *temp = newTemp();
         addQuadruple($1.place, "*", $3.place, temp);
         strcpy($$.place, temp);
     }
     | term DIVIDE factor
     {
         char *temp = newTemp();
         addQuadruple($1.place, "/", $3.place, temp);
         strcpy($$.place, temp);
     }
     | term MODULO factor
     {
         char *temp = newTemp();
         addQuadruple($1.place, "%", $3.place, temp);
         strcpy($$.place, temp);
     }
     ;

factor : IDENTIFIER
       {
           strcpy($$.place, $1);
       }
       | IDENTIFIER LBRACKET expression RBRACKET
       {
           char array_ref[20];
           sprintf(array_ref, "%s[%s]", $1, $3.place);
           
           char *temp = newTemp();
           addQuadruple(array_ref, "", "", temp);
           
           strcpy($$.place, temp);
       }
       | INT_CONST
       {
           char int_str[10];
           sprintf(int_str, "%d", $1);
           strcpy($$.place, int_str);
       }
       | CHAR_CONST
       {
           char char_str[5];
           sprintf(char_str, "'%c'", charVal);
           strcpy($$.place, char_str);
       }
       | STRING_CONST
       {
           char *temp = newTemp();
           addQuadruple($1, "", "", temp);
           strcpy($$.place, temp);
       }
       | LPAREN expression RPAREN
       {
           strcpy($$.place, $2.place);
       }
       | BASE_INT
       {
           strcpy($$.place, baseIntVal);
       }
       ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "%s\n", s);
}

int main(int argc, char** argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            fprintf(stderr, "Error opening file %s\n", argv[1]);
            return 1;
        }
    } else {
        yyin = stdin;
    }

    yyparse();
    
    // Print the complete 3AC table
    print_Quad_Table();
    
    printf("\nOutput: Successfully parsed and generated 3AC code\n");
    
    if (yyin != stdin) {
        fclose(yyin);
    }
    
    return 0;
}