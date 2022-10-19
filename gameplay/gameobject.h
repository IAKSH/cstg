#pragma once
#include <SDL2/SDL.h>
#include "animation.h"

typedef struct GameObject {
    int id;  // if id < 0 then: this is a FX object
    int typeId;
    int x, y, z;
    int w, h;
    int speedX;
    int speedY;
    int hp, mp;
    int state;  // 0:dead 1:alive ~:custom...
    char* name;
    void (*onCreate)(struct GameObject* thisGO);
    void (*onDestroy)(struct GameObject* thisGO);
    void (*onTick)(struct GameObject* thisGO);
    Animator_t animator;

} GameObject_t;