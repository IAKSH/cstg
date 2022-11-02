#include "custom_audio_loadder.h"
#include <string.h>
#include <audiomanager.h>
#include <path.h>

static void custom_loadAudio(char* name, char* path)
{
    char buffer[128];
    strcpy(buffer, rootPath);
    strcat(buffer, "/");
    strcat(buffer, path);
    loadAudio("sound_01", buffer);
}

void initializeCustomAudio(void)
{
    // load all your audio here
    custom_loadAudio("sound_01", "th08_01.mp3");
}