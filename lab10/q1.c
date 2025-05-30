#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "q1.h"

ScopeNode* symbolTableStack = NULL;
int currentScope = 0;

int hash(char* name) {
    unsigned long hash = 5381;
    int c;
    while ((c = *name++))
        hash = ((hash << 5) + hash) + c;
    return hash % HASH_TABLE_SIZE;
}

void initSymbolTable() {
    // Initialize the symbol table stack
    ScopeNode* newScope = (ScopeNode*)malloc(sizeof(ScopeNode));
    newScope->hashTable = (HashTable*)malloc(sizeof(HashTable));
    
    // Initialize all hash table entries to NULL
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        newScope->hashTable->table[i] = NULL;
    }
    
    newScope->next = NULL;
    symbolTableStack = newScope;
    currentScope = 0;
}

void insertSymbol(char* name, char* type) {
    if (symbolTableStack == NULL) {
        initSymbolTable();
    }
    
    HashTable* currentTable = symbolTableStack->hashTable;
    int index = hash(name);
    Symbol* newSymbol = (Symbol*)malloc(sizeof(Symbol));
    newSymbol->name = strdup(name);
    newSymbol->type = strdup(type);
    newSymbol->next = currentTable->table[index];
    currentTable->table[index] = newSymbol;
}

void printSymbolTable() {
    if (symbolTableStack == NULL || symbolTableStack->hashTable == NULL) {
        printf("\nSymbol table is empty!\n");
        return;
    }
    printf("\n================ Symbol Table ================\n");
    printf("| %-15s | %-10s |\n", "Name", "Type");
    printf("---------------------------------------------\n");
    HashTable* globalTable = symbolTableStack->hashTable; // Access only the top-level table
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        Symbol* currentSymbol = globalTable->table[i];
        while (currentSymbol != NULL) {
            printf("| %-15s | %-10s |\n",
                currentSymbol->name,
                currentSymbol->type);
            currentSymbol = currentSymbol->next;
        }
    }
    printf("==============================================\n");
}