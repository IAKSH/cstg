#include <SDL2/SDL.h>
#include <bits/pthreadtypes.h>
#include <stdio.h>
#include <gameplay.h>
#include <message.h>
#include <hook.h>
#include <pthread.h>

static void drawEachGameObject();
static void hookDemo(GamePlayMsg* msg);
static void playerHookDemo(GamePlayMsg* msg);
static void doHooks();
static void computing();

typedef struct
{
	int id;
	int x,y,z;
	int speedX;
	int speedY;
	char* name;
	SDL_Texture* texture;
} Player;

static Player p;

#ifdef MULTITHREAD_TEST
void renderThreadProc(void)
{
	// render loop
	while(!gameShouldBeClose)
	{
		// Renderer Run
		drawEachGameObject();
		// Events Run
		gamePlayUpateEvents();
	}
}
#endif

int main(void)
{
	gameplayInit();
	msgsInit();
	// add hooks (demo)
	hooksInit();
	hooksAdd(hookDemo);
	hooksAdd(playerHookDemo);
	hooksAdd(playerHookDemo);// usless but usful ,debug only

#ifdef MULTITHREAD_TEST
	pthread_t renderThread;
	pthread_create(&renderThread,NULL,(void*)renderThreadProc,NULL);
	pthread_detach(renderThread);
#endif

	while (!gameShouldBeClose)
	{
#ifndef MULTITHREAD_TEST
		// Renderer Run
		drawEachGameObject();
		// Events Run
		gamePlayUpateEvents();
#endif
		// Computing Run
		computing();
		// Run Hooks (Test)
		//msgsForeach(hookDemo);
		doHooks();
		// Sync , Remenber: If you turn this delay on , you need to enable inputLocker(control function of bool inputLocked)
		// or you will cause a huge delay on msg processing.
	}

	GamePlayMsg msg1 = 
	{
		.type = KEYBOARD_DOWN,
		.content.keyboardDown.keycode = event.key.keysym.sym
	};
	msgsAdd(&msg1);
	GamePlayMsg msg2 = 
	{
		.type = KEYBOARD_DOWN,
		.content.keyboardDown.keycode = event.key.keysym.sym
	};
	msgsAdd(&msg2);

	doHooks();

	gamePlayDestory();
	return 0;
}

void computing()
{
	p.x += p.speedX;
	p.y += p.speedY;
}

static void playerHookDemo(GamePlayMsg* msg)
{
	if(msg->type == KEYBOARD_DOWN)
	{
		// Humm , SDL doesn't use Cartesian coordinate system?
		// okey... I remenber OpenGL doesn't use it too.
		if(msg->content.keyboardDown.keycode == SDLK_w) p.speedY = -1;
		else if(msg->content.keyboardDown.keycode == SDLK_s) p.speedY = 1;
		else if(msg->content.keyboardDown.keycode == SDLK_a) p.speedX = -1;
		else if(msg->content.keyboardDown.keycode == SDLK_d) p.speedX = 1;
	}
	else if(msg->type == KEYBOARD_UP)
	{
		if(msg->content.keyboardDown.keycode == SDLK_w) p.speedY = 0;
		else if(msg->content.keyboardDown.keycode == SDLK_s) p.speedY = 0;
		else if(msg->content.keyboardDown.keycode == SDLK_a) p.speedX = 0;
		else if(msg->content.keyboardDown.keycode == SDLK_d) p.speedX = 0;
	}
}

void doHooks()
{
	HookNode_t* node =  getHooks()->first;
	if(node == NULL) return;
	else if(node->next == NULL)
	{
		msgsForeach(node->func);
	}
	else
	{
		while(node->next != NULL)
		{
			msgsForeach(node->func);
			node = node->next;
		}
	}
	msgsClean();
}

void hookDemo(GamePlayMsg* msg)
{
	switch (msg->type)
	{
		case KEYBOARD_DOWN:
			{
				if(msg->content.keyboardDown.keycode == SDLK_ESCAPE) gameShouldBeClose = true;
				break;
			}
		
		case COMMAND:
			{
				if(msg->content.commmand.type == QUILT) gameShouldBeClose = true;
				break;
			}
		default:break;
	}
}

void drawEachGameObject()
{
	// test
	static int i = 0;
	static int x;
	if (i++ == 0)
	{
		p.id = 0;
		p.x = 0;
		p.y = 114;
		p.z = 0;
		p.speedX = 0;
		p.speedY = 0;
		p.name = "player";
		SDL_Surface* sur = IMG_Load("/home/zrj/chainList_test/build/a.png");
		p.texture = SDL_CreateTextureFromSurface(renderer, sur);
		SDL_FreeSurface(sur);
	}
	x++;
	gamePlayDrawGameObjects(p.x, p.y, p.z, 100, 100, p.texture);
	if (x == 100) x = 0;
}