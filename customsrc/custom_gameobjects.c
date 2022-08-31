#include "custom_gameobjects.h"
#include <SDL2/SDL_image.h>
#include <utools.h>

SDL_Surface* custom_loadImage(const char* fileName)
{
    char buffer[128];
    strcpy(buffer,rootPath);
    strcat(buffer,"/a.png");
    return IMG_Load(buffer);
}

// include your gameobjects' head file here
#include "custom_go_player.h"
#include "custom_go_monster.h"

void custom_gameObjectsInit(void)
{
    // you need to call all your gameobjects' init func here.
    player_init();
    monster_init();
}