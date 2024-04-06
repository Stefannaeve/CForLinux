#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <../include/client.h>

#define BUFFERSIZE 1024

int client(){
    struct sockaddr_in saAddr = {0};
    int sockFd;
    int iPort = 8000;
    int readValue;
    int i = 0;
    char buffer[BUFFERSIZE];
    char *msg[] = {
            "HELO Stefan, 127.0.0.1",
            "MAIL FROM: <stefan.naeve@hotmail.com>",
            "RCPT TO: <amund.myrnokka@gay.no",
            "Hei, du din fjøsnisse",
            "Test",
            "QUIT"

    };

    sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockFd < 0){
        printf("socket failed with %s\n", strerror(errno));
    } else {
        printf("Socket successfully bound to IP address\n");
    }

    saAddr.sin_family = AF_INET;
    saAddr.sin_port = htons(iPort);
    saAddr.sin_addr.s_addr = htonl(0x7F000001); //Home

    int irc = connect(sockFd, (struct sockaddr*) &saAddr, sizeof(saAddr));

    if(irc < 0){
        printf("Connection failed: Error message: %s\n", strerror(errno));
    } else {
        printf("Connect successfully handled\n");
    }

    memset(buffer, 0, BUFFERSIZE);
    while(1){
        readValue = read(sockFd, buffer, BUFFERSIZE-1);
        sleep(1.5f);
        if(readValue < 0){
            printf("Reading failed: Error message: %s\n", strerror(errno));
        } else {
            printf("%s\n", buffer);
        }
        send(sockFd, msg[i], strlen(msg[i]), 0);
        if(i > 4){
            break;
        }
        memset(buffer, 0, BUFFERSIZE);
        i++;
    }

    printf("Closing socket\n");

    close(sockFd);
    sockFd = -1;

    return 0;
}
