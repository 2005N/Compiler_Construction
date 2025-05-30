
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser.y"

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



/* Line 189 of yacc.c  */
#line 781 "parser.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

/* "%code requires" blocks.  */

/* Line 209 of yacc.c  */
#line 708 "parser.y"

    #include "ast.h"



/* Line 209 of yacc.c  */
#line 811 "parser.tab.c"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENTIFIER = 258,
     STRING_CONST = 259,
     STRING_FORMAT = 260,
     INPUT_FORMAT = 261,
     CHAR_CONST = 262,
     BASE_INT = 263,
     INT_CONST = 264,
     BEGIN_PROGRAM = 265,
     END_PROGRAM = 266,
     BEGIN_VARDECL = 267,
     END_VARDECL = 268,
     BEGIN_K = 269,
     END_K = 270,
     INT_TYPE = 271,
     CHAR_TYPE = 272,
     COLON = 273,
     SEMICOLON = 274,
     COMMA = 275,
     PRINT = 276,
     SCAN = 277,
     IF = 278,
     ELSE = 279,
     WHILE = 280,
     FOR = 281,
     DO = 282,
     TO = 283,
     INC = 284,
     DEC = 285,
     ASSIGN = 286,
     ADD_ASSIGN = 287,
     SUB_ASSIGN = 288,
     MUL_ASSIGN = 289,
     DIV_ASSIGN = 290,
     MOD_ASSIGN = 291,
     PLUS = 292,
     MINUS = 293,
     MULTIPLY = 294,
     DIVIDE = 295,
     MODULO = 296,
     LT = 297,
     GT = 298,
     LE = 299,
     GE = 300,
     NE = 301,
     LPAREN = 302,
     RPAREN = 303,
     LBRACE = 304,
     RBRACE = 305,
     LBRACKET = 306,
     RBRACKET = 307,
     ERROR = 308
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 712 "parser.y"

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



