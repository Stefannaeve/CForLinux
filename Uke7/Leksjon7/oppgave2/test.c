#include <stdio.h>
#include <stdlib.h>

#define ARRAYSIZE 5

void newThing(int **array1, int **array2);

int main() {

    int *array;
    int count = 0;
    int *pCount = &count;
    array = (int *) malloc(sizeof(int));

    int *array2 = (int *) malloc(ARRAYSIZE*sizeof(int));
    int *array3 = (int *) malloc(ARRAYSIZE*sizeof(int));

    for (int i = 1; i < ARRAYSIZE+1; ++i) {
        array2[i-1] = i;
    }
    for (int i = ARRAYSIZE; i > 0; --i) {
        array3[count] = i;
        count++;
    }



    *array = 1;
    printf("%hx, ", array);
    printf("%d, ", *array);
    printf("%hx, ", &array);
    printf("%hx, ", &count);
    printf("%hx, ", pCount);

    printf("\n");

    for (int i = 0; i < ARRAYSIZE; ++i) {
        printf("%d", array2[i]);
    }
    printf("\n");
    for (int i = 0; i < ARRAYSIZE; ++i) {
        printf("%d", array3[i]);
    }
    printf("\n");


    newThing(&array2, &array3);

    printf("%hx\n", array2);
    printf("%hx\n", array3);

    for (int i = 0; i < ARRAYSIZE; ++i) {
        printf("%d", array2[i]);
    }
    printf("\n");
    for (int i = 0; i < ARRAYSIZE; ++i) {
        printf("%d", array3[i]);
    }
    printf("\n");

    return 0;
}

void newThing(int **array1, int **array2){
    printf("Inside function\n");

    printf("\n");
    *array1 = *array2;

    printf("\nFunction done\n");

}