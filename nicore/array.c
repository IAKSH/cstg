#include "array.h"

#include <stdio.h>

void arrayInitialize(Array_t *array,size_t size,uint32_t len)
{
    array->len = len;
    array->first = calloc(size,len);
}

void arrayDestory(Array_t *array)
{
    free(array->first);
}

void *arrayGetAt(Array_t *array,uint32_t index)
{
    if(index + 1 > array->len)
    {
        printf("[NICORE ERROR] array index out of range\n");
        abort();
    }

    return array->first + index;
}