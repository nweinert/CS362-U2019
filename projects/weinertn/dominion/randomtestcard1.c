/* -----------------------------------------------------------------------
* Random Test for Baron function
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

int getDiscardEstates(struct gameState *state, int currentPlayer) {

	int discardEstates = 0;
	for (int i = 0; i < state->discardCount[currentPlayer]; i++) {
		if (state->discard[currentPlayer][i] == estate) {
			discardEstates++;
		}
	}
	return discardEstates;
}

int getNumEstates(struct gameState *state, int currentPlayer) {

	int numEstates = 0;
	for (int i = 0; i < numHandCards(state); i++) {
		if (state->hand[currentPlayer][i] == estate) {
			numEstates++;
		}
	}
	return numEstates;
}

int testBaron(int choice1, struct gameState *state, int currentPlayer) {
	//choice1==1 is discard an estate

	struct gameState preTest;
	memcpy(&preTest, state, sizeof(struct gameState));

	int returnVal = baronEffect(choice1, state, currentPlayer);

	assertTrue(preTest.numBuys + 1, state->numBuys);
	printf("TEST: 1 more buy.\n");

	//Discard estate
	if (choice1 == 1 && getNumEstates(&preTest, currentPlayer) > 0) {
		printf("Discarding Estate\n");
		assertTrue(getNumEstates(&preTest, currentPlayer) - 1, getNumEstates(state, currentPlayer));
		printf("TEST: 1 fewer estate in hand.\n");
		assertTrue(preTest.coins + 4, state->coins);
		printf("TEST: Coins + 4.\n");
		assertTrue(getDiscardEstates(&preTest, currentPlayer) + 1, getDiscardEstates(state, currentPlayer));
		printf("TEST: 1 more estate in discard pile.\n");
	}
	//gain estate
	else {
		printf("Gaining Estate\n");
		assertTrue(getNumEstates(&preTest, currentPlayer) + 1, getNumEstates(state, currentPlayer));
		printf("TEST: 1 more estate in hand.\n");
		assertTrue(preTest.coins, state->coins);
		printf("TEST: Coins unchanged.\n");
		assertTrue(supplyCount(1, &preTest) - 1, supplyCount(1, state));
		printf("TEST: 1 fewer estate in supply pile.\n");
	}

	return returnVal;

}

int main() {

	struct gameState G;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };
	srand(time(0));

	printf("Tests for BARON\n");

	PutSeed(3);
	SelectStream(2);

	for (int i = 0; i < 2000; i++) {
		int posNeg = floor(Random() * 2);
		for (int j = 0; j < sizeof(struct gameState); j++) {
			((char*)&G)[i] = floor(Random() * 256);
		}
		//initializing all the cards in the supply
		for (int j = 0; j < 27; j++) {
			G.supplyCount[j] = floor(Random() * 10);
		}
		//initializing numBuys and coins
		G.numBuys = floor(Random() * 256);
		G.coins = floor(Random() * 256);
		if (posNeg == 1) {
			G.numBuys *= -1;
			G.coins *= -1;
		}
		int choice1 = floor(Random() * 2);
		int player = floor(Random() * 3 + 2);
		G.handCount[player] = 0;
		G.deckCount[player] = 0;
		G.discardCount[player] = 0;
		G.whoseTurn = player;
		//initializing handCount and hand
		for (int j = 0; j < floor(Random() * 500); j++) {
			int supplyPos = floor(Random() * 27);
			gainCard(supplyPos, &G, 2, player);
		}

		testBaron(choice1, &G, player);
	}/*
	//hard coded tests of empty supply 
	for (int i = 0; i < 10; i++) {
		int seed = rand() % 1000;
		int choice = rand() % 2;
		printf("\nStarting new round of tests.\n");
		initializeGame(2, k, seed, &G);

		for (int j = 0; j < supplyCount(estate, &G) * 8; j++) {
			gainCard(1, &G, 0, 0);
		}

		testBaron(choice, &G, 0);
	}*/

}
