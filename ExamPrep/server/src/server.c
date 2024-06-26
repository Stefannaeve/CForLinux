#include <errno.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <server.h>

#define BUFFERSIZE 1024

typedef struct _SNP_HEADER {
    int32_t contentType;
    int32_t sizeOfBody;
} SNP_HEADER;

typedef struct _SNP {
    SNP_HEADER snpHeader;
    char body[];
} SNP;

enum CONTENTTYPE{
    STRING,
    CHAR,
    INT,
    DOUBLE,
};

int server(int argc, char *argv[]) {

    struct sockaddr_in saAddr = {0};
    struct sockaddr_in saConClient = {0};
    SNP_HEADER clientHeader = {0};

    int sockFd;
    int sockNewFd = 0;
    int iPort = 8080;
    int addrLen = sizeof(saAddr);
    char buffer[BUFFERSIZE];

    saAddr.sin_family = AF_INET;
    saAddr.sin_port = htons(iPort);
    saAddr.sin_addr.s_addr = INADDR_ANY;

    sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFd < 0) {
        printf("Failed to create endpoint and retrieve file descriptor - Error message %s\n", strerror(errno));
    } else {
        printf("Successfully created endpoint with socket\n");

        if (bind(sockFd, (struct sockaddr *) &saAddr, sizeof(saAddr)) < 0) {
            printf("Failed to bind address and port to socket - Error message: %s\n", strerror(errno));
        } else {
            printf("Socket successfully bound to IP address and port\n");

            int irc = listen(sockFd, 5);

            if (irc < 0) {
                printf("Failed to find incoming connection through listen - Error message %s", strerror(errno));
            } else {

                sockNewFd = accept(sockFd, (struct sockaddr *) &saConClient, (socklen_t *) &addrLen);
                if (sockNewFd < 0) {
                    printf("Failed to extract first connection request and create new socket - Error message: %s\n",
                           strerror(errno));
                } else {

                    read(sockNewFd, &clientHeader, sizeof(clientHeader));

                    printf("ContentType: %d, size of Body: %d\n", clientHeader.contentType, clientHeader.sizeOfBody);

                    printf("Successfully created new socket from connection request\n");

                    printf("Closing socket\n");

                    close(sockFd);
                    close(sockNewFd);
                    sockFd = -1;
                    sockNewFd = -1;

                    return 0;
                }
            }
        }
    }
    return -1;
}