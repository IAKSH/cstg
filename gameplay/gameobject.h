#pragma once
#include <SDL2/SDL.h>

typedef struct GameObject
{
    int id;
    int x,y,z;
    int w,h;
    int speedX;
    int speedY;
    char* name;
    void(*onCreate)(struct GameObject* thisGO);
    void(*onDestroy)(struct GameObject* thisGO);
    void(*onTick)(struct GameObject* thisGO);
    SDL_Texture* texture;

} GameObject_t;