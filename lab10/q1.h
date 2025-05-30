#ifndef Q1_H
#define Q1_H

#include <string.h>

#define HASH_TABLE_SIZE 101

typedef struct Symbol {
    char* name;
    char* type;
    struct Symbol* next;
} Symbol;

typedef struct HashTable {
    Symbol* table[HASH_TABLE_SIZE];
} HashTable;

typedef struct ScopeNode {
    HashTable* hashTable;
    struct ScopeNode* next;
} ScopeNode;

extern ScopeNode* symbolTableStack;
extern int currentScope;

int hash(char* name);
void initSymbolTable();
void insertSymbol(char* name, char* type);
void printSymbolTable();

#endif