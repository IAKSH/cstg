#pragma once
#include "gameobject.h"

//extern void gameObjectModelsInit(void);
//extern void gameObjectModelsAdd(GameObject* go);

extern void gameObjectsInit(void);
extern void gameObjectsSpawn(GameObject_t*);
extern void gameObjectsDestroyById(int);
extern void gameObjectDestroyByName(const char*);
extern void gameObjectsForeach( void(*)(GameObject_t*));
extern GameObject_t* gameObjectsGetById(int);
extern GameObject_t* gameObjectsGetByTypeId(int);
extern GameObject_t* gameObjectsGetByName(char*);
extern int allocateGameObjectId();