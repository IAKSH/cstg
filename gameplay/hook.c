#include "hook.h"

typedef struct HookNode {
    void*            func;
    struct HookNode* next;
} HookNode_t;

typedef struct {
    HookNode_t* first;
} HookLinkListHead;

// invisible from outside
static HookLinkListHead globalHooks;

void hooksInit(void) { globalHooks.first = NULL; }

void hooksAdd(void (*func)(GamePlayMsg*))
{
    if(globalHooks.first == NULL)
    {
        globalHooks.first       = (HookNode_t*)malloc(sizeof(HookNode_t));
        globalHooks.first->next = NULL;
        // copy
        globalHooks.first->func = func;
    }
    else
    {
        HookNode_t* node = globalHooks.first;
        while(node->next != NULL) node = node->next;
        node->next = (HookNode_t*)malloc(sizeof(HookNode_t));
        node       = node->next;
        node->next = NULL;
        node->func = func;
    }
}

void hooksRun(void)
{
    HookNode_t* node = globalHooks.first;
    if(node == NULL)
        return;
    else if(node->next == NULL) { msgsForeach(node->func); }
    else
    {
        while(node->next != NULL)
        {
            msgsForeach(node->func);
            node = node->next;
        }
        // call the last hook
        msgsForeach(node->func);
    }
    msgsClean();
}