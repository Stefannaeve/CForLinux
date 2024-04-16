#include <stdio.h>
#include <errno.h>
#include <malloc.h>
#include <string.h>
#include "menuApplication.h"

void printListOptions(char *array[], int sizeOfArray);
int inputWithCharLimit(char* charArray, int lengthOfArray);
void menuHandling(char *array[]);

int menuApplication(){
    char *array[] = {
            "Add an item in the database",
            "Find an item in the database",
            "Find the number of items in the database",
            "Delete an item from the database"
    };

    menuHandling(array);
    return 0;
}

void menuHandling(char *array[]){
    int sizeOfArray = sizeof(array)/sizeof(char *);

    printf("Type the command you want [1-%d]:\n", sizeOfArray);

    printListOptions(array, sizeOfArray);

    char *inputArray = (char*) malloc(sizeof(char));

    int result = inputWithCharLimit(inputArray, 1);
    if (result != 0){
        printf("Issue with getting stream from user - Error message: %s", strerror(errno));
        exit(result);
    }
}

void printListOptions(char *array[], int sizeOfArray){
    for (int i = 0; i < sizeOfArray; ++i) {
        printf("%d. %s\n", i+1, array[i]);
    }
}

int inputWithCharLimit(char* charArray, int lengthOfArray){
    if(charArray == NULL){
        printf("Given array is Null, probably a memory allocation issue\n");
        errno = ENOMEM; // Not enough space/cannot allocate memory
        return errno;
    }

    if(lengthOfArray > 99){
        printf("The lengthOfArray is to big, please write a smaller one\n");
        errno = EINVAL; // Invalid Argument
        return errno;
    }

    int i = 0;
    char character;

    while(((character = fgetc(stdin)) != '\n')){
        if(i < lengthOfArray){
            charArray[i++] = character;
        }
    }

    charArray[i] = '\0';

    return 0;
}