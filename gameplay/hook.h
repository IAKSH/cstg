#pragma once
#include "message.h"

typedef struct HookNode
{
    void* func;
    struct HookNode* next;
} HookNode_t;

typedef struct
{
    HookNode_t* first;
} HookLinkListHead;

extern void hooksInit();
extern void hooksAdd(void(*func)(GamePlayMsg*));
HookLinkListHead* getHooks();