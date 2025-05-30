#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

// Helper function to allocate a new AST node
static ASTNode *create_node(NodeType type) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed for AST node\n");
        exit(1);
    }
    memset(node, 0, sizeof(ASTNode)); // Initialize to zeros
    node->type = type;
    return node;
}

// Helper function to duplicate a string
static char *str_dup(const char *s) {
    if (!s) return NULL;
    char *dup = strdup(s);
    if (!dup) {
        fprintf(stderr, "Memory allocation failed for string duplication\n");
        exit(1);
    }
    return dup;
}

// Program node
ASTNode *ast_program(ASTNode *declarations, ASTNode *statements) {
    ASTNode *node = create_node(NODE_PROGRAM);
    node->data.program.declarations = declarations;
    node->data.program.statements = statements;
    return node;
}

// Variable declaration node
ASTNode *ast_var_decl(char *name, ASTNode *type) {
    ASTNode *node = create_node(NODE_VAR_DECL);
    node->data.var_decl.name = str_dup(name);
    node->data.var_decl.type = type;
    return node;
}

// Array declaration node
ASTNode *ast_array_decl(char *name, int size, ASTNode *type) {
    ASTNode *node = create_node(NODE_ARRAY_DECL);
    node->data.array_decl.name = str_dup(name);
    node->data.array_decl.size = size;
    node->data.array_decl.type = type;
    return node;
}

// Statement list node
ASTNode *ast_stmt_list(ASTNode *stmt, ASTNode *next) {
    ASTNode *node = create_node(NODE_STMT_LIST);
    node->data.stmt_list.stmt = stmt;
    node->data.stmt_list.next = next;
    return node;
}

// Type nodes
ASTNode *ast_type_int(void) {
    return create_node(NODE_TYPE_INT);
}

ASTNode *ast_type_char(void) {
    return create_node(NODE_TYPE_CHAR);
}

// Assignment node
ASTNode *ast_assign(char *name, ASTNode *value) {
    ASTNode *node = create_node(NODE_ASSIGN);
    node->data.assign.name = str_dup(name);
    node->data.assign.value = value;
    return node;
}

// Array assignment node
ASTNode *ast_assign_arr(char *name, ASTNode *index, ASTNode *value) {
    ASTNode *node = create_node(NODE_ASSIGN_ARR);
    node->data.assign_arr.name = str_dup(name);
    node->data.assign_arr.index = index;
    node->data.assign_arr.value = value;
    return node;
}

// Print statement node
ASTNode *ast_print(ASTNode *format, ASTNode *args) {
    ASTNode *node = create_node(NODE_PRINT);
    node->data.print.format = format;
    node->data.print.args = args;
    return node;
}

// Scan statement node
ASTNode *ast_scan(ASTNode *format, ASTNode *args) {
    ASTNode *node = create_node(NODE_SCAN);
    node->data.scan.format = format;
    node->data.scan.args = args;
    return node;
}

// If statement node
ASTNode *ast_if(ASTNode *condition, ASTNode *if_body, ASTNode *else_body) {
    ASTNode *node = create_node(NODE_IF);
    node->data.if_stmt.condition = condition;
    node->data.if_stmt.if_body = if_body;
    node->data.if_stmt.else_body = else_body;
    return node;
}

// While statement node
ASTNode *ast_while(ASTNode *condition, ASTNode *body) {
    ASTNode *node = create_node(NODE_WHILE);
    node->data.while_stmt.condition = condition;
    node->data.while_stmt.body = body;
    return node;
}

// For statement node
ASTNode *ast_for(ASTNode *init, ASTNode *limit, ASTNode *update, ASTNode *body) {
    ASTNode *node = create_node(NODE_FOR);
    node->data.for_stmt.init = init;
    node->data.for_stmt.limit = limit;
    node->data.for_stmt.update = update;
    node->data.for_stmt.body = body;
    return node;
}

// Increment node
ASTNode *ast_inc(ASTNode *expr) {
    ASTNode *node = create_node(NODE_INC);
    node->data.inc_dec.expr = expr;
    return node;
}

// Decrement node
ASTNode *ast_dec(ASTNode *expr) {
    ASTNode *node = create_node(NODE_DEC);
    node->data.inc_dec.expr = expr;
    return node;
}

