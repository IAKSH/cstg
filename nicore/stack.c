#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void stackInitialize(Stack_t *stack,int size)
{
    stack->count = 0;
    stack->allocSize = 0;
    stack->itemSize = size;
    stack->bottom = NULL;
}

void stackResize(Stack_t *stack,int n)
{
    if (n < stack->count)
    {
        printf("[NICORE ERROR] bad stack resize\n");
        abort();
    }

    void *buffer = calloc(stack->itemSize,n);
    if(!buffer)
    {
        printf("[NICORE ERROR] can't alloc memory for stack resize\n");
        abort();
    }

    for(int i = 0;i < stack->count;i++)
        memcpy(buffer + i,stack->bottom + i,stack->itemSize);

    stack->allocSize = n;
    
    if(stack->count > 0)
        free(stack->bottom);
    stack->bottom = buffer;
}

void stackPush(Stack_t *stack,void *p)
{
    if(++(stack->count) > stack->allocSize)
        stackResize(stack,stack->allocSize + 1);
    memcpy(stack->bottom + stack->count - 1,p,stack->itemSize);
}

void stackPop(Stack_t *stack)
{
    if(stack->count == 0)
    {
        printf("[NICORE ERROR] trying to pop from an empty stack\n");
        abort();
    }

    stack->count--;
}

void *stackGetTop(Stack_t *stack)
{
    return stack->bottom + stack->count - 1;
}

void stackRelease(Stack_t *stack)
{
    for(int i = stack->count - 1;i < stack->allocSize - 1;i++)
        free(stack->bottom + i);
}

void stackDestory(Stack_t *stack)
{
    free(stack->bottom);
}
