#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]){
	int **iArray, i, j, k, hasElevated = 0, attempts = 0;
	int iRandomNumbersR[8];
	int iRandomNumbersC[8];
	int iUserIntegers[8];
	int iRows = 5, iCols = 5, iRes;
	
	do {
		printf("Write the input for rows (first) and column (second)\n");
		printf("In this format: \"x, y\"\n");
		iRes = scanf("%d, %d", &iRows, &iCols);
		printf("Row: %d, Cols: %d\n", iRows, iCols);
		printf("iRes: %d\n", iRes);
	}
	while(iRes != 2);
	
	printf("Rows: %d, collumns: %d\n", iRows, iCols);
	
	iArray = (int **) malloc (iRows * sizeof(int));
	for(i = 0; i < iRows; i++){
		iArray[i] = (int *) malloc (iCols * sizeof(int));
	}
	
	do {
		printf("Write 8 integers for insertion into the array\n");
		printf("In this format: \"x, y, z, ...\"\n");
		
		
		
		iRes = scanf("%d, %d, %d, %d, %d, %d, %d, %d", 
		&iUserIntegers[0], &iUserIntegers[1], &iUserIntegers[2],
		&iUserIntegers[3], &iUserIntegers[4], &iUserIntegers[5],
		&iUserIntegers[6], &iUserIntegers[7]);
		
		printf("iRes: %d\n", iRes);
	}
	while(iRes != 8);
	
	printf("Hallo?\n");
	
	srand(time(NULL));
	
	for(k = 0; k < 8; k++){
		iRandomNumbersR[k] = rand() % (iRows-1);
		iRandomNumbersC[k] = rand() % (iCols-1);
	}
	
	for(k = 0; k < 8; k++){
		printf("Random: %d, %d, userInput: %d\n", iRandomNumbersR[k], 
		iRandomNumbersC[k], iUserIntegers[k]);
	}
	
	for(i = 0; i < 8; i++){
		int *pNewValue = &iArray[iRandomNumbersR[i]][iRandomNumbersC[i]];
		if(*pNewValue == 0){
			*pNewValue = iUserIntegers[i];
		}else{
			while(attempts < 8){
				int pluss = (i+1);
				attempts++;
				int *pNewValue2 = NULL;
				if(pluss >= 8 || hasElevated == 1){
					if(hasElevated == 0){
						pluss = 0;
					}
					hasElevated = 1;
					
					pNewValue2 = &iArray[iRandomNumbersR[i+1]][iRandomNumbersC[pluss]];
					
				}else{
					pNewValue2 = &iArray[iRandomNumbersR[i]][iRandomNumbersC[pluss]];
				}
				if(*pNewValue2 == 0){
					*pNewValue2 = iUserIntegers[i];
					break;
				}
			}
		}
	}
	
	for(i = 0; i < iRows; i++) {
		for(j = 0; j < iCols; j++){
		/*
			int *pNewValue = &iArray[i][j];
			*pNewValue = i+j;
		*/ 
			printf("Row: %d, Column: %d, Value: %d\n", i, j, iArray[i][j]);
		}
	}
}
