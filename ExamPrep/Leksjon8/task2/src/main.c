#include <stdio.h>
#include <stdint.h>

#define BIGGEST_BIT_SIZE 64
#define SMALLEST_BIT_SIZE 4

int convertToBinary(int8_t *binary, int64_t integer, int bitSize);
int printBinary(int8_t *binary, int bitSize);
int invertBinary(int8_t *binary, int bitSize);
int binaryToChar(int8_t *binary, int *newNumber);

// Unsigned
// 1-bit max == 2/1
// 4-bit max == 16/15
// 8-bit max == 256/255 (Size of unsigned char or int8_t)
// 16-bit max == 65536/65535
// 32-bit max == 4294967296/4294967295 (Size of a regular int)
// 64-bit max == A fucking lot

int main(){
    int bitSize = 8;
    int8_t binary[bitSize];
    int number = 'a';
    int newNumber;

    printf("%c\n", number);

    convertToBinary(binary, number, bitSize);
    printBinary(binary, bitSize);

    binaryToChar(binary, &newNumber);

    printf("%c\n", newNumber);
    return 0;
}

int binaryToChar(int8_t *binary, int *newNumber){
    int asciiBitSize = 8;
    int j = 0;

    for (int i = asciiBitSize-1; i >= 0; i--) {
        char mask = binary[j++] << i;
        (*newNumber) += mask;
        printf("mask: %d\n", mask);

    }

    return 0;
}

int invertBinary(int8_t *binary, int bitSize){
    for (int i = 0; i < bitSize; ++i) {
        binary[i] = !binary[i];
    }
}

int convertToBinary(int8_t *binary, int64_t integer, int bitSize){

    if (bitSize > BIGGEST_BIT_SIZE){
        printf("Invalid input: bit size exceeds 64 bits");
        return -1;
    }

    if (bitSize < SMALLEST_BIT_SIZE){
        printf("Invalid input: Bit size is to small");
        return -1;
    }

    for (int i = bitSize-1; i >= 0; i--) {
        binary[i] = (integer & 1) ? 1 : 0;
        integer >>= 1;
    }

    return 0;
}

int printBinary(int8_t *binary, int bitSize){
    for (int i = 0; i < bitSize; ++i) {
        if ((i%8) == 0 && i != 0){
            printf(" ");
        }
        printf("%d", binary[i]);
    }
    printf("\n");
}