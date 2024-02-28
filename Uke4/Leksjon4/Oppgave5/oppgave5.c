#include <stdio.h>

int main(int argc, char* argv[]){
	
	for(int i = 1; i < argc; i++){
		printf("%s ", argv[i]);
	}
	printf("\n");
	printf("Number of strings: %d\n", argc-1);
	
	for(int i = 1; i < argc; i++){
		printf("%d: %s\n", i, argv[i]);
	}
}
