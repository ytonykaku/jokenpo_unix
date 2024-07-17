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
    int sockfd, newsockfds[MAX_CONNECTIONS], clilen;
    struct sockaddr_in serv_addr, cli_addr;
    int player1Play, player2Play, player1Score = 0, player2Score = 0;

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

    newsockfds[0] = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfds[0] < 0) {
        perror("Error accepting connection");
        exit(1);
    }
    printf("Connection established with player 1.\n");

    newsockfds[1] = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfds[1] < 0) {
        perror("Error accepting connection");
        exit(1);
    }
    printf("Connection established with player 2.\n");

    int result;

    while(player1Play != 0 || player2Play != 0){
        for(int i = 0; i < 2; i++){

        // Recebe a jogada do jogador 1
        int bytes_read = read(newsockfds[0], &player1Play, sizeof(player1Play));
        if (bytes_read < 0) {
            perror("Error reading from socket");
            exit(1);
        }
        if(player1Play == 0) break;

        // Recebe a jogada do jogador 2
        bytes_read = read(newsockfds[1], &player2Play, sizeof(player2Play));
        if (bytes_read < 0) {
            perror("Error reading from socket");
            exit(1);
        }
        if(player2Play == 0) break;

        result = pickWinner(player1Play, player2Play);

        int bytes_sent1 = send(newsockfds[0], &result, sizeof(result), 0);
        if (bytes_sent1 < 0) {
            perror("Error sending data to player 1");
            exit(1);
        }

        int bytes_sent2 = send(newsockfds[1], &result, sizeof(result), 0);
        if (bytes_sent2 < 0) {
            perror("Error sending data to player 2");
            exit(1);
        }


        /*close(newsockfds[0]);
        close(newsockfds[1]);*/
        announceWinner(result);
        if(result == 1){
            player1Score = increaseScore(player1Score);
            int bytes_sent3 = send(newsockfds[1], &player1Score, sizeof(player1Score), 0);
            if (bytes_sent3 < 0) {
                perror("Error sending data to player 2");
                exit(1);
            }
        }
        else if(result == 2){
            player2Score = increaseScore(player2Score);
            int bytes_sent4 = send(newsockfds[1], &player2Score, sizeof(player2Score), 0);
            if (bytes_sent4 < 0) {
                perror("Error sending data to player 2");
                exit(1);
            }
        }
        printf("Player 1 Score: %d\n", player1Score);
        printf("Player 2 Score: %d\n", player2Score);

        }
    }

    
    close(sockfd);

    return 0;
}
