#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
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

static void drawEachGameObject(void);
static void engineHook(GamePlayMsg* msg);
static void computing(void);

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

static void moveCamera(void)
{
    camera.x += camera.speedX;
    camera.y += camera.speedY;
}

static void _computing(GameObject_t* go) { go->onTick(go); }

static void computing()
{
    moveCamera();
    gameObjectsForeach(_computing); 
}

// processing command and engine's events.
static void engineHook(GamePlayMsg* msg)
{
    switch(msg->type)
    {
    case KEYBOARD_DOWN: {
        if(msg->content.keyboardDown.keycode == SDLK_ESCAPE) gameShouldBeClose = true;
        else if(msg->content.keyboardDown.keycode == SDLK_LEFT) camera.speedX = -1;
        else if(msg->content.keyboardDown.keycode == SDLK_RIGHT) camera.speedX = 1;
        else if(msg->content.keyboardDown.keycode == SDLK_UP) camera.speedY = -1;
        else if(msg->content.keyboardDown.keycode == SDLK_DOWN) camera.speedY = 1;
        break;
    }

    case KEYBOARD_UP: {
        if(msg->content.keyboardUp.keycode == SDLK_LEFT) camera.speedX = 0;
        else if(msg->content.keyboardUp.keycode == SDLK_RIGHT) camera.speedX = 0;
        else if(msg->content.keyboardUp.keycode == SDLK_UP) camera.speedY = 0;
        else if(msg->content.keyboardUp.keycode == SDLK_DOWN) camera.speedY = 0;
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

static void drawEachGameObject(void)
{
    // testing
    gameObjectsForeach(_func);
    gameplayFlash();
}