#ifndef AST_H
#define AST_H


typedef struct {
 char* value;
} StringLiteralNode;


typedef enum {
 NODE_PROGRAM,
 NODE_VAR_DECL,
 NODE_ARRAY_DECL,
 NODE_STMT_LIST,
 NODE_STRING_LITERAL,
 NODE_TYPE_INT,
 NODE_TYPE_CHAR,
 NODE_ASSIGN,
 NODE_ASSIGN_ARR,
 NODE_PRINT,
 NODE_SCAN,
 NODE_IF,
 NODE_WHILE,
 NODE_FOR,
 NODE_INC,
 NODE_DEC,
 NODE_BINARY,
 NODE_IDENTIFIER,
 NODE_LITERAL_INT,
 NODE_LITERAL_BASE,
 BASE_NUM_NODE
}NodeType;



typedef struct ASTNode {
 NodeType type;
 
 union {
 struct {
 struct ASTNode *declarations;
 struct ASTNode *statements;
 }program;
 
 struct {
 char *name;
 struct ASTNode *type;
 } var_decl;
 
 struct {
 char *name;
 int size;
 struct ASTNode *type;
 } array_decl;
 
 struct {
 struct ASTNode *stmt;
 struct ASTNode *next;
 } stmt_list;
 


 struct {
 char *name;
 struct ASTNode *value;
 } assign;
 
 struct {
 char *name;
 struct ASTNode *index;
 struct ASTNode *value;
 } assign_arr;
 
 struct {
 struct ASTNode *format;
 struct ASTNode *args;
 } print;
 
 struct {
 struct ASTNode *format;
 struct ASTNode *args;
 } scan;
 
 struct {
 struct ASTNode *condition;
 struct ASTNode *if_body;
 struct ASTNode *else_body;
 } if_stmt;
 
 struct {
 struct ASTNode *condition;
 struct ASTNode *body;
 } while_stmt;
 
 struct {
 struct ASTNode *init;
 struct ASTNode *limit;
 struct ASTNode *update;
 struct ASTNode *body;
 } for_stmt;
 
 struct {
 struct ASTNode *expr;
 } inc_dec;
 
 struct {
 char *op;
 struct ASTNode *left;
 struct ASTNode *right;
 } binary;
 
 struct {
 char *name;
 } identifier;
 
 struct {
 int value;
 } int_literal;
 
 struct {
 char* value; 
 char* base; 
 } base_literal;

 struct {
 char *value;
 } string_literal;
 
 } data;
} ASTNode;

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

ASTNode* makeBaseNumber(char* value, char* base);


void printBaseNumber(ASTNode* node);

void ast_print_generalized_list(ASTNode *root);

// Execution and symbol table functions
void execute_program(ASTNode* root);
void execute_stmt(ASTNode* node);
int evaluate_expr(ASTNode* node);
void add_symbol(const char* name, int type);
struct symbol_entry* lookup_symbol(const char* name);
void print_symbol_table();

// AST validation functions
void validate_ast(ASTNode* node);
void validate_declarations(ASTNode* declarations);
void validate_statements(ASTNode* statements);

// Semantic checking functions
void check_type_compatibility(ASTNode* left, ASTNode* right, const char* operation);
void check_array_bounds(const char* array_name, ASTNode* index_expr);

#endif