#include "drawsort.h"
#include <stdlib.h>

typedef struct
{
    DrawLinkListNode_t* first;
} DrawLinkListHead;

// invisibel from outside
static DrawLinkListHead draws;

void drawsInit()
{
    draws.first = NULL;
}

void drawsAdd(GameObject_t* go)
{
    if(draws.first == NULL)
    {
        draws.first = (DrawLinkListNode_t*)malloc(sizeof(DrawLinkListNode_t));
        draws.first->next = NULL;
        draws.first->go = go;
    }
    else
    {
        DrawLinkListNode_t* node = draws.first;
        while(node->next != NULL) node = node->next;
        node->next = (DrawLinkListNode_t*)malloc(sizeof(DrawLinkListNode_t));
        node = node->next;
        node->next = NULL;
        node->go = go;
    }
}

void drawsForeach(void(*func)(DrawLinkListNode_t*))
{
    DrawLinkListNode_t* node = draws.first;
    while(node != NULL)
    {
        func(node);
        node = node->next;
    }
}

void drawsClean(void)
{
    DrawLinkListNode_t* node = draws.first;
    DrawLinkListNode_t* preNode;
    while(node != NULL)
    {
        preNode = node;
        node = node->next;
        free(preNode);
    }
    draws.first = NULL;
}

void drawsSort(void)
{
    // TODO
}