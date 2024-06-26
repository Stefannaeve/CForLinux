#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <../include/client.h>

#define BUFFERSIZE 2048

int client() {

    struct sockaddr_in saAddr = {0};

    int sockFd;
    int iPort;
    int readValue;
    int i = 0;
    int value;
    int position;
    char buffer[BUFFERSIZE];
    char readFromFile[BUFFERSIZE];
    const char lineBeforeBody[] = "\r\n\r\n";
    char *token;
    char *request = "GET / HTTP/1.1\r\nHost: www.ikke.no\r\n\r\n";
    char *filename = "amunderar.txt";

    iPort = 80;

    struct addrinfo *addr;
    int result = getaddrinfo("www.ikke.no", NULL, NULL, &addr);

    if(result != 0){
        printf("Failed getting ip address from web server - Error message: %s\n", strerror(errno));
    }
    else {

		struct sockaddr_in* internet_addr = (struct sockaddr_in*) addr->ai_addr;

		printf("ikke.no is at: %s\n", inet_ntoa(internet_addr->sin_addr));
		internet_addr->sin_port = htons(iPort);
		printf("ikke.no is now using port: %d\n", ntohl(internet_addr->sin_port));
		printf("ikke.no is using family: %u. 2 is AF_INET\n", internet_addr->sin_family);

		sockFd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockFd < 0) {
		    printf("Failed to create endpoint and retrieve file descriptor - Error message %s\n", strerror(errno));
		} else {
            printf("Successfully created endpoint with socket\n");

            if (connect(sockFd, (struct sockaddr *) internet_addr, sizeof(*internet_addr)) < 0) {
                close(sockFd);
                sockFd = -1;
                printf("Connection failed - Error message: %s\n", strerror(errno));
                return 1;
            } else {
                printf("Connect successfully handled\n");


                memset(buffer, 0, BUFFERSIZE);

                value = send(sockFd, request, strlen(request), 0);

                if (value < 0) {
                    printf("Failed to transmit message - Error massage: %s\n", strerror(errno));
                } else {

                    readValue = read(sockFd, buffer, BUFFERSIZE - 1);

                    if (readValue < 0) {
                        printf("Reading failed: Error message: %s\n", strerror(errno));
                    } else {

                        printf("Closing socket\n");

                        token = strstr(buffer, lineBeforeBody);

                        if (token == NULL) {
                            printf("Failed to retrieve token - Error message %s\n", strerror(errno));
                        } else {
                            token += strlen(lineBeforeBody);

                            FILE *newFile = fopen(filename, "w+");

                            if (newFile == NULL) {
                                printf("Failed to open file - Error message: %s\n", strerror(errno));
                            } else {

                                fputs(token, newFile);

                                fseek(newFile, 0, SEEK_END);
                                position = ftell(newFile);

                                printf("Position: %d\n", position);

                                rewind(newFile);

                                fread(readFromFile, 2048, sizeof(char), newFile);

                                printf("%s\n", readFromFile);

                                fclose(newFile);

                                close(sockFd);
                                sockFd = -1;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}
