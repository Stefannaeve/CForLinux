#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	//Initilize a buffer, and a pointer to a memory address with 101*char
	// memory space
	char buffer[101];
	char *input = (char *)malloc(101*sizeof(char));
	int numberOfChunks = 1;
	
	// We check if input is null, if it is, the memory allocation has failed
	// Therefore we will return a fail message, in this case, "1"
	if(!input){
		printf("Failed to allocate memory..\n");
		return 1;
	}
	
	// We initialize a string, to keep from getting problems from strcat
	input[0] = '\0';
	
	// The while reads the entire transcript from the user up to either the
	// "\n" or when the size of the buffer is hit, if that size is hit, it will
	// use realloc to resize the input array to the size of input + buffer
	// strcat will transfer the buffer string into input, making input ready
	// for the next cycle, having the string, and the new buffer size
	// if we finally get through a loop which doesnt exeed the buffer size
	// We will enter the if statement, and allocate the buffer string into the
	// input one final time 
	while(fgets(buffer, sizeof(buffer), stdin)){
		if(buffer[strlen(buffer) - 1] == '\n'){
			buffer[strlen(buffer) - 1] = '\0';
			strcat(input, buffer);
			break;
		}
		
		input = realloc(input, strlen(input) + strlen(buffer) + 1);
		strcat(input, buffer);
		if (!input){
			free(input);
			printf("Failed to reallocate memory..\n");
			return 1;
		}
		//input = temp;
		//strcat(input, buffer);
		numberOfChunks++;
	}
	
	int count = 0;
	
	for(int i = 0; input[i] != '\0'; ++i){
		count++;
	}
	
	printf("You wrtote: %s\n", input);
	printf("Number Of Chunks Used: %d, size of array: %d\n", numberOfChunks, count);
	free(input);
	return 0;
}
