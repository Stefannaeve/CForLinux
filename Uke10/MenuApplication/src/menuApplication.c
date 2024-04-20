#include <stdio.h>
#include <errno.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "menuApplication.h"
#include "linkedList.h"

#define ERROR -1
#define FALSE 0
#define TRUE 1
#define QUIT 2
#define ARRAYSIZE 100

typedef struct _MOVIE {
    char *title;
    char *director;
    int rating;
} MOVIE;

void printListOptions(char *array[], int sizeOfArray);

int inputWithCharLimit(char *charArray, int lengthOfArray);

int menuHandling(char *array[], char *inputArray, int sizeOfArray);

int addMovie(LIST *list);

int askUserQuestion(char *title, char *inputArray, int expectedSize);

int yesOrNo();

int menuApplication() {
    char *array[] = {
            "Add an item in the database",
            "Find an item in the database",
            "Find the number of items in the database",
            "Delete an item from the database",
            "Quit"
    };

    int sizeOfArray = sizeof(array) / sizeof(char *);
    char *inputArray = (char *) malloc(sizeof(char) * 2);
    LIST list = {NULL, NULL, 0};

    while(TRUE) {

        char result = menuHandling(array, inputArray, sizeOfArray);

        if (result != TRUE) {

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
    char inputArray[ARRAYSIZE];
    askUserQuestion(title, inputArray, ARRAYSIZE);
}

int menuHandling(char *array[], char *inputArray, int sizeOfArray) {

    printf("Type the command you want [1-%d]:\n", sizeOfArray);

    printListOptions(array, sizeOfArray);

    int result = inputWithCharLimit(inputArray, 1);
    if (result != TRUE) {
        printf("Issue with getting stream from user - Error message: %s", strerror(errno));
        return ERROR;
    }

    return TRUE;
}

void printListOptions(char *array[], int sizeOfArray) {
    for (int i = 0; i < sizeOfArray; ++i) {
        printf("%d. %s\n", i + 1, array[i]);
    }
}

int askUserQuestion(char *title, char *inputArray, int expectedSize) {
    while (1) {
        printf("%s\n", title);
        int result = inputWithCharLimit(inputArray, expectedSize);
        if (result != TRUE) {
            printf("Error message: %s\nTry again", strerror(errno));
            return ERROR;
        } else {
            printf("You wrote: %s\nIs that right? y/n or q for quit\n", inputArray);
            int status = yesOrNo();
            if (status != TRUE){
                if (status == QUIT){
                    return QUIT;
                }
                printf("Try again\n");
            } else {
                return TRUE;
            }
        }
    }
}

int yesOrNo() {
    char character[2];
    while (1) {
        inputWithCharLimit(&character, 2);
        switch (character[0]) {
            case 'y':
                return TRUE;
            case 'n':
                return FALSE;
            case 'q':
                printf("Are you sure you want to quit? y/n\n");
                inputWithCharLimit(&character, 2);
                if(character[0] == 'y'){
                    return QUIT;
                } else {
                    return FALSE;
                }
            default:
                printf("Wrong input, it has to be \"y\" or \"n\"");
                break;
        }
    }
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

    return TRUE;
}