#include <stdio.h>

void amundECringe();

int main() {

    int justARandomNumber = 10;
    for (int i = 0; i < justARandomNumber; ++i) {
        amundECringe();
    }
}

void amundECringe(){
    static int amund = 0;
    amund++;
    printf("Time nr. %d\n", amund);
}
