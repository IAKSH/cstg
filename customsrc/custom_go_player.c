#include "custom_go_player.h"
#include "animation.h"
#include "custom_gameobject_loadder.h"
#include "gameobject.h"
#include "gomanager.h"
#include "message.h"
#include "textdisplay.h"
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_timer.h>
#include <audiomanager.h>
#include <gameplay.h>
#include <hook.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <path.h>

static void hook_movement(GamePlayMsg*);
static void hook_testSound(GamePlayMsg*);

static void onCreate(GameObject_t*);
static void onTick(GameObject_t*);
static void onDestroy(GameObject_t*);

GameObject_t player;

void player_init()
{
    player.typeId = 1;
    player.x = 0;
    player.y = 0;
    player.z = 0;
    player.w = 50;
    player.h = 75;
    player.speedX = 0;
    player.speedY = 0;
    player.hp = 1;
    player.mp = 100;
    player.state = 1;
    player.name = "player";
    player.onCreate = onCreate;
    player.onTick = onTick;
    player.onDestroy = onDestroy;
    initializeAnimator(&player.animator);
    addAnimationNameMapping(&player.animator, "stand_down", getAnimation("ani_player_stand_down"));
    addAnimationNameMapping(&player.animator, "stand_up_dont_collide", getAnimation("ani_player_stand_up"));
    addAnimationNameMapping(&player.animator, "stand_left", getAnimation("ani_player_stand_left"));
    addAnimationNameMapping(&player.animator, "stand_right", getAnimation("ani_player_stand_right"));
    addAnimationNameMapping(&player.animator, "walk_down", getAnimation("ani_player_walk_down"));
    addAnimationNameMapping(&player.animator, "walk_up_dont_collide", getAnimation("ani_player_walk_up"));
    addAnimationNameMapping(&player.animator, "walk_left", getAnimation("ani_player_walk_left"));
    addAnimationNameMapping(&player.animator, "walk_right", getAnimation("ani_player_walk_right"));
    animatorLoadAnimation(&player.animator, "stand_down");

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

    // DEBUG: Draw text
    drawMovingText("I have made a game using ISO C!", 500, 500, 0, 800, 25, 128, 0, 128, 128);
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
        {
            if(go->speedY != -1) animatorLoadAnimation(&go->animator, "walk_up_dont_collide");
            go->speedY = -1;
        }
        else if(msg->content.keyboardDown.keycode == SDLK_s)
        {
            if(go->speedY != 1) animatorLoadAnimation(&go->animator, "walk_down");
            go->speedY = 1;
        }
        else if(msg->content.keyboardDown.keycode == SDLK_a)
        {
            if(go->speedX != -1) animatorLoadAnimation(&go->animator, "walk_left");
            go->speedX = -1;
        }
        else if(msg->content.keyboardDown.keycode == SDLK_d)
        {
            if(go->speedX != 1) animatorLoadAnimation(&go->animator, "walk_right");
            go->speedX = 1;
        }
    }
    else if(msg->type == KEYBOARD_UP)
    {
        if(msg->content.keyboardDown.keycode == SDLK_w)
        {
            go->speedY = 0;
            animatorLoadAnimation(&go->animator, "stand_up_dont_collide");
        }
        else if(msg->content.keyboardDown.keycode == SDLK_s)
        {
            go->speedY = 0;
            animatorLoadAnimation(&go->animator, "stand_down");
        }
        else if(msg->content.keyboardDown.keycode == SDLK_a)
        {
            go->speedX = 0;
            animatorLoadAnimation(&go->animator, "stand_left");
        }
        else if(msg->content.keyboardDown.keycode == SDLK_d)
        {
            go->speedX = 0;
            animatorLoadAnimation(&go->animator, "stand_right");
        }
    }
}

static void hook_testSound(GamePlayMsg* msg)
{
    if(msg->type == KEYBOARD_DOWN)
    {
        if(msg->content.keyboardDown.keycode == SDLK_z)
            playAudio(-1, "sound_01", 0);
        else if(msg->content.keyboardDown.keycode == SDLK_x)
            stopAudio(-1);
        else if(msg->content.keyboardDown.keycode == SDLK_c)
            resumeAudio(-1);
        else if(msg->content.keyboardDown.keycode == SDLK_v)
            setChannelVolume(-1, 50);
        else if(msg->content.keyboardDown.keycode == SDLK_b)
            setChannelVolume(-1, 100);
    }
}