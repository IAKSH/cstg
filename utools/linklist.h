#pragma once

typedef struct LinkListNode {
    void* var;
    struct LinkListNode* next;
    struct LinkListNode* forward;
} LinkListNode_t;

typedef struct LinkListHead {
    LinkListNode_t* first;
} LinkListHead_t;

extern void linkListInitialize(LinkListHead_t*);
extern void linkListInsertTail(LinkListHead_t*, void*);
extern void linkListInsertFront(LinkListHead_t*, void*);
extern void linkListPopTail(LinkListHead_t*);
extern void linkListPopHead(LinkListHead_t*);
extern void linkListRemove(LinkListHead_t*, int);
extern void linkListClean(LinkListHead_t*);
extern void* linkListGet(LinkListHead_t*, int);
extern int linkListLength(LinkListHead_t*);