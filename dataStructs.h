#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H

#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
#include <string.h>

#define HASH_SIZE = 97;

// Data Types
typedef enum {UNDF, NUMB, OPER, ASGN, IDEN} tokenType; // --  { KEYW, NUMB, IDEN, OPER, COMPR, LPAR, RPAR, LBRK, RBRK, COLN }

typedef struct Token
{
	char* data;
	tokenType type;

} Token;

typedef struct TokenQueue
{ 
    int front, rear, size; 
    unsigned capacity; 
    struct Token* array;
} TokenQueue;

typedef struct HashSet
{
    Token* array;
    int capacity;
    int size;
} HashSet;


// HashSet Function Declarations
HashSet* init_HashSet(unsigned capacity);
int hashCode(const char* string);
Token getVal(HashSet* set, char* key);
void addVal(HashSet* set, const char* key, Token* token);



// Queue Function Declarations
struct TokenQueue* createTokenQueue(unsigned capacity);
int isFull(struct TokenQueue* queue);
int isEmpty(struct TokenQueue* queue);
void enqueue(struct TokenQueue* queue, struct Token token);
struct Token dequeue(struct TokenQueue* queue);
struct Token front(struct TokenQueue* queue);
struct Token rear(struct TokenQueue* queue);

#endif