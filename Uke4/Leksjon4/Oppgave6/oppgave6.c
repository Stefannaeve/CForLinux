#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int swap(char **pA, char **pB);

int main(int argc, char* argv[]){
	
	int hasSwapped;
	for(int pass = 1; pass < argc-1; pass++){
		hasSwapped = 0;
		for(int i = 1; i < argc - pass; i++){
			int compared = strcmp(argv[i], argv[i+1]);
			printf("compared: %d\n", compared);
			if(compared > 0){
				printf("%s is bigger than %s, switching...\n", argv[i], argv[i+1]);
				swap(&argv[i], &argv[i+1]);
				hasSwapped = 1;
				
				printf("Current state of the array sorting proccess: \n     ");
				for(int j = 1; j < argc; j++){
					if(i != j && i+1 != j){
						printf("%s, ", argv[j]);
					}else{
						printf("\033[32m%s\033[0m, ", argv[j]);
					}
				}
			}
			printf("\n\n");
		}
		if(hasSwapped == 0){
			break;
		}
	}
	
	printf("Finished sorting array, printing...\n");
	for(int i = 1; i < argc; i++){
		printf("%s ", argv[i]);
	}
	
	printf("\n");
	
	return 0;
	
	
}

int swap(char **pA, char **pB){
	char *j = *pA;
	*pA = *pB; 
	*pB = j;
}

