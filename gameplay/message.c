#include "message.h"
#include <linklist.h>
#include <stdlib.h>

// invisibel from outside
static LinkListHead_t globalMsgs;

void msgsInit(void) {linkListInitialize(&globalMsgs);};

void msgsAdd(GamePlayMsg* msg) { linkListInsertTail(&globalMsgs, msg,sizeof(*msg)); }

void msgsForeach(void (*func)(GamePlayMsg*))
{
    LinkListNode_t* node = globalMsgs.first;
    while(node != NULL)
    {
        func(node->var);
        node = node->next;
    }
}

void msgsClean(void) { linkListClean(&globalMsgs); }