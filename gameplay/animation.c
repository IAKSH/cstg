#include "animation.h"
#include "hashtable.h"
#include "linklist.h"
#include <string.h>

LinkListHead_t globalAnimations;

static void initializeAnimation(Animation_t* animation, char* name, int intervalTick, bool loop)
{
    animation->intervalTick = intervalTick;
    animation->remainIntervalTick = intervalTick;
    animation->loop = loop;
    strcpy(animation->name, name);
    linkListInitialize(&animation->metas);
}

void initializeAnimator(Animator_t* animator)
{
    initializeHashTable(&animator->animationNameMap, ORDINARY_HASHTABLE_SIZE, sizeof(Animation_t));
    animator->frame = 0;
    animator->currentAnimation = NULL;
}

void animatorLoadAnimation(Animator_t* animator, char* name)
{
    HashKey_t key = { (void*)name, strlen(name) * sizeof(char) };
    void* buffer = hashTableGetValue(&animator->animationNameMap, key);
    if(!buffer)
    {
        fprintf(stderr,"[ERROR] animatorLoadAnimation(): unable to get %s in animationNameMap\n",name);
        abort();
    }
    animator->currentAnimation = buffer;
}

DrawMeta_t getDrawMeta(Animator_t* animator)
{
    if(animator->frame < linkListLength(&animator->currentAnimation->metas))
    {
        DrawMeta_t* buffer = (DrawMeta_t*)linkListGet(&animator->currentAnimation->metas,animator->frame);
        animator->frame++;
        return *buffer;
    }
    else
    {
        if(animator->currentAnimation->loop)
        {
            animator->frame = 0;
            return *(DrawMeta_t*)linkListGet(&animator->currentAnimation->metas,0);
        }
        else
        {
            return *(DrawMeta_t*)linkListGet(&animator->currentAnimation->metas,linkListLength(&animator->currentAnimation->metas - 1));
        }
    }
}


void addAnimationNameMapping(Animator_t* animator, char* name, Animation_t* animation)
{
    HashKey_t key = { name, strlen(name) * sizeof(char) };
    hashTableAdd(&animator->animationNameMap, key, animation,sizeof(Animation_t));
}

void createAnimation(char* name, int intervalTick, bool loop)
{
    Animation_t animation;
    initializeAnimation(&animation, name, intervalTick, loop);
    linkListInsertTail(&globalAnimations, &animation, sizeof(animation));
}

void animationAddFrame(Animation_t* animation, DrawMeta_t drawMeta)
{
    linkListInsertTail(&animation->metas,&drawMeta,sizeof(DrawMeta_t));
}

static char* _name = NULL;
static Animation_t* _animation = NULL;

static void foreachSingleAnimationCheckName(void* animation)
{
    if(strcmp(((Animation_t*)animation)->name, _name) == 0) _animation = animation;
}

Animation_t* getAnimation(char* name)
{
    _name = name;
    linkListForeach(&globalAnimations, foreachSingleAnimationCheckName);
    Animation_t* buffer = _animation;
    _animation = NULL;
    _name = NULL;
    return buffer;
}
