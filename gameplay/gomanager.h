#pragma once
#include "gameobject.h"

//extern void gameObjectModelsInit(void);
//extern void gameObjectModelsAdd(GameObject* go);

extern void gameObjectsInit(void);
extern void gameObjectsSpawn(GameObject* go);
extern void gameObjectsDestroyById(int id);
extern void gameObjectDestroyByName(const char* name);
extern void gameObjectsForeach( void(*func)(GameObject*));