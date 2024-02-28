#include <stdio.h>

int main() {
    char *fileName = "../test.txt";
    char savedChar;
    char lastChar;
    char tempChar;
    int check = 0;
    int from = 3;
    int until = 7;
    int vowelCount = 0;
    int letterPair = 0;
    int seperatedLetterPairs = 0;
    int currentPosition = 0;
    int currentPositionForPrint = 0;
    int character;

    int ftelling = 0;

    FILE *file;
    file = fopen(fileName, "r");

    if (file == NULL) {
        printf("Could not find file");
        return 1;
    }

    while ((character = fgetc(file)) != EOF) {
        if (character == 'a' || character == 'e' || character == 'i' || character == 'o' || character == 'u') {
            if (check == 1) {
                check = 0;
                vowelCount++;
                printf("a pair of vowels: %c%c\n", savedChar, character);
            } else {
                check = 1;
                savedChar = character;
            }
        } else {
            check = 0;
        }

        if (lastChar == character) {
            printf("Hitler didnt even have those! pairs: %c%c\n", lastChar, character);
            letterPair++;
        }

//        TODO change magic numbers to char values
        if((character >  65 && character < 91) || (character > 96 && character < 122)){
            lastChar = (char) character;

            currentPosition = ftell(file);
            fseek(file, from-1, SEEK_CUR);
            for (int i = 0; i < until-from+1; ++i) {
                ftelling = ftell(file);

                tempChar = fgetc(file);
                if(tempChar == character){
                    currentPositionForPrint = ftell(file);
                    printf("%ld\n", ftell(file));
                    printf("The char %c(%d), and the char %c(%d) is twins\n", character, currentPosition, tempChar, currentPositionForPrint);
                    seperatedLetterPairs++;
                }
            }
            fseek(file, currentPosition, SEEK_SET);
        }
    }
    printf("Vowel pairs: %d\n", vowelCount);
    printf("Letter pairs: %d\n", letterPair);
    printf("Seperated letter pairs: %d\n", seperatedLetterPairs);
}