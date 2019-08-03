#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state, 
		int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);

// the below function prototypes were created as part of assignment 2

void gainEstate(int currentPlayer, struct gameState *state); 
int baronEffect(int choice, int currentPlayer, struct gameState *state, int *bonus, int handPos);
void discardHand(int player, struct gameState *state);
int minionEffect(int choice1, int choice2, int currentPlayer, struct gameState *state, int *bonus, int handPos);
int ambassadorEffect(int choice1, int choice2, int currentPlayer, struct gameState *state, int handPos);
int tributeEffect(int currentPlayer, struct gameState *state, int *bonus, int handPos);
int mineEffect(int choice1, int choice2, int currentPlayer, struct gameState *state, int handPos);

// the above function prototypes were created as part of assignment 2

int cardEffect(int card, int choice1, int choice2, int choice3, 
	       struct gameState *state, int handPos, int *bonus);

#endif
