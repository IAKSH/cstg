#include "hashtable.h"
#include "hashfunc.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32_t hash(char* data, int maxLength) { return fnv1a_32(data) % maxLength; }

void initializeHashTable(HashTable_t* hashTable, int maxLength, int singleObjectSize)
{
    hashTable->maxLength = maxLength;
    hashTable->singleObjectSize = maxLength;
    hashTable->list = calloc(maxLength, singleObjectSize);
    if(!hashTable->list)
    {
        fprintf(stderr,"[ERROR] can't allocate memory for HashTable_t\n");
        abort();
    }
    memset(hashTable->list, 0, maxLength * singleObjectSize);
}

void hashTableFree(HashTable_t* hashTable)
{
    HashTableNode_t* meta = hashTable->list;
    for(int i = 0; i < hashTable->maxLength; i++)
    {
        if(meta++)
        {
            free(meta);
            meta = NULL;
        }
    }
}

void hashTableRemove(HashTable_t* hashTable, HashKey_t key)
{
    void* buffer = hashTable->list[hash(key.begin, key.size)].val;
    hashTable->list[hash(key.begin, key.size)].val = NULL;
    free(buffer);
}

void hashTableAdd(HashTable_t* hashTable, HashKey_t key, void* val) { hashTable->list[hash(key.begin, key.size)].val = val; }

void* hashTableGetValue(HashTable_t* hashTable, HashKey_t key) { return hashTable->list[hash(key.begin, key.size)].val; }

bool hashTableCheckExistance(HashTable_t* hashTable, HashKey_t key) { return hashTable->list[hash(key.begin, key.size)].val == NULL; }