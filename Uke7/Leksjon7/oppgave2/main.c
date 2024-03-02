#include <stdio.h>
#include <stdlib.h>
#include "stestdlib.h"

#define ARRAYSIZE 10

int main(){
    int count = 0;

    int *array = (int *) malloc(ARRAYSIZE*sizeof(int));
    if (array == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    for (int i = ARRAYSIZE; i > 0; ++i) {
        array[count] = i;
        count++;
    }

    for (int i = 0; i < ARRAYSIZE; ++i) {
        printf("%d, ", array[i]);
    }

    bubbleSort(ARRAYSIZE, array);

    for (int i = 0; i < ARRAYSIZE; ++i) {
        printf("%d, ", array[i]);
    }

    free(array);
}
