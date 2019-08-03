/* -----------------------------------------------------------------------
* Unit Test for Ambassador function
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

int cardCounter(int card, int currentPlayer, struct gameState *state) {

	int count = 0;
	for (int i = 0; i < state->handCount[currentPlayer]; i++) {
		if (state->hand[currentPlayer][i] == card) {
			count++;
		}
	}
	return count;
}

int testAmbassador(int choice1, int choice2, int currentPlayer, struct gameState *state, int handPos, int numPlayers) {
	int revealedCard = choice1;
	int curPlayerCardCount = cardCounter(revealedCard, currentPlayer, state);
	int curPlayerHand = state->handCount[currentPlayer];
	int othPlayerCardCount = cardCounter(revealedCard, 1, state);
	int othPlayerHand = state->handCount[1];
	int suppCount = supplyCount(choice1, state);

	int returnVal = ambassadorEffect(choice1, choice2, currentPlayer, state, handPos);

	assertTrue(curPlayerHand - choice2, state->handCount[currentPlayer]);
	printf("TEST: Current player has chosen number fewer cards in hand\n");	
	assertTrue(curPlayerCardCount - choice2, cardCounter(revealedCard, currentPlayer, state));
	printf("TEST: Current player has chosen number fewer of chosen card\n");
	assertTrue(othPlayerHand + 1, state->handCount[1]);
	printf("TEST: Other player has 1 more card in hand\n");
	assertTrue(othPlayerCardCount + 1, cardCounter(revealedCard, 1, state));
	printf("TEST: Current player has 1 more of chosen card\n");

	assertTrue(suppCount + choice2 - numPlayers, supplyCount(choice1, state));
	printf("TEST: Supply has appropriate number of cards\n");

	return returnVal;
}

int main() {

	struct gameState G, tmp;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };
	srand(time(0));


	printf("\n\n\n\n\nTests for AMBASSADOR\n");
	//Random test of basic card functionality	
	for (int i = 0; i < 50; i++) {
		int seed = rand() % 1000;
		int choice2 = rand() % 2 + 1;

		printf("\nStarting new round of tests.\n");
		initializeGame(2, k, seed, &G);
		int choice1 = G.hand[0][0];
		memcpy(&tmp, &G, sizeof(struct gameState));
		testAmbassador(choice1, choice2, 0, &G, 0, 2);

	}

	return 0;
}
