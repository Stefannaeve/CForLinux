#include <stdio.h>

void amundECringe();

int main() {
    int amund = 0;
    amundECringe(&amund);
    amundECringe(&amund);
    amundECringe(&amund);

    printf("%d", amund);
}

void amundECringe(int *amund){
    *amund = *amund +1;
    printf("Time nr. %d\n", *amund);
}
