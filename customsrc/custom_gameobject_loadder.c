// DO NOT EDIT THIS FILE IF YOU AREN'T THE ENGINE'S DEVELOPER, EXCEPT THOSE MARKED AREA.

#include "custom_gameobject_loadder.h"
#include <SDL2/SDL_image.h>

#include <audiomanager.h>
#include <utools.h>

// include your gameobjects' head file here
#include "custom_go_monster.h"
#include "custom_go_player.h"

void initializeCustomGameObject(void)
{
    // you need to call all your gameobjects' init func here.
    player_init();
    monster_init();
}
