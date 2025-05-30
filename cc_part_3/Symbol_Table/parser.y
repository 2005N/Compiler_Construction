%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ast.h"

// AST root node
ASTNode *root = NULL;

extern int yylex();
extern FILE *yyin;
extern char *yytext;  // Add declaration for yytext
//extern int yylineno; // Line number for error reporting
// Function declarations
static char *str_dup(const char *s);

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

// AST helper functions
static ASTNode *create_node(NodeType type) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed for AST node\n");
        exit(1);
    }
    memset(node, 0, sizeof(ASTNode)); 
    node->type = type;
    return node;
}

static char *str_dup(const char *s) {
    if (!s) return NULL;
    char *dup = strdup(s);
    if (!dup) {
        fprintf(stderr, "Memory allocation failed for str_dup\n");
        exit(1);
    }
    return dup;
}

ASTNode *ast_program(ASTNode *declarations, ASTNode *statements) {
    ASTNode *node = create_node(NODE_PROGRAM);
    node->data.program.declarations = declarations;
    node->data.program.statements = statements;
    return node;
}

ASTNode *ast_var_decl(char *name, ASTNode *type) {
    ASTNode *node = create_node(NODE_VAR_DECL);
    node->data.var_decl.name = str_dup(name);
    node->data.var_decl.type = type;
    return node;
}

ASTNode *ast_array_decl(char *name, int size, ASTNode *type) {
    ASTNode *node = create_node(NODE_ARRAY_DECL);
    node->data.array_decl.name = str_dup(name);
    node->data.array_decl.size = size;
    node->data.array_decl.type = type;
    return node;
}

ASTNode *ast_stmt_list(ASTNode *stmt, ASTNode *next) {
    ASTNode *node = create_node(NODE_STMT_LIST);
    node->data.stmt_list.stmt = stmt;
    node->data.stmt_list.next = next;
    return node;
}

ASTNode *ast_type_int(void) {
    return create_node(NODE_TYPE_INT);
}

ASTNode *ast_type_char(void) {
    return create_node(NODE_TYPE_CHAR);
}

ASTNode *ast_assign(char *name, ASTNode *value) {
    ASTNode *node = create_node(NODE_ASSIGN);
    node->data.assign.name = str_dup(name);
    node->data.assign.value = value;
    return node;
}

ASTNode *ast_binary(char *op, ASTNode *left, ASTNode *right) {
    ASTNode *node = create_node(NODE_BINARY);
    node->data.binary.op = str_dup(op);
    node->data.binary.left = left;
    node->data.binary.right = right;
    return node;
}

ASTNode *ast_identifier(char *name) {
    ASTNode *node = create_node(NODE_IDENTIFIER);
    node->data.identifier.name = str_dup(name);
    return node;
}

ASTNode *ast_literal_int(int value) {
    ASTNode *node = create_node(NODE_LITERAL_INT);
    node->data.int_literal.value = value;
    return node;
}

ASTNode *ast_if(ASTNode *condition, ASTNode *if_body, ASTNode *else_body) {
    ASTNode *node = create_node(NODE_IF);
    node->data.if_stmt.condition = condition;
    node->data.if_stmt.if_body = if_body;
    node->data.if_stmt.else_body = else_body;
    return node;
}

ASTNode *ast_while(ASTNode *condition, ASTNode *body) {
    ASTNode *node = create_node(NODE_WHILE);
    node->data.while_stmt.condition = condition;
    node->data.while_stmt.body = body;
    return node;
}

ASTNode *ast_for(ASTNode *init, ASTNode *limit, ASTNode *update, ASTNode *body) {
    ASTNode *node = create_node(NODE_FOR);
    node->data.for_stmt.init = init;
    node->data.for_stmt.limit = limit;
    node->data.for_stmt.update = update;
    node->data.for_stmt.body = body;
    return node;
}

ASTNode *ast_inc(ASTNode *expr) {
    ASTNode *node = create_node(NODE_INC);
    node->data.inc_dec.expr = expr;
    return node;
}

