#pragma once
#include "gameobject.h"

//extern void gameObjectModelsInit(void);
//extern void gameObjectModelsAdd(GameObject* go);

extern void gameObjectsInit(void);
extern void gameObjectsSpawnById(int id);
extern void gameObjectsSpawnByName(const char* name);
extern void gameObjectsDestroyById(int id);
extern void gameObjectDestroyByName(const char* name);
extern void gameObjectsForeach( void(*func)(GameObject*));