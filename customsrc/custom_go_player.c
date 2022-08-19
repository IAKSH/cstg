#include "custom_go_player.h"
#include "gameobject.h"
#include "gomanager.h"
#include <hook.h>
#include <gameplay.h>

static void hook_movement(GamePlayMsg* msg);
static void onCreate(GameObject_t* go);
static void onTick(GameObject_t* go);
static void onDestroy(GameObject_t* go);

GameObject_t player;

void player_init()
{
    player.id = 0;
    player.x = 0;
    player.y = 114;
    player.z = 0;
    player.w = 100;
    player.h = 100;
    player.speedX = 0;
    player.speedY = 0;
    player.name = "player";
    player.onCreate = onCreate;
    player.onTick = onTick;
    player.onDestroy = onDestroy;
    SDL_Surface* sur = IMG_Load("/home/zrj/chainList_test/build/a.png");
    player.texture = SDL_CreateTextureFromSurface(globalRenderer, sur);
    SDL_FreeSurface(sur);
    // add hook , if you have
    hooksAdd(hook_movement);
}

static void onCreate(GameObject_t* go)
{
    SDL_Log("player created!");
}

static void onTick(GameObject_t* go)
{
    // processing movement
    go->x += go->speedX;
    go->y += go->speedY;
}

static void onDestroy(GameObject_t* go)
{
    SDL_Log("player killed!");
}

static void hook_movement(GamePlayMsg* msg)
{
    GameObject_t* go = gameObjectsGetById(0);
    if(msg->type == KEYBOARD_DOWN)
    {
        // Humm , SDL doesn't use Cartesian coordinate system?
        // okay... I remenber OpenGL doesn't use it too.
        if(msg->content.keyboardDown.keycode == SDLK_w) go->speedY = -1;
        else if(msg->content.keyboardDown.keycode == SDLK_s) go->speedY = 1;
        else if(msg->content.keyboardDown.keycode == SDLK_a) go->speedX = -1;
        else if(msg->content.keyboardDown.keycode == SDLK_d) go->speedX = 1;
    }
    else if(msg->type == KEYBOARD_UP)
    {
        if(msg->content.keyboardDown.keycode == SDLK_w) go->speedY = 0;
        else if(msg->content.keyboardDown.keycode == SDLK_s) go->speedY = 0;
        else if(msg->content.keyboardDown.keycode == SDLK_a) go->speedX = 0;
        else if(msg->content.keyboardDown.keycode == SDLK_d) go->speedX = 0;
    }
}