ASTNode *ast_dec(ASTNode *expr) {
    ASTNode *node = create_node(NODE_DEC);
    node->data.inc_dec.expr = expr;
    return node;
}

void ast_print_generalized_list(ASTNode *root) {
    if (!root) return;
    
    switch (root->type) {
        case NODE_PROGRAM:
            printf("(\n");
            ast_print_generalized_list(root->data.program.declarations);
            ast_print_generalized_list(root->data.program.statements);
            printf("\n)\n");
            break;
            
        case NODE_STMT_LIST:
            ast_print_generalized_list(root->data.stmt_list.stmt);
            if (root->data.stmt_list.next) {
                printf("\n");
                ast_print_generalized_list(root->data.stmt_list.next);
            }
            break;
            
        case NODE_VAR_DECL:
            printf("(%s ", root->data.var_decl.name);
            ast_print_generalized_list(root->data.var_decl.type);
            printf(")\n");
            break;
            
        case NODE_TYPE_INT:
            printf("int");
            break;
            
        case NODE_TYPE_CHAR:
            printf("char");
            break;
            
        case NODE_ASSIGN:
            printf("(:= %s ", root->data.assign.name);
            ast_print_generalized_list(root->data.assign.value);
            printf(")\n");
            break;
            
        case NODE_BINARY:
            printf("(%s ", root->data.binary.op);
            ast_print_generalized_list(root->data.binary.left);
            printf(" ");
            ast_print_generalized_list(root->data.binary.right);
            printf(")");
            break;
            
        case NODE_IDENTIFIER:
            printf("%s", root->data.identifier.name);
            break;
            
        case NODE_LITERAL_INT:
            printf("%d", root->data.int_literal.value);
            break;

        case NODE_IF:
            printf("(if\n");
            ast_print_generalized_list(root->data.if_stmt.condition);
            printf(" ");
            ast_print_generalized_list(root->data.if_stmt.if_body);
            if (root->data.if_stmt.else_body) {
                printf(" ");
                ast_print_generalized_list(root->data.if_stmt.else_body);
            }
            printf(")\n");
            break;

        case NODE_WHILE:
            printf("(while ");
            ast_print_generalized_list(root->data.while_stmt.condition);
            printf(" ");
            ast_print_generalized_list(root->data.while_stmt.body);
            printf(")\n");
            break;

        case NODE_FOR:
            printf("(for \n ");
            ast_print_generalized_list(root->data.for_stmt.init);
            printf(" ");
            ast_print_generalized_list(root->data.for_stmt.limit);
            printf(" ");
            ast_print_generalized_list(root->data.for_stmt.update);
            printf(" ");
            ast_print_generalized_list(root->data.for_stmt.body);
            printf(")\n");
            break;

        case NODE_INC:
            printf("(inc ");
            ast_print_generalized_list(root->data.inc_dec.expr);
            printf(")\n");
            break;

        case NODE_DEC:
            printf("(dec ");
            ast_print_generalized_list(root->data.inc_dec.expr);
            printf(")\n");
            break;

        default:
            break;
    }
}

// Symbol table entry structure
struct symbol_entry {
    char name[50];
    enum { TYPE_INT, TYPE_CHAR, TYPE_INT_ARRAY, TYPE_CHAR_ARRAY } type;
    union {
        int int_val;
        char char_val;
        struct {
            void* data;
            int size;
        } array;
    } value;
    int is_initialized;
    int array_size;
} symbol_table[100];
int symbol_count = 0;

void add_symbol(const char* name, int type) {
    if (symbol_count >= 100) {
        fprintf(stderr, "Symbol table full\n");
        return;
    }
    strcpy(symbol_table[symbol_count].name, name);
    symbol_table[symbol_count].type = type;
    symbol_table[symbol_count].is_initialized = 0;
    symbol_count++;
}

struct symbol_entry* lookup_symbol(const char* name) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            return &symbol_table[i];
        }
    }
    return NULL;
}

