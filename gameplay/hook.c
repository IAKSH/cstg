#include "hook.h"
#include "function.h"
#include "linklist.h"
#include <utools.h>

// invisible from outside
static LinkListHead_t globalHooks;

void hooksInit(void) { linkListInitialize(&globalHooks);}

void hooksAdd(void (*func)(GamePlayMsg*))
{
    Function_t f = {func};
    linkListInsertTail(&globalHooks,&f,sizeof(f));
}

void hooksRun(void)
{
    LinkListNode_t* node = globalHooks.first;
    Function_t* f;
    while(node)
    {
        f = node->var;
        msgsForeach(f->func);
        node = node->next;
    }
    msgsClean();
}