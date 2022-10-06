#pragma once
#include "drawsort.h"
#include "gameobject.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>
#include <stdbool.h>

struct Camera
{
    int speedX,speedY;
    int x,y;
    //int x,y,z;
    //float zoom;//didn't realize yet.
};

extern struct Camera camera;

extern SDL_Window* globalWindow;
extern SDL_Renderer* globalRenderer;
extern SDL_Texture* globalTexture;
// surface can't support hardware acceleration
// static SDL_Surface* surface;
extern SDL_Event globalEvent;
extern SDL_Rect windowFillRect;
extern bool gameShouldBeClose;

extern void gameplayInit();
extern void gamePlayDestory();
extern void gamePlayUpateEvents();
extern void gamePlayDrawGameObjects(GameObject_t*);
extern void gamePlayDrawFx(SDL_Surface*);
extern void gameplayFlash(void);