void print_symbol_table() {
    printf("\nSymbol Table Contents:\n");
    printf("%-20s %-10s %-15s %-15s\n", "Name", "Type", "Initialized", "Value");
    printf("----------------------------------------------------\n");
    
    for (int i = 0; i < symbol_count; i++) {
        struct symbol_entry* entry = &symbol_table[i];
        char type_str[10], value_str[20];
        
        switch (entry->type) {
            case TYPE_INT:
                strcpy(type_str, "int");
                sprintf(value_str, "%d", entry->value.int_val);
                break;
            case TYPE_CHAR:
                strcpy(type_str, "char");
                sprintf(value_str, "'%c'", entry->value.char_val);
                break;
            case TYPE_INT_ARRAY:
                strcpy(type_str, "int[]");
                sprintf(value_str, "size=%d", entry->array_size);
                break;
            case TYPE_CHAR_ARRAY:
                strcpy(type_str, "char[]");
                sprintf(value_str, "size=%d", entry->array_size);
                break;
        }
        
        printf("%-20s %-10s %-15s %-15s\n",
               entry->name,
               type_str,
               entry->is_initialized ? "yes" : "no",
               entry->is_initialized ? value_str : "undefined");
    }
    printf("\n");
}

// AST Evaluation functions
int evaluate_expr(ASTNode* node) {
    if (!node) return 0;
    
    switch(node->type) {
        case NODE_LITERAL_INT:
            return node->data.int_literal.value;
        
        case NODE_IDENTIFIER: {
            struct symbol_entry* entry = lookup_symbol(node->data.identifier.name);
            if (!entry) {
                fprintf(stderr, "Error: Undeclared variable %s\n", node->data.identifier.name);
                return 0;
            }
            if (!entry->is_initialized) {
                fprintf(stderr, "Error: Using uninitialized variable %s\n", node->data.identifier.name);
                return 0;
            }
            return entry->value.int_val;
        }
        
        case NODE_BINARY: {
            int left = evaluate_expr(node->data.binary.left);
            int right = evaluate_expr(node->data.binary.right);
            
            if (strcmp(node->data.binary.op, "+") == 0) return left + right;
            if (strcmp(node->data.binary.op, "-") == 0) return left - right;
            if (strcmp(node->data.binary.op, "*") == 0) return left * right;
            if (strcmp(node->data.binary.op, "/") == 0) {
                if (right == 0) {
                    fprintf(stderr, "Error: Division by zero\n");
                    return 0;
                }
                return left / right;
            }
            if (strcmp(node->data.binary.op, "%") == 0) {
                if (right == 0) {
                    fprintf(stderr, "Error: Modulo by zero\n");
                    return 0;
                }
                return left % right;
            }
            if (strcmp(node->data.binary.op, ">") == 0) return left > right;
            if (strcmp(node->data.binary.op, "<") == 0) return left < right;
            if (strcmp(node->data.binary.op, ">=") == 0) return left >= right;
            if (strcmp(node->data.binary.op, "<=") == 0) return left <= right;
            if (strcmp(node->data.binary.op, "==") == 0) return left == right;
            if (strcmp(node->data.binary.op, "!=") == 0) return left != right;
        }
    }
    return 0;
}

