#include <stdio.h>
#include <stdint.h>

typedef struct _PORT{
    uint16_t source :16;
    uint16_t destination :16;
} PORT;

typedef struct _TCPHEADER{
    PORT port;
    uint32_t sequenceNumber :32;
    uint32_t acknowledgementNumber :32;
    uint8_t offset :4;
    uint8_t reserved :4;
    uint8_t flags :8;
    uint16_t windowSize :16;
    uint16_t checkSum :16;
    uint16_t urgentPointer :16;
    uint32_t options[];
} TCPHEADER;

int main(){

}