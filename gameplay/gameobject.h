#pragma once
#include <SDL2/SDL.h>

typedef struct
{
    int id;
    int x,y,z;
    int speedX;
    int speedY;
    char* name;
    void(*onCreate)(void);
    void(*onDestroy)(void);
    void(*onTick)(void);
    SDL_Texture* texture;

} GameObject;