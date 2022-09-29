#include <SDL2/SDL.h>
#include <audiomanager.h>
#include <custom_gameobjects.h>
#include <drawsort.h>
#include <gameobject.h>
#include <gameplay.h>
#include <gomanager.h>
#include <hook.h>
#include <message.h>
#include <stdio.h>
#include <textdisplay.h>
#include <utools.h>

static void drawEachGameObject();
static void engineHook(GamePlayMsg* msg);
static void computing();

int main(int argc, char** argv)
{
    initUtools(argc, argv);
    gameplayInit();
    InitTextDisplay();
    audioInit();
    msgsInit();
    hooksInit();
    hooksAdd(engineHook);
    custom_gameObjectsInit();
    drawsInit();

    // test
    //  create an gameobject
    gameObjectsSpawn(&player);
    gameObjectsSpawn(&monster);

    while(!gameShouldBeClose)
    {
        drawEachGameObject();
        gamePlayUpateEvents();
        computing();
        hooksRun();
    }

    audioRelease();
    closeTextDisplay();
    gamePlayDestory();
    return 0;
}

static void _computing(GameObject_t* go) { go->onTick(go); }

static void computing() { gameObjectsForeach(_computing); }

// processing command and engine's events.
static void engineHook(GamePlayMsg* msg)
{
    switch(msg->type)
    {
    case KEYBOARD_DOWN: {
        if(msg->content.keyboardDown.keycode == SDLK_ESCAPE) gameShouldBeClose = true;
        break;
    }

    case COMMAND: {
        if(msg->content.commmand.type == QUILT) gameShouldBeClose = true;
        break;
    }
    default:
        break;
    }
}

static void _func(GameObject_t* go) { gamePlayDrawGameObjects(go); }

static void drawEachGameObject()
{
    // testing
    gameObjectsForeach(_func);
    gameplayFlash();
}