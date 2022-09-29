#include "textdisplay.h"
#include <SDL2/SDL_ttf.h>

static TTF_Font* font = NULL;

void InitTextDisplay(void)
{
    TTF_Init();
    font = TTF_OpenFont("unifont-13.0.01.ttf",20);
    if(!font)
    {
        puts("Failed to load font, SDL_GetError:");
        puts(TTF_GetError());
        abort();
    }
}

void closeTextDisplay(void)
{
    TTF_CloseFont(font);
    TTF_Quit();
}