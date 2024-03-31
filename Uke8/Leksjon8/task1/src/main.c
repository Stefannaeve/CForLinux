#include <stdio.h>

typedef struct _TGAHSTRUCT{
    unsigned char idLength:8;
    unsigned char colorMapType:8;
    unsigned char imageType:8;
    unsigned short firstEntryIndex:16;
    unsigned short colorMapLength:16;
    unsigned char colorMapEntrySize:8;
    unsigned short xOriginOfImage:16;
    unsigned short yOriginOfImage:16;
    unsigned short imageWidth:16;
    unsigned short imageHeight:16;
    unsigned char pixelDepth:8;
    unsigned char pixelDescriptor:8;
} TGAHSTRUCT;

int main(){
    char array[18] = {0};
    FILE *file = fopen("../resources/1.tga", "r");
    TGAHSTRUCT tgaStruct;
    fread(&tgaStruct, 1, 18, file);
    fclose(file);


    printf("%hx\n", tgaStruct.idLength);
    printf("%hx\n", tgaStruct.colorMapType);
    printf("%hx\n", tgaStruct.imageType);
    printf("%hx\n", tgaStruct.firstEntryIndex);
    printf("%hx\n", tgaStruct.colorMapLength);
    printf("%hx\n", tgaStruct.colorMapEntrySize);
    printf("%hx\n", tgaStruct.xOriginOfImage);
    printf("%hx\n", tgaStruct.yOriginOfImage);
    printf("%hx\n", tgaStruct.imageWidth);
    printf("%hx\n", tgaStruct.imageHeight);
    printf("%hx\n", tgaStruct.pixelDepth);
    printf("%hx\n", tgaStruct.pixelDescriptor);


}