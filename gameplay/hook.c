#include "hook.h"

static HookLinkListHead hooks;

void hooksInit()
{
    hooks.first = NULL;
}

void hooksAdd(void(*func)(GamePlayMsg*))
{
    if(hooks.first == NULL)
    {
        hooks.first = (HookNode_t*)malloc(sizeof(HookNode_t));
        hooks.first->next = NULL;
        // copy
        hooks.first->func = func;
    }
    else
    {
        HookNode_t* node = hooks.first;
        while(node->next != NULL) node = node->next;
        node->next = (HookNode_t*)malloc(sizeof(HookNode_t));
        node = node->next;
        node->next = NULL;
        node->func = func;
    }
}

HookLinkListHead* getHooks() {return &hooks;};