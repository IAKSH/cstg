#include "custom_go_monster.h"
#include "custom_gameobjects.h"
#include "gameobject.h"
#include "gameplay.h"
#include "gomanager.h"

#include <string.h>

static void onCreate(GameObject_t* go);
static void onTick(GameObject_t* go);
static void onDestroy(GameObject_t* go);

GameObject_t monster;

void monster_init()
{
    monster.typeId    = 2;
    monster.x         = 200;
    monster.y         = 300;
    monster.z         = 1;
    monster.h         = 50;
    monster.w         = 50;
    monster.speedX    = 0;
    monster.speedY    = 0;
    monster.hp        = 50;
    monster.mp        = 10;
    monster.state     = 1;
    monster.name      = "monster";
    monster.onCreate  = onCreate;
    monster.onTick    = onTick;
    monster.onDestroy = onDestroy;
    SDL_Surface* sur  = custom_loadImage("a.png");
    monster.texture   = SDL_CreateTextureFromSurface(globalRenderer, sur);
    SDL_FreeSurface(sur);
}

static void onCreate(GameObject_t* go)
{
    go->id = allocateGameObjectId();
    SDL_Log("monster created!");
}

static void onTick(GameObject_t* go) {}

static void onDestroy(GameObject_t* go) { SDL_Log("monster killed!"); }