// Binary operation node
ASTNode *ast_binary(char *op, ASTNode *left, ASTNode *right) {
    ASTNode *node = create_node(NODE_BINARY);
    node->data.binary.op = str_dup(op);
    node->data.binary.left = left;
    node->data.binary.right = right;
    return node;
}

// Identifier node
ASTNode *ast_identifier(char *name) {
    ASTNode *node = create_node(NODE_IDENTIFIER);
    node->data.identifier.name = str_dup(name);
    return node;
}

// Integer literal node
ASTNode *ast_literal_int(int value) {
    ASTNode *node = create_node(NODE_LITERAL_INT);
    node->data.int_literal.value = value;
    return node;
}

// Base integer literal node
ASTNode *ast_literal_base(char* value, char* base) {
    ASTNode *node = create_node(NODE_LITERAL_BASE);
    node->data.base_literal.value = strdup(value);
    node->data.base_literal.base = strdup(base);
    return node;
}

// String literal node
ASTNode* ast_string_literal(const char* value) {
    ASTNode* node = create_node(NODE_STRING_LITERAL);
    node->data.string_literal.value = strdup(value);
    return node;
}

// Base number node
ASTNode *makeBaseNumber(char* value, char* base) {
    ASTNode *node = create_node(NODE_LITERAL_BASE);
    node->data.base_literal.value = strdup(value);
    node->data.base_literal.base = strdup(base);
    return node;
}

// Update print function to print strings
void printBaseNumber(ASTNode *node) {
    if (node->type == NODE_LITERAL_BASE) {
        printf("(%s, %s)", node->data.base_literal.value, node->data.base_literal.base);
    }
}

// Print AST for debugging
// void ast_print_tree(ASTNode *root, int level) {
//     if (!root) return;
    
//     // Indentation
//     for (int i = 0; i < level; i++) {
//         printf("  ");
//     }
    
//     // Print node based on its type
//     switch(root->type) {
//         case NODE_PROGRAM:
//             printf("Program\n");
//             ast_print_tree(root->data.program.declarations, level + 1);
//             ast_print_tree(root->data.program.statements, level + 1);
//             break;
            
//         case NODE_VAR_DECL:
//             printf("VarDecl: %s\n", root->data.var_decl.name);
//             ast_print_tree(root->data.var_decl.type, level + 1);
//             break;
            
//         case NODE_ARRAY_DECL:
//             printf("ArrayDecl: %s[%d]\n", root->data.array_decl.name, root->data.array_decl.size);
//             ast_print_tree(root->data.array_decl.type, level + 1);
//             break;
            
//         case NODE_STMT_LIST:
//             printf("StmtList\n");
//             ast_print_tree(root->data.stmt_list.stmt, level + 1);
//             ast_print_tree(root->data.stmt_list.next, level);
//             break;
            
//         case NODE_TYPE_INT:
//             printf("Type: int\n");
//             break;
            
//         case NODE_TYPE_CHAR:
//             printf("Type: char\n");
//             break;
            
//         case NODE_ASSIGN:
//             printf("Assign: %s =\n", root->data.assign.name);
//             ast_print_tree(root->data.assign.value, level + 1);
//             break;
            
//         case NODE_ASSIGN_ARR:
//             printf("AssignArr: %s[] =\n", root->data.assign_arr.name);
//             printf("Index:\n");
//             ast_print_tree(root->data.assign_arr.index, level + 1);
//             if (root->data.assign_arr.value) {
//                 printf("Value:\n");
//                 ast_print_tree(root->data.assign_arr.value, level + 1);
//             }
//             break;
            
//         case NODE_PRINT:
//             printf("Print:\n");
//             printf("Format:\n");
//             ast_print_tree(root->data.print.format, level + 1);
//             if (root->data.print.args) {
//                 printf("Args:\n");
//                 ast_print_tree(root->data.print.args, level + 1);
//             }
//             break;
            
//         case NODE_SCAN:
//             printf("Scan:\n");
//             printf("Format:\n");
//             ast_print_tree(root->data.scan.format, level + 1);
//             if (root->data.scan.args) {
//                 printf("Args:\n");
//                 ast_print_tree(root->data.scan.args, level + 1);
//             }
//             break;
            