void execute_stmt(ASTNode* node) {
    if (!node) return;

    switch(node->type) {
        case NODE_ASSIGN: {
            struct symbol_entry* entry = lookup_symbol(node->data.assign.name);
            if (!entry) {
                fprintf(stderr, "Error: Undeclared variable %s\n", node->data.assign.name);
                return;
            }
            
            int value = evaluate_expr(node->data.assign.value);
            entry->value.int_val = value;
            entry->is_initialized = 1;
            printf("%s = %d\n", node->data.assign.name, value);
            break;
        }
        
        case NODE_IF: {
            if (evaluate_expr(node->data.if_stmt.condition)) {
                execute_stmt(node->data.if_stmt.if_body);
            } else if (node->data.if_stmt.else_body) {
                execute_stmt(node->data.if_stmt.else_body);
            }
            break;
        }
        
        case NODE_WHILE: {
            while (evaluate_expr(node->data.while_stmt.condition)) {
                execute_stmt(node->data.while_stmt.body);
            }
            break;
        }
        
        case NODE_FOR: {
            // Execute initialization
            execute_stmt(node->data.for_stmt.init);
            
            // Get loop variable name from init node
            char* loop_var = NULL;
            if (node->data.for_stmt.init->type == NODE_ASSIGN) {
                loop_var = node->data.for_stmt.init->data.assign.name;
            }
            
            if (!loop_var) {
                fprintf(stderr, "Error: Invalid for loop initialization\n");
                return;
            }
            
            struct symbol_entry* var_entry = lookup_symbol(loop_var);
            if (!var_entry) {
                fprintf(stderr, "Error: Loop variable %s not found\n", loop_var);
                return;
            }
            
            // Loop until condition is false
            int limit = evaluate_expr(node->data.for_stmt.limit);
            while (var_entry->value.int_val <= limit) {
                execute_stmt(node->data.for_stmt.body);
                
                // Update loop variable
                if (node->data.for_stmt.update) {
                    execute_stmt(node->data.for_stmt.update);
                } else {
                    var_entry->value.int_val++;
                }
            }
            break;
        }
        
        case NODE_STMT_LIST: {
            execute_stmt(node->data.stmt_list.stmt);
            execute_stmt(node->data.stmt_list.next);
            break;
        }
        
        case NODE_INC: {
            if (node->data.inc_dec.expr->type == NODE_IDENTIFIER) {
                struct symbol_entry* entry = lookup_symbol(node->data.inc_dec.expr->data.identifier.name);
                if (entry) {
                    entry->value.int_val++;
                    printf("%s = %d\n", node->data.inc_dec.expr->data.identifier.name, entry->value.int_val);
                }
            }
            break;
        }
        
        case NODE_DEC: {
            if (node->data.inc_dec.expr->type == NODE_IDENTIFIER) {
                struct symbol_entry* entry = lookup_symbol(node->data.inc_dec.expr->data.identifier.name);
                if (entry) {
                    entry->value.int_val--;
                    printf("%s = %d\n", node->data.inc_dec.expr->data.identifier.name, entry->value.int_val);
                }
            }
            break;
        }
    }
}

void execute_program(ASTNode* root) {
    if (!root || root->type != NODE_PROGRAM) return;
    
    printf("\n=== Program Execution ===\n");
    
    // Process declarations first
    ASTNode* decl = root->data.program.declarations;
    while (decl) {
        if (decl->type == NODE_STMT_LIST && decl->data.stmt_list.stmt) {
            ASTNode* var_decl = decl->data.stmt_list.stmt;
            if (var_decl->type == NODE_VAR_DECL) {
                int type = (var_decl->data.var_decl.type->type == NODE_TYPE_INT) ? TYPE_INT : TYPE_CHAR;
                add_symbol(var_decl->data.var_decl.name, type);
            } else if (var_decl->type == NODE_ARRAY_DECL) {
                // Handle array declarations
                int type = (var_decl->data.array_decl.type->type == NODE_TYPE_INT) ? TYPE_INT_ARRAY : TYPE_CHAR_ARRAY;
                add_symbol(var_decl->data.array_decl.name, type);
                struct symbol_entry* entry = lookup_symbol(var_decl->data.array_decl.name);
                if (entry) {
                    entry->array_size = var_decl->data.array_decl.size;
                    size_t elem_size = (type == TYPE_INT_ARRAY) ? sizeof(int) : sizeof(char);
                    entry->value.array.data = calloc(var_decl->data.array_decl.size, elem_size);
                    entry->value.array.size = var_decl->data.array_decl.size;
                }
            }
        }
        decl = decl->data.stmt_list.next;
    }
    
    // Execute statements
    execute_stmt(root->data.program.statements);
    
    // Print final symbol table
    print_symbol_table();
}

