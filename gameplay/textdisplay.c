#include "textdisplay.h"
#include "gameplay.h"
#include "linklist.h"
#include "utools.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>

LinkListHead_t uiTexts;
LinkListHead_t movingTexts;

static TTF_Font* font = NULL;

void InitTextDisplay(void)
{
    TTF_Init();
    char buffer[128];
    strcpy(buffer, rootPath);
    strcat(buffer, "/unifont-13.0.01.ttf");
    font = TTF_OpenFont(buffer, 20);
    if(!font)
    {
        puts("Failed to load font, SDL_GetError:");
        puts(TTF_GetError());
        abort();
    }

    linkListInitialize(&uiTexts);
    linkListInitialize(&movingTexts);
}

void closeTextDisplay(void)
{
    TTF_CloseFont(font);
    TTF_Quit();
}

static TextObject_t* generateTextObject(char* str, int x, int y, int z, int w, int h, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    SDL_Color color = { r, g, b, a };
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, str, color);

    TextObject_t* text = (TextObject_t*)malloc(sizeof(TextObject_t));
    text->texture = SDL_CreateTextureFromSurface(globalRenderer, surface);
    text->x = x;
    text->y = y;
    text->z = z;
    text->w = w;
    text->h = h;
    SDL_FreeSurface(surface);
    return text;
}

void drawUIText(char* str, int x, int y, int z, int w, int h, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    linkListInsertTail(&uiTexts, generateTextObject(str, x, y, z, w, h, r, g, b, a), sizeof(TextObject_t));
}

void drawMovingText(char* str, int x, int y, int z, int w, int h, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    linkListInsertTail(&movingTexts, generateTextObject(str, x, y, z, w, h, r, g, b, a), sizeof(TextObject_t));
}

void uiTextsForeach(void (*func)(TextObject_t*))
{
    static LinkListNode_t* node;
    node = uiTexts.first;
    while(node != NULL)
    {
        func(node->var);
        node = node->next;
    }
}

void movingTextsForeach(void (*func)(TextObject_t*))
{
    static LinkListNode_t* node;
    node = movingTexts.first;
    while(node != NULL)
    {
        func(node->var);
        node = node->next;
    }
}

static void freeTextureInSingleTextObject(TextObject_t* text)
{
    SDL_DestroyTexture(text->texture);
    text->texture = NULL;
}

void textsClean(void)
{
    uiTextsForeach(freeTextureInSingleTextObject);
    movingTextsForeach(freeTextureInSingleTextObject);
    linkListClean(&uiTexts);
    linkListClean(&movingTexts);
}