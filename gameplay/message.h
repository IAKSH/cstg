#pragma once
#include <SDL2/SDL_keycode.h>

enum GAMEPLAY_MSG_TYPE {
    KEYBOARD_UP,
    KEYBOARD_DOWN,
    MOUSE_WHELL_UP,
    MOUSE_WHELL_DOWN,
    MOUSE_CLICK_LEFT_DOWN,
    MOUSE_CLICK_LEFT_UP,
    MOUSE_CLICK_RIGHT_DOWN,
    MOUSE_CLICK_RIGHT_UP,
    COMMAND,
    GAMEOBJECT_CREATE,
    GAMEOBJECT_DESTROYED,
    GAMEOBJECT_ANNOUNCEMENT
};

struct _GamePlayKBUp {
    SDL_KeyCode keycode;
};

struct _GamePlayKBDown {
    SDL_KeyCode keycode;
};

// struct _MouseWellUp{};
// struct _MouseWellDown{};
// struct _MouseClickLeftDown{};
// struct _MouseClickLeftUp{};
// struct _MouseClickRightDown {};
// struct _MouseClickRightUp {};

enum COMMAND_TYPE { HELP, QUILT };

struct _Command {
    int   type;
    char* args[4];
};

struct _GameObjectCreate {
    // the game object's id
    int id;
};

struct _GameObjectDestroy {
    // the game object's id
    int id;
};

struct _GameObjectAnnouncement {
    // the game object's id
    int id;
    // custom code
    int code;
};

union _Content {
    struct _GamePlayKBUp   keyboardUp;
    struct _GamePlayKBDown keyboardDown;
    // struct _MouseWellUp mouseWellUp;
    // struct _MouseWellDown mouseWellDown;
    // struct _MouseClickLeftDown mouseClickLeftDown;
    // struct _MouseClickLeftUp mouseClickLeftUp;
    // struct _MouseClickRightDown mouseClickRightDown;
    // struct _MouseClickRightUp mouseClickRightUp;
    struct _Command                commmand;
    struct _GameObjectCreate       gameobjectCreate;
    struct _GameObjectDestroy      gameobjectDestroy;
    struct _GameObjectAnnouncement gameobjectAnnouncement;
};

typedef struct {
    int            type;
    union _Content content;
} GamePlayMsg;

extern void msgsInit(void);
extern void msgsAdd(GamePlayMsg* msg);
extern void msgsForeach(void (*func)(GamePlayMsg*));
extern void msgsClean(void);