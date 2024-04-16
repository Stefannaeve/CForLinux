#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct _NODE {
    struct _NODE *pNext;
    int iSze;
    char szBuffer[];
} NODE;

typedef struct _LIST{
    NODE *pHead;
    NODE *pTail;
    int size;
} LIST;

void addToEnd(LIST *list, const char *szValue);
void addToBeginning(LIST *list, const char *szBuffer);
void addToSpecificPosition(LIST list, const char *szValue, int index);
void freeLinkedList(LIST *list);
void printAllNodes(NODE *head);

int main(){
    int value;

    NODE *head;
	NODE *node0;
    NODE *node1;
    NODE *node2;
    NODE *node3;
    NODE *tail;

    node0 = (NODE *) malloc(sizeof(NODE));
    node1 = (NODE *) malloc(sizeof(NODE));
    node2 = (NODE *) malloc(sizeof(NODE));
    node3 = (NODE *) malloc(sizeof(NODE));

    node0->iSze = 0;
    node1->iSze = 1;
    node2->iSze = 2;
    node3->iSze = 3;

    node0->pNext = node1;
    node1->pNext = node2;
    node2->pNext = node3;
    node3->pNext = NULL;

    head = node0;
    tail = node3;


    node1->iSze = 10;
    node0->pNext = node1;
    printf("%d\n", node0->pNext->iSze);

    value = 4;
    addToEnd(head);

    freeLinkedList(head);
}

void addToEnd(LIST *list, const char *szValue){
    NODE *temp;
    int iLength = strlen(szValue);
    temp = (NODE *) malloc(sizeof(NODE) + iLength);
    temp->iSze = iLength;
    strncpy(temp->szBuffer, szValue, iLength);
    temp->szBuffer[iLength - 1] = '\0';
    temp->pNext = NULL;
    list->pHead->pNext = temp;
    list->pTail = temp;
    list->size++;
}


void addToBeginning(LIST *list, const char *szBuffer){
    int iLength = strlen(szBuffer);
    NODE *temp;
    temp = (NODE *) malloc(sizeof(NODE) + iLength);
    temp->iSze = iLength;
    temp->szBuffer[iLength] = '\0';
    temp->pNext = list->pHead;
    list->pHead = temp;
    list->size++;
}

void addToSpecificPosition(LIST list, const char *szValue, int index){
    NODE *temp;
    NODE *current;
    int iLength = strlen(szValue);
    int counter = 0;
    temp = (NODE *) malloc(sizeof(NODE) + iLength);
    temp->iSze = iLength;
    strncpy(temp->szBuffer, szValue, iLength);
    temp->szBuffer[iLength - 1] = '\0';
    current = list.pHead;
    while (current->pNext != NULL && counter < index) {
        current = current->pNext;
        counter++;
    }
    temp->pNext = current->pNext;
    current->pNext = temp;
    list.size++;
}

void freeLinkedList(LIST *list){
    NODE *current = list->pHead;
    NODE *next;
    while (current != NULL) {
        next = current->pNext;
        current->pNext = NULL;
        free(current);
        current = next;
    }
}

void printAllNodes(LIST *list){
    NODE *current = list->pHead;
    while (current != NULL) {
        printf("%s\n", current->szBuffer);
        current = current->pNext;
    }
}


