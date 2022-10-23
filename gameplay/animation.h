#pragma once
#include "hashtable.h"
#include <SDL2/SDL_render.h>
#include <linklist.h>
#include <stdbool.h>

typedef struct {
    SDL_Texture* texture;
} DrawMeta_t;

typedef struct {
    float intervalMs;
    float lastDraw;
    bool loop;
    char name[128];
    LinkListHead_t metas;
} Animation_t;

typedef struct {
    HashTable_t animationNameMap;  // mapping name (str) to Animation_t
    Animation_t* currentAnimation;
    int frame;
} Animator_t;

extern LinkListHead_t globalAnimations;

extern DrawMeta_t getDrawMeta(Animator_t*);
extern Animation_t* getAnimation(char*);
extern void initializeAnimator(Animator_t*);
extern void addAnimationNameMapping(Animator_t*, char*, Animation_t*);
extern void createAnimation(char*,int,bool);
extern void animationAddFrame(Animation_t*, DrawMeta_t);
extern void animatorLoadAnimation(Animator_t*, char*);