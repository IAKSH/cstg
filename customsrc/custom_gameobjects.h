// DO NOT EDIT THIS FILE IF YOU AREN'T THE ENGINE'S DEVELOPER, EXCEPT THOSE MARKED AREA.

// here the engine create all the gameobject examples.
// you need to add your own gameobjects' declaration here and then they will be loaded.

#pragma once
#include "custom_go_player.h"

// Custom GameObjects Begin
extern GameObject_t player;
extern GameObject_t monster;
// Custom GameObjects End

extern void         custom_gameObjectsInit(void);
extern void         custom_loadAudio(char*, char*);
extern SDL_Surface* custom_loadImage(char* fileName);
