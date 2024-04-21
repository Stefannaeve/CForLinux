#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 4096
#define NUM_THREADS 2
#define BYTE_RANGE 256

typedef struct _THREAD_A {
    pthread_mutex_t *mutex;
    int *bytes_in_buffer;
    pthread_cond_t *cond_full, *cond_empty;
    unsigned char *buffer;
} THREAD_A;

typedef struct _THREAD_B {
    pthread_mutex_t *mutex;
    int *bytes_in_buffer;
    pthread_cond_t *cond_full, *cond_empty;
    unsigned char *buffer;
    int *count;
} THREAD_B;


void *thread_A(THREAD_A *structA) {
    FILE *fp = fopen("../eksamen_v23_oppgave4_pg2265.txt", "rb");
    if (!fp) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    while (1) {
        pthread_mutex_lock(structA->mutex);
        while (*structA->bytes_in_buffer != BUFFER_SIZE)
            pthread_cond_wait(structA->cond_empty, structA->mutex);

        //Stopped here
        int read_bytes = fread(buffer + *bytes_in_buffer, 1, BUFFER_SIZE - *bytes_in_buffer, fp);
        *bytes_in_buffer += read_bytes;

        if (read_bytes < BUFFER_SIZE - *bytes_in_buffer) {
            pthread_mutex_unlock(mutex);
            break;
        }
        pthread_cond_signal(&cond_full);
        pthread_mutex_unlock(mutex);
    }
    fclose(fp);
    pthread_exit(NULL);
}

void *thread_B(THREAD_B *structB) {
    memset(count, 0, sizeof(count));

    while (1) {
        pthread_mutex_lock(mutex);
        while (*bytes_in_buffer == 0)
            pthread_cond_wait(&cond_full, mutex);

        for (int i = 0; i < *bytes_in_buffer; i++)
            count[buffer[i]]++;

        *bytes_in_buffer = 0;
        pthread_cond_signal(&cond_empty);
        pthread_mutex_unlock(mutex);

        if (*bytes_in_buffer == 0)
            break;
    }
    for (int i = 0; i < BYTE_RANGE; i++)
        printf("%d: %d\n", i, count[i]);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t threadA, threadB;

    pthread_mutex_t mutex;
    int bytes_in_buffer = 0;
    pthread_cond_t cond_full, cond_empty;
    unsigned char *buffer = (unsigned char *)malloc(BUFFER_SIZE);
    int *count = (int *)malloc(BUFFER_SIZE);

    THREAD_A *structA = (THREAD_A *) malloc(sizeof(THREAD_A) + BUFFER_SIZE);
    structA->mutex = &mutex;
    structA->bytes_in_buffer = &bytes_in_buffer;
    structA->cond_full = &cond_full;
    structA->cond_empty = &cond_empty;
    structA->buffer = buffer;

    THREAD_B *structB = (THREAD_B *) malloc(sizeof(THREAD_A) + BUFFER_SIZE + BYTE_RANGE);
    structB->mutex = &mutex;
    structB->bytes_in_buffer = &bytes_in_buffer;
    structB->cond_full = &cond_full;
    structB->cond_empty = &cond_empty;
    structB->buffer = buffer;
    structB->count = count;



    if (pthread_create(&threadA, NULL, thread_A(&mutex, &bytes_in_buffer), (void *) structA) != 0) {
        perror("Could not create thread A");
        exit(1);
    }

    if (pthread_create(&threadB, NULL, thread_B(&mutex, &bytes_in_buffer), (void *) structB) != 0) {
        perror("Could not create thread B");
        exit(1);
    }

    if (pthread_join(threadA, NULL) != 0) {
        perror("Could not join thread A");
        exit(1);
    }
    if (pthread_join(threadB, NULL) != 0) {
        perror("Could not join thread B");
        exit(1);
    }


    free(buffer);
    free(count);
    return 0;
}










