#include "message.h"
#include <linklist.h>
#include <stdlib.h>
#include <string.h>

// invisibel from outside
static GamePlayMsg globalMsg;

void msgsInit(void) { };

void msgsAdd(GamePlayMsg* msg) { memcpy(&globalMsg,msg, sizeof(GamePlayMsg)); }

void msgsForeach(void (*func)(GamePlayMsg*))
{
    func(&globalMsg);
}

void msgsClean(void) { }