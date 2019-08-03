/* -----------------------------------------------------------------------
* Unit Test for endTurn function
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


int testEndTurn(struct gameState *state, int numPlayers) {

	int player = state->whoseTurn;
	int deckNum = state->deckCount[state->whoseTurn];
	int nextPlayer = 0;
	if (player == numPlayers) {
		nextPlayer = 0;
	}
	else {
		nextPlayer = player + 1;
	}
	int nextDeckCount = state->deckCount[nextPlayer];

	int returnVal = endTurn(state);

	assertTrue(deckNum, state->deckCount[player]);
	printf("TEST: Ending deck unchanged.\n");

	assertTrue(nextDeckCount, state->deckCount[state->whoseTurn]);
	printf("TEST: Next deck unchanged.\n");

	assertTrue(nextPlayer, state->whoseTurn);
	printf("TEST: Incremented turn properly.\n");

	assertTrue(state->numActions, 1);
	printf("TEST: Turn contains 1 action.\n");

	assertTrue(numHandCards(state), 5);
	printf("TEST: Turn contains 5 cards in next hand.\n");

	int money = 0;
	for (int i = 0; i < numHandCards(state); i++) {
		if (state->hand[state->whoseTurn][i] == copper) {
			money++;
		}
		else if (state->hand[state->whoseTurn][i] == silver) {
			money += 2;
		}
		else if (state->hand[state->whoseTurn][i] == gold) {
			money += 3;
		}
	}

	assertTrue(money, state->coins);
	printf("TEST: Correct number of coins in next hand.\n");

	return returnVal;
}

int main() {

	struct gameState G;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };
	srand(time(0));

	int seed = rand() % 1000;

	printf("\n\n\nTESTING ENDTURN FUNCTION\n\n\n");

	for (int i = 0; i < 20; i++) {
		int numPlayers = rand() % 3 + 2;
		initializeGame(numPlayers, k, seed, &G);
		for (int j = 0; j < 20; j++) {
			int card = rand() % 20 + 1;
			gainCard(card, &G, 1, 0);
		}
		while (G.handCount[0] > 0)
		{
			discardCard(0, 0, &G, 0);
		}
		for (int j = 0; j < 5; j++) {
			drawCard(0, &G);
		}

		testEndTurn(&G, numPlayers);
	}

	return 0;
}
