#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAYSIZE 130

void findWordInScramble(FILE *file, const char *compareArray, int *positionArray);
void makeScrambleForUserInput(char *userInput, char *scrambledUserInput, int *positionInArray, int lengthOfArray);

int main() {
    const char fileName[] = "../adventures.txt";
    const char computer[] = "computer";
    char userInput[ARRAYSIZE];
    int positionInArray[ARRAYSIZE];
    char *scrambledUserInput;
    scrambledUserInput = (char *) malloc(ARRAYSIZE*10*sizeof(char));
    int computerPositions[8];
    char oneChar;
    char intArray[ARRAYSIZE];
    int i = 0;

    srand(time(NULL));

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

    i = 0;
    while((oneChar = fgetc(stdin)) != '\n' && oneChar != ' ' && oneChar != ',' && oneChar != '.'){
        if((oneChar >  65 && oneChar < 91) || (oneChar > 96 && oneChar < 122)){
            userInput[i] = oneChar;
            i++;
        }
    }

    makeScrambleForUserInput(userInput, scrambledUserInput, positionInArray, i);

    printf("%s\n", userInput);

    for (int j = 0; j < i; ++j) {
        printf("%d ", positionInArray[j]);
    }
    printf("\n");
    for (int j = 0; j < i; ++j) {
        printf("%c  ", scrambledUserInput[positionInArray[j]]);
    }

}

void makeScrambleForUserInput(char *userInput, char *scrambledUserInput, int *positionInArray, int lengthOfArray){
    int count = 0;
    for (int i = 0; i < lengthOfArray; ++i) {
        int randomCount = 10 + rand() % (18 - 10 + 1);
        int randomNumber;
        int countConst = count;
        for (count = count; count < countConst + randomCount; count++) {
            randomNumber = 97 + rand() % (122 - 97 + 1);
            scrambledUserInput[count] = (char) randomNumber;
        }
        scrambledUserInput[count] = userInput[i];
        positionInArray[i] = count;
        count++;
    }
    scrambledUserInput[count] = '\0';
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