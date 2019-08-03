/* -----------------------------------------------------------------------
* Unit Test for Baron function
* Include the following lines in your makefile:
*
* testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
*      gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
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

int testBaron(int choice1, int currentPlayer, struct gameState *state, int handPos) {
	//choice1==1 is discard an estate
	int oldBuys = state->numBuys;
	int numEstates = getNumEstates(state, currentPlayer);
	int discardEstates = getDiscardEstates(state, currentPlayer);
	int supplyEstates = supplyCount(1, state);
	int money = state->coins;


	int returnVal = baronEffect(choice1, currentPlayer, state, &money, handPos);
	
	assertTrue(oldBuys + 1, state->numBuys);
	printf("TEST: 1 more buy.\n");

	//Discard estate
	if (choice1 == 1 && numEstates > 0) {
		printf("Discarding Estate\n");
			assertTrue(numEstates - 1, getNumEstates(state, currentPlayer));
		printf("TEST: 1 fewer estate in hand.\n");
			assertTrue(money + 4, state->coins);
		printf("TEST: Coins + 4.\n");
			assertTrue(discardEstates + 1, getDiscardEstates(state,	currentPlayer));
		printf("TEST: 1 more estate in discard pile.\n");
	}
	//gain estate
	else {
		printf("Gaining Estate\n");
			assertTrue(numEstates, numEstates + 1);
		printf("TEST: 1 more estate in hand.\n");
			assertTrue(money, state->coins);
		printf("TEST: Coins unchanged.\n");
			assertTrue(supplyEstates - 1, supplyCount(1, state));
		printf("TEST: 1 fewer estate in supply pile.\n");
	}

	return returnVal;

}

int main() {

	struct gameState G, tmp;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };
	srand(time(0));

	printf("Tests for BARON\n");
	

	//Random test of basic card functionality	
	for (int i = 0; i < 30; i++) {
		int seed = rand() % 1000;
		int choice = rand() % 2;
		printf("\nStarting new round of tests.\n");
		initializeGame(2, k, seed, &G);
		memcpy(&tmp, &G, sizeof(struct gameState));
		testBaron(choice, 0, &G, 0);
		assertTrue(tmp.handCount[1], G.handCount[1]);
		printf("Test: Other players hand count did not change.");
	}

	//hard coded tests of empty supply 
	for(int i = 0; i < 10; i++){
		int seed = rand() % 1000;
		int choice = rand() % 2;
		printf("\nStarting new round of tests.\n");
		initializeGame(2, k, seed, &G);

		for(int j = 0; j < supplyCount(estate, &G) * 8; j++){
			gainCard(1, &G, 0, 0);
		}

		testBaron(choice, 0, &G, 0);
	}

}
