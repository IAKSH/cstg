#pragma once
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* texture;
// surface can't support hardware acceleration
//static SDL_Surface* surface;
extern SDL_Event event;
extern SDL_Rect fillRect;
extern bool gameShouldBeClose;
extern bool inputLocked;

extern void gameplayInit();
extern void gamePlayDestory();
extern void gamePlayUpateEvents();
extern void gamePlayDrawGameObjects(int x, int y, int z, int w, int h, SDL_Texture* goTexture);