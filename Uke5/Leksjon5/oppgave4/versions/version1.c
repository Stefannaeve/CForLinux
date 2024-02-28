#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define ALENGTH 3

typedef struct {
	char array[3][3];
} BOT;

typedef struct {
	BOT BOTArray[2];
} BOTLIST;

void printBots(BOTLIST *botList);
BOT* makeRandomBot();

int main(int argc, char* argv[]){
	
    BOT bot = {
        {
            {'1', '0', '1'},
            {'0', '1', '1'},
            {'1', '0', '0'}
        }
    };
    
    BOT bot2 = {
		{
		    {'0', '1', '0'},
		    {'1', '0', '0'},
		    {'0', '1', '1'}
		}
    };
    
    BOT* newBot = makeRandomBot();
    
    BOTLIST botList = {
    		.BOTArray = {bot, *newBot}
    };
    
    printBots(&botList);
    
    free(newBot);

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
	srand(time(NULL));
	
	for(int i = 0; i < 9; i++){
		int randomBinary = rand() % 2;
		iArray[i] = randomBinary;
	}
	
	BOT *pBot;
	pBot = malloc(sizeof(BOT));
	
	int count = 0;
	
	for(int i = 0; i < ALENGTH; i++){
		for(int j = 0; j < ALENGTH; j++){
			pBot->array[i][j] = iArray[count] + '0';
			count++;
		}
	}
	
	return pBot;

}























