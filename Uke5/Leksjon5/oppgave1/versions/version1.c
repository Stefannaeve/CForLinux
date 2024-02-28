#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	int **iArray, i, j, k;
	int iRows = 5, iCols = 5, iRes;
	
	do {
		printf("Write the input for rows (first) and column (second)\n");
		printf("In this format: \"x, y\"\n");
		iRes = scanf("%d, %d", &iRows, &iCols);
		printf("iRes: %d\n", iRes);
	}
	while(iRes != 2);
	
	printf("Rows: %d, collumns: %d\n", iRows, iCols);
	
	iArray = (int **) malloc (iRows * sizeof(int));
	for(i = 0; i < iRows; i++){
		iArray[i] = (int *) malloc (iCols * sizeof(int));
	}
	
	int *pArray = &iArray[0][0];
	*pArray = 1; 
	
	for(i = 0; i < iRows; i++)
		for(j = 0; j < iCols; j++){
			int *pNewValue = &iArray[i][j];
			*pNewValue = i+j; 
			printf("Row: %d, Column: %d, Value: %d\n", i, j, iArray[i][j]);
		}
}
