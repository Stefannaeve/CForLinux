#include <stdio.h>

typedef struct _LIST {
    struct _LIST *pNext;
    int iSze;
    char cBuf[1];
} LIST;

int main(){
	printf("Hello World\n");
	return 0;
}


