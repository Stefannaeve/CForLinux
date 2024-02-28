#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void getValuesFromUser(int *pRow, int *pCols);
void print2DArray(int iRows, int iCols, int **pArray);
void insertIntegerAtRandomArrayPosition(int sizeOfUserInput, int iCols, int 					*pRandomNumbersR, int *pRandomNumbersC, int **pArray, int *pUserIntegers);
int sort(int *pA, int *pB);
void bubbleSort(int iRows, int iCols, int **pArray);

int main(int argc, char* argv[]){
	int **iArray, i, j, k, hasElevated = 0, attempts = 0;
	int iRandomNumbersR[8];
	int iRandomNumbersC[8];
	int iUserIntegers[8];
	int iRows = 5, iCols = 5, iRes;
	int sizeOfUserInput = 8;
	
	// USER INPUT TO POPULATE IROWS AND ICOLS DYNAMICALLY
	getValuesFromUser(&iRows, &iCols);
	
	//TESTCODE
	printf("Rows: %d, collumns: %d\n", iRows, iCols);
	
	// INITIALIZE ARRAY BASED ON USER INPUT
	iArray = (int **) malloc (iRows * sizeof(int*));
	for(i = 0; i < iRows; i++){
		iArray[i] = (int *) malloc (iCols * sizeof(int));
		for(j = 0; j < iCols; j++){
			iArray[i][j] = 0;
		}
	}
	
	// ASK USER FOR 8 INTEGERS 
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
	
	// GET TWO ARRAYS OF RANDOM INTEGER BASED ON IROWS AND ICOLS LENGTH
	
	srand(time(NULL));
	
	for(k = 0; k < 8; k++){
		iRandomNumbersR[k] = rand() % (iRows);
		iRandomNumbersC[k] = rand() % (iCols);
	}
	
	
	// TESTCODE
	for(k = 0; k < 8; k++){
		printf("Random: %d, %d, userInput: %d\n", iRandomNumbersR[k], 
		iRandomNumbersC[k], iUserIntegers[k]);
	}
	
	insertIntegerAtRandomArrayPosition(sizeOfUserInput, iCols, iRandomNumbersR, iRandomNumbersC, iArray, iUserIntegers);
	
	print2DArray(iRows, iCols, iArray);
	
	bubbleSort(iRows, iCols, iArray);
	
	print2DArray(iRows, iCols, iArray);
	
	for(i = 0; i < iRows; i++){
		free(iArray[i]);
	}
	
	free(iArray);
}

	// LOGIC FOR INSERTING USERINTEGERS INTO RANDOM PLACES IN IARRAY
	// USING POINTERS
void insertIntegerAtRandomArrayPosition(int sizeOfUserInput, int iCols, int *pRandomNumbersR, int *pRandomNumbersC, int **pArray, int *pUserIntegers){
	int attempts = 0;
	int hasElevated = 0;
	int i;
	for(i = 0; i < sizeOfUserInput; i++){
		int *pNewValue = &pArray[pRandomNumbersR[i]][pRandomNumbersC[i]];
		if(*pNewValue == 0){
			*pNewValue = pUserIntegers[i];
		}else{
			int pluss = (pRandomNumbersC[i]+1);
			int *pNewValue2 = NULL;
			while(attempts < sizeOfUserInput){
				attempts++;
				if(pluss == iCols-1 || hasElevated == 1){
					if(hasElevated == 0){
						pluss = 0;
					}
					hasElevated = 1;
					
					pNewValue2 = &pArray[pRandomNumbersR[i+1]][pRandomNumbersC[pluss]];
					
				}else{
					pNewValue2 = &pArray[pRandomNumbersR[i]][pRandomNumbersC[pluss]];
				}
				if(*pNewValue2 == 0){
					*pNewValue2 = pUserIntegers[i];
					break;
				}
				pluss++;
			}
		}
	}
}

void print2DArray(int iRows, int iCols, int **pArray){
	printf("iRows: %d\n", iRows);
	for(int i = 0; i < iRows; i++){
		for(int j = 0; j < iCols; j++){
			printf("Row: %d, Column: %d, Value: %d\n", i, j, pArray[i][j]);
		}
	}
}

void getValuesFromUser(int *pRow, int *pCols){
	int iRes;
	do {
		printf("Write the input for rows (first) and column (second)\n");
		printf("In this format: \"x, y\"\n");
		iRes = scanf("%d, %d", pRow, pCols);
		printf("Row: %d, Cols: %d\n", *pRow, *pCols);
		printf("iRes: %d\n", iRes);
	}
	while(iRes != 2);
}

void bubbleSort(int iRows, int iCols, int **pArray) {
    for (int i = 0; i < iRows; i++) {
        for (int pass = 0; pass < iCols - 1; pass++) {
            int hasPassed = 0;
            
            for (int j = 0; j < iCols - pass - 1; j++) {
                if (pArray[i][j] > pArray[i][j + 1]) {
                    int temp = pArray[i][j];
                    pArray[i][j] = pArray[i][j + 1];
                    pArray[i][j + 1] = temp;
                    hasPassed = 1;
                }
            }
            if (hasPassed == 0) {
                break;
            }
        }
    }

    // Printing the sorted 2D array
    for (int i = 0; i < iRows; i++) {
        for (int j = 0; j < iCols; j++) {
            printf("%d ", pArray[i][j]);
        }
        printf("\n");
    }
}

int sort(int *pA, int *pB){	
	int j = *pA;
	*pA = *pB; 
	*pB = j;
}