//         case NODE_IF:
//             printf("If\n");
//             printf("Condition:\n");
//             ast_print_tree(root->data.if_stmt.condition, level + 1);
//             printf("If Body:\n");
//             ast_print_tree(root->data.if_stmt.if_body, level + 1);
//             if (root->data.if_stmt.else_body) {
//                 printf("Else Body:\n");
//                 ast_print_tree(root->data.if_stmt.else_body, level + 1);
//             }
//             break;
            
//         case NODE_WHILE:
//             printf("While\n");
//             printf("Condition:\n");
//             ast_print_tree(root->data.while_stmt.condition, level + 1);
//             printf("Body:\n");
//             ast_print_tree(root->data.while_stmt.body, level + 1);
//             break;
            
//         case NODE_FOR:
//             printf("For\n");
//             printf("Init:\n");
//             ast_print_tree(root->data.for_stmt.init, level + 1);
//             printf("Limit:\n");
//             ast_print_tree(root->data.for_stmt.limit, level + 1);
//             printf("Update:\n");
//             ast_print_tree(root->data.for_stmt.update, level + 1);
//             printf("Body:\n");
//             ast_print_tree(root->data.for_stmt.body, level + 1);
//             break;
            
//         case NODE_INC:
//             printf("Inc\n");
//             ast_print_tree(root->data.inc_dec.expr, level + 1);
//             break;
            
//         case NODE_DEC:
//             printf("Dec\n");
//             ast_print_tree(root->data.inc_dec.expr, level + 1);
//             break;
            
//         case NODE_BINARY:
//             printf("Binary: %s\n", root->data.binary.op);
//             printf("Left:\n");
//             ast_print_tree(root->data.binary.left, level + 1);
//             printf("Right:\n");
//             ast_print_tree(root->data.binary.right, level + 1);
//             break;
            
//         case NODE_IDENTIFIER:
//             printf("Identifier: %s\n");
//             break;
            
//         case NODE_LITERAL_INT:
//             printf("IntLiteral: %d\n");
//             break;
            
//         case NODE_LITERAL_BASE:
//             printf("BaseLiteral: %d (base %d)\n", root->data.base_literal.value, root->data.base_literal.base);
//             break;
            
//         default:
//             printf("Unknown node type: %d\n", root->type);
//     }
// }

// // Free AST
// void ast_free_tree(ASTNode *root) {
//     if (!root) return;
    
//     // Free node based on its type
//     switch(root->type) {
//         case NODE_PROGRAM:
//             ast_free_tree(root->data.program.declarations);
//             ast_free_tree(root->data.program.statements);
//             break;
            
//         case NODE_VAR_DECL:
//             free(root->data.var_decl.name);
//             ast_free_tree(root->data.var_decl.type);
//             break;
            
//         case NODE_ARRAY_DECL:
//             free(root->data.array_decl.name);
//             ast_free_tree(root->data.array_decl.type);
//             break;
            
//         case NODE_STMT_LIST:
//             ast_free_tree(root->data.stmt_list.stmt);
//             ast_free_tree(root->data.stmt_list.next);
//             break;
            
//         case NODE_ASSIGN:
//             free(root->data.assign.name);
//             ast_free_tree(root->data.assign.value);
//             break;
            
//         case NODE_ASSIGN_ARR:
//             free(root->data.assign_arr.name);
//             ast_free_tree(root->data.assign_arr.index);
//             if (root->data.assign_arr.value) {
//                 ast_free_tree(root->data.assign_arr.value);
//             }
//             break;
            
//         case NODE_PRINT:
//             ast_free_tree(root->data.print.format);
//             if (root->data.print.args) {
//                 ast_free_tree(root->data.print.args);
//             }
//             break;
            
//         case NODE_SCAN:
//             ast_free_tree(root->data.scan.format);
//             if (root->data.scan.args) {
//                 ast_free_tree(root->data.scan.args);
//             }
//             break;
            
//         case NODE_IF:
//             ast_free_tree(root->data.if_stmt.condition);
//             ast_free_tree(root->data.if_stmt.if_body);
//             if (root->data.if_stmt.else_body) {
//                 ast_free_tree(root->data.if_stmt.else_body);
//             }
//             break;
            
