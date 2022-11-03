#pragma once

#include <stdint.h>
#include <stdlib.h>

typedef struct
{
    uint32_t len;
    void *first;
} Array_t;

extern void arrayInitialize(Array_t *array,size_t size,uint32_t len);
extern void arrayDestory(Array_t *array);
extern void *arrayGetAt(Array_t *array,uint32_t index);