%}

%code requires {
    #include "ast.h"
}

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
        ASTNode *node;     // AST node pointer
    } attr;

    // For AST nodes
    ASTNode *node;
}

/*--------- tokens ---------*/
%token <id> IDENTIFIER
%token <str> STRING_CONST STRING_FORMAT INPUT_FORMAT CHAR_CONST BASE_INT
%token <num> INT_CONST
%token BEGIN_PROGRAM END_PROGRAM BEGIN_VARDECL END_VARDECL BEGIN_K END_K
%token INT_TYPE CHAR_TYPE
%token COLON SEMICOLON COMMA
%token PRINT SCAN 
%token IF ELSE WHILE FOR DO TO INC DEC
%token ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
%token PLUS MINUS MULTIPLY DIVIDE MODULO
%token LT GT LE GE NE
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token ERROR

/*--------- nonterminals & their types ---------*/
%type <node> program vardecl_section var_declarations var_declaration type
%type <node> statements statement assignment if_statement while_statement 
%type <node> for_statement inc_statement dec_statement
%type <attr> expression term factor condition
%type <str> relational_op

%start program

%%

program : BEGIN_PROGRAM vardecl_section statements END_PROGRAM
        { 
            // Create AST and generate 3AC
            $$ = ast_program($2, $3); 
            root = $$;
        }
        ;

vardecl_section : BEGIN_VARDECL var_declarations END_VARDECL
                { 
                    $$ = $2; // Pass up the declarations AST
                }
                ;

var_declarations : /* empty */
                { 
                    $$ = NULL; 
                }
                | var_declaration var_declarations
                { 
                    $$ = ast_stmt_list($1, $2); 
                }
                ;

var_declaration : LPAREN IDENTIFIER COMMA type RPAREN SEMICOLON
                { 
                    $$ = ast_var_decl($2, $4);
                }
                | LPAREN IDENTIFIER LBRACKET INT_CONST RBRACKET COMMA type RPAREN SEMICOLON
                {
                    // Generate both AST and 3AC for array declaration
                    $$ = ast_array_decl($2, $4, $7);
                    char size[10];
                    sprintf(size, "%d", $4);
                    addQuadruple("array", size, "", $2);
                }
                ;

type : INT_TYPE   { $$ = ast_type_int(); }
     | CHAR_TYPE  { $$ = ast_type_char(); }
     ;

statements : /* empty */               { $$ = NULL; }
           | BEGIN_K statement statements END_K 
           {
               $$ = ast_stmt_list($2, $3);
           }
           | statement statements      
           { 
               $$ = ast_stmt_list($1, $2); 
           }
           ;

statement : assignment SEMICOLON
          | if_statement SEMICOLON
          | while_statement SEMICOLON
          | for_statement SEMICOLON
          | inc_statement SEMICOLON 
          | dec_statement SEMICOLON
          | error SEMICOLON { yyerrok; printf("Error token: %s\n", yytext); $$ = NULL; }
          ;

