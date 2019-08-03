/* -----------------------------------------------------------------------
* Unit Test for Minion function
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
	struct gameState preTest;
	memcpy(&preTest, state, sizeof(struct gameState));

	int returnVal = minionEffect(choice1, choice2, currentPlayer, state, &state->coins, handPos);

	assertTrue(preTest.numActions + 1, state->numActions);
	printf("TEST: 2 more coins.\n");

	//Discard estate
	if (choice1 == 1) {
		printf("+2\n");
		assertTrue(preTest.coins + 2, state->coins);
		printf("TEST: 2 more coins.\n");
	}
	//gain estate
	else {
		printf("New Hand\n");
		assertTrue(state->handCount[currentPlayer], 4);
		printf("TEST: 4 cards in hand.\n");
		assertTrue(state->handCount[currentPlayer + 1], 4);
		printf("TEST: 4 cards in opponents hand.\n");
		assertTrue(state->deckCount[currentPlayer], preTest.deckCount[currentPlayer]);
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
	for (int i = 0; i < 2000; i++) {
		int posNeg = floor(Random() * 2);
		for (int j = 0; j < sizeof(struct gameState); j++) {
			((char*)&G)[i] = floor(Random() * 256);
		}

		//initializing numBuys and coins
		G.numBuys = floor(Random() * 256);
		G.coins = floor(Random() * 256);
		if (posNeg == 1) {
			G.numBuys *= -1;
			G.coins *= -1;
		}
		//initializing all the cards in the supply
		for (int j = 0; j < 27; j++) {
			G.supplyCount[j] = floor(Random() * 500);
		}

		int choice1 = floor(Random() * 2);
		int player = ((int)floor(Random() * 500) % 3) + 2;
		G.numPlayers = player;
		//randomly initialize player's cards
		for (int j = 0; j <= player; j++) {
			G.handCount[j] = 0;
			G.deckCount[j] = 0;
			G.discardCount[j] = 0;
			int limit = floor(Random() * 500);
			for (int k = 0; k < limit; k++) {
				int supplyPos = floor(Random() * 27);
				int toFlag = floor(Random() * 3);
				gainCard(supplyPos, &G, toFlag, j);
			}
		}
		int choice2 = floor(Random() * G.handCount[player]);
		G.playedCardCount = 0;
		G.whoseTurn = player;
		//initializing handCount and hand


		testMinion(0, player, choice1, choice2, &G);
	}

}
