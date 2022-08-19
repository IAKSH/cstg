#include <SDL2/SDL.h>
#include <bits/pthreadtypes.h>
#include <stdio.h>
#include <gameplay.h>
#include <message.h>
#include <hook.h>
#include <gameobject.h>
#include <custom_gameobjects.h>

static void drawEachGameObject();
static void engineHook(GamePlayMsg* msg);
static void computing();

int main(void)
{
    gameplayInit();
    msgsInit();
    hooksInit();
    hooksAdd(engineHook);
    custom_gameObjectsInit();

    while (!gameShouldBeClose)
    {
        drawEachGameObject();
        gamePlayUpateEvents();
        computing();
        hooksRun();
    }

    gamePlayDestory();
    return 0;
}

static void computing()
{
    // test only
    custom_gameObjectsOnTick();
}

// processing command and engine's events.
static void engineHook(GamePlayMsg* msg)
{
    switch (msg->type)
    {
        case KEYBOARD_DOWN:
            {
                if(msg->content.keyboardDown.keycode == SDLK_ESCAPE) gameShouldBeClose = true;
                break;
            }
        
        case COMMAND:
            {
                if(msg->content.commmand.type == QUILT) gameShouldBeClose = true;
                break;
            }
        default:break;
    }
}

static void drawEachGameObject()
{
    // Test Only Code
    gamePlayDrawGameObjects(player.x, player.y, player.z, 100, 100, player.texture);
}