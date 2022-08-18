#include "message.h"
#include <stdlib.h>

// Link List of Msg
typedef struct MsgLinkListNode
{
    GamePlayMsg msg;
    struct MsgLinkListNode* next;
} MsgLinkListNode_t;

typedef struct
{
    MsgLinkListNode_t* first;
} MsgLinkListHead;

static MsgLinkListHead msgs;

void msgsInit()
{
    msgs.first = NULL;
}

void msgsAdd(GamePlayMsg* msg)
{
    if(msgs.first == NULL)
    {
        msgs.first = (MsgLinkListNode_t*)malloc(sizeof(MsgLinkListNode_t));
        msgs.first->next = NULL;
        // copy
        msgs.first->msg = *msg;
    }
    else
    {
        MsgLinkListNode_t* node = msgs.first;
        while(node->next != NULL) node = node->next;
        node->next = (MsgLinkListNode_t*)malloc(sizeof(MsgLinkListNode_t));
        node = node->next;
        node->next = NULL;
        node->msg = *msg;
    }
}

void msgsForeach(void(*func)(GamePlayMsg*))
{
    MsgLinkListNode_t* node = msgs.first;
    while(node != NULL)
    {
        func(&node->msg);
        node = node->next;
    }
}

void msgsClean()
{
    MsgLinkListNode_t* node = msgs.first;
    MsgLinkListNode_t* preNode = NULL;
    while(node != NULL)
    {
        preNode = node;
        node = node->next;
        free(preNode);
    }
    msgs.first = NULL;
}