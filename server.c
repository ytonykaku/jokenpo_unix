#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "jokenpo.h" // Adicionando a inclusão do arquivo de cabeçalho

#define PORT 12345
#define MAX_CONNECTIONS 2

int main() {
    int sockfd, newsockfd, clilen;
    struct sockaddr_in serv_addr, cli_addr;
    int player1Play, player2Play;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket");
        exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error binding");
        exit(1);
    }

    listen(sockfd, MAX_CONNECTIONS);
    clilen = sizeof(cli_addr);

    printf("Waiting for connections...\n");

    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) {
        perror("Error accepting connection");
        exit(1);
    }
    printf("Connection established with player 1.\n");

    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) {
        perror("Error accepting connection");
        exit(1);
    }
    printf("Connection established with player 2.\n");

    int result;

    player1Play = pickPlay(&player1Play, 1);
    player2Play = pickPlay(&player2Play, 2);

    result = pickWinner(player1Play, player2Play);
    announceWinner(result);

    close(newsockfd);
    close(sockfd);

    return 0;
}
