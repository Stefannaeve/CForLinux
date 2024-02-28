#include <stdio.h>
#include <string.h>
#define MAXLENGTH 2000

int main(int argc, char* argv[]){
	char max[MAXLENGTH];
	
	fgets(max, MAXLENGTH, stdin);
	max[MAXLENGTH-1] = '\0';
	
	int lengthOfArray = strlen(max);
	
	for(int i = 0; i < lengthOfArray; i++){
		printf("%c", max[i]);
	}

}
