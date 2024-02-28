#include <stdio.h>
#include <stdlib.h>

int sort(int *pA, int *pB){	
	int j = *pA;
	*pA = *pB; 
	*pB = j;
}

int main(int argc, char* argv[]){
	int array[argc-1];
	int iElementsInArray = (sizeof(array)/sizeof(array[0]));

	for(int i = 1; i < iElementsInArray+1; i++){
		array[i-1] = atoi(argv[i]);
	}
	
	int hasPassed;
	for(int pass = 0; pass < iElementsInArray-1; pass++){
		hasPassed = 0;
		for(int i = 0; i < iElementsInArray - pass - 1; i++){
			if(array[i] > array[i+1]){
				sort(&array[i], &array[i+1]);
				hasPassed = 1;
			}
		}
		if(hasPassed == 0){
			break;
		}
	}
	
	for(int i = 0; i < iElementsInArray; i++){
		printf("%d\n", array[i]);
	}
}
