#include "drawsort.h"
#include "gameobject.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    DrawLinkListNode_t* first;
} DrawLinkListHead;

// invisibel from outside
static DrawLinkListHead draws;
static int drawAmount;

static DrawLinkListNode_t* drawLinkListGetAt(int index)
{
    DrawLinkListNode_t* node = draws.first;
    for(int i = 0; i < index; i++)
    {
        if(!node)
        {
            fprintf(stderr, "drawsGetAt() failed: out of range\n");
            abort();
        }
        node = node->next;
    }
    return node;
}

void drawsInit()
{
    draws.first = NULL;
    drawAmount = 0;
}

void drawsAdd(GameObject_t* go)
{
    if(draws.first == NULL)
    {
        draws.first = (DrawLinkListNode_t*)malloc(sizeof(DrawLinkListNode_t));
        draws.first->next = NULL;
        draws.first->go = (GameObject_t*)malloc(sizeof(GameObject_t));
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
        _da_node->go = (GameObject_t*)malloc(sizeof(GameObject_t));
        _da_node->go = go;
    }
    drawAmount++;
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
    drawAmount = 0;
}

void drawsSort(void)
{
    int i, j;
    for(i = 1; i < drawAmount; i++)
    {
        j = i - 1;
        while((j >= 0) && (drawLinkListGetAt(i)->go->z < drawLinkListGetAt(j)->go->z))
        {
            drawLinkListGetAt(j + 1)->go = drawLinkListGetAt(j)->go;
            j--;
        }
        drawLinkListGetAt(j + 1)->go = drawLinkListGetAt(i)->go;
    }
}