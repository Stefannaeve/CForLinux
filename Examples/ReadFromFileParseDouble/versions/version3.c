#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define ARRAYSIZE 130

void readFromFileAndStoreInArray(char *charArray, FILE *file, size_t size);
void changingStringToDouble(int *iEndOfFile, FILE *file, double *pDoubleArray);

int main(int argc, char *argv[]){
	char str[] = "double.txt";
	char binaryFileName[] = "binaryFile.bin";
	char *pInputFromFile;
	char *pIntInputFromFile;
	double *pDoubleArray;
	pDoubleArray = (double *) malloc(ARRAYSIZE * sizeof(double));
	pInputFromFile = (char *) malloc(ARRAYSIZE * sizeof(char));
	pIntInputFromFile = (char *) malloc(ARRAYSIZE * sizeof(char));
	
	if (pInputFromFile == NULL){
		printf("Failed to allocate memory");
		return 1;
	}
	
	FILE *file;
	file = fopen(str, "r");
	
	if(!file){
		perror("fopen");
		return EXIT_FAILURE;
	}
	
	int *iEndOfFile;
	iEndOfFile = (int *) malloc(sizeof(int));
	
	if(fseek(file, 0, SEEK_END) == 0){
		*iEndOfFile = ftell(file);
		printf("ftell1: %ld\n", ftell(file));
		rewind(file);
		printf("ftell2: %ld\n", ftell(file));
	}
	
	readFromFileAndStoreInArray(pInputFromFile, file, ARRAYSIZE);
	
	changingStringToDouble(iEndOfFile, file, pDoubleArray);
	
	fclose(file);
	
	FILE *binaryFile;
	binaryFile = fopen(binaryFileName, "wb+");
	
	if(!file){
		perror("fopen");
		return EXIT_FAILURE;
	}

	fwrite(pInputFromFile, ARRAYSIZE, sizeof(char), binaryFile);
	fseek(file, 0, SEEK_SET);
	size_t itemsToRead = fread(pIntInputFromFile, sizeof(char), ARRAYSIZE, binaryFile);
	printf("%d\n", itemsToRead);
	
	for(int i = 0; i < itemsToRead; i++){
		printf("%c", pIntInputFromFile[i]);
	}
	printf("\n");
	
	free(pInputFromFile);
	free(pIntInputFromFile);
}

void readFromFileAndStoreInArray(char *charArray, FILE *file, size_t size){
	if(fgets(charArray, size, file)){
		printf("%s", charArray);
	} else {
		printf("Was not able to store file informatino into array\n");
	}
}

void changingStringToDouble(int *iEndOfFile, FILE *file, double *pDoubleArray){
	rewind(file);
	int lastPositionForBreak = 0;
	int currentPositionForBreak;
	int lengthFromEndOfDoubleToStartOfDouble = 2;
	int positionInDoubleArray = 0;
	char character;
	printf("Hallo3\n");
	while((character = fgetc(file)) != EOF){
		printf("Hallo2\n");
		if(character == ','){
			currentPositionForBreak = ftell(file)-1;
			fseek(file, lastPositionForBreak, SEEK_SET);
			char str[currentPositionForBreak - lastPositionForBreak + 1];
			int i = 0;
			printf("Hallo1\n");
			printf("Current Position: %d\n", currentPositionForBreak);
			printf("Last Position: %d\n", lastPositionForBreak);
			while(i < (currentPositionForBreak - lastPositionForBreak) && (str[i] = fgetc(file)) != '\0'){
				printf("Printing char in while: %c\n", str[i]);
				i++;
			}
			lastPositionForBreak = currentPositionForBreak+lengthFromEndOfDoubleToStartOfDouble;
			fgetc(file);
			fgetc(file);
			str[i] = '\0';
			printf("Hallo\n");
			printf("Length of string: %s\n", str);
			pDoubleArray[positionInDoubleArray] = strtod(str, NULL);
			printf("Double: %f\n", pDoubleArray[positionInDoubleArray]);
		}
	}
}
