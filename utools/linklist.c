#include "linklist.h"
#include <stdio.h>
#include <string.h>

static void linklistAppenAtHead(LinkListHead_t* head, void* val, size_t size)
{
    LinkListNode_t* newNode = (LinkListNode_t*)malloc(sizeof(LinkListNode_t));
    newNode->forward = NULL;
    newNode->next = NULL;
    newNode->var = malloc(size);
    memcpy(newNode->var, val, size);
    head->first = newNode;
}

static LinkListNode_t* iterateLinkListNodeTo(LinkListNode_t* node, int index)
{
    for(int i = 0; i < index; i++)
    {
        if(node->next)
            node = node->next;
        else
        {
            fprintf(stderr, "linkListRemove() failed: out of range\n");
            abort();
        };
    }
    return node;
}

void linkListInitialize(LinkListHead_t* head) { head->first = NULL; }

// this function will copy val in heap
void linkListInsertTail(LinkListHead_t* head, void* val, size_t size)
{
    if(head->first)
    {
        LinkListNode_t* node = head->first;
        while(node->next) node = node->next;
        LinkListNode_t* newNode = (LinkListNode_t*)malloc(sizeof(LinkListHead_t));
        newNode->forward = node;
        newNode->next = NULL;
        newNode->var = malloc(size);
        memcpy(newNode->var, val, size);
        node->next = newNode;
    }
    else
        linklistAppenAtHead(head, val, size);
}

// this function will copy val in heap
void linkListInsertFront(LinkListHead_t* head, void* val, size_t size)
{
    if(head->first)
    {
        LinkListNode_t* node = head->first;
        LinkListNode_t* newNode = (LinkListNode_t*)malloc(sizeof(LinkListHead_t));
        newNode->forward = NULL;
        newNode->next = node;
        newNode->var = malloc(size);
        memcpy(newNode->var, val, size);
        head->first = newNode;
        node->forward = newNode;
    }
    else
        linklistAppenAtHead(head, val, size);
}

void linkListPopTail(LinkListHead_t* head)
{
    if(head->first)
    {
        LinkListNode_t* node = head->first;
        while(node->next) node = node->next;
        free(node->var);
        node = node->forward;
        free(node->next);
        node->next = NULL;
    }
}

void linkListPopHead(LinkListHead_t* head)
{
    if(head->first)
    {
        LinkListNode_t* secondNode = head->first->next;
        if(secondNode)
        {
            free(head->first->var);
            free(head->first);
            head->first = secondNode;
            secondNode->forward = NULL;
        }
        else
        {
            free(head->first->var);
            free(head->first);
            head->first = NULL;
        }
    }
}

void linkListRemove(LinkListHead_t* head, int index)
{
    if(index == 0)
        linkListPopHead(head);
    else
    {
        if(head->first)
        {
            LinkListNode_t* node = head->first;
            node = iterateLinkListNodeTo(node, index);
            LinkListNode_t* nextNode = node->next;
            if(nextNode)
            {
                nextNode->forward = node->forward;
                free(node->var);
                node = node->forward;
                free(node->next);
                node->next = nextNode;
            }
            else
            {
                free(node->var);
                node = node->forward;
                free(node->next);
                node->next = NULL;
            }
        }
    }
}

void* linkListGet(LinkListHead_t* head, int index)
{
    if(head->first)
    {
        LinkListNode_t* node = head->first;
        node = iterateLinkListNodeTo(node, index);
        return node->var;
    }
    else
        return NULL;
}

int linkListLength(LinkListHead_t* head)
{
    if(!head->first) return 0;
    LinkListNode_t* node = head->first;
    int i = 0;
    for(; 1; i++)
        if(!node->next) break;
    return i;
}

void linkListClean(LinkListHead_t* head)
{
    LinkListNode_t* node = head->first;
    if(node)
    {
        while(node->next)
        {
            node = node->next;
            free(node->forward->var);
            free(node->forward);
        }
        free(node->var);
        free(node);
        head->first = NULL;
    }
}