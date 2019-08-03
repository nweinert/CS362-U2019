/* -----------------------------------------------------------------------
* Unit Test for Tribute function
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

int testTribute(int revealedCard1, int revealedCard2, struct gameState *state, int currentPlayer) {

	int numCards = state->handCount[currentPlayer];
	int numActions = state->numActions;
	int money = state->coins;
	int fullDeck = state->deckCount[currentPlayer];
	int opponentDeckCount = state->deckCount[1];
	int opponentHandCount = state->handCount[1];

	int returnVal = tributeEffect(currentPlayer, state, &state->coins, 0);

	assertTrue(opponentDeckCount, state->deckCount[1]);
	printf("TEST: Opponent Deck unchanged\n");
	assertTrue(opponentHandCount - 2, state->handCount[1]);
	printf("TEST: Opponent HandCount 2 fewer\n");

	if (revealedCard1 == revealedCard2) {
		printf("CARDS THE SAME\n");
		if (revealedCard1 == copper || revealedCard1 == silver || revealedCard1 == gold) {
			assertTrue(money + 2, state->coins);
			printf("TEST: Cards the same (TREASURE) - 2 more coins.\n");
			assertTrue(fullDeck, state->deckCount[currentPlayer]);
			printf("TEST: Cards the same (TREASURE) - DeckCount unchanged.\n");
			assertTrue(numCards, state->handCount[currentPlayer]);
			printf("TEST: Cards the same (TREASURE) - HandCount unchanged.\n");
			assertTrue(numActions, state->numActions);
			printf("TEST: Cards the same (TREASURE) - ActionCount unchanged.\n");
		}
		else if (revealedCard1 == estate || revealedCard1 == duchy || revealedCard1 == province || revealedCard1 == gardens || revealedCard1 == great_hall) {
			assertTrue(numCards + 2, state->handCount[currentPlayer]);
			printf("TEST: Cards the same (VICTORY) - 2 more cards.\n");
			assertTrue(fullDeck, state->deckCount[currentPlayer]);
			printf("TEST: Cards the same (VICTORY) - DeckCount unchanged.\n");
			assertTrue(money, state->coins);
			printf("TEST: Cards the same (VICTORY) - Coins unchanged.\n");
			assertTrue(numActions, state->numActions);
			printf("TEST: Cards the same (VICTORY) - ActionCount unchanged.\n");
		}
		else {
			assertTrue(numActions + 2, state->numActions);
			printf("TEST: Cards the same (ACTION) - 2 more actions.\n");
			assertTrue(fullDeck, state->deckCount[currentPlayer]);
			printf("TEST: Cards the same (ACTION) - DeckCount unchanged.\n");
			assertTrue(money, state->coins);
			printf("TEST: Cards the same (ACTION) - Coins unchanged.\n");
			assertTrue(numCards, state->handCount[currentPlayer]);
			printf("TEST: Cards the same (ACTION) - HandCount unchanged.\n");
		}
	}
	else {
		printf("CARDS DIFFERENT\n");
		if (revealedCard1 == copper || revealedCard1 == silver || revealedCard1 == gold) {
			assertTrue(money + 2, state->coins);
			printf("TEST: First Card (TREASURE) - 2 more coins.\n");
			assertTrue(fullDeck, state->deckCount[currentPlayer]);
			printf("TEST: First Card (TREASURE) - DeckCount unchanged.\n");
			assertTrue(numCards, state->handCount[currentPlayer]);
			printf("TEST: First Card (TREASURE) - HandCount unchanged.\n");
			assertTrue(numActions, state->numActions);
			printf("TEST: First Card (TREASURE) - ActionCount unchanged.\n");
		}
		else if (revealedCard1 == estate || revealedCard1 == duchy || revealedCard1 == province || revealedCard1 == gardens || revealedCard1 == great_hall) {
			assertTrue(numCards + 2, state->handCount[currentPlayer]);
			printf("TEST: First Card (VICTORY) - 2 more cards.\n");
			assertTrue(fullDeck, state->deckCount[currentPlayer]);
			printf("TEST: First Card (VICTORY) - DeckCount unchanged.\n");
			assertTrue(money, state->coins);
			printf("TEST: First Card (VICTORY) - Coins unchanged.\n");
			assertTrue(numActions, state->numActions);
			printf("TEST: First Card (VICTORY) - ActionCount unchanged.\n");
		}
		else {
			assertTrue(numActions + 2, state->numActions);
			printf("TEST: First Card (ACTION) - 2 more actions.\n");
			assertTrue(fullDeck, state->deckCount[currentPlayer]);
			printf("TEST: First Card (ACTION) - DeckCount unchanged.\n");
			assertTrue(money, state->coins);
			printf("TEST: First Card (ACTION) - Coins unchanged.\n");
			assertTrue(numCards, state->handCount[currentPlayer]);
			printf("TEST: First Card (ACTION) - HandCount unchanged.\n");
		}
		if (revealedCard2 == copper || revealedCard2 == silver || revealedCard2 == gold) {
			assertTrue(money + 2, state->coins);
			printf("TEST: Second Card (TREASURE) - 2 more coins.\n");
			assertTrue(fullDeck, state->deckCount[currentPlayer]);
			printf("TEST: Second Card (TREASURE) - DeckCount unchanged.\n");
			assertTrue(numCards, state->handCount[currentPlayer]);
			printf("TEST: Second Card (TREASURE) - HandCount unchanged.\n");
			assertTrue(numActions, state->numActions);
			printf("TEST: Second Card (TREASURE) - ActionCount unchanged.\n");
		}
		else if (revealedCard2 == estate || revealedCard2 == duchy || revealedCard2 == province || revealedCard2 == gardens || revealedCard2 == great_hall) {
			assertTrue(numCards + 2, state->handCount[currentPlayer]);
			printf("TEST: Second Card (VICTORY) - 2 more cards.\n");
			assertTrue(fullDeck, state->deckCount[currentPlayer]);
			printf("TEST: Second Card (VICTORY) - DeckCount unchanged.\n");
			assertTrue(money, state->coins);
			printf("TEST: Second Card (VICTORY) - Coins unchanged.\n");
			assertTrue(numActions, state->numActions);
			printf("TEST: Second Card (VICTORY) - ActionCount unchanged.\n");
		}
		else {
			assertTrue(numActions + 2, state->numActions);
			printf("TEST: Second Card (ACTION) - 2 more actions.\n");
			assertTrue(fullDeck, state->deckCount[currentPlayer]);
			printf("TEST: Second Card (ACTION) - DeckCount unchanged.\n");
			assertTrue(money, state->coins);
			printf("TEST: Second Card (ACTION) - Coins unchanged.\n");
			assertTrue(numCards, state->handCount[currentPlayer]);
			printf("TEST: Second Card (ACTION) - HandCount unchanged.\n");
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
	//Random test of basic card functionality	
	for (int i = 0; i < 50; i++) {
		int seed = rand() % 1000;
		int choice2 = rand() % 2 + 1;

		printf("\nStarting new round of tests.\n");
		initializeGame(2, k, seed, &G);
		for (int j = 0; j < 20; j++) {
			int card = rand() % 20 + 1;
			gainCard(card, &G, 1, 1);
		}
		shuffle(1, &G);

		while (G.handCount[1] > 0)
		{
			discardCard(0, 1, &G, 0);
		}
		for (int j = 0; j < 5; j++) {
			drawCard(1, &G);
		}
		int random = rand() % 3;
		int revealedCard1 = G.hand[1][0];
		int revealedCard2 = G.hand[1][1];
		if (random == 0) {
			revealedCard1 = revealedCard1;
		}

		testTribute(revealedCard1, revealedCard2, &G, 0);
	}

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

		testTribute(revealedCard1, revealedCard2, &G, 1);

	}	

	return 0;
}
