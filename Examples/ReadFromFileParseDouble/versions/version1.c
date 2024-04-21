#include <stdio.h>

int main(int argc, char *argv[]){
	char str[] = "double.txt";
	char inputFromFile[130];
	
	FILE *file = fopen(str, "r");
	
	if(file == NULL){
		fclose(file);
		return 1;
	}
	
	int iEndOfFile;
	
	if(fseek(file, 0, SEEK_END) == 0){
		iEndOfFile = ftell(file);
		rewind(file);
	}

	while(!feof(file)){
		if(fgets(inputFromFile, sizeof(inputFromFile), file)){
			printf("%s", inputFromFile);
		}
	}
	
	printf("ftell: %ld\n", ftell(file));
	printf("iEndOfFile: %d\n", iEndOfFile);
	
	for(int i = 0; inputFromFile[i] != '\0'; i++){
		printf("%c", inputFromFile[i]);
	}
	
	printf("Hei");
	printf("\n");
	printf("%s", inputFromFile);
	
	fclose(file);
}
