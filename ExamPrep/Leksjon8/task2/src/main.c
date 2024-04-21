#include <stdio.h>
#include <stdint.h>

#define BIGGEST_BIT_SIZE 64
#define SMALLEST_BIT_SIZE 4

int printBinaryFromInteger(int64_t integer, int bitSize);

int main(){
    printBinaryFromInteger(328, 16);
    return 0;
}

int printBinaryFromInteger(int64_t integer, int bitSize){
    char binary[bitSize+1];

    if (bitSize > BIGGEST_BIT_SIZE){
        printf("Invalid input: bit size exceeds 64 bits");
        return -1;
    }

    if (bitSize < SMALLEST_BIT_SIZE){
        printf("Invalid input: Bit size is to small");
        return -1;
    }

    for (int i = bitSize-1; i >= 0; i--) {
        binary[i] = (integer & 1) ? '1' : '0';
        integer >>= 1;
    }
    binary[bitSize] = '\0';
    printf("\n");

    for (int i = 0; i < bitSize; ++i) {
        if ((i%8) == 0 && i != 0){
            printf(" ");
        }
        printf("%c", binary[i]);
    }
}