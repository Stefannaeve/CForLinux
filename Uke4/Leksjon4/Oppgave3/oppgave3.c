#include <stdio.h>

int main(int argc, char* argv[]){
	int a, b;
	int *pA = &a;
	int *pB = &b;
	printf("Type two integers seperated with space\n");
	scanf("%d %d", pA, pB);
	
	if(a>b){
		printf("The biggest number is: %d\n", a);
	} else {
		printf("The biggest number is: %d\n", b);
	}
	
}
