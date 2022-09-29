#include "textdisplay.h"
#include "utools.h"
#include <SDL2/SDL_ttf.h>
#include <string.h>

static TTF_Font* font = NULL;

void InitTextDisplay(void)
{
    TTF_Init();
    char buffer[128];
    strcpy(buffer,rootPath);
    strcat(buffer,"/unifont-13.0.01.ttf");
    font = TTF_OpenFont(buffer,20);
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