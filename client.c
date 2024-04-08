#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT 12345
#define SERVER_ADDR "127.0.0.1"

int main() {
    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int play;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket");
        exit(1);
    }

    server = gethostbyname(SERVER_ADDR);
    if (server == NULL) {
        perror("Error, host not found");
        exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy((char *)&serv_addr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
    serv_addr.sin_port = htons(PORT);

    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        perror("Error connecting");
        exit(1);
    }

    printf("Choose your play:\nROCK - 1\nPAPER - 2\nSCISSORS - 3\n");
    scanf("%d", &play);

    int bytes_written = write(sockfd, &play, sizeof(play));
    if (bytes_written < 0) {
        perror("Error writing to socket");
        exit(1);
    }

    close(sockfd);
    return 0;
}
