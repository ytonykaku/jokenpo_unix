#include <stdio.h>
#include <stdlib.h>
#include "jokenpo.h"

#define ROCK 1
#define PAPER 2
#define SCISSORS 3

int main(){
    int player1Play;
    int player2Play;
    int result;

    player1Play = pickPlay(&player1Play);
    player2Play = pickPlay(&player2Play);

    result = pickWinner(player1Play, player2Play);
    announceWinner(result);

    return 0;
}