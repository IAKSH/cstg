#include "message.h"
#include <stdlib.h>

// Link List of Msg
typedef struct MsgLinkListNode {
    GamePlayMsg             msg;
    struct MsgLinkListNode* next;
} MsgLinkListNode_t;

typedef struct {
    MsgLinkListNode_t* first;
} MsgLinkListHead;

// invisibel from outside
static MsgLinkListHead globalMsgs;

void msgsInit(void) { globalMsgs.first = NULL; }

void msgsAdd(GamePlayMsg* msg)
{
    if(globalMsgs.first == NULL)
    {
        globalMsgs.first       = (MsgLinkListNode_t*)malloc(sizeof(MsgLinkListNode_t));
        globalMsgs.first->next = NULL;
        // copy
        globalMsgs.first->msg = *msg;
    }
    else
    {
        MsgLinkListNode_t* node = globalMsgs.first;
        while(node->next != NULL) node = node->next;
        node->next = (MsgLinkListNode_t*)malloc(sizeof(MsgLinkListNode_t));
        node       = node->next;
        node->next = NULL;
        // copy
        node->msg = *msg;
    }
}

void msgsForeach(void (*func)(GamePlayMsg*))
{
    MsgLinkListNode_t* node = globalMsgs.first;
    while(node != NULL)
    {
        func(&node->msg);
        node = node->next;
    }
}

void msgsClean(void)
{
    MsgLinkListNode_t* node = globalMsgs.first;
    MsgLinkListNode_t* preNode;
    while(node != NULL)
    {
        preNode = node;
        node    = node->next;
        free(preNode);
    }
    globalMsgs.first = NULL;
}