//         case NODE_WHILE:
//             ast_free_tree(root->data.while_stmt.condition);
//             ast_free_tree(root->data.while_stmt.body);
//             break;
            
//         case NODE_FOR:
//             ast_free_tree(root->data.for_stmt.init);
//             ast_free_tree(root->data.for_stmt.limit);
//             ast_free_tree(root->data.for_stmt.update);
//             ast_free_tree(root->data.for_stmt.body);
//             break;
            
//         case NODE_INC:
//         case NODE_DEC:
//             ast_free_tree(root->data.inc_dec.expr);
//             break;
            
//         case NODE_BINARY:
//             free(root->data.binary.op);
//             ast_free_tree(root->data.binary.left);
//             ast_free_tree(root->data.binary.right);
//             break;
            
//         case NODE_IDENTIFIER:
//             free(root->data.identifier.name);
//             break;
            
//         case NODE_TYPE_INT:
//         case NODE_TYPE_CHAR:
//         case NODE_LITERAL_INT:
//         case NODE_LITERAL_BASE:
//             // No additional memory to free
//             break;
            
//         default:
//             fprintf(stderr, "Unknown node type during free: %d\n", root->type);
//     }
    
//     // Free the node itself
//     free(root);
// }

void ast_print_generalized_list(ASTNode *root) {
    if (!root) return;
    
    switch (root->type) {
        case NODE_PROGRAM:
            printf("(");
            ast_print_generalized_list(root->data.program.declarations);
            ast_print_generalized_list(root->data.program.statements);
            printf("\n)");
            break;
            
        case NODE_STMT_LIST:
            if (root->data.stmt_list.stmt->type == NODE_VAR_DECL) {
                printf("\n");
                ast_print_generalized_list(root->data.stmt_list.stmt);
                if (root->data.stmt_list.next) {
                    ast_print_generalized_list(root->data.stmt_list.next);
                }
            } else {
                if (root->data.stmt_list.next) {
                    printf("\n(\n");
                }
                ast_print_generalized_list(root->data.stmt_list.stmt);
                if (root->data.stmt_list.next) {
                    printf("\n");
                    ast_print_generalized_list(root->data.stmt_list.next);
                    printf("\n)");
                }
            }
            break;
            
        case NODE_VAR_DECL:
            printf("(%s ", root->data.var_decl.name);
            ast_print_generalized_list(root->data.var_decl.type);
            printf(")");
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
            printf(")");
            break;
            
        case NODE_PRINT:
            printf("(print ");
            char *str = root->data.print.format->data.identifier.name;
            if (str[0] == '"' && str[strlen(str)-1] == '"') {
                printf("\"%.*s\"", (int)strlen(str)-2, str+1);
            } else {
                printf("%s", str);
            }
            if (root->data.print.args) {
                printf(" ");
                ast_print_generalized_list(root->data.print.args);
            }
            printf(")");
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
            
        case NODE_LITERAL_BASE:
            printf("(%s %s)", root->data.base_literal.value, root->data.base_literal.base);
            break;

            case NODE_FOR:
            printf("(for ");
            ast_print_generalized_list(root->data.for_stmt.init);
            printf(" ");
            ast_print_generalized_list(root->data.for_stmt.limit);
            printf(" ");
            ast_print_generalized_list(root->data.for_stmt.update);
            printf(" ");
            ast_print_generalized_list(root->data.for_stmt.body);
            printf(")");
            break;
        
        case NODE_WHILE:
            printf("(while ");
            ast_print_generalized_list(root->data.while_stmt.condition);
            printf(" ");
            ast_print_generalized_list(root->data.while_stmt.body);
            printf(")");
            break;
        
        case NODE_IF:
            printf("(if ");
            ast_print_generalized_list(root->data.if_stmt.condition);
            printf(" ");
            ast_print_generalized_list(root->data.if_stmt.if_body);
            if (root->data.if_stmt.else_body) {
                printf(" ");
                ast_print_generalized_list(root->data.if_stmt.else_body);
            }
            printf(")");
            break;
        
        case NODE_STRING_LITERAL:
            printf("\"%s\"", root->data.string_literal.value);
            break;
            
        default:
            break;
    }
}


