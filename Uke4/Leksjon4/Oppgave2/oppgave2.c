#include <stdio.h>

int main(int argc, char* argv[]){
	int *pInt;
	char *pChar;
	short *pShort;
	double *pDouble;
	
	printf("The size of pointers are %lu, %lu, %lu, %lu respectively \n", sizeof(pInt), sizeof(pChar), sizeof(pShort), sizeof(pDouble));
		printf("The size of pointers are %lu, %lu, %lu, %lu respectively \n", sizeof(*pInt), sizeof(*pChar), sizeof(*pShort), sizeof(*pDouble));
}
