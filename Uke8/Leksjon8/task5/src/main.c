#include <stdio.h>
#include <pthread.h>
#include <string.h>
#define RESET "\033[0m"

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
    threadSend1.color = "\e[0;31m";

    THREADSEND threadSend2;
    threadSend2.alphabet = alphabet;
    threadSend2.lengthofArray = lengthOfArray;
    threadSend2.color = "\e[0;32m";

    THREADSEND threadSend3;
    threadSend3.alphabet = alphabet;
    threadSend3.lengthofArray = lengthOfArray;
    threadSend3.color = "\e[0;35m";

    THREADSEND *pThreadSend1 = &threadSend1;
    THREADSEND *pThreadSend2 = &threadSend2;
    THREADSEND *pThreadSend3 = &threadSend3;

    printf("Before function\n");

    pthread_create(&pThread1, NULL, PrintFunction, (void *) pThreadSend1);
    pthread_create(&pThread2, NULL, PrintFunction, (void *) pThreadSend2);
    pthread_create(&pThread3, NULL, PrintFunction, (void *) pThreadSend3);

    printf("After function ");

    pthread_join(pThread1, NULL);
    pthread_join(pThread2, NULL);
    pthread_join(pThread3, NULL);

    printf("%s", RESET);

    printf("After threads are finished\n");

}


void *PrintFunction(void *pThreadStruct) {
    THREADSEND *pThreadsend = (THREADSEND *) pThreadStruct;
    int count = 0;

    for (int i = 1; i < 201; ++i) {
        printf("%s%d%s ", pThreadsend->color, i, RESET);
        if(count == 33){
            printf("\n");
            count = 0;
        }
        count++;
    }
    printf("\n");
}
