#include <stdio.h>
#include <pthread.h>
#include <malloc.h>
#include <semaphore.h>

#define ARRAYSIZE 11

sem_t semaphore;

void *writeToFile();

typedef struct _THREADSEND{
    FILE *file;
    sem_t *sem;
    char *charArray;
} THREADSEND;

int main(){
    pthread_t thread1;
    char *charBuffer = (char *) malloc(ARRAYSIZE*sizeof(char));
    char oneChar;
    int count = 0;
    FILE *file = NULL;
    THREADSEND threadSend;

    sem_init(&semaphore, 0, 0);

    threadSend.charArray = charBuffer;
    threadSend.file = file;
    threadSend.sem = &semaphore;

    THREADSEND *pThreadSend = &threadSend;

    pthread_create(&thread1, NULL, writeToFile, (void *) pThreadSend);

    while ((oneChar = fgetc(stdin)) != '\n'){
        if(count < ARRAYSIZE-1){
            charBuffer[count] = oneChar;
            count++;
        } else {
            charBuffer[count] = '\0';
            sem_post(&semaphore);
        }
    }

    pthread_join(thread1, NULL);
    sem_destroy(&semaphore);
    free(charBuffer);
}

void *writeToFile(void *threadSend){
    THREADSEND *pThreadSend = (THREADSEND *) threadSend;

    FILE *file = pThreadSend->file;
    file = fopen("output.txt", "w");

    if (file == NULL) {
        printf("Error opening file.\n");
        pthread_exit(NULL);
    }

    sem_wait(pThreadSend->sem);

    fclose(file);
}