#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void *PrintFunction(void *pThreadStruct);

typedef struct _THREADSEND {
    char *alphabet;
    int lengthofArray;
} THREADSEND;

int main(int argc, char *argv[]) {
    pthread_t pThread1, pThread2, pThread3;

    char *alphabet = "abcdefghijklmnop\0";

    int lengthOfArray = strlen(alphabet);

    printf("\\033[0;31m"); //Set the text to the color red
    printf("Hello\n"); //Display Hello in red
    printf("\\033[0m"); //Resets the text to default color


    THREADSEND threadSend;
    threadSend.alphabet = alphabet;
    threadSend.lengthofArray = lengthOfArray;

    THREADSEND *pThreadSend = &threadSend;

    printf("Before function\n");

    pthread_create(&pThread1, NULL, PrintFunction, (void *) pThreadSend);
    pthread_create(&pThread2, NULL, PrintFunction, (void *) pThreadSend);
    pthread_create(&pThread3, NULL, PrintFunction, (void *) pThreadSend);

    printf("After function\n");

    pthread_join(pThread1, NULL);
    pthread_join(pThread2, NULL);
    pthread_join(pThread3, NULL);

    printf("After threads are finished\n");

}


void *PrintFunction(void *pThreadStruct) {
    THREADSEND *pThreadsend = (THREADSEND *) pThreadStruct;
    int count = 0;

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
