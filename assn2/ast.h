#ifndef AST_H
#define AST_H


typedef struct {
    char* value;
} StringLiteralNode;


// Node types for AST
typedef enum {
    // Program structure
    NODE_PROGRAM,
    
    // Declarations
    NODE_VAR_DECL,
    NODE_ARRAY_DECL,
    NODE_STMT_LIST,
    NODE_STRING_LITERAL,
    // Types
    NODE_TYPE_INT,
    NODE_TYPE_CHAR,
    
    // Statements
    NODE_ASSIGN,
    NODE_ASSIGN_ARR,
    NODE_PRINT,
    NODE_SCAN,
    NODE_IF,
    NODE_WHILE,
    NODE_FOR,
    NODE_INC,
    NODE_DEC,
    
    // Expressions
    NODE_BINARY,
    NODE_IDENTIFIER,
    NODE_LITERAL_INT,
    NODE_LITERAL_BASE,
    BASE_NUM_NODE
} NodeType;

// AST node structure
typedef struct ASTNode {
    NodeType type;
    
    union {
        // Program 
        struct {
            struct ASTNode *declarations;
            struct ASTNode *statements;
        } program;
        
        // Declarations
        struct {
            char *name;
            struct ASTNode *type;
        } var_decl;
        
        struct {
            char *name;
            int size;
            struct ASTNode *type;
        } array_decl;
        
        // Statement list (for multiple statements)
        struct {
            struct ASTNode *stmt;
            struct ASTNode *next;
        } stmt_list;
        
        // Assignment
        struct {
            char *name;
            struct ASTNode *value;
        } assign;
        
        // Array assignment
        struct {
            char *name;
            struct ASTNode *index;
            struct ASTNode *value;
        } assign_arr;
        
        // Print statement
        struct {
            struct ASTNode *format;
            struct ASTNode *args;
        } print;
        
        // Scan statement
        struct {
            struct ASTNode *format;
            struct ASTNode *args;
        } scan;
        
        // If statement
        struct {
            struct ASTNode *condition;
            struct ASTNode *if_body;
            struct ASTNode *else_body;
        } if_stmt;
        
        // While statement
        struct {
            struct ASTNode *condition;
            struct ASTNode *body;
        } while_stmt;
        
        // For statement
        struct {
            struct ASTNode *init;
            struct ASTNode *limit;
            struct ASTNode *update;
            struct ASTNode *body;
        } for_stmt;
        
        // Increment/decrement
        struct {
            struct ASTNode *expr;
        } inc_dec;
        
        // Binary operations
        struct {
            char *op;
            struct ASTNode *left;
            struct ASTNode *right;
        } binary;
        
        // Identifier
        struct {
            char *name;
        } identifier;
        
        // Integer literal
        struct {
            int value;
        } int_literal;
        
        // Base integer literal
        struct {
            char* value;    // Store original string value
            char* base;     // Store original base as string
        } base_literal;

        // String literal
        struct {
            char *value;
        } string_literal;
        
    } data;
} ASTNode;

// AST creation functions
ASTNode *ast_program(ASTNode *declarations, ASTNode *statements);
ASTNode *ast_var_decl(char *name, ASTNode *type);
ASTNode *ast_array_decl(char *name, int size, ASTNode *type);
ASTNode *ast_stmt_list(ASTNode *stmt, ASTNode *next);

ASTNode *ast_type_int(void);
ASTNode *ast_type_char(void);

ASTNode *ast_assign(char *name, ASTNode *value);
ASTNode *ast_assign_arr(char *name, ASTNode *index, ASTNode *value);
ASTNode *ast_print(ASTNode *format, ASTNode *args);
ASTNode *ast_scan(ASTNode *format, ASTNode *args);
ASTNode *ast_if(ASTNode *condition, ASTNode *if_body, ASTNode *else_body);
ASTNode *ast_while(ASTNode *condition, ASTNode *body);
ASTNode *ast_for(ASTNode *init, ASTNode *limit, ASTNode *update, ASTNode *body);
ASTNode *ast_inc(ASTNode *expr);
ASTNode *ast_dec(ASTNode *expr);

ASTNode *ast_binary(char *op, ASTNode *left, ASTNode *right);
ASTNode *ast_identifier(char *name);
ASTNode *ast_literal_int(int value);
ASTNode *ast_literal_base(char* value, char* base);
ASTNode *ast_string_literal(const char *value);

// Function declarations for base number handling
ASTNode* makeBaseNumber(char* value, char* base);
void printBaseNumber(ASTNode* node);

void ast_print_generalized_list(ASTNode *root);

#endif /* AST_H */