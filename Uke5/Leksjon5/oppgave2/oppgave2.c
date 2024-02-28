#include <stdio.h>

void printCharArray(int iCount, char *cArray);
int countCharsInString(char *cArray);

int main(int argc, char* argv[]){
	char cStringArray[12] = {"hello world\0"};
	
	int iCount = countCharsInString(cStringArray);
	printCharArray(iCount, cStringArray);
}

void printCharArray(int iCount, char *cArray){
	for(int i = 0; i < iCount; i++){
		printf("%c", cArray[i]);
	}
	printf("\n");
}

int countCharsInString(char *cArray){
	int iCount = 0;
	while (*cArray != '\0'){
		iCount++;
		cArray++;
	}
	return iCount;
}
