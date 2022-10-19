#pragma once
#include "hashfunc.h"
#include <stdbool.h>

#define ORDINARY_HASHTABLE_SIZE 10000

typedef struct {
    void* begin;
    uint32_t size;
} HashKey_t;

typedef struct {
    void* val;
} HashTableNode_t;

typedef struct {
    uint32_t maxLength, singleObjectSize;
    HashTableNode_t* list;
} HashTable_t;

extern uint32_t hash(char*,int);
extern bool hashTableCheckExistance(HashTable_t*, HashKey_t);
extern void* hashTableGetValue(HashTable_t*, HashKey_t);
extern void initializeHashTable(HashTable_t*, int, int);
extern void hashTableAdd(HashTable_t*, HashKey_t, void*);
extern void hashTableRemove(HashTable_t*, HashKey_t);
extern void hashTableFree(HashTable_t*);