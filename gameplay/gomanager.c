#include "gomanager.h"
#include "gameobject.h"
#include <string.h>

typedef struct GOLinkListNode {
    GameObject_t           go;
    struct GOLinkListNode* next;
} GOLinkListNode_t;

typedef struct {
    GOLinkListNode_t* first;
} GOLinkListHead;

// invisible from outside
static GOLinkListHead globalGameObjects;
int                   idHead = 0;

void gameObjectsInit(void) { globalGameObjects.first = NULL; }

void gameObjectsSpawn(GameObject_t* go)
{
    if(globalGameObjects.first == NULL)
    {
        globalGameObjects.first       = (GOLinkListNode_t*)malloc(sizeof(GOLinkListNode_t));
        globalGameObjects.first->next = NULL;
        // copy
        globalGameObjects.first->go = *go;
        go->onCreate(&globalGameObjects.first->go);
    }
    else
    {
        GOLinkListNode_t* node = globalGameObjects.first;
        while(node->next != NULL) node = node->next;
        node->next = (GOLinkListNode_t*)malloc(sizeof(GOLinkListNode_t));
        node       = node->next;
        node->next = NULL;
        // copy
        node->go = *go;
        go->onCreate(&globalGameObjects.first->go);
    }
}

// didn't test yet , may cause bugs.
void gameObjectsDestroyById(int id)
{
    GOLinkListNode_t* node    = globalGameObjects.first;
    GOLinkListNode_t* preNode = NULL;
    while(node != NULL)
    {
        if(node->go.id != id)
        {
            preNode = node;
            node    = node->next;
        }
        else
        {
            preNode = node;
            node->go.onDestroy(&node->go);
            preNode->next = node->next;
            free(node);
        }
    }
}

// didn't test yet , may cause bugs.
void gameObjectDestroyByName(const char* name)
{
    GOLinkListNode_t* node    = globalGameObjects.first;
    GOLinkListNode_t* preNode = NULL;
    while(node != NULL)
    {
        if(strcmp(node->go.name, name))
        {
            preNode = node;
            node    = node->next;
        }
        else
        {
            preNode = node;
            node->go.onDestroy(&node->go);
            preNode->next = node->next;
            free(node);
        }
    }
}

void gameObjectsForeach(void (*func)(GameObject_t*))
{
    GOLinkListNode_t* node = globalGameObjects.first;
    while(node != NULL)
    {
        func(&node->go);
        node = node->next;
    }
}

static GameObject_t* goFound     = NULL;
static int           requestId   = -1;
static const char*   requestName = NULL;

static void _fun1(GameObject_t* go)
{
    if(go->id == requestId) goFound = go;
}

static void _fun2(GameObject_t* go)
{
    if(strcmp(go->name, requestName)) goFound = go;
}

static void _fun3(GameObject_t* go)
{
    if(go->typeId == requestId) goFound = go;
}

GameObject_t* gameObjectsGetById(int id)
{
    requestId = id;
    gameObjectsForeach(_fun1);
    requestId = -1;
    return goFound;
}

GameObject_t* gameObjectsGetByTypeId(int id)
{
    requestId = id;
    gameObjectsForeach(_fun3);
    requestId = -1;
    return goFound;
}

GameObject_t* gameObjectsGetByName(char* name)
{
    requestName = name;
    gameObjectsForeach(_fun2);
    requestName = NULL;
    return goFound;
}

int allocateGameObjectId() { return ++idHead; }