#pragma once
#include "gameobject.h"
#include <SDL2/SDL_render.h>

typedef struct DrawLinkListNode {
    GameObject_t*            go;
    struct DrawLinkListNode* next;
} DrawLinkListNode_t;

extern void drawsInit(void);
extern void drawsAdd(GameObject_t* go);
extern void drawsForeach(void (*func)(DrawLinkListNode_t*));
extern void drawsClean(void);
extern void drawsSort(void);