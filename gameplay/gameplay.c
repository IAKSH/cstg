
#include "gameplay.h"
#include "message.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

SDL_Window* globalWindow;
SDL_Renderer* globalRenderer;
SDL_Texture* globalTexture;
// surface can't support hardware acceleration
//static SDL_Surface* surface;
SDL_Event globalEvent;
SDL_Rect windowFillRect = { 0,0,640,480 };
SDL_Rect gameobjectRect;
bool gameShouldBeClose = false;

void gameplayInit()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
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

void gamePlayDestory()
{
    SDL_DestroyWindow(globalWindow);
    SDL_DestroyRenderer(globalRenderer);
    SDL_DestroyTexture(globalTexture);
    IMG_Quit();
    SDL_Quit();
}

void gamePlayUpateEvents()
{
    if (SDL_PollEvent(&globalEvent))
    {
        switch (globalEvent.type)
        {
        case SDL_KEYDOWN:
            {
                GamePlayMsg msg = 
                {
                    .type = KEYBOARD_DOWN,
                    .content.keyboardDown.keycode = globalEvent.key.keysym.sym
                };
                msgsAdd(&msg);
                break;
            }
        case SDL_KEYUP:
            {
                GamePlayMsg msg = 
                {
                    .type = KEYBOARD_UP,
                    .content.keyboardDown.keycode = globalEvent.key.keysym.sym
                };
                msgsAdd(&msg);
                break;
            }

        case SDL_QUIT:
            {
                GamePlayMsg msg = 
                {
                    .type = COMMAND,
                    .content.commmand.type = QUILT,
                    .content.commmand.args = {"","",""}
                };
                msgsAdd(&msg);
                break;
            }

        default: break;
        }
    }
}

void gamePlayDrawGameObjects(int x, int y, int z, int w, int h, SDL_Texture* goTexture)
{
    SDL_RenderClear(globalRenderer);
    gameobjectRect.x = x;
    gameobjectRect.y = y;
    gameobjectRect.w = w;
    gameobjectRect.h = h;
    SDL_RenderCopy(globalRenderer, goTexture, NULL, &gameobjectRect);
    SDL_RenderPresent(globalRenderer);
}