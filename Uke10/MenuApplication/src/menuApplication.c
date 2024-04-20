#include <stdio.h>
#include <errno.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "menuApplication.h"
#include "linkedList.h"

typedef struct _MOVIE {
    char *title;
    char *director;
    int rating;
} MOVIE;

void printListOptions(char *array[], int sizeOfArray);

int inputWithCharLimit(char *charArray, int lengthOfArray);

int menuHandling(char *array[], char *inputArray, int sizeOfArray);

int addMovie(LIST *list);

int inputFromUser(char *title, int expectedSize);

int menuApplication() {
    char *array[] = {
            "Add an item in the database",
            "Find an item in the database",
            "Find the number of items in the database",
            "Delete an item from the database",
            "Quit"
    };

    int sizeOfArray = sizeof(array) / sizeof(char *);
    char *inputArray = (char *) malloc(sizeof(char));
    LIST list = {NULL, NULL, 0};

    while (1) {

        char result = menuHandling(array, inputArray, sizeOfArray);

        if (result != 0) {

        } else {
            switch (*inputArray) {
                case '1':
                    addMovie(&list);
                    break;
                case '2':
                    printf("2\n");
                    break;
                case '3':
                    printf("3\n");
                    break;
                case '4':
                    printf("4\n");
                    break;
                case '5':
                    printf("5\n");
                    break;
                default:
                    printf("You done fucked up bub\n");
                    break;
            }
        }

    }

    free(inputArray);
    return 0;
}

int addMovie(LIST *list) {
    char title[] = "What is the name of the movie?";
    inputFromUser(&title, 60);
}

int menuHandling(char *array[], char *inputArray, int sizeOfArray) {

    printf("Type the command you want [1-%d]:\n", sizeOfArray);

    printListOptions(array, sizeOfArray);

    int result = inputWithCharLimit(inputArray, 1);
    if (result != 0) {
        printf("Issue with getting stream from user - Error message: %s", strerror(errno));
        return -1;
    }

    return 0;
}

void printListOptions(char *array[], int sizeOfArray) {
    for (int i = 0; i < sizeOfArray; ++i) {
        printf("%d. %s\n", i + 1, array[i]);
    }
}

int inputFromUser(char *title, int expectedSize) {
    char *inputArray = (char *) malloc(sizeof(char) * expectedSize);
    while(1){
        printf("%s\n", title);
        int result = inputWithCharLimit(inputArray, expectedSize);
        if (result != 0){
            printf("Fuck up");
        } else {
            printf("You wrote: %s\nIs that right? y/n", inputArray);
        }
    }
}

int yesOrNo(){
    //inputWithCharLimit()
}

int inputWithCharLimit(char *charArray, int lengthOfArray) {
    if (charArray == NULL) {
        printf("Given array is Null, probably a memory allocation issue\n");
        errno = ENOMEM; // Not enough space/cannot allocate memory
        return errno;
    }

    if (lengthOfArray > 1024) {
        printf("The lengthOfArray is to big, please write a smaller one\n");
        errno = EINVAL; // Invalid Argument
        return errno;
    }

    int i = 0;
    char character;

    while (((character = fgetc(stdin)) != '\n')) {
        if (i < lengthOfArray) {
            charArray[i++] = character;
        }
    }

    charArray[i] = '\0';

    return 0;
}