assignment : IDENTIFIER ASSIGN expression
           {
               // Generate both AST and 3AC
               $$ = ast_assign($1, $3.node);
               addQuadruple($3.place, "", "", $1);
           }
           | IDENTIFIER ADD_ASSIGN expression
           {
               // Generate AST and 3AC for += operator
               $$ = ast_assign($1, ast_binary("+", ast_identifier($1), $3.node));
               char *temp = newTemp();
               addQuadruple($1, "+", $3.place, temp);
               addQuadruple(temp, "", "", $1);
           }
           | IDENTIFIER SUB_ASSIGN expression
           {
               // Generate AST and 3AC for -= operator
               $$ = ast_assign($1, ast_binary("-", ast_identifier($1), $3.node));
               char *temp = newTemp();
               addQuadruple($1, "-", $3.place, temp);
               addQuadruple(temp, "", "", $1);
           }
           | IDENTIFIER MUL_ASSIGN expression
           {
               // Generate AST and 3AC for *= operator
               $$ = ast_assign($1, ast_binary("*", ast_identifier($1), $3.node));
               char *temp = newTemp();
               addQuadruple($1, "*", $3.place, temp);
               addQuadruple(temp, "", "", $1);
           }
           | IDENTIFIER DIV_ASSIGN expression
           {
               // Generate AST and 3AC for /= operator
               $$ = ast_assign($1, ast_binary("/", ast_identifier($1), $3.node));
               char *temp = newTemp();
               addQuadruple($1, "/", $3.place, temp);
               addQuadruple(temp, "", "", $1);
           }
           | IDENTIFIER MOD_ASSIGN expression
           {
               // Generate AST and 3AC for %= operator
               $$ = ast_assign($1, ast_binary("%", ast_identifier($1), $3.node));
               char *temp = newTemp();
               addQuadruple($1, "%", $3.place, temp);
               addQuadruple(temp, "", "", $1);
           }
           | IDENTIFIER LBRACKET expression RBRACKET ASSIGN expression
           {
               // Generate AST and 3AC for array assignment
               char index_str[20];
               sprintf(index_str, "%s[%s]", $1, $3.place);
               $$ = ast_assign(index_str, $6.node);
               addQuadruple($6.place, "", "", index_str);
           }
           ;

expression : term
           {
               strcpy($$.place, $1.place);
               $$.node = $1.node;
           }
           | expression PLUS term
           {
               char *temp = newTemp();
               $$.node = ast_binary("+", $1.node, $3.node);
               addQuadruple($1.place, "+", $3.place, temp);
               strcpy($$.place, temp);
           }
           | expression MINUS term
           {
               char *temp = newTemp();
               $$.node = ast_binary("-", $1.node, $3.node);
               addQuadruple($1.place, "-", $3.place, temp);
               strcpy($$.place, temp);
           }
           ;

term : factor
     {
         strcpy($$.place, $1.place);
         $$.node = $1.node;
     }
     | term MULTIPLY factor
     {
         char *temp = newTemp();
         $$.node = ast_binary("*", $1.node, $3.node);
         addQuadruple($1.place, "*", $3.place, temp);
         strcpy($$.place, temp);
     }
     | term DIVIDE factor
     {
         char *temp = newTemp();
         $$.node = ast_binary("/", $1.node, $3.node);
         addQuadruple($1.place, "/", $3.place, temp);
         strcpy($$.place, temp);
     }
     | term MODULO factor
     {
         char *temp = newTemp();
         $$.node = ast_binary("%", $1.node, $3.node);
         addQuadruple($1.place, "%", $3.place, temp);
         strcpy($$.place, temp);
     }
     ;

factor : IDENTIFIER
       {
           strcpy($$.place, $1);
           $$.node = ast_identifier($1);
       }
       | IDENTIFIER LBRACKET expression RBRACKET
       {
           char array_ref[20];
           sprintf(array_ref, "%s[%s]", $1, $3.place);
           
           char *temp = newTemp();
           addQuadruple(array_ref, "", "", temp);
           
           strcpy($$.place, temp);
           $$.node = ast_identifier(array_ref);
       }
       | INT_CONST
       {
           char int_str[10];
           sprintf(int_str, "%d", $1);
           strcpy($$.place, int_str);
           $$.node = ast_literal_int($1);
       }
       | CHAR_CONST
       {
           char char_str[5];
           sprintf(char_str, "'%c'", charVal);
           strcpy($$.place, char_str);
           $$.node = ast_literal_int(charVal);
       }
       | STRING_CONST
       {
           char *temp = newTemp();
           addQuadruple($1, "", "", temp);
           strcpy($$.place, temp);
           $$.node = ast_identifier($1);
       }
       | LPAREN expression RPAREN
       {
           strcpy($$.place, $2.place);
           $$.node = $2.node;
       }
       | BASE_INT
       {
            char digits[128] = {0}, base[16] = {0};
    sscanf(yylval.str, "(%[^,],%[^)])", digits, base);
    
    // Trim spaces again if needed
    char *d_ptr = digits;
    while(*d_ptr && isspace(*d_ptr)) d_ptr++;
    
    char *b_ptr = base;
    while(*b_ptr && isspace(*b_ptr)) b_ptr++;
    
    // Convert using the correct base
    int base_val = atoi(b_ptr);
    long int value = strtol(d_ptr, NULL, base_val);
    
    strcpy($$.place, yylval.str);  // Keep the original representation if needed
    $$.node = ast_literal_int((int)value);  // Store the properly converted value
       }
       ;

