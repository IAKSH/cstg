#include "custom_go_tpsdisplayer.h"
#include "gameobject.h"
#include "textdisplay.h"
#include <time.h>

GameObject_t tpsdisplayer;

static void onCreate(GameObject_t*);
static void onTick(GameObject_t*);
static void onDestroy(GameObject_t*);

float last = 0.0f;

void tpsdisplayer_init(void)
{
    tpsdisplayer.typeId = 3;
    tpsdisplayer.x = 0;
    tpsdisplayer.y = 0;
    tpsdisplayer.z = 0;
    tpsdisplayer.w = 50;
    tpsdisplayer.h = 50;
    tpsdisplayer.speedX = 0;
    tpsdisplayer.speedY = 0;
    tpsdisplayer.hp = 1;
    tpsdisplayer.mp = 100;
    tpsdisplayer.state = 1;
    tpsdisplayer.name = "tpsdisplayer";
    tpsdisplayer.onCreate = onCreate;
    tpsdisplayer.onTick = onTick;
    tpsdisplayer.onDestroy = onDestroy;
    initializeAnimator(&tpsdisplayer.animator);
}

static void onCreate(GameObject_t* go) {}

static void onTick(GameObject_t* go)
{
    while((1.0f / ((clock() - last) / CLOCKS_PER_SEC)) > 120) {}
    float now = clock();
    char p[32];
    sprintf(p, "TPS: %g", (1.0f / ((now - last) / CLOCKS_PER_SEC)));
    drawUIText(p, 10, 10, 0, 250, 25, 0, 255, 0, 255);
    last = now;
}

static void onDestroy(GameObject_t* go) {}