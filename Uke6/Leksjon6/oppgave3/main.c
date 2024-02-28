#include <stdio.h>
#include <stdlib.h>
#define ARRAYSIZE 130

void findWordInScramble(FILE *file, const char *compareArray, int *positionArray);

int main() {
    const char fileName[] = "../adventures.txt";
    const char computer[] = "computer";
    char userInput[ARRAYSIZE];
    int computerPositions[8];
    char oneChar;
    char intArray[ARRAYSIZE];
    int i = 0;

    FILE *file;
    file = fopen(fileName, "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        printf("%s\n", line);
    }

    printf("\nhei\n");
    rewind(file);

    findWordInScramble(file, computer, computerPositions);

    printf("\n");
    for (i = 0; i < sizeof(computerPositions) / sizeof(int); ++i) {
        printf("%d\n", computerPositions[i]);
    }
    rewind(file);
    for (i = 0; i < sizeof(computerPositions)/sizeof(int); ++i) {
        fseek(file, computerPositions[i], SEEK_SET);
        char newChar = getc(file);
        printf("%c", newChar);
    }

    fclose(file);

    printf("\nWrite something please\n");

    fgets(userInput, ARRAYSIZE, stdin);
    printf("%s", userInput);

    i = 0;
    while((oneChar = fgetc(stdin)) != '\n' && oneChar != ' ' && oneChar != ',' && oneChar != '.'){
        if((oneChar >  65 && oneChar < 91) || (oneChar > 96 && oneChar < 122)){
            userInput[i] = oneChar;
            i++;
        }
    }

    printf("%s", userInput);

}

void findWordInScramble(FILE *file, const char *compareArray, int *positionArray){
    char oneChar;
    int count = 0;
    int charCount = 0;
    int rightPositionInFile;

    while ((oneChar = getc(file)) != EOF) {
        if (oneChar == compareArray[count] && charCount > 9) {

            rightPositionInFile = ftell(file)-1;
            printf("Position: %d, Char: %c\n", rightPositionInFile, oneChar);
            positionArray[count] = rightPositionInFile;
            count++;
            charCount = 0;
        }
        if (count == 8){
            break;
        }
        charCount++;
    }
}