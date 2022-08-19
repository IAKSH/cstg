#include "gomanager.h"
#include "gameobject.h"
#include <string.h>

typedef struct GOLinkListNode
{
    GameObject go;
    struct GOLinkListNode* next;
} GOLinkListNode_t;

typedef struct 
{
    GOLinkListNode_t* first;
} GOLinkListHead;

// invisible from outside
static GOLinkListHead globalGameObjects;

void gameObjectsInit(void)
{
    globalGameObjects.first = NULL;
}

void gameObjectsSpawn(GameObject* go)
{
    if(globalGameObjects.first == NULL)
    {
        globalGameObjects.first = (GameObject*)malloc(sizeof(GameObject));
        globalGameObjects.first->next = NULL;
        // copy
        globalGameObjects.first->go = * go;
    }
    else
    {
        GOLinkListNode_t* node = globalGameObjects.first;
        while(node->next != NULL) node = node->next;
        node->next = (GOLinkListNode_t*)malloc(sizeof(GOLinkListNode_t));
        node = node->next;
        node->next = NULL;
        // copy
        node->go = *go;
    }
}

// didn't test yet , may cause bugs.
void gameObjectsDestroyById(int id)
{
    GOLinkListNode_t* node = globalGameObjects.first;
    GOLinkListNode_t* preNode = NULL;
    while(node != NULL)
    {
        if(node->go.id != id)
        {
            preNode = node;
            node = node->next;
        }
        else
        {
            preNode = node;
            node->go.onDestroy();
            preNode->next = node->next;
            free(node);
        }
    }
}

// didn't test yet , may cause bugs.
void gameObjectDestroyByName(const char* name)
{
    GOLinkListNode_t* node = globalGameObjects.first;
    GOLinkListNode_t* preNode = NULL;
    while(node != NULL)
    {
        if(strcmp(node->go.name,name))
        {
            preNode = node;
            node = node->next;
        }
        else
        {
            preNode = node;
            node->go.onDestroy();
            preNode->next = node->next;
            free(node);
        }
    }
}

void gameObjectsForeach( void(*func)(GameObject*))
{
    GOLinkListNode_t* node = globalGameObjects.first;
    while(node != NULL)
    {
        func(&node->go);
        node = node->next;
    }
}