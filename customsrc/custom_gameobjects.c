#include "custom_gameobjects.h"
#include "custom_player.h"


void custom_gameObjectsInit(void)
{
    // you need to call all your gameobjects' init func here.
    player_init();
}


// test only
void custom_gameObjectsOnTick(void)
{
    player.onTick();
}