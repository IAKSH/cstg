#pragma once

typedef struct
{
    int count;
    int allocSize;
    int itemSize;
    void* bottom;
} Stack_t;

extern void stackInitialize(Stack_t *stack,int size);
extern void stackResize(Stack_t *stack,int n);
extern void stackRelease(Stack_t *stack);
extern void stackDestory(Stack_t *stack);
extern void stackPush(Stack_t *stack,void *p);
extern void stackPop(Stack_t *stack);
extern void *stackGetTop(Stack_t *stack);