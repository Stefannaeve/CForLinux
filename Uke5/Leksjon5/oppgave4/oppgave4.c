#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define ALENGTH 3
#define TRUE 1
#define FALSE 0

typedef struct {
	char array[3][3];
    int value;
    int dead;
} BOT;

typedef struct {
    int size;
	BOT BOTArray[];
} BOTLIST;

typedef struct {
    int health;
    char healthBar[3][42];
} HEALTHBAR;

typedef enum{
    success,
    memoryError,
    indexOutOfBoundError
} STATUSCODE;

void printBots(BOTLIST *botList);
BOT makeRandomBot();
void makeHealthBar(HEALTHBAR* healthbar);
void printHealthBar(HEALTHBAR* healthbar);
void looseHealth(HEALTHBAR * healthbar, int amount);
void updateHealthGUI(HEALTHBAR* healthbar);
void killBot(BOT *bot);
STATUSCODE inputWithCharLimit(char* charArray, int lengthOfArray);

int main(int argc, char* argv[]){
    int randomNumber = 6;

	srand(time(NULL));

    BOTLIST *botList = malloc(sizeof(BOTLIST) + sizeof(BOT) * randomNumber);
    HEALTHBAR *healthbar = malloc(sizeof(HEALTHBAR));

    healthbar->health = 40;

    makeHealthBar(healthbar);

    if(botList == NULL){
        printf("Failed to allocate memory");
        exit(memoryError);
    }

    botList->size = randomNumber;

    for (int i = 0; i < botList->size; ++i) {
        botList->BOTArray[i] = makeRandomBot();
    }

    printHealthBar(healthbar);
    looseHealth(healthbar, 4);
    looseHealth(healthbar, 2);
    printHealthBar(healthbar);

    killBot(&botList->BOTArray[0]);
    killBot(&botList->BOTArray[1]);
    killBot(&botList->BOTArray[2]);

    printf("%d\n", botList->BOTArray[3].value);

    printBots(botList);

    printf("These are your adversaries, lets funk em up\n");

    STATUSCODE result;

    while(1){
        while (1){
            printf("Are you ready to begin? \"yes\" or \"no\"\n");
            char *charArray = malloc(sizeof(char)*(3+1));
            result = inputWithCharLimit(charArray, 3);
            if (result != success){
                exit(result);
            }
            if (charArray == NULL){
                printf("Please try again\n");
            } else if ((strcmp(charArray, "yes")) == 0 || (strcmp(charArray, "no")) == 0){
                if ((strcmp(charArray, "yes")) == 0) {
                    printf("Let the game begin!\n");
                    break;
                } else if ((strcmp(charArray, "no")) == 0) {
                    printf("Okay, maybe next time!\n");
                    exit(0);
                }
            } else {
                printf("Invalid input, try again\n");
                free(charArray);
            }
        }
        if (result != success){
            exit(result);
        }

        printf("Hallo?\n");
    }

    free(healthbar);
    free(botList);

}

STATUSCODE inputWithCharLimit(char* charArray, int lengthOfArray){
    if(charArray == NULL){
        printf("Given array is Null, probably a memory allocation issue\n");
        return memoryError;
    }

    if(lengthOfArray > 99){
        printf("The lengthOfArray is to big, please write a smaller one\n");
        return indexOutOfBoundError;
    }

    int i = 0;
    int character;

    while(((character = fgetc(stdin)) != '\n')){
        if(i < lengthOfArray){
            charArray[i++] = (char)character;
        }
    }

    charArray[i] = '\0';

    return success;
}

void makeHealthBar(HEALTHBAR* healthbar){
    strcpy(healthbar->healthBar[0], "+----------------------------------------+");
    strcpy(healthbar->healthBar[1], "|////////////////////////////////////////|");
    strcpy(healthbar->healthBar[2], "+----------------------------------------+");
}

void printHealthBar(HEALTHBAR* healthbar){
    // 3 is the size of the first position of the 2s Array, 42 is the size of the second
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 42; ++j) {
            printf("%c", healthbar->healthBar[i][j]);
        }
        printf("\n");
    }
}

void looseHealth(HEALTHBAR * healthbar, int amount){
    healthbar->health -= amount;
    updateHealthGUI(healthbar);
}

void updateHealthGUI(HEALTHBAR* healthbar){
    for (int i = 1; i < healthbar->health; ++i) {
        healthbar->healthBar[1][i] = '/';
    }
    // 41 is the position of +, at the end of the healthbar, we don't want to erase that
    for (int i = healthbar->health+1; i < 41; ++i) {
        healthbar->healthBar[1][i] = ' ';
    }
}

void printBots(BOTLIST *botList){
	int length = botList->size;

	for(int i = 0; i < ALENGTH; i++){
		for(int k = 0; k < length; k++){
			for(int j = 0; j < ALENGTH; j++){
			        printf("%c", botList->BOTArray[k].array[i][j]);
			}
			printf("  ");
		}
	printf("\n");
	}
}
BOT makeRandomBot(){
	int iArray[9];

    int value = 0;

	for(int i = 0; i < 9; i++){
		int randomBinary = rand() % 2;
		iArray[i] = randomBinary;
        value += randomBinary;
	}

	BOT pBot;

	int count = 0;
    pBot.value = value;
    pBot.dead = 0;

	for(int i = 0; i < ALENGTH; i++){
		for(int j = 0; j < ALENGTH; j++){
			pBot.array[i][j] = iArray[count] + '0';
			count++;
		}
	}

	return pBot;
}

void killBot(BOT *bot){
    char *DED = "DED";
    for(int i = 0; i < ALENGTH; i++){
        for(int j = 0; j < ALENGTH; j++){
            if(i == 0 || i == 1){
                bot->array[i][j] = ' ';
            }else{
                bot->array[i][j] = DED[j];
            }
        }
    }
    bot->dead = 1;
}