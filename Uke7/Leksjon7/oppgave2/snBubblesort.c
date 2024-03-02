#include "stestdlib.h"

int sort(int *pA, int *pB){
    int j = *pA;
    *pA = *pB;
    *pB = j;
}

int bubbleSort(int length, int *array){

    int hasPassed;
    for(int pass = 0; pass < length - 1; pass++){
        hasPassed = 0;
        for(int i = 0; i < length - pass - 1; i++){
            if(array[i] > array[i + 1]){
                sort(&array[i], &array[i + 1]);
                hasPassed = 1;
            }
        }
        if(hasPassed == 0){
            break;
        }
    }
    return 0;
}