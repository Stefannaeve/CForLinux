#include <stdio.h>
#include <pthread.h>
#include <malloc.h>
#include <semaphore.h>
#include <string.h>

#define ARRAYSIZE 11
#define QUITARRAY 7

void *writeToFile();

typedef struct _THREADSEND {
    FILE *file;
    sem_t *bufferFull;
    sem_t *bufferCleared;
    char *charArray;
    int *exit;
} THREADSEND;

int main() {
    pthread_t thread1;
    char *charBuffer = (char *) malloc(ARRAYSIZE * sizeof(char));
    char *quitMessage = (char *) malloc(QUITARRAY * sizeof(char));
    char oneChar;
    int count = 0;
    FILE *file = NULL;
    THREADSEND threadSend;
    int *exit = (int *) malloc(sizeof(int));
    *exit = 0;
    sem_t bufferFull;
    sem_t bufferCleared;

    for (int i = 0; i < QUITARRAY - 1; ++i) {
        quitMessage[i] = (char) (i + 97);
    }
    quitMessage[QUITARRAY - 1] = '\0';

    sem_init(&bufferFull, 0, 0);
    sem_init(&bufferCleared, 0, 0);

    threadSend.charArray = charBuffer;
    threadSend.file = file;
    threadSend.bufferFull = &bufferFull;
    threadSend.bufferCleared = &bufferCleared;
    threadSend.exit = exit;

    THREADSEND *pThreadSend = &threadSend;

    pthread_create(&thread1, NULL, writeToFile, (void *) pThreadSend);

    printf("Start recording in file: Please write things you wish to record to the file.. Write quit on a newline to quit\n");

    while ((oneChar = fgetc(stdin)) != EOF) {

        if (count < ARRAYSIZE - 1) {
            charBuffer[count++] = oneChar;
            charBuffer[count] = '\0';
            for (int i = 0; i < QUITARRAY - 2; ++i) {
                quitMessage[i] = quitMessage[i + 1];
            }
            quitMessage[5] = oneChar;
        }

        if (count == ARRAYSIZE - 1) {
            sem_post(&bufferFull);
            sem_wait(&bufferCleared);
            count = 0;
        }

        if ((strcmp(quitMessage, "\nquit\n")) == 0) {
            *exit = 1;
            sem_post(pThreadSend->bufferFull);
            break;
        }


    }

    printf("Finished recording in file\n");

    pthread_join(thread1, NULL);
    sem_destroy(&bufferFull);
    sem_destroy(&bufferCleared);
    free(charBuffer);
    free(quitMessage);
    free(exit);
}

void *writeToFile(void *threadSend) {
    THREADSEND *pThreadSend = (THREADSEND *) threadSend;

    pThreadSend->file = fopen("output.txt", "w");

    if (pThreadSend->file == NULL) {
        printf("Error opening file.\n");
        pthread_exit(NULL);
    }

    sem_wait(pThreadSend->bufferFull); // Wait for main to give the go ahead

    while (*pThreadSend->exit == 0) {
        fputs(pThreadSend->charArray, pThreadSend->file);
        fflush(pThreadSend->file);
        memset(pThreadSend->charArray, 0, ARRAYSIZE * sizeof(char));
        sem_post(pThreadSend->bufferCleared);
        sem_wait(pThreadSend->bufferFull); // Changed position from beginning of while, to make the exit strategy with the int exit work properly
    }

    fclose(pThreadSend->file);
}