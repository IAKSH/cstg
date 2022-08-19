#include "custom_gameobjects.h"

// include your gameobjects' head file here
#include "custom_go_player.h"
#include "custom_go_monster.h"

void custom_gameObjectsInit(void)
{
    // you need to call all your gameobjects' init func here.
    player_init();
    monster_init();
}