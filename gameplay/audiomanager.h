#pragma once

extern void audioInit(void);
extern void audioRelease(void);
extern void loadAudio(char*, char*);
extern void playAudio(int, char*, int);
extern void stopAudio(int);
extern void resumeAudio(int);
extern void setChannelVolume(int, int);