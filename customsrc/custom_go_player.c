#include "custom_go_player.h"
#include "custom_gameobjects.h"
#include "gameobject.h"
#include "gomanager.h"
#include "message.h"
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_timer.h>
#include <audiomanager.h>
#include <gameplay.h>
#include <hook.h>
#include <stdio.h>
#include <string.h>
#include <utools.h>

static void hook_movement(GamePlayMsg*);
static void hook_testSound(GamePlayMsg*);

static void onCreate(GameObject_t*);
static void onTick(GameObject_t*);
static void onDestroy(GameObject_t*);

GameObject_t player;

void player_init()
{
    player.typeId    = 1;
    player.x         = 0;
    player.y         = 0;
    player.z         = 0;
    player.w         = 100;
    player.h         = 100;
    player.speedX    = 0;
    player.speedY    = 0;
    player.hp        = 1;
    player.mp        = 100;
    player.state     = 1;
    player.name      = "player";
    player.onCreate  = onCreate;
    player.onTick    = onTick;
    player.onDestroy = onDestroy;

    // preload images
    // TODO:...
    SDL_Surface* sur = custom_loadImage("a.png");  // temp code

    // add preloaded images to this game object
    player.texture = SDL_CreateTextureFromSurface(globalRenderer, sur);
    SDL_FreeSurface(sur);

    // preload music
    custom_loadAudio("sound_01", "th08_01.mp3");

    // add hook , if you have
    hooksAdd(hook_movement);
    hooksAdd(hook_testSound);
}

static void onCreate(GameObject_t* self)
{
    self->id = allocateGameObjectId();
    SDL_Log("player created!");
}

static void _func1(GameObject_t* go)
{
    GameObject_t* _player = gameObjectsGetByTypeId(1);
    if(go->typeId == 2)
    {
        if(squareCollisionCheck(_player->x, _player->y, _player->w, _player->h, go->x, go->y, go->w, go->h)) { _player->hp -= 100; }
    }
}

static void onTick(GameObject_t* self)
{
    // processing movement
    self->x += self->speedX;
    self->y += self->speedY;

    // check if player hit any monster
    gameObjectsForeach(_func1);

    // check if player dead
    if(self->hp <= 0)
    {
        puts("You dead.");
        gameShouldBeClose = true;
    }

    // DEBUG
    // printf("x:%d\ty:%d\n",self->x,self->y);
    // fflush(stdout);
}

static void onDestroy(GameObject_t* self) { SDL_Log("player killed!"); }

static void hook_movement(GamePlayMsg* msg)
{
    GameObject_t* go = gameObjectsGetByTypeId(1);
    if(msg->type == KEYBOARD_DOWN)
    {
        // Humm , SDL doesn't use Cartesian coordinate system?
        // okay... I remenber OpenGL doesn't use it too.
        if(msg->content.keyboardDown.keycode == SDLK_w)
            go->speedY = -1;
        else if(msg->content.keyboardDown.keycode == SDLK_s)
            go->speedY = 1;
        else if(msg->content.keyboardDown.keycode == SDLK_a)
            go->speedX = -1;
        else if(msg->content.keyboardDown.keycode == SDLK_d)
            go->speedX = 1;
    }
    else if(msg->type == KEYBOARD_UP)
    {
        if(msg->content.keyboardDown.keycode == SDLK_w)
            go->speedY = 0;
        else if(msg->content.keyboardDown.keycode == SDLK_s)
            go->speedY = 0;
        else if(msg->content.keyboardDown.keycode == SDLK_a)
            go->speedX = 0;
        else if(msg->content.keyboardDown.keycode == SDLK_d)
            go->speedX = 0;
    }
}

static void hook_testSound(GamePlayMsg* msg)
{
    if(msg->type == KEYBOARD_DOWN)
    {
        if(msg->content.keyboardDown.keycode == SDLK_z) playAudio(-1, "sound_01", 0);
        if(msg->content.keyboardDown.keycode == SDLK_x) stopAudio(-1);
        if(msg->content.keyboardDown.keycode == SDLK_c) resumeAudio(-1);
        if(msg->content.keyboardDown.keycode == SDLK_v) setChannelVolume(-1, 50);
        if(msg->content.keyboardDown.keycode == SDLK_b) setChannelVolume(-1, 100);
    }
}