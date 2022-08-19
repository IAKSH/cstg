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

void gameObjectsSpawnById(int id)
{
    
}

void gameObjectsSpawnByName(const char* name)
{

}

void gameObjectsDestroyById(int id)
{

}

void gameObjectDestroyByName(const char* name)
{

}

void gameObjectsForeach( void(*func)(GameObject*))
{

}