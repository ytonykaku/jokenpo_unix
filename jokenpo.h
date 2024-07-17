#ifndef JOKENPO_H
#define JOKENPO_H

int pickPlay(int *play, int player);
int pickWinner(int player1Play, int player2Play);
void announceWinner(int result);
int increaseScore(int playerScore);

#endif
