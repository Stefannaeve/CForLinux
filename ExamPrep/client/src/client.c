#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <../include/client.h>

#define BUFFERSIZE 1024

int userInput(char *buffer, int size);

typedef struct _SNP_HEADER {
    int32_t sizeOfBody: 4;
} SNP_HEADER;

typedef struct _SNP {
    SNP_HEADER snpHeader;
    char body[];
} SNP;

int client(int argc, char *argv[]) {
    int sockFd;
    int iPort = 8080;
    char buffer[BUFFERSIZE];
    int sizeOfBuffer;

    struct sockaddr_in saAddr = {0};
    saAddr.sin_family = AF_INET;
    saAddr.sin_port = htons(iPort);
    saAddr.sin_addr.s_addr = htonl(0x7F000001); //Home

    sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFd < 0) {
        printf("Failed to create endpoint and retrieve file descriptor - Error message %s\n", strerror(errno));

    } else {
        printf("Successfully created endpoint with socket\n");

        if (connect(sockFd, (struct sockaddr *) &saAddr, sizeof(saAddr)) < 0) {
            printf("Connection failed: Error message: %s\n", strerror(errno));

        } else {
            printf("Connect successfully handled\n");

            userInput(&buffer, BUFFERSIZE);

            sizeOfBuffer = strlen(buffer);

            SNP *snp = (SNP *) malloc(sizeof(SNP) + sizeOfBuffer * sizeof(char));

            memset(snp, 0, sizeof(SNP) + sizeOfBuffer * sizeof(char));

            snp->snpHeader.sizeOfBody = sizeOfBuffer;
            strncpy(snp->body, buffer, sizeOfBuffer);

            snp->body[sizeOfBuffer - 1] = '\0';

            send(sockFd, snp, sizeof(SNP) + snp->snpHeader.sizeOfBody, 0);

            printf("Closing socket\n");

            close(sockFd);
            sockFd = -1;
            return 0;
        }
        close(sockFd);
        sockFd = -1;
    }

    return 1;
}

int userInput(char *buffer, int size) {
    int bufferLength;
    fgets(buffer, size - 1, stdin);

    bufferLength = strlen(buffer);

    while (buffer[bufferLength - 1] == '\r' || buffer[bufferLength - 1] == '\n') {
        buffer[bufferLength - 1] = '\0';
        bufferLength = strlen(buffer);
    }

    buffer[size - 1] = '\0';
}
