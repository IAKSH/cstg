#include "custom_player.h"
#include "gameobject.h"
#include <hook.h>
#include <gameplay.h>

static void playerHook_movement(GamePlayMsg* msg);

GameObject player;

void player_init()
{
    player.id = 0;
    player.x = 0;
    player.y = 114;
    player.z = 0;
    player.speedX = 0;
    player.speedY = 0;
    player.name = "player";
    SDL_Surface* sur = IMG_Load("/home/zrj/chainList_test/build/a.png");
    player.texture = SDL_CreateTextureFromSurface(globalRenderer, sur);
    SDL_FreeSurface(sur);
    hooksAdd(playerHook_movement);
}

void player_onCreate()
{

}

void player_onTick()
{
    // processing movement
    player.x += player.speedX;
    player.y += player.speedY;
}

void player_onDestroy()
{

}

static void playerHook_movement(GamePlayMsg* msg)
{
    if(msg->type == KEYBOARD_DOWN)
    {
        // Humm , SDL doesn't use Cartesian coordinate system?
        // okay... I remenber OpenGL doesn't use it too.
        if(msg->content.keyboardDown.keycode == SDLK_w) player.speedY = -1;
        else if(msg->content.keyboardDown.keycode == SDLK_s) player.speedY = 1;
        else if(msg->content.keyboardDown.keycode == SDLK_a) player.speedX = -1;
        else if(msg->content.keyboardDown.keycode == SDLK_d) player.speedX = 1;
    }
    else if(msg->type == KEYBOARD_UP)
    {
        if(msg->content.keyboardDown.keycode == SDLK_w) player.speedY = 0;
        else if(msg->content.keyboardDown.keycode == SDLK_s) player.speedY = 0;
        else if(msg->content.keyboardDown.keycode == SDLK_a) player.speedX = 0;
        else if(msg->content.keyboardDown.keycode == SDLK_d) player.speedX = 0;
    }
}