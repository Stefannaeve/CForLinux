#include <stdio.h>
void sizes();

int main(int argc, char* argv[]){
	sizes();
}

void sizes(){
	int iInteger = 3;
	float fFloating = 4;
	double dDoubling = 5;
	long lLonging = 6;
	signed int iSignedInt = 7;
	unsigned int iUnsignedInt = 8;
	int* pInteger = &iInteger;
	float* pFloat = &fFloating;
	int iArray[10];

	printf("%d int\n", sizeof(iInteger));
	printf("%d float\n", sizeof(fFloating));
	printf("%d double\n", sizeof(dDoubling));
	printf("%d long\n", sizeof(lLonging));
	printf("%d signed int\n", sizeof(iInteger));
	printf("%d unsigned int\n", sizeof(iUnsignedInt));
	printf("%d pointer int\n", pInteger);
	printf("%X pointer float\n", pFloat);
	printf("%d array\n", (sizeof(iArray)/sizeof(int)));
	
	
}
