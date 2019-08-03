/* -----------------------------------------------------------------------
* Unit Test for Shuffle function
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


int compare2(const void* a, const void* b) {
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


int testShuffle(int player, struct gameState *state) {

	int newDeck[MAX_DECK];
	int nextPlayerDeck[MAX_DECK];
	int comp = 0;
	int deckCount = state->deckCount[player];

	for (int i = 0; i < state->deckCount[player + 1]; i++) {
		nextPlayerDeck[i] = state->deck[player + 1][i];
	}

	for (int i = 0; i < state->deckCount[player]; i++) {
		newDeck[i] = state->deck[player][i];
	}

	int returnVal = shuffle(player, state);

	assertTrue(deckCount, state->deckCount[player]);
	printf("TEST: Number of cards in deck unchanged.\n");

	if (deckCount == state->deckCount[player]) {
		for (int i = 0; i < deckCount; i++) {
			if (newDeck[i] != state->deck[player][i]) {
				comp++;
			}
		}
	}

	if (comp > 0) {
		assertTrue(comp, comp);
		printf("TEST: Cards not in same order.\n");
	}
	else {
		assertTrue(comp, 1);
		printf("TEST: Cards not in same order.\n");
	}

	qsort((void*)(state->deck[player]), state->deckCount[player], sizeof(int), compare2);
	qsort((void*)(newDeck), deckCount, sizeof(int), compare2);
	int failed = 0;
	for (int i = 0; i < state->deckCount[player]; i++) {
		if (newDeck[i] != state->deck[player][i]) {
			failed = 1;
		}
	}

	assertTrue(failed, 0);
	printf("TEST: Same cards in deck.\n");

	failed = 0;
	for (int i = 0; i < state->deckCount[player]; i++) {
		if (nextPlayerDeck[i] != state->deck[player + 1][i]) {
			failed = 1;
		}
	}

	assertTrue(failed, 0);
	printf("TEST: Next player's deck unchanged.\n");

	return returnVal;
}

int main() {

	struct gameState G;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };
	srand(time(0));

	int seed = rand() % 1000;

	printf("\n\n\nTESTING SHUFFLE FUNCTION\n\n\n");
	initializeGame(3, k, seed, &G);

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

	testShuffle(0, &G);


	return 0;
}
