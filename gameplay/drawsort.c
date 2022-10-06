#include "drawsort.h"
#include "gameobject.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    DrawLinkListNode_t* first;
} DrawLinkListHead;

// invisibel from outside
static DrawLinkListHead draws;

void drawsInit() { draws.first = NULL; }

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
        static DrawLinkListNode_t* _da_node;
        _da_node = draws.first;
        while(_da_node->next != NULL) _da_node = _da_node->next;
        _da_node->next = (DrawLinkListNode_t*)malloc(sizeof(DrawLinkListNode_t));
        _da_node = _da_node->next;
        _da_node->next = NULL;
        _da_node->go = go;
    }
}

void drawsForeach(void (*func)(DrawLinkListNode_t*))
{
    static DrawLinkListNode_t* _df_node;
    _df_node = draws.first;
    while(_df_node != NULL)
    {
        func(_df_node);
        _df_node = _df_node->next;
    }
}

void drawsClean(void)
{
    static DrawLinkListNode_t* _dc_node;
    static DrawLinkListNode_t* _dc_preNode;
    _dc_node = draws.first;

    while(_dc_node != NULL)
    {
        _dc_preNode = _dc_node;
        _dc_node = _dc_node->next;
        free(_dc_preNode);
    }
    draws.first = NULL;
}

void drawsSort(void)
{
    // Bubble Sort
    static int i, count, num;
    static DrawLinkListNode_t *node, *preNode;
    GameObject_t* goBuffer;
    node = draws.first;
    count = 0;

    while(node != NULL)
    {
        ++count;
        node = node->next;
    }

    // this loop is so bad , may cause performance issues
    // better to replace this with a loop using C(i,2)
    // anyway , I'm lazy , so...
    for(int i = 0; i < count - 1; i++)
    {
        node = draws.first;
        while(node != NULL)
        {
            preNode = node;
            node = node->next;
            if(node == NULL) break;
            if(preNode->go->z < node->go->z)
            {
                goBuffer = node->go;
                node->go = preNode->go;
                preNode->go = goBuffer;
            }
        }
    }
}