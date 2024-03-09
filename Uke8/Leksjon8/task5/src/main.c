#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void *PrintFunction(void *pThreadStruct);

typedef struct _THREADSEND {
    char *alphabet;
    int lengthofArray;
    char *color;
} THREADSEND;

int main(int argc, char *argv[]) {
    pthread_t pThread1, pThread2, pThread3;

    char *alphabet = "abcdefghijklmnop\0";

    int lengthOfArray = strlen(alphabet);

    THREADSEND threadSend1;
    threadSend1.alphabet = alphabet;
    threadSend1.lengthofArray = lengthOfArray;
    threadSend1.color = "\033[0;34m";

    THREADSEND threadSend2;
    threadSend2.alphabet = alphabet;
    threadSend2.lengthofArray = lengthOfArray;
    threadSend2.color = "\033[0;36m";

    THREADSEND *pThreadSend1 = &threadSend1;
    THREADSEND *pThreadSend2 = &threadSend2;

    printf("Before function\n");

    pthread_create(&pThread1, NULL, PrintFunction, (void *) pThreadSend1);
    pthread_create(&pThread2, NULL, PrintFunction, (void *) pThreadSend2);

    printf("After function\n");

    pthread_join(pThread1, NULL);
    pthread_join(pThread2, NULL);

    printf("After threads are finished\n");

}


void *PrintFunction(void *pThreadStruct) {
    THREADSEND *pThreadsend = (THREADSEND *) pThreadStruct;
    int count = 0;

    printf("%s", pThreadsend->color);

    for (int i = 0; i < 1000; ++i) {
        printf("%d ", i);
        if(count == 100){
            printf("\n");
            count = 0;
        }
        count++;
    }
    printf("\n");
}
