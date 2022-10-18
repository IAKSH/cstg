#pragma once
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <inttypes.h>
#include <stdint.h>
#include <sys/types.h>

typedef struct {
    int x, y, z, w, h;
    SDL_Texture* texture;
} TextObject_t;

extern void InitTextDisplay(void);
extern void closeTextDisplay(void);
extern void drawUIText(char*, int, int, int, int, int, uint8_t, uint8_t, uint8_t, uint8_t);
extern void drawMovingText(char*, int, int, int, int, int, uint8_t, uint8_t, uint8_t, uint8_t);
extern void uiTextsForeach(void (*)(TextObject_t*));
extern void movingTextsForeach(void (*)(TextObject_t*));
extern void textsClean(void);