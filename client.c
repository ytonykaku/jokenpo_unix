#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "jokenpo.h"

#define PORT 12345
#define SERVER_ADDR "127.0.0.1"

int main() {
    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int play, result, player1Score = 0, player2Score = 0;

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

    while(play != 0){
        pickPlay(&play);

        if (play == 0) break;

        int bytes_written = write(sockfd, &play, sizeof(play));
        if (bytes_written < 0) {
            perror("Error writing to socket");
            exit(1);
        }

        // Recebendo o resultado do servidor
        int bytes_received = recv(sockfd, &result, sizeof(result), 0);

        printf("%d\n", result);

        if (result == 0) printf("Draw!\n");
        else {
            printf("Winner: Player %d!\n", result);
            if(result == 1) player1Score += 1;
            else player2Score +=1;
        }
        printf("Player 1 Score: %d\n", player1Score);
        printf("Player 2 Score: %d\n", player2Score);
    }

    close(sockfd);
    return 0;
    
}
