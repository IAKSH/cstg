#include "custom_animation_loadder.h"
#include "animation.h"
#include <SDL2/SDL_render.h>
#include <utools.h>
#include <SDL2/SDL_image.h>
#include <gameplay.h>

static SDL_Texture* loadTextrue(char* fileName)
{
    char buffer[128];
    strcpy(buffer, rootPath);
    strcat(buffer, "/");
    strcat(buffer, fileName);
    return IMG_LoadTexture(globalRenderer,buffer);
}

static void addFrame(char* name,char* path)
{
    DrawMeta_t dm = {loadTextrue(path)};
    animationAddFrame(getAnimation(name),dm);
}

extern void initializeCustomAnimation(void)
{
    
    // load all your animation here
    createAnimation("animation_player_stand", 100, true);
    addFrame("animation_player_stand","unknow.png");
    addFrame("animation_player_stand","a.png");

    createAnimation("animation_monster_stand", 10, true);
    addFrame("animation_monster_stand","a.png");
}