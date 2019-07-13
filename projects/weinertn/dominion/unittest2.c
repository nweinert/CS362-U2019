/* -----------------------------------------------------------------------
* Unit Test for Minion function
* Include the following lines in your makefile:
*
* -----------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"




void assertTrue(int test, int value) {
	if (test == value) {
		printf("PASSED\t");
	}
	else {
		printf("FAILED\t");
	}
}

int testMinion(int handPos, int currentPlayer, int choice1, int choice2, struct gameState *state) {
	//choice1==1 is discard an estate
	int oldActions = state->numActions;
	int money = state->coins;
	//int handSize = state->handCount[currentPlayer];
	int deckSize = state->deckCount[currentPlayer];
	//int discardSize = state->discardCount[currentPlayer];

	int returnVal = minionEffect(handPos, currentPlayer, choice1, choice2, state);

	assertTrue(oldActions + 1, state->numActions);
	printf("TEST: 2 more coins.\n");

	//Discard estate
	if (choice1 == 1) {
		printf("+2\n");
		assertTrue(money + 2, state->coins);
		printf("TEST: 2 more coins.\n");		
	}
	//gain estate
	else {
		printf("New Hand\n");
		assertTrue(state->handCount[currentPlayer], 4);
		printf("TEST: 4 cards in hand.\n");
		assertTrue(state->handCount[currentPlayer + 1], 4);
		printf("TEST: 4 cards in opponents hand.\n");
		assertTrue(state->deckCount[currentPlayer], deckSize);
		printf("TEST: Deck did not change state\n");
	}
	return returnVal;
}

int main() {

	struct gameState G, tmp;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };
	srand(time(0));


	printf("\n\n\n\n\nTests for MINION\n");
	//Random test of basic card functionality	
	for (int i = 0; i < 30; i++) {
		int seed = rand() % 1000;
		int choice1 = rand() % 2;
		int choice2 = 0;
		if (!choice1) {
			choice2 = 1;
		}

		printf("\nStarting new round of tests.\n");
		initializeGame(2, k, seed, &G);
		G.handCount[1] = 5;
		memcpy(&tmp, &G, sizeof(struct gameState));
		testMinion(0, 0, choice1, choice2, &G);
		assertTrue(tmp.handCount[1], G.handCount[1]);
		printf("Test: Other players hand count changed.");
	}

	//hard coded tests of opponent with fewer than 5 cards
	for (int i = 0; i < 10; i++) {
		int seed = rand() % 1000;
		int choice1 = rand() % 2;
		int choice2 = 0;
		if (!choice1) {
			choice2 = 1;
		}
		printf("\nStarting new round of tests - Opponent has 4 cards already\n");
		initializeGame(2, k, seed, &G);
		G.handCount[1] = 3;
		memcpy(&tmp, &G, sizeof(struct gameState));
		testMinion(0, 0, choice1, choice2, &G);
		assertTrue(G.handCount[1], 3);
		printf("Test: Other players hand count did not change.");
	}

}
