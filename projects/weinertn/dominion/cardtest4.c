/* -----------------------------------------------------------------------
* Unit Test for getWinners function
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


int testGetWinners(struct gameState *state, int numPlayers) {

	int highScore = 0;
	int winner = 0;
	int players[MAX_PLAYERS];

	for (int i = 0; i < numPlayers; i++) {
		if (i > state->whoseTurn) {
			if (scoreFor(i, state) + 1 >= highScore) {
				highScore = scoreFor(i, state) + 1;
				winner = i;
			}
		}
		else {
			if (scoreFor(i, state) + 1 >= highScore) {
				highScore = scoreFor(i, state) + 1;
				winner = i;
			}
		}
	}
	
	int returnVal = getWinners(players, state);

	for (int i = 0; i < MAX_PLAYERS; i++) {
		if (players[i] == 1) {
			assertTrue(i, winner);
			printf("TEST: Winner is the right winner.\n");
		}
		else if (i > numPlayers) {
			assertTrue(players[i], 0);
			printf("TEST: Non players didn't win.\n");
		}
	}

	return returnVal;
}

int main() {

	struct gameState G;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };
	srand(time(0));

	int seed = rand() % 1000;

	printf("\n\n\nTESTING GETWINNERS FUNCTION\n\n\n");

	for (int i = 0; i < 20; i++) {
		printf("Starting new test\n");
		int numPlayers = rand() % 3 + 2;
		initializeGame(numPlayers, k, seed, &G);
		for (int x = 0; x < numPlayers; x++) {
			for (int j = 0; j < 20; j++) {
				int card = rand() % 20 + 1;
				gainCard(card, &G, 1, x);
			}
			while (G.handCount[x] > 0)
			{
				discardCard(0, x, &G, 0);
			}
			for (int j = 0; j < 5; j++) {
				drawCard(x, &G);
			}
		}
		testGetWinners(&G, numPlayers);
	}

	return 0;
}
