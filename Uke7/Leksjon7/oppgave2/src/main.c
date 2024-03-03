#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/printing.h"
#include "../include/snBubblesort.h"

#define ARRAYSIZE 10

int main(){
    int count = 0;

    int *array = (int *) malloc(ARRAYSIZE*sizeof(int));
    char *charArray = (char *) malloc(ARRAYSIZE*sizeof(char));

    if (array == NULL || charArray == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    strncpy(charArray, "Hei der", ARRAYSIZE);

    printf("%s\n", charArray);

    for (int i = ARRAYSIZE; i > 0; --i) {
        array[count] = i;
        count++;
    }

    for (int i = 0; i < ARRAYSIZE; ++i) {
        printf("%d, ", array[i]);
    }

    printing(charArray);
    bubbleSort(ARRAYSIZE, array);

    for (int i = 0; i < ARRAYSIZE; ++i) {
        printf("%d, ", array[i]);
    }
    printf("\n");

    free(array);
    free(charArray);
}
