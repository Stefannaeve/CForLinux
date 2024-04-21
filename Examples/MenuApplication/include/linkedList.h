//
// Created by Stefan on 17/04/2024.
//

#ifndef __TASK_DATABASE_H__
#define __TASK_DATABASE_H__

#define START 0
#define END 1

typedef struct _NODE {
    struct _NODE *pNext;
    struct _NODE *pPrev;
    int iSze;
    char szBuffer[];
} NODE;

typedef struct _LIST {
    NODE *pHead;
    NODE *pTail;
    int size;
} LIST;

int add(LIST *list, const char *szValue);

int addAt(LIST *list, const char *szValue, int indexOffset, int position);

void freeLinkedList(LIST *list);

void printAllNodes(LIST *list);

void printAllNodesBackwards(LIST *list);

int printSpecificNode(LIST *list, int index);

int deleteSpecificNode(LIST *list, int index);

#endif //__TASK_DATABASE_H__