if_statement : IF LPAREN condition RPAREN statements
             {
                 char *else_label = newLabel();
                 char *end_label = newLabel();
                 
                 // Generate 3AC
                 addIf($3.place, else_label);
                 addLabel(else_label);
                 addLabel(end_label);
                 
                 // Generate AST
                 $$ = ast_if($3.node, $5, NULL);
             }
             | IF LPAREN condition RPAREN statements ELSE statements
             {
                 char *else_label = newLabel();
                 char *end_label = newLabel();
                 
                 // Generate 3AC
                 addIf($3.place, else_label);
                 addLabel(else_label);
                 addLabel(end_label);
                 
                 // Generate AST
                 $$ = ast_if($3.node, $5, $7);
             }
             ;

while_statement : WHILE LPAREN condition RPAREN DO BEGIN_K statements END_K 
                {
                    char *start_label = newLabel();
                    char *end_label = newLabel();
                    
                    // Generate 3AC 
                    addLabel(start_label);
                    addIf($3.place, end_label);
                    addGoto(start_label);
                    addLabel(end_label);
                    
                    // Generate AST
                    $$ = ast_while($3.node, $7);
                }
                ;

for_statement : FOR IDENTIFIER ASSIGN expression TO expression INC expression DO BEGIN_K statements END_K
              {
                  char *start_label = newLabel();
                  char *end_label = newLabel();
                  
                  // Initial assignment
                  addQuadruple($4.place, "", "", $2);
                  
                  // Generate loop structure
                  addLabel(start_label);
                  
                  // Condition check
                  char *temp = newTemp();
                  addQuadruple($2, "<", $6.place, temp);
                  addIf(temp, end_label);
                  
                  // Loop body
                  addGoto(start_label);
                  addLabel(end_label);
                  
                  // Generate AST
                  $$ = ast_for(ast_assign($2, $4.node), $6.node, NULL, $11);
              }
              ;

condition : expression relational_op expression
         {
             char *temp = newTemp();
             addQuadruple($1.place, $2, $3.place, temp);
             strcpy($$.place, temp);
             $$.node = ast_binary($2, $1.node, $3.node);
         }
         ;

relational_op : LT   { $$ = strdup("<"); }
              | GT   { $$ = strdup(">"); }
              | LE   { $$ = strdup("<="); }
              | GE   { $$ = strdup(">="); }
              | NE   { $$ = strdup("!="); }
              ;

inc_statement : INC expression
              {
                  char *temp = newTemp();
                  addQuadruple($2.place, "+", "1", temp);
                  //strcpy($$.place, temp);
                  
                  // Generate AST
                  $$  = ast_inc($2.node);
              }
              ;

dec_statement : DEC expression
              {
                  char *temp = newTemp();
                  addQuadruple($2.place, "-", "1", temp);
                  //strcpy($$.place, temp);
                  
                  // Generate AST
                  $$ = ast_dec($2.node);
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

    if (yyparse() == 0) {
        printf("\n=== Abstract Syntax Tree ===\n");
        ast_print_generalized_list(root);
        
        printf("\n=== Three Address Code ===\n");
        print_Quad_Table();
        
        execute_program(root);
        
        printf("\nParsing completed successfully.\n");
    }
    
    if (yyin != stdin) {
        fclose(yyin);
    }
    
    return 0;
}