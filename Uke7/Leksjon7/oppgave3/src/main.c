#include <stdio.h>
#include <malloc.h>
#include <string.h>

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

void addToEnd(LIST *list, NODE *temp);

void addToIndex(LIST *list, NODE *temp, int index);

void freeLinkedList(LIST *list);

void printAllNodes(LIST *list);

void printAllNodesBackwards(LIST *list);

int printSpecificNode(LIST *list, int index);

int deleteSpecificNode(LIST *list, int index);

int main() {
    LIST list = {NULL, NULL, 0};
    int status;

    add(&list, "1");
    add(&list, "2");
    add(&list, "3");
    add(&list, "4");
    add(&list, "5");
    add(&list, "6");
    add(&list, "7");
    add(&list, "8");
    add(&list, "9");

    printAllNodes(&list);
    printf("Size of list: %d\n", list.size);

    addAt(&list, "00", 9, START);

    printAllNodes(&list);

    addAt(&list, "01", 0, START);

    addAt(&list, "50", 5, START);

    printAllNodes(&list);
    printAllNodesBackwards(&list);
    printSpecificNode(&list, 5);

    deleteSpecificNode(&list, 0);
    deleteSpecificNode(&list, 0);
    deleteSpecificNode(&list, 0);
    deleteSpecificNode(&list, 0);

    printAllNodes(&list);

    deleteSpecificNode(&list, 7);
    deleteSpecificNode(&list, 6);
    deleteSpecificNode(&list, 5);
    deleteSpecificNode(&list, 4);

    printAllNodes(&list);

    freeLinkedList(&list);
}

int add(LIST *list, const char *szValue){
    int status = addAt(list, szValue, 0, END);
    if(status != 0){
        return 1;
    }
    return 0;
}

int addAt(LIST *list, const char *szValue, int indexOffset, int position) {
    if (szValue == NULL) {
        printf("Invalid input\n");
        return 1;
    }

    NODE *temp;
    int iLength = strlen(szValue);

    temp = (NODE *) malloc(sizeof(NODE) + iLength + 1);
    if (temp == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    if (indexOffset < 0) {
        printf("Error: Index cannot be negative!\n");
        return 1;
    }

    if (indexOffset > list->size+1) {
        printf("Error: Index out of range!\n");
        return 1;
    }

    temp->iSze = iLength;
    strncpy(temp->szBuffer, szValue, iLength);
    temp->szBuffer[iLength] = '\0';
    temp->pNext = NULL;
    temp->pPrev = NULL;

    if (list->pHead == NULL) {
        list->pHead = temp;
        list->pTail = temp;
        return 0;
    }

    switch (position) {
        case 0:
            addToIndex(list, temp, indexOffset);
            break;
        case 1:
            addToEnd(list, temp);
            break;
        default:
            printf("Invalid position");
            free(temp);
            return 1;
    }
    return 0;
}

void addToEnd(LIST *list, NODE *temp) {
    list->pTail->pNext = temp;
    temp->pPrev = list->pTail;
    list->pTail = temp;

    list->size++;
}

void addToIndex(LIST *list, NODE *temp, int index) {

    NODE *current;
    int counter = 0;

    if(index == list->size+1){
        addToEnd(list, temp);
        printf("Added node to end of linked list. Method \"add\" can be used for this purpose instead..\n");
        return;
    }
    if (index == 0) {
        temp->pNext = list->pHead;
        list->pHead->pPrev = temp;
        list->pHead = temp;
    } else {
        current = list->pHead;
        while (current->pNext != NULL && counter < index - 1) {
            current = current->pNext;
            counter++;
        }
        temp->pNext = current->pNext;
        temp->pPrev = current;
        if (current->pNext != NULL) {
            current->pNext->pPrev = temp;
        }
        current->pNext = temp;
    }
    list->size++;
}

void freeLinkedList(LIST *list) {
    NODE *current = list->pHead;
    NODE *next;
    while (current != NULL) {
        next = current->pNext;
        current->pNext = NULL;
        free(current);
        current = next;
    }
}

void printAllNodes(LIST *list) {
    NODE *current = list->pHead;
    while (current != NULL) {
        printf("%s, ", current->szBuffer);
        current = current->pNext;
    }
    printf("\n");
}

void printAllNodesBackwards(LIST *list) {
    NODE *current = list->pTail;
    while (current != NULL) {
        printf("%s, ", current->szBuffer);
        current = current->pPrev;
    }
    printf("\n");
}

int printSpecificNode(LIST *list, int index) {
    if (index < 0) {
        printf("Error: Index cannot be negative!\n");
        return 1;
    }

    NODE *current = list->pHead;
    int counter = 0;
    while (current != NULL && counter < index) {
        current = current->pNext;
        counter++;
    }
    if (current == NULL) {
        printf("Index out of range!\n");
        return 1;
    }
    printf("%s\n", current->szBuffer);
    return 0;
}

int deleteSpecificNode(LIST *list, int index) {
    if (index < 0) {
        printf("Error: Index cannot be negative!\n");
        return 1;
    }

    if (index > list->size) {
        printf("Error: Index out of range!\n");
        return 1;
    }

    NODE *current = list->pHead;
    int counter = 0;

    while (current != NULL && counter < index) {
        current = current->pNext;
        counter++;
    }

    if (current == NULL) {
        printf("Error: Index out of range!\n");
        return 1;
    }
    if (current->pPrev == NULL) {
        list->pHead = current->pNext;
    } else {
        current->pPrev->pNext = current->pNext;
    }

    if (current->pNext == NULL) {
        list->pTail = current->pPrev;
    } else {
        current->pNext->pPrev = current->pPrev;
    }

    free(current);
    list->size--;

    return 0;
}


