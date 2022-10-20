
#include "gameplay.h"
#include "animation.h"
#include "drawsort.h"
#include "message.h"
#include "textdisplay.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#define SCREEN_SIZE_W 1024
#define SCREEN_SIZE_H 720

SDL_Window* globalWindow;
SDL_Renderer* globalRenderer;
SDL_Texture* globalTexture;
// surface can't support hardware acceleration
// static SDL_Surface* surface;
SDL_Event globalEvent;
SDL_Rect windowFillRect = { 0, 0, SCREEN_SIZE_W, SCREEN_SIZE_H };
bool gameShouldBeClose = false;

struct Camera camera;

static void cameraInit(void)
{
    camera.x = 0;
    camera.y = 0;
    camera.z = 50;
    // camera.zoom = 1.0f;
}

void gameplayInit(void)
{
    cameraInit();
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
    {
        SDL_Log("SDL2 initialize failed.");
        abort();
    }
    IMG_Init(IMG_INIT_PNG);
    globalWindow = SDL_CreateWindow("Game Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_SIZE_W, SCREEN_SIZE_H, SDL_WINDOW_SHOWN);
    // Renderer's Hardware Acceleration enabled , together with VSync
    globalRenderer = SDL_CreateRenderer(globalWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    globalTexture = SDL_CreateTexture(globalRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_SIZE_W, SCREEN_SIZE_H);
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

static void drawSingleGameObject(DrawLinkListNode_t* node)
{
    // camera will stay on the left up corner of the window
    if(node->go->z > camera.z) return;
    gameobjectRect.x = node->go->x - camera.x;
    gameobjectRect.y = node->go->y - camera.y;
    gameobjectRect.w = node->go->w;
    gameobjectRect.h = node->go->h;
    SDL_RenderCopy(globalRenderer, getDrawMeta(&node->go->animator).texture, &windowFillRect, &gameobjectRect);
}

static void drawSingleUITextObject(TextObject_t* text)
{
    if(text->z > camera.z) return;
    gameobjectRect.x = text->x;
    gameobjectRect.y = text->y;
    gameobjectRect.w = text->w;
    gameobjectRect.h = text->h;
    SDL_RenderCopy(globalRenderer, text->texture, &windowFillRect, &gameobjectRect);
}

static void drawSingleMovingTextObject(TextObject_t* text)
{
    if(text->z > camera.z) return;
    gameobjectRect.x = text->x - camera.x;
    gameobjectRect.y = text->y - camera.y;
    gameobjectRect.w = text->w;
    gameobjectRect.h = text->h;
    SDL_RenderCopy(globalRenderer, text->texture, &windowFillRect, &gameobjectRect);
}

void gamePlayDrawGameObjects(GameObject_t* go) { drawsAdd(go); }

// draw all gameobjects in order (form z=max to z=0)
// this function will do both rendering and sorting
void gameplayFlash(void)
{
    drawsSort();
    drawsForeach(drawSingleGameObject);
    uiTextsForeach(drawSingleUITextObject);
    movingTextsForeach(drawSingleMovingTextObject);
    SDL_RenderPresent(globalRenderer);
    SDL_RenderClear(globalRenderer);
    drawsClean();
    textsClean();
}

void gamePlayDrawFx(SDL_Surface* surface) {}