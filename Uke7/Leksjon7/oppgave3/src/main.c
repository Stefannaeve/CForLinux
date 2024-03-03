#include <stdio.h>

typedef struct _LIST {
    struct _LIST *pNext;
    int iSze;
    char cBuf[1];
} LIST;

int main(){
	LIST list1;
    LIST list2;
    list2.iSze = 10;
    list1.pNext = &list2;
    printf("%d\n", list1.pNext->iSze);
}


