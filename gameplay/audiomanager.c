#include "audiomanager.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_mixer.h>
#include <stdlib.h>

// Maybe Hashtable will be a better choice?
// I will swap this Link List into Hashtable in the future.
// together with the Link List in gomanager.c

typedef struct AudioNode {
    char              name[16];
    Mix_Chunk*        chunk;
    struct AudioNode* next;
} AudioNode_t;

AudioNode_t head;

void audioInit(void)
{
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 8, 2048);
    strcpy(head.name, "[NOT_AUDIO]");
    head.chunk = NULL;
    head.next  = NULL;
}

void audioRelease(void)
{
    Mix_CloseAudio();
    // TODO: free all audio file
    // humm,maybe I can just leave this work to OS?
}

void loadAudio(char* name, char* path)
{
    if(head.next == NULL)
    {
        head.next       = (AudioNode_t*)malloc(sizeof(AudioNode_t));
        head.next->next = NULL;
        loadAudio(name, path);
    }
    else
    {
        AudioNode_t* node = &head;
        while(node->next != NULL) node = node->next;
        if(!(node->chunk = Mix_LoadWAV(path)))
        {
            printf("Failed to load sound file \"%s\",MIX ERROR:%s\n", name, Mix_GetError());
            abort();
        }
        strcpy(node->name, name);
    }
}

Mix_Chunk* getSound(char* name)
{
    AudioNode_t* node = &head;
    while(node->next != NULL)
    {
        // too bad,I need hashtable!
        node = node->next;
        if(strcmp(node->name, name) == 0) return node->chunk;
    }
    return NULL;
}

void playAudio(int channelID, char* name, int time)
{
    Mix_Chunk* buffer;
    if(!(buffer = getSound(name)))
    {
        printf("Failed to index sound \"%s\",MIX ERROR:%s\n", name, Mix_GetError());
        abort();
    }
    Mix_PlayChannel(channelID, buffer, time);
}

void stopAudio(int channelID) { Mix_HaltChannel(channelID); }

// dosen't work
void resumeAudio(int channelID) { Mix_Resume(channelID); }

void setChannelVolume(int channelID, int volume) { Mix_Volume(channelID, volume); }