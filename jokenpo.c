#include <stdio.h>
#include <stdlib.h>

#define ROCK 1
#define PAPER 2
#define SCISSORS 3

int pickPlay(int *play, int player){
    printf("Choose your play, player %d:\nROCK - 1\nPAPER - 2\nSCISSORS - 3\n", player);
    scanf("%d", play);
    return *play;
}

int pickWinner(int player1Play, int player2Play){
    if(player1Play == player2Play) return 0; /*draw*/
    else if(player1Play == ROCK){
        if(player2Play == SCISSORS) return 1; /*player 1 wins*/
        else return 2; /*player 2 wins*/
    }
    else if(player1Play == PAPER){
        if(player2Play == ROCK) return 1;
        else return 2;
    }
    else { /* player1Play == SCISSORS */
        if(player2Play == PAPER) return 1;
        else return 2;
    }
}

void announceWinner(int result){
    if (result == 0) printf("Draw!\n");
    else if(result == 1) printf("Winner: Player 1!\n");
    else printf("Winner: Player 2!\n");
}