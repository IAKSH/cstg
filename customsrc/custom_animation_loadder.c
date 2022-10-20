#include "custom_animation_loadder.h"
#include "animation.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <gameplay.h>
#include <utools.h>

static SDL_Texture* loadTextrue(char* fileName)
{
    char buffer[128];
    strcpy(buffer, rootPath);
    strcat(buffer, "/");
    strcat(buffer, fileName);
    return IMG_LoadTexture(globalRenderer, buffer);
}

static SDL_Texture* loadTextrueRescaled(char* fileName, int oriPosX, int w, int h)
{
    char buffer[128];
    strcpy(buffer, rootPath);
    strcat(buffer, "/");
    strcat(buffer, fileName);
    SDL_Surface* surface = IMG_Load(buffer);
    SDL_Surface* newSurface;
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = w;
    rect.h = h;
    SDL_BlitScaled(surface, NULL, newSurface, &rect);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(globalRenderer, newSurface);
    SDL_FreeSurface(surface);
    SDL_FreeSurface(newSurface);
    return texture;
}

static SDL_Texture* loadTextrueCut(char* fileName, int oriPosX, int oriPosY, int w, int h)
{
    // TODO
    return NULL;
}

static SDL_Texture* loadTextrueCutRescaled(char* fileName, int oriPosX, int oriPosY, int w, int h)
{
    // TODO
    return NULL;
}

static void addFrame(char* name, char* path)
{
    DrawMeta_t dm = { loadTextrue(path) };
    animationAddFrame(getAnimation(name), dm);
}

extern void initializeCustomAnimation(void)
{

    // load all your animation here
    createAnimation("ani_player_stand_down", 75, false);
    addFrame("ani_player_stand_down", "minami_walk_down_0.png");

    createAnimation("ani_player_stand_up", 75, false);
    addFrame("ani_player_stand_up", "minami_walk_up_0.png");

    createAnimation("ani_player_stand_left", 75, false);
    addFrame("ani_player_stand_left", "minami_walk_left_0.png");

    createAnimation("ani_player_stand_right", 75, false);
    addFrame("ani_player_stand_right", "minami_walk_right_0.png");

    createAnimation("ani_player_walk_down", 75, true);
    addFrame("ani_player_walk_down", "minami_walk_down_0.png");
    addFrame("ani_player_walk_down", "minami_walk_down_1.png");
    addFrame("ani_player_walk_down", "minami_walk_down_2.png");
    addFrame("ani_player_walk_down", "minami_walk_down_3.png");

    createAnimation("ani_player_walk_up", 75, true);
    addFrame("ani_player_walk_up", "minami_walk_up_0.png");
    addFrame("ani_player_walk_up", "minami_walk_up_1.png");
    addFrame("ani_player_walk_up", "minami_walk_up_2.png");
    addFrame("ani_player_walk_up", "minami_walk_up_3.png");

    createAnimation("ani_player_walk_left", 75, true);
    addFrame("ani_player_walk_left", "minami_walk_left_0.png");
    addFrame("ani_player_walk_left", "minami_walk_left_1.png");
    addFrame("ani_player_walk_left", "minami_walk_left_2.png");
    addFrame("ani_player_walk_left", "minami_walk_left_3.png");

    createAnimation("ani_player_walk_right", 75, true);
    addFrame("ani_player_walk_right", "minami_walk_right_0.png");
    addFrame("ani_player_walk_right", "minami_walk_right_1.png");
    addFrame("ani_player_walk_right", "minami_walk_right_2.png");
    addFrame("ani_player_walk_right", "minami_walk_right_3.png");

    createAnimation("ani_monster_stand", 500, false);
    addFrame("ani_monster_stand", "a.png");
    addFrame("ani_monster_stand", "unknow.png");
}