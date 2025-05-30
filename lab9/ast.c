#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

// Function to create a number node in the AST
ASTNode* createNumberNode(int value) {
    printf("Creating NUMBER node: %d\n", value);
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->type = NODE_NUMBER;
    node->data.value = value;
    return node;
}

// Function to create a variable node in the AST
ASTNode* createVarNode(char name) {
    printf("Creating VARIABLE node: %c\n", name);
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->type = NODE_VAR;
    node->data.var = name;
    return node;
}

// Function to create an operator node with left and right children
ASTNode* createOperatorNode(NodeType type, ASTNode* left, ASTNode* right) {
    printf("Creating OPERATOR node: %d\n", type);
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->type = type;
    node->data.children.left = left;
    node->data.children.right = right;
    return node;
}

// Function to print the AST in a readable format
void printAST(ASTNode* node) {
    if (node == NULL) return;
    
    if(node->type==NODE_VAR){
        printf("%c",node->data.var);
    }else if (node->type == NODE_NUMBER) {
        printf("%d", node->data.value);
    } else {
        printf("("); // Start expression
        switch (node->type) {
            case NODE_ADD:
                printf("+ ");
                break;
            case NODE_SUB:
                printf("- ");
                break;
            case NODE_MUL:
                printf("* ");
                break;
            case NODE_DIV:
                printf("/ ");
                break;
            case NODE_EQ:
                printf("= ");
                break;
            default:
                printf("? "); // Handle unknown node types
        }
        printAST(node->data.children.left);
        printf(" ");
        printAST(node->data.children.right);
        printf(")"); // Close expression
    }
    
}

// Function to free the memory allocated for the AST
void freeAST(ASTNode* node) {
    if (node == NULL) return;
    if (node->type != NODE_NUMBER) {
        freeAST(node->data.children.left);
        freeAST(node->data.children.right);
    }
    free(node);
}

