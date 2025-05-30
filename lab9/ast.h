#ifndef AST_H
#define AST_H

typedef enum {
    NODE_NUMBER,
    NODE_VAR,
    NODE_ADD,
    NODE_SUB,
    NODE_MUL,
    NODE_DIV,
    NODE_EQ,
    NODE_COM
} NodeType;

typedef struct ASTNode {
    NodeType type;
    union {
        int value;
        char var; 
        struct {
            struct ASTNode* left;
            struct ASTNode* right;
        } children;
    } data;
} ASTNode;

ASTNode* createNumberNode(int value);
ASTNode* createVarNode(char var);
ASTNode* createOperatorNode(NodeType type, ASTNode* left, ASTNode* right);
void printAST(ASTNode* node);
void freeAST(ASTNode* node);

#endif // AST_H

