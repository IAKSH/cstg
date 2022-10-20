#include "hashfunc.h"
#include <string.h>

uint32_t fnv1a_32(char* data)
{
    // 32bit version of the algorithm FNV-1a
    static const uint32_t HASH_OFFSET_BASIS_32 = 0x811C9DC5;
    static const uint32_t FNV_PRIME_32         = 16777619;

    uint32_t hash = HASH_OFFSET_BASIS_32;
    int len = strlen(data);
    for(int i = 0; i < len; i++)
    {
        hash *= FNV_PRIME_32;
        hash ^= data[i];
    }

    return hash;
}

uint32_t bkdr_32(char* data)
{
    static uint32_t SEED = 131;
    uint32_t hash = 0;
    for(int i = 0;i < strlen(data);i++) hash = hash * SEED + data[i];
    return (hash & 0x7FFFFFFF);
}

uint64_t bkdr_64(char* data)
{
    static uint32_t SEED = 131;
    uint32_t hash = 0;
    for(int i = 0;i < strlen(data);i++) hash = hash * SEED + data[i];
    return (hash & 0x7FFFFFFFFFFFFFFFL);
}