#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define ALENGTH 3

typedef struct {
	char array[3][3];
} BOT;

typedef struct {
	BOT BOTArray[6];
} BOTLIST;

void printBots(BOTLIST *botList);
BOT* makeRandomBot();

int main(int argc, char* argv[]){

	srand(time(NULL));
    
    BOT* newBot1 = makeRandomBot();
    BOT* newBot2 = makeRandomBot();
    BOT* newBot3 = makeRandomBot();
    BOT* newBot4 = makeRandomBot();
    BOT* newBot5 = makeRandomBot();
    BOT* newBot6 = makeRandomBot();
    
    BOTLIST botList = {
    		.BOTArray = {*newBot1, *newBot2, *newBot3, *newBot4, *newBot5, *newBot6}
    };
    
    printBots(&botList);
    

    free(newBot1);

    free(newBot2);

	
}

void printBots(BOTLIST *botList){
	int length = (sizeof(botList->BOTArray)/sizeof(botList->BOTArray[0]));
	
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
BOT* makeRandomBot(){
	int iArray[9];
	
	for(int i = 0; i < 9; i++){
		int randomBinary = rand() % 2;
		iArray[i] = randomBinary;
	}
	
	BOT *pBot;
	pBot = (BOT*)malloc(sizeof(BOT));
	
	int count = 0;
	
	for(int i = 0; i < ALENGTH; i++){
		for(int j = 0; j < ALENGTH; j++){
			pBot->array[i][j] = iArray[count] + '0';
			count++;
		}
	}
	
	return pBot;

}























