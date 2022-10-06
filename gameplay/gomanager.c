#include "gomanager.h"
#include "gameobject.h"
#include "linklist.h"
#include <string.h>

static LinkListHead_t globalGameObjects;
int idHead = 0;

void gameObjectsInit(void) { globalGameObjects.first = NULL; }

void gameObjectsSpawn(GameObject_t* go)
{
    if(globalGameObjects.first)
    {
        LinkListNode_t* node = globalGameObjects.first;
        while(node->next) node = node->next;
        LinkListNode_t* newNode = (LinkListNode_t*)malloc(sizeof(LinkListHead_t));
        newNode->forward = node;
        newNode->next = NULL;
        newNode->var = malloc(sizeof(GameObject_t));
        memcpy(newNode->var, go, sizeof(GameObject_t));
        node->next = newNode;
        GameObject_t* newGo = newNode->var;
        newGo->onCreate(newGo);
    }
    else
    {
        LinkListNode_t* newNode = (LinkListNode_t*)malloc(sizeof(LinkListNode_t));
        newNode->forward = NULL;
        newNode->next = NULL;
        newNode->var = malloc(sizeof(GameObject_t));
        memcpy(newNode->var, go, sizeof(GameObject_t));
        globalGameObjects.first = newNode;
        GameObject_t* newGo = newNode->var;
        newGo->onCreate(newGo);
    }
}

// didn't test yet , may cause bugs.
void gameObjectsDestroyById(int id)
{
    LinkListNode_t* node = globalGameObjects.first;
    GameObject_t* go;
    while(node)
    {
        go = node->var;
        if(go->id == id)
        {
            go->onDestroy(go);
            node->next->forward = node->forward;
            node->forward->next = node->next;
            free(node->var);
            free(node);
        }
        node = node->next;
    }
}

// didn't test yet , may cause bugs.
void gameObjectDestroyByName(const char* name)
{
    LinkListNode_t* node = globalGameObjects.first;
    GameObject_t* go;
    while(node)
    {
        go = node->var;
        if(strcmp(go->name, name) == 0)
        {
            go->onDestroy(go);
            node->next->forward = node->forward;
            node->forward->next = node->next;
            free(node->var);
            free(node);
        }
        node = node->next;
    }
}

void gameObjectsForeach(void (*func)(GameObject_t*))
{
    LinkListNode_t* node = globalGameObjects.first;
    while(node)
    {
        func(node->var);
        node = node->next;
    }
}

static GameObject_t* goFound = NULL;
static int requestId = -1;
static const char* requestName = NULL;

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