/* Line 214 of yacc.c  */
#line 903 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 915 "parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   176

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  52
/* YYNRULES -- Number of states.  */
#define YYNSTATES  127

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   308

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     8,    12,    13,    16,    23,    33,    35,
      37,    38,    43,    46,    49,    52,    55,    58,    61,    64,
      67,    71,    75,    79,    83,    87,    91,    98,   100,   104,
     108,   110,   114,   118,   122,   124,   129,   131,   133,   135,
     139,   141,   147,   155,   164,   177,   181,   183,   185,   187,
     189,   191,   194
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      55,     0,    -1,    10,    56,    60,    11,    -1,    12,    57,
      13,    -1,    -1,    58,    57,    -1,    47,     3,    20,    59,
      48,    19,    -1,    47,     3,    51,     9,    52,    20,    59,
      48,    19,    -1,    16,    -1,    17,    -1,    -1,    14,    61,
      60,    15,    -1,    61,    60,    -1,    62,    19,    -1,    66,
      19,    -1,    67,    19,    -1,    68,    19,    -1,    71,    19,
      -1,    72,    19,    -1,     1,    19,    -1,     3,    31,    63,
      -1,     3,    32,    63,    -1,     3,    33,    63,    -1,     3,
      34,    63,    -1,     3,    35,    63,    -1,     3,    36,    63,
      -1,     3,    51,    63,    52,    31,    63,    -1,    64,    -1,
      63,    37,    64,    -1,    63,    38,    64,    -1,    65,    -1,
      64,    39,    65,    -1,    64,    40,    65,    -1,    64,    41,
      65,    -1,     3,    -1,     3,    51,    63,    52,    -1,     9,
      -1,     7,    -1,     4,    -1,    47,    63,    48,    -1,     8,
      -1,    23,    47,    69,    48,    60,    -1,    23,    47,    69,
      48,    60,    24,    60,    -1,    25,    47,    69,    48,    27,
      14,    60,    15,    -1,    26,     3,    31,    63,    28,    63,
      29,    63,    27,    14,    60,    15,    -1,    63,    70,    63,
      -1,    42,    -1,    43,    -1,    44,    -1,    45,    -1,    46,
      -1,    29,    63,    -1,    30,    63,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   758,   758,   766,   773,   776,   782,   786,   796,   797,
     800,   801,   805,   811,   812,   813,   814,   815,   816,   817,
     820,   826,   834,   842,   850,   858,   866,   876,   881,   888,
     897,   902,   909,   916,   925,   930,   941,   948,   955,   962,
     967,   988,  1001,  1016,  1032,  1057,  1066,  1067,  1068,  1069,
    1070,  1073,  1084
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "STRING_CONST",
  "STRING_FORMAT", "INPUT_FORMAT", "CHAR_CONST", "BASE_INT", "INT_CONST",
  "BEGIN_PROGRAM", "END_PROGRAM", "BEGIN_VARDECL", "END_VARDECL",
  "BEGIN_K", "END_K", "INT_TYPE", "CHAR_TYPE", "COLON", "SEMICOLON",
  "COMMA", "PRINT", "SCAN", "IF", "ELSE", "WHILE", "FOR", "DO", "TO",
  "INC", "DEC", "ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN",
  "DIV_ASSIGN", "MOD_ASSIGN", "PLUS", "MINUS", "MULTIPLY", "DIVIDE",
  "MODULO", "LT", "GT", "LE", "GE", "NE", "LPAREN", "RPAREN", "LBRACE",
  "RBRACE", "LBRACKET", "RBRACKET", "ERROR", "$accept", "program",
  "vardecl_section", "var_declarations", "var_declaration", "type",
  "statements", "statement", "assignment", "expression", "term", "factor",
  "if_statement", "while_statement", "for_statement", "condition",
  "relational_op", "inc_statement", "dec_statement", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    55,    56,    57,    57,    58,    58,    59,    59,
      60,    60,    60,    61,    61,    61,    61,    61,    61,    61,
      62,    62,    62,    62,    62,    62,    62,    63,    63,    63,
      64,    64,    64,    64,    65,    65,    65,    65,    65,    65,
      65,    66,    66,    67,    68,    69,    70,    70,    70,    70,
      70,    71,    72
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     3,     0,     2,     6,     9,     1,     1,
       0,     4,     2,     2,     2,     2,     2,     2,     2,     2,
       3,     3,     3,     3,     3,     3,     6,     1,     3,     3,
       1,     3,     3,     3,     1,     4,     1,     1,     1,     3,
       1,     5,     7,     8,    12,     3,     1,     1,     1,     1,
       1,     2,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     4,     0,     1,     0,     0,     4,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     3,     5,    19,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      34,    38,    37,    40,    36,     0,    51,    27,    30,    52,
       2,    12,    13,    14,    15,    16,    17,    18,     0,     0,
      20,    21,    22,    23,    24,    25,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     8,
       9,     0,     0,     0,    11,    46,    47,    48,    49,    50,
       0,     0,     0,     0,     0,    39,    28,    29,    31,    32,
      33,     0,     0,     0,    45,    41,     0,     0,    35,     6,
       0,    26,     0,     0,     0,     0,    42,     0,     0,     0,
      43,     0,     7,     0,     0,     0,    44
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     4,     7,     8,    81,    17,    18,    19,    68,
      47,    48,    20,    21,    22,    69,    90,    23,    24
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -59
static const yytype_int16 yypact[] =
{
      -8,    17,    27,   -16,    98,   -59,    61,    54,   -16,    52,
     -21,   146,    42,    43,    69,     0,     0,    85,    25,    79,
      81,    83,    84,    86,    88,   -19,   -59,   -59,   -59,     0,
       0,     0,     0,     0,     0,     0,   115,     0,     0,    73,
      59,   -59,   -59,   -59,   -59,     0,    -4,    38,   -59,    -4,
     -59,   -59,   -59,   -59,   -59,   -59,   -59,   -59,    21,   102,
      -4,    -4,    -4,    -4,    -4,    -4,     4,    99,   122,    65,
      67,     0,     0,    20,     0,     0,     0,     0,     0,   -59,
     -59,    71,    68,    91,   -59,   -59,   -59,   -59,   -59,   -59,
       0,    62,    90,    15,     8,   -59,    38,    38,   -59,   -59,
     -59,   106,   111,     0,    -4,   108,   112,     0,   -59,   -59,
      21,    -4,   132,   115,    37,    89,   -59,   119,     0,   117,
     -59,    32,   -59,   125,   115,   127,   -59
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -59,   -59,   -59,   135,   -59,    40,   -18,   137,   -59,   -10,
     -58,     6,   -59,   -59,   -59,   114,   -59,   -59,   -59
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -11
static const yytype_int8 yytable[] =
{
      51,    58,     1,    40,    41,    46,    49,    42,    43,    44,
      29,    30,    31,    32,    33,    34,    96,    97,    67,    60,
      61,    62,    63,    64,    65,    66,     9,     5,    10,     3,
      35,     6,    59,    74,    75,    73,   -10,    79,    80,    11,
     -10,    74,    75,   107,   -10,    74,    75,    45,    12,   -10,
      13,    14,    74,    75,    15,    16,    83,    74,    75,   123,
     108,    93,    94,     9,    25,    10,   118,    26,    95,    74,
      75,    28,    39,   105,    74,    75,    11,    76,    77,    78,
     104,   -10,    98,    99,   100,    12,   -10,    13,    14,    37,
      38,    15,    16,   111,   116,   117,    50,   114,    52,     9,
      53,    10,    54,    55,    71,    56,   125,    57,   121,   -10,
      72,    82,    11,    91,    84,    92,     9,   106,    10,   101,
     102,    12,   103,    13,    14,   109,   113,    15,    16,    11,
     -10,   110,   112,     9,   120,    10,   122,   119,    12,   124,
      13,    14,   126,    27,    15,    16,    11,     9,    36,    10,
     115,   -10,    70,     0,     0,    12,     0,    13,    14,    74,
      75,    15,    16,     0,    85,    86,    87,    88,    89,    12,
       0,    13,    14,     0,     0,    15,    16
};

static const yytype_int8 yycheck[] =
{
      18,    20,    10,     3,     4,    15,    16,     7,     8,     9,
      31,    32,    33,    34,    35,    36,    74,    75,    36,    29,
      30,    31,    32,    33,    34,    35,     1,     0,     3,    12,
      51,    47,    51,    37,    38,    45,    11,    16,    17,    14,
      15,    37,    38,    28,    19,    37,    38,    47,    23,    24,
      25,    26,    37,    38,    29,    30,    52,    37,    38,    27,
      52,    71,    72,     1,     3,     3,    29,    13,    48,    37,
      38,    19,     3,    91,    37,    38,    14,    39,    40,    41,
      90,    19,    76,    77,    78,    23,    24,    25,    26,    47,
      47,    29,    30,   103,   112,   113,    11,   107,    19,     1,
      19,     3,    19,    19,    31,    19,   124,    19,   118,    11,
      51,     9,    14,    48,    15,    48,     1,    27,     3,    48,
      52,    23,    31,    25,    26,    19,    14,    29,    30,    14,
      15,    20,    24,     1,    15,     3,    19,    48,    23,    14,
      25,    26,    15,     8,    29,    30,    14,     1,    11,     3,
     110,    19,    38,    -1,    -1,    23,    -1,    25,    26,    37,
      38,    29,    30,    -1,    42,    43,    44,    45,    46,    23,
      -1,    25,    26,    -1,    -1,    29,    30
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    10,    55,    12,    56,     0,    47,    57,    58,     1,
       3,    14,    23,    25,    26,    29,    30,    60,    61,    62,
      66,    67,    68,    71,    72,     3,    13,    57,    19,    31,
      32,    33,    34,    35,    36,    51,    61,    47,    47,     3,
       3,     4,     7,     8,     9,    47,    63,    64,    65,    63,
      11,    60,    19,    19,    19,    19,    19,    19,    20,    51,
      63,    63,    63,    63,    63,    63,    63,    60,    63,    69,
      69,    31,    51,    63,    37,    38,    39,    40,    41,    16,
      17,    59,     9,    52,    15,    42,    43,    44,    45,    46,
      70,    48,    48,    63,    63,    48,    64,    64,    65,    65,
      65,    48,    52,    31,    63,    60,    27,    28,    52,    19,
      20,    63,    24,    14,    63,    59,    60,    60,    29,    48,
      15,    63,    19,    27,    14,    60,    15
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 759 "parser.y"
    { 
            // Create AST and generate 3AC
            (yyval.node) = ast_program((yyvsp[(2) - (4)].node), (yyvsp[(3) - (4)].node)); 
            root = (yyval.node);
        ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 767 "parser.y"
    { 
                    (yyval.node) = (yyvsp[(2) - (3)].node); // Pass up the declarations AST
                ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 773 "parser.y"
    { 
                    (yyval.node) = NULL; 
                ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 777 "parser.y"
    { 
                    (yyval.node) = ast_stmt_list((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); 
                ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 783 "parser.y"
    { 
                    (yyval.node) = ast_var_decl((yyvsp[(2) - (6)].id), (yyvsp[(4) - (6)].node));
                ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 787 "parser.y"
    {
                    // Generate both AST and 3AC for array declaration
                    (yyval.node) = ast_array_decl((yyvsp[(2) - (9)].id), (yyvsp[(4) - (9)].num), (yyvsp[(7) - (9)].node));
                    char size[10];
                    sprintf(size, "%d", (yyvsp[(4) - (9)].num));
                    addQuadruple("array", size, "", (yyvsp[(2) - (9)].id));
                ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 796 "parser.y"
    { (yyval.node) = ast_type_int(); ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 797 "parser.y"
    { (yyval.node) = ast_type_char(); ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 800 "parser.y"
    { (yyval.node) = NULL; ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 802 "parser.y"
    {
               (yyval.node) = ast_stmt_list((yyvsp[(2) - (4)].node), (yyvsp[(3) - (4)].node));
           ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 806 "parser.y"
    { 
               (yyval.node) = ast_stmt_list((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); 
           ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 817 "parser.y"
    { yyerrok; printf("Error token: %s\n", yytext); (yyval.node) = NULL; ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 821 "parser.y"
    {
               // Generate both AST and 3AC
               (yyval.node) = ast_assign((yyvsp[(1) - (3)].id), (yyvsp[(3) - (3)].attr).node);
               addQuadruple((yyvsp[(3) - (3)].attr).place, "", "", (yyvsp[(1) - (3)].id));
           ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 827 "parser.y"
    {
               // Generate AST and 3AC for += operator
               (yyval.node) = ast_assign((yyvsp[(1) - (3)].id), ast_binary("+", ast_identifier((yyvsp[(1) - (3)].id)), (yyvsp[(3) - (3)].attr).node));
               char *temp = newTemp();
               addQuadruple((yyvsp[(1) - (3)].id), "+", (yyvsp[(3) - (3)].attr).place, temp);
               addQuadruple(temp, "", "", (yyvsp[(1) - (3)].id));
           ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 835 "parser.y"
    {
               // Generate AST and 3AC for -= operator
               (yyval.node) = ast_assign((yyvsp[(1) - (3)].id), ast_binary("-", ast_identifier((yyvsp[(1) - (3)].id)), (yyvsp[(3) - (3)].attr).node));
               char *temp = newTemp();
               addQuadruple((yyvsp[(1) - (3)].id), "-", (yyvsp[(3) - (3)].attr).place, temp);
               addQuadruple(temp, "", "", (yyvsp[(1) - (3)].id));
           ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 843 "parser.y"
    {
               // Generate AST and 3AC for *= operator
               (yyval.node) = ast_assign((yyvsp[(1) - (3)].id), ast_binary("*", ast_identifier((yyvsp[(1) - (3)].id)), (yyvsp[(3) - (3)].attr).node));
               char *temp = newTemp();
               addQuadruple((yyvsp[(1) - (3)].id), "*", (yyvsp[(3) - (3)].attr).place, temp);
               addQuadruple(temp, "", "", (yyvsp[(1) - (3)].id));
           ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 851 "parser.y"
    {
               // Generate AST and 3AC for /= operator
               (yyval.node) = ast_assign((yyvsp[(1) - (3)].id), ast_binary("/", ast_identifier((yyvsp[(1) - (3)].id)), (yyvsp[(3) - (3)].attr).node));
               char *temp = newTemp();
               addQuadruple((yyvsp[(1) - (3)].id), "/", (yyvsp[(3) - (3)].attr).place, temp);
               addQuadruple(temp, "", "", (yyvsp[(1) - (3)].id));
           ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 859 "parser.y"
    {
               // Generate AST and 3AC for %= operator
               (yyval.node) = ast_assign((yyvsp[(1) - (3)].id), ast_binary("%", ast_identifier((yyvsp[(1) - (3)].id)), (yyvsp[(3) - (3)].attr).node));
               char *temp = newTemp();
               addQuadruple((yyvsp[(1) - (3)].id), "%", (yyvsp[(3) - (3)].attr).place, temp);
               addQuadruple(temp, "", "", (yyvsp[(1) - (3)].id));
           ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 867 "parser.y"
    {
               // Generate AST and 3AC for array assignment
               char index_str[20];
               sprintf(index_str, "%s[%s]", (yyvsp[(1) - (6)].id), (yyvsp[(3) - (6)].attr).place);
               (yyval.node) = ast_assign(index_str, (yyvsp[(6) - (6)].attr).node);
               addQuadruple((yyvsp[(6) - (6)].attr).place, "", "", index_str);
           ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 877 "parser.y"
    {
               strcpy((yyval.attr).place, (yyvsp[(1) - (1)].attr).place);
               (yyval.attr).node = (yyvsp[(1) - (1)].attr).node;
           ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 882 "parser.y"
    {
               char *temp = newTemp();
               (yyval.attr).node = ast_binary("+", (yyvsp[(1) - (3)].attr).node, (yyvsp[(3) - (3)].attr).node);
               addQuadruple((yyvsp[(1) - (3)].attr).place, "+", (yyvsp[(3) - (3)].attr).place, temp);
               strcpy((yyval.attr).place, temp);
           ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 889 "parser.y"
    {
               char *temp = newTemp();
               (yyval.attr).node = ast_binary("-", (yyvsp[(1) - (3)].attr).node, (yyvsp[(3) - (3)].attr).node);
               addQuadruple((yyvsp[(1) - (3)].attr).place, "-", (yyvsp[(3) - (3)].attr).place, temp);
               strcpy((yyval.attr).place, temp);
           ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 898 "parser.y"
    {
         strcpy((yyval.attr).place, (yyvsp[(1) - (1)].attr).place);
         (yyval.attr).node = (yyvsp[(1) - (1)].attr).node;
     ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 903 "parser.y"
    {
         char *temp = newTemp();
         (yyval.attr).node = ast_binary("*", (yyvsp[(1) - (3)].attr).node, (yyvsp[(3) - (3)].attr).node);
         addQuadruple((yyvsp[(1) - (3)].attr).place, "*", (yyvsp[(3) - (3)].attr).place, temp);
         strcpy((yyval.attr).place, temp);
     ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 910 "parser.y"
    {
         char *temp = newTemp();
         (yyval.attr).node = ast_binary("/", (yyvsp[(1) - (3)].attr).node, (yyvsp[(3) - (3)].attr).node);
         addQuadruple((yyvsp[(1) - (3)].attr).place, "/", (yyvsp[(3) - (3)].attr).place, temp);
         strcpy((yyval.attr).place, temp);
     ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 917 "parser.y"
    {
         char *temp = newTemp();
         (yyval.attr).node = ast_binary("%", (yyvsp[(1) - (3)].attr).node, (yyvsp[(3) - (3)].attr).node);
         addQuadruple((yyvsp[(1) - (3)].attr).place, "%", (yyvsp[(3) - (3)].attr).place, temp);
         strcpy((yyval.attr).place, temp);
     ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 926 "parser.y"
    {
           strcpy((yyval.attr).place, (yyvsp[(1) - (1)].id));
           (yyval.attr).node = ast_identifier((yyvsp[(1) - (1)].id));
       ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 931 "parser.y"
    {
           char array_ref[20];
           sprintf(array_ref, "%s[%s]", (yyvsp[(1) - (4)].id), (yyvsp[(3) - (4)].attr).place);
           
           char *temp = newTemp();
           addQuadruple(array_ref, "", "", temp);
           
           strcpy((yyval.attr).place, temp);
           (yyval.attr).node = ast_identifier(array_ref);
       ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 942 "parser.y"
    {
           char int_str[10];
           sprintf(int_str, "%d", (yyvsp[(1) - (1)].num));
           strcpy((yyval.attr).place, int_str);
           (yyval.attr).node = ast_literal_int((yyvsp[(1) - (1)].num));
       ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 949 "parser.y"
    {
           char char_str[5];
           sprintf(char_str, "'%c'", charVal);
           strcpy((yyval.attr).place, char_str);
           (yyval.attr).node = ast_literal_int(charVal);
       ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 956 "parser.y"
    {
           char *temp = newTemp();
           addQuadruple((yyvsp[(1) - (1)].str), "", "", temp);
           strcpy((yyval.attr).place, temp);
           (yyval.attr).node = ast_identifier((yyvsp[(1) - (1)].str));
       ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 963 "parser.y"
    {
           strcpy((yyval.attr).place, (yyvsp[(2) - (3)].attr).place);
           (yyval.attr).node = (yyvsp[(2) - (3)].attr).node;
       ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 968 "parser.y"
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
    
    strcpy((yyval.attr).place, yylval.str);  // Keep the original representation if needed
    (yyval.attr).node = ast_literal_int((int)value);  // Store the properly converted value
       ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 989 "parser.y"
    {
                 char *else_label = newLabel();
                 char *end_label = newLabel();
                 
                 // Generate 3AC
                 addIf((yyvsp[(3) - (5)].attr).place, else_label);
                 addLabel(else_label);
                 addLabel(end_label);
                 
                 // Generate AST
                 (yyval.node) = ast_if((yyvsp[(3) - (5)].attr).node, (yyvsp[(5) - (5)].node), NULL);
             ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 1002 "parser.y"
    {
                 char *else_label = newLabel();
                 char *end_label = newLabel();
                 
                 // Generate 3AC
                 addIf((yyvsp[(3) - (7)].attr).place, else_label);
                 addLabel(else_label);
                 addLabel(end_label);
                 
                 // Generate AST
                 (yyval.node) = ast_if((yyvsp[(3) - (7)].attr).node, (yyvsp[(5) - (7)].node), (yyvsp[(7) - (7)].node));
             ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 1017 "parser.y"
    {
                    char *start_label = newLabel();
                    char *end_label = newLabel();
                    
                    // Generate 3AC 
                    addLabel(start_label);
                    addIf((yyvsp[(3) - (8)].attr).place, end_label);
                    addGoto(start_label);
                    addLabel(end_label);
                    
                    // Generate AST
                    (yyval.node) = ast_while((yyvsp[(3) - (8)].attr).node, (yyvsp[(7) - (8)].node));
                ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 1033 "parser.y"
    {
                  char *start_label = newLabel();
                  char *end_label = newLabel();
                  
                  // Initial assignment
                  addQuadruple((yyvsp[(4) - (12)].attr).place, "", "", (yyvsp[(2) - (12)].id));
                  
                  // Generate loop structure
                  addLabel(start_label);
                  
                  // Condition check
                  char *temp = newTemp();
                  addQuadruple((yyvsp[(2) - (12)].id), "<", (yyvsp[(6) - (12)].attr).place, temp);
                  addIf(temp, end_label);
                  
                  // Loop body
                  addGoto(start_label);
                  addLabel(end_label);
                  
                  // Generate AST
                  (yyval.node) = ast_for(ast_assign((yyvsp[(2) - (12)].id), (yyvsp[(4) - (12)].attr).node), (yyvsp[(6) - (12)].attr).node, NULL, (yyvsp[(11) - (12)].node));
              ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 1058 "parser.y"
    {
             char *temp = newTemp();
             addQuadruple((yyvsp[(1) - (3)].attr).place, (yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].attr).place, temp);
             strcpy((yyval.attr).place, temp);
             (yyval.attr).node = ast_binary((yyvsp[(2) - (3)].str), (yyvsp[(1) - (3)].attr).node, (yyvsp[(3) - (3)].attr).node);
         ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 1066 "parser.y"
    { (yyval.str) = strdup("<"); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 1067 "parser.y"
    { (yyval.str) = strdup(">"); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 1068 "parser.y"
    { (yyval.str) = strdup("<="); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 1069 "parser.y"
    { (yyval.str) = strdup(">="); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 1070 "parser.y"
    { (yyval.str) = strdup("!="); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 1074 "parser.y"
    {
                  char *temp = newTemp();
                  addQuadruple((yyvsp[(2) - (2)].attr).place, "+", "1", temp);
                  //strcpy($$.place, temp);
                  
                  // Generate AST
                  (yyval.node)  = ast_inc((yyvsp[(2) - (2)].attr).node);
              ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 1085 "parser.y"
    {
                  char *temp = newTemp();
                  addQuadruple((yyvsp[(2) - (2)].attr).place, "-", "1", temp);
                  //strcpy($$.place, temp);
                  
                  // Generate AST
                  (yyval.node) = ast_dec((yyvsp[(2) - (2)].attr).node);
              ;}
    break;



/* Line 1455 of yacc.c  */
#line 2753 "parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 1095 "parser.y"


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
