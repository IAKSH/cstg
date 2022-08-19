#pragma once
#include "message.h"

extern void hooksInit(void);
extern void hooksAdd(void(*func)(GamePlayMsg*));
extern void hooksRun(void);