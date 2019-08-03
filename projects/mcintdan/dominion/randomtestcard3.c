/* -----------------------------------------------------------------------
* Random Test for Tribute function
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

int testTribute(int revealedCard1, int revealedCard2, int currentPlayer, struct gameState *state) {

	struct gameState preTest;
	memcpy(&preTest, state, sizeof(struct gameState));

	int numCards = state->handCount[currentPlayer];
	int numActions = state->numActions;
	int money = state->coins;
	int fullDeck = state->deckCount[currentPlayer];
	int opponentDeckCount = state->deckCount[1];
	int opponentHandCount = state->handCount[1];

	int returnVal = tributeEffect(currentPlayer, state, &state->coins, 0);

	assertTrue(preTest.deckCount[currentPlayer - 1], state->deckCount[currentPlayer - 1]);
	printf("TEST: Opponent Deck unchanged\n");
	assertTrue(preTest.handCount[currentPlayer - 1] - 2, state->handCount[currentPlayer - 1]);
	printf("TEST: Opponent HandCount 2 fewer\n");

	if (revealedCard1 == revealedCard2) {
		printf("CARDS THE SAME\n");
		if (revealedCard1 == copper || revealedCard1 == silver || revealedCard1 == gold) {
			assertTrue(preTest.coins + 2, state->coins);
			printf("TEST: Cards the same (TREASURE) - 2 more coins.\n");
			assertTrue(preTest.deckCount[currentPlayer], state->deckCount[currentPlayer]);
			printf("TEST: Cards the same (TREASURE) - DeckCount unchanged.\n");
			assertTrue(preTest.handCount[currentPlayer], state->handCount[currentPlayer]);
			printf("TEST: Cards the same (TREASURE) - HandCount unchanged.\n");
			assertTrue(preTest.numActions, state->numActions);
			printf("TEST: Cards the same (TREASURE) - ActionCount unchanged.\n");
		}
		else if (revealedCard1 == estate || revealedCard1 == duchy || revealedCard1 == province || revealedCard1 == gardens || revealedCard1 == great_hall) {
			assertTrue(preTest.handCount[currentPlayer] + 2, state->handCount[currentPlayer]);
			printf("TEST: Cards the same (VICTORY) - 2 more cards.\n");
			assertTrue(preTest.deckCount[currentPlayer], state->deckCount[currentPlayer]);
			printf("TEST: Cards the same (VICTORY) - DeckCount unchanged.\n");
			assertTrue(preTest.coins, state->coins);
			printf("TEST: Cards the same (VICTORY) - Coins unchanged.\n");
			assertTrue(preTest.numActions, state->numActions);
			printf("TEST: Cards the same (VICTORY) - ActionCount unchanged.\n");
		}
		else {
			assertTrue(preTest.numActions + 2, state->numActions);
			printf("TEST: Cards the same (ACTION) - 2 more actions.\n");
			assertTrue(preTest.deckCount[currentPlayer], state->deckCount[currentPlayer]);
			printf("TEST: Cards the same (ACTION) - DeckCount unchanged.\n");
			assertTrue(preTest.coins, state->coins);
			printf("TEST: Cards the same (ACTION) - Coins unchanged.\n");
			assertTrue(preTest.handCount[currentPlayer], state->handCount[currentPlayer]);
			printf("TEST: Cards the same (ACTION) - HandCount unchanged.\n");
		}
	}
	else {
		printf("CARDS DIFFERENT\n");
		if (revealedCard1 == copper || revealedCard1 == silver || revealedCard1 == gold) {
			assertTrue(preTest.coins + 2, state->coins);
			printf("TEST: Cards the same (TREASURE) - 2 more coins.\n");
			assertTrue(preTest.deckCount[currentPlayer], state->deckCount[currentPlayer]);
			printf("TEST: Cards the same (TREASURE) - DeckCount unchanged.\n");
			assertTrue(preTest.handCount[currentPlayer], state->handCount[currentPlayer]);
			printf("TEST: Cards the same (TREASURE) - HandCount unchanged.\n");
			assertTrue(preTest.numActions, state->numActions);
			printf("TEST: Cards the same (TREASURE) - ActionCount unchanged.\n");
		}
		else if (revealedCard1 == estate || revealedCard1 == duchy || revealedCard1 == province || revealedCard1 == gardens || revealedCard1 == great_hall) {
			assertTrue(preTest.handCount[currentPlayer] + 2, state->handCount[currentPlayer]);
			printf("TEST: Cards the same (VICTORY) - 2 more cards.\n");
			assertTrue(preTest.deckCount[currentPlayer], state->deckCount[currentPlayer]);
			printf("TEST: Cards the same (VICTORY) - DeckCount unchanged.\n");
			assertTrue(preTest.coins, state->coins);
			printf("TEST: Cards the same (VICTORY) - Coins unchanged.\n");
			assertTrue(preTest.numActions, state->numActions);
			printf("TEST: Cards the same (VICTORY) - ActionCount unchanged.\n");
		}
		else {
			assertTrue(preTest.numActions + 2, state->numActions);
			printf("TEST: Cards the same (ACTION) - 2 more actions.\n");
			assertTrue(preTest.deckCount[currentPlayer], state->deckCount[currentPlayer]);
			printf("TEST: Cards the same (ACTION) - DeckCount unchanged.\n");
			assertTrue(preTest.coins, state->coins);
			printf("TEST: Cards the same (ACTION) - Coins unchanged.\n");
			assertTrue(preTest.handCount[currentPlayer], state->handCount[currentPlayer]);
			printf("TEST: Cards the same (ACTION) - HandCount unchanged.\n");
		}
		if (revealedCard2 == copper || revealedCard2 == silver || revealedCard2 == gold) {
			assertTrue(preTest.coins + 2, state->coins);
			printf("TEST: Cards the same (TREASURE) - 2 more coins.\n");
			assertTrue(preTest.deckCount[currentPlayer], state->deckCount[currentPlayer]);
			printf("TEST: Cards the same (TREASURE) - DeckCount unchanged.\n");
			assertTrue(preTest.handCount[currentPlayer], state->handCount[currentPlayer]);
			printf("TEST: Cards the same (TREASURE) - HandCount unchanged.\n");
			assertTrue(preTest.numActions, state->numActions);
			printf("TEST: Cards the same (TREASURE) - ActionCount unchanged.\n");
		}
		else if (revealedCard2 == estate || revealedCard2 == duchy || revealedCard2 == province || revealedCard2 == gardens || revealedCard2 == great_hall) {
			assertTrue(preTest.handCount[currentPlayer] + 2, state->handCount[currentPlayer]);
			printf("TEST: Cards the same (VICTORY) - 2 more cards.\n");
			assertTrue(preTest.deckCount[currentPlayer], state->deckCount[currentPlayer]);
			printf("TEST: Cards the same (VICTORY) - DeckCount unchanged.\n");
			assertTrue(preTest.coins, state->coins);
			printf("TEST: Cards the same (VICTORY) - Coins unchanged.\n");
			assertTrue(preTest.numActions, state->numActions);
			printf("TEST: Cards the same (VICTORY) - ActionCount unchanged.\n");
		}
		else {
			assertTrue(preTest.numActions + 2, state->numActions);
			printf("TEST: Cards the same (ACTION) - 2 more actions.\n");
			assertTrue(preTest.deckCount[currentPlayer], state->deckCount[currentPlayer]);
			printf("TEST: Cards the same (ACTION) - DeckCount unchanged.\n");
			assertTrue(preTest.coins, state->coins);
			printf("TEST: Cards the same (ACTION) - Coins unchanged.\n");
			assertTrue(preTest.handCount[currentPlayer], state->handCount[currentPlayer]);
			printf("TEST: Cards the same (ACTION) - HandCount unchanged.\n");
		}
	}

	return returnVal;
}

int main() {

	struct gameState G;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };
	srand(time(0));

	printf("\n\n\n\n\nTests for TRIBUTE\n");
	for (int i = 0; i < 2000; i++) {
		int posNeg = floor(Random() * 2);
		for (int j = 0; j < sizeof(struct gameState); j++) {
			((char*)&G)[i] = floor(Random() * 256);
		}
	//Random test of basic card functionality	
		int seed = rand() % 1000;
		int choice2 = rand() % 2 + 1;
		int numPlayers = rand() % 2 + 3;
		G.numPlayers = numPlayers;
		G.playedCardCount = 0;
		printf("\nStarting new round of tests.\n");
		//draw valid hands for our num player and previous player
		for (int k = numPlayers; k >= numPlayers - 1; k--) {
			G.handCount[k] = 0;
			for (int j = 0; j < 20; j++) {
				int card = rand() % 20 + 1;
				gainCard(card, &G, 1, k);
				G.deckCount[k] = j + 1;
			}
			G.handCount[k] = 0;
			for (int j = 0; j < 5; j++) {
				drawCard(k, &G);
				G.handCount[k] = j + 1;
			}
		}
		if(rand() % 5 == 0){
			G.handCount[numPlayers - 1] = 2;
			G.deckCount[numPlayers - 1] = rand() % 2;
			G.discardCount[numPlayers - 1] = rand() % 2;
		}
		int random = rand() % 3;
		int revealedCard1 = G.hand[numPlayers - 1][0];
		int revealedCard2 = G.hand[numPlayers - 1][1];
		if (random == 0) {
			revealedCard1 = revealedCard1;
		}

		testTribute(revealedCard1, revealedCard2, numPlayers, &G);
	}

	/*
	for (int i = 0; i < 10; i++) {
		int seed = rand() % 1000;
		int choice2 = rand() % 2 + 1;

		printf("\nStarting new round of tests.\n");
		initializeGame(2, k, seed, &G);
		shuffle(1, &G);

		while (G.deckCount[1] > 0)
		{
			drawCard(1, &G);
		}
		while (G.handCount[1] > 2)
		{
			discardCard(0, 1, &G, 0);
		}
		for (int j = 0; j < 2; j++) {
			drawCard(1, &G);
		}

		int random = rand() % 3;

		if (random == 0) {
			for (int j = 0; j < 5; j++) {
				int card = rand() % 20 + 1;
				gainCard(card, &G, 0, 1);
			}
		}

		int revealedCard1 = G.hand[1][0];
		int revealedCard2 = G.hand[1][1];
		if (random == 0) {
			revealedCard1 = revealedCard1;
		}

		testTribute(revealedCard1, revealedCard2, 0, &G);

	}*/

	return 0;
}
