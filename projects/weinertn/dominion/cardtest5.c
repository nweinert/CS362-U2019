/* -----------------------------------------------------------------------
* Unit Test for drawCard function
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

int compare3(const void* a, const void* b) {
	if (*(int*)a > *(int*)b)
		return 1;
	if (*(int*)a < *(int*)b)
		return -1;
	return 0;
}


void assertTrue(int test, int value) {
	if (test == value) {
		printf("PASSED\t");
	}
	else {
		printf("FAILED\t");
	}
}


int testDrawCard(struct gameState *state, int currentPlayer) {

	int deckCount = state->deckCount[currentPlayer];
	int handCount = state->handCount[currentPlayer];	
	int othDeckCount = state->deckCount[currentPlayer + 1];
	int othHandCount = state->handCount[currentPlayer + 1];
	int oldDeck[MAX_DECK];
	int newDeck[MAX_DECK];

	if (deckCount == 0) {
		for (int i = 0; i < state->discardCount[currentPlayer]; i++) {
			state->deck[currentPlayer][i] = state->discard[currentPlayer][i];
			state->discard[currentPlayer][i] = -1;
			state->deckCount[currentPlayer]++;
			state->discardCount[currentPlayer]--;
		}
	}
	for (int i = 0; i < deckCount; i++) {
		oldDeck[i] = state->deck[currentPlayer][i];
	}
	for (int i = 0; i < handCount; i++) {
		oldDeck[i + deckCount] = state->hand[currentPlayer][i];
	}

	int returnVal = drawCard(currentPlayer, state);

	for (int i = 0; i < state->deckCount[currentPlayer]; i++) {
		newDeck[i] = state->deck[currentPlayer][i];
	}
	for (int i = 0; i < state->handCount[currentPlayer]; i++) {
		newDeck[(i + state->deckCount[currentPlayer])] = state->hand[currentPlayer][i];
	}

	assertTrue(handCount + 1, state->handCount[currentPlayer]);
	printf("TEST: 1 more card in hand.\n");
	assertTrue(deckCount, state->deckCount[currentPlayer]);
	printf("TEST: Same number of cards in deck.\n");
	assertTrue(othHandCount, state->handCount[currentPlayer + 1]);
	printf("TEST: Other players hand unchanged.\n");
	assertTrue(othDeckCount, state->deckCount[currentPlayer + 1]);
	printf("TEST: Other players deck unchanged.\n");

	qsort((void*)(oldDeck), (deckCount + handCount), sizeof(int), compare3);
	qsort((void*)(newDeck), (state->deckCount[currentPlayer] + state->handCount[currentPlayer]), sizeof(int), compare3);

	int failure = 0;
	for (int i = 0; i < (deckCount + handCount); i++) {
		if (oldDeck[i] != newDeck[i]) {
			failure = 1;
		}
	}
	assertTrue(failure, 0);
	printf("TEST: Same cards in deck.\n");

	return returnVal;
}

int main() {

	struct gameState G;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };
	srand(time(0));

	int seed = rand() % 1000;

	printf("\n\n\nTESTING DRAWCARD FUNCTION\n\n\n");

	for (int i = 0; i < 20; i++) {
		printf("Starting new test\n");
		int numPlayers = rand() % 3 + 2;
		initializeGame(numPlayers, k, seed, &G);
		if (seed % 3 == 0) {
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
		}
		testDrawCard(&G, 0);
	}

	return 0;
}
