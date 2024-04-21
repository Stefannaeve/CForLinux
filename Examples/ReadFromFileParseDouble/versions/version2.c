#include <stdio.h>
#include <stdlib.h>
#define ARRAYSIZE 130

void readFromFileAndStoreInArray(char *charArray, FILE *file, size_t size);

int main(int argc, char *argv[]){
	char str[] = "double.txt";
	char *pInputFromFile;
	pInputFromFile = (char *) malloc(ARRAYSIZE * sizeof(char));
	
	if (pInputFromFile == NULL){
		printf("Failed to allocate memory");
		return 1;
	}
	
	FILE *file;
	file = fopen(str, "r");
	
	if(file == NULL){
		return 1;
	}
	
	int iEndOfFile;
	
	if(fseek(file, 0, SEEK_END) == 0){
		iEndOfFile = ftell(file);
		rewind(file);
	}
	
	readFromFileAndStoreInArray(pInputFromFile, file, ARRAYSIZE);
	
	printf("ftell: %ld\n", ftell(file));
	printf("iEndOfFile: %d\n", iEndOfFile);
	
	for(int i = 0; pInputFromFile[i] != '\0'; i++){
		printf("%c", pInputFromFile[i]);
	}
	
	printf("Hei");
	printf("\n");
	printf("%s", pInputFromFile);
	
	free(pInputFromFile);
	
	fclose(file);
}

void readFromFileAndStoreInArray(char *charArray, FILE *file, size_t size){
	while(!feof(file)){
		if(fgets(charArray, size, file)){
			printf("%s", charArray);
		}
	}
}
