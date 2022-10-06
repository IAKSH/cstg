
#include "gameplay.h"
#include "drawsort.h"
#include "message.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

SDL_Window* globalWindow;
SDL_Renderer* globalRenderer;
SDL_Texture* globalTexture;
// surface can't support hardware acceleration
// static SDL_Surface* surface;
SDL_Event globalEvent;
SDL_Rect windowFillRect = { 0, 0, 640, 480 };
bool gameShouldBeClose = false;

struct Camera camera;

static void cameraInit(void)
{
    camera.x = 0;
    camera.y = 0;
    //camera.z = 2;
    //camera.zoom = 1.0f;
}

void gameplayInit(void)
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
    {
        SDL_Log("SDL2 initialize failed.");
        abort();
    }
    IMG_Init(IMG_INIT_PNG);
    globalWindow = SDL_CreateWindow("Game Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    // Renderer's Hardware Acceleration enabled , together with VSync
    globalRenderer = SDL_CreateRenderer(globalWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    globalTexture = SDL_CreateTexture(globalRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 640, 480);
}

void gamePlayDestory(void)
{
    SDL_DestroyWindow(globalWindow);
    SDL_DestroyRenderer(globalRenderer);
    SDL_DestroyTexture(globalTexture);
    IMG_Quit();
    SDL_Quit();
}

void gamePlayUpateEvents(void)
{
    if(SDL_PollEvent(&globalEvent))
    {
        switch(globalEvent.type)
        {
        case SDL_KEYDOWN: {
            GamePlayMsg msg = { .type = KEYBOARD_DOWN, .content.keyboardDown.keycode = globalEvent.key.keysym.sym };
            msgsAdd(&msg);
            break;
        }
        case SDL_KEYUP: {
            GamePlayMsg msg = { .type = KEYBOARD_UP, .content.keyboardDown.keycode = globalEvent.key.keysym.sym };
            msgsAdd(&msg);
            break;
        }

        case SDL_QUIT: {
            GamePlayMsg msg = { .type = COMMAND, .content.commmand.type = QUILT, .content.commmand.args = { "", "", "" } };
            msgsAdd(&msg);
            break;
        }

        default:
            break;
        }
    }
}

// draw every single texture
SDL_Rect gameobjectRect;

static void _func(DrawLinkListNode_t* node)
{
    //if(node->go->z > camera.z) return;
    gameobjectRect.x = node->go->x - camera.x;
    gameobjectRect.y = node->go->y - camera.y;
    gameobjectRect.w = node->go->w;
    gameobjectRect.h = node->go->h;
    SDL_RenderCopy(globalRenderer, node->go->texture, &windowFillRect, &gameobjectRect);
}

static void _func_old(DrawLinkListNode_t* node)
{
    gameobjectRect.x = node->go->x;
    gameobjectRect.y = node->go->y;
    gameobjectRect.w = node->go->w;
    gameobjectRect.h = node->go->h;
    SDL_RenderCopy(globalRenderer, node->go->texture, &windowFillRect, &gameobjectRect);
}

void gamePlayDrawGameObjects(GameObject_t* go) { drawsAdd(go); }

// draw all gameobjects in order (form z=max to z=0)
// this function will do both rendering and sorting
void gameplayFlash(void)
{
    drawsSort();
    drawsForeach(_func);
    SDL_RenderPresent(globalRenderer);
    SDL_RenderClear(globalRenderer);
    drawsClean();
}

void gamePlayDrawFx(SDL_Surface* surface) {}