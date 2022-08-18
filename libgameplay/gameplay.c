
#include "gameplay.h"
#include "message.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;
// surface can't support hardware acceleration
//static SDL_Surface* surface;
SDL_Event event;
SDL_Rect fillRect = { 0,0,640,480 };
SDL_Rect gameobjectRect;
bool gameShouldBeClose = false;
bool inputLocked = false;

void gameplayInit()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
	{
		SDL_Log("SDL2 initialize failed.");
		abort();
	}
	IMG_Init(IMG_INIT_PNG);
	window = SDL_CreateWindow("Game Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	// Renderer's Hardware Acceleration enabled , together with VSync
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 640, 480);
}

void gamePlayDestory()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(texture);
	IMG_Quit();
	SDL_Quit();
}

void gamePlayUpateEvents()
{
	if(inputLocked) return;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			{
				GamePlayMsg msg = 
				{
					.type = KEYBOARD_DOWN,
					.content.keyboardDown.keycode = event.key.keysym.sym
				};
				msgsAdd(&msg);
				break;
			}
		case SDL_KEYUP:
			{
				GamePlayMsg msg = 
				{
					.type = KEYBOARD_UP,
					.content.keyboardDown.keycode = event.key.keysym.sym
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
	// TEST
	//SDL_RenderClear(renderer);
	//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	//SDL_Rect rect = { x,y,w,h };
	//SDL_RenderDrawRect(renderer, &rect);
	//SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
	//SDL_SetRenderTarget(renderer, goTexture);
	//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	// draw rect
	//SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	//SDL_SetTextureBlendMode(goTexture, SDL_BLENDMODE_BLEND);
	//SDL_RenderFillRect(renderer, &r);
	//SDL_RenderDrawRect(renderer, &r);
	gameobjectRect.x = x;
	gameobjectRect.y = y;
	gameobjectRect.w = w;
	gameobjectRect.h = h;
	SDL_RenderCopy(renderer, goTexture, NULL, &gameobjectRect);
	SDL_RenderPresent(renderer);
	//SDL_SetRenderTarget(renderer, NULL);
}