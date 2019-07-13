/* -----------------------------------------------------------------------
* Unit Test for Mine function
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

int testMine(int choice1, int choice2, int currentPlayer, int handPos, struct gameState *state) {

	int deckCount = state->deckCount[currentPlayer];
	int handCount = state->handCount[currentPlayer];
	int othPlayerDeckCount = state->deckCount[1];
	int othPlayerHandCount = state->handCount[1];
	int copperCount = cardCounter(copper, currentPlayer, state);
	int silverCount = cardCounter(silver, currentPlayer, state);
	int goldCount = cardCounter(gold, currentPlayer, state);

	int trashCard = state->hand[currentPlayer][choice1];
	/*int trashCardCost = 0;
	if (trashCard >= copper && trashCard <= gold) {
		if (trashCard == copper) {
			trashCardCost = 1;
		}
		else if (trashCard == silver) {
			trashCardCost = 3;
		}
		else {
			trashCardCost = 6;
		}
	}*/

	int gainCard = choice2;
	/*int gainCardCost = 0;
	if (gainCard >= copper && gainCard <= gold) {
		if (gainCard == copper) {
			gainCardCost = 1;
		}
		else if (gainCard == silver) {
			gainCardCost = 3;
		}
		else {
			gainCardCost = 6;
		}
	}*/

	int returnVal = mineEffect(choice1, choice2, currentPlayer, handPos, state);

	if (gainCard < copper || gainCard > gold) {
		assertTrue(returnVal, -1);
		printf("TEST: Adding NON TREASURE card.\n");
	}	
	if (trashCard < copper || trashCard > gold) {
		assertTrue(returnVal, -1);
		printf("TEST: Trashing NON TREASURE card.\n");
	}


	assertTrue(handCount, state->handCount[currentPlayer]);
	printf("TEST: Current player has same number of cards in hand\n");	
	assertTrue(othPlayerHandCount, state->handCount[1]);
	printf("TEST: Other player has same number of cards in hand\n");	
	assertTrue(deckCount, state->deckCount[currentPlayer]);
	printf("TEST: Current player has same number of cards in deck\n");	
	assertTrue(othPlayerDeckCount, state->deckCount[1]);
	printf("TEST: Other player has same number of cards in deck\n");

	//Trashing a copper
	if (trashCard == copper && gainCard == copper) {
		printf("TRASHED COPPER, ADDED COPPER\n");
		assertTrue(copperCount, cardCounter(copper, currentPlayer, state));
		printf("TEST: Number of copper cards in hand unchanged.\n");
		assertTrue(silverCount, cardCounter(silver, currentPlayer, state));
		printf("TEST: Number of silver cards in hand unchanged.\n");
		assertTrue(goldCount, cardCounter(gold, currentPlayer, state));
		printf("TEST: Number of gold cards in hand unchanged.\n");
	}
	else if (trashCard == copper && gainCard == silver) {
		printf("TRASHED COPPER, ADDED SILVER\n");
		assertTrue(copperCount - 1, cardCounter(copper, currentPlayer, state));
		printf("TEST: Number of copper cards in hand decreased by 1.\n");
		assertTrue(silverCount + 1, cardCounter(silver, currentPlayer, state));
		printf("TEST: Number of silver cards in hand increased by 1.\n");
		assertTrue(goldCount, cardCounter(gold, currentPlayer, state));
		printf("TEST: Number of gold cards in hand unchanged.\n");
	}
	else if (trashCard == copper && gainCard == gold) {
		printf("TRASHED COPPER, ADDED GOLD\n");
		assertTrue(copperCount, cardCounter(copper, currentPlayer, state));
		printf("TEST: Number of copper cards in hand unchanged.\n");
		assertTrue(silverCount, cardCounter(silver, currentPlayer, state));
		printf("TEST: Number of silver cards in hand unchanged.\n");
		assertTrue(goldCount, cardCounter(gold, currentPlayer, state));
		printf("TEST: Number of gold cards in hand unchanged.\n");
	}
	//Trashing a silver
	if (trashCard == silver && gainCard == copper) {
		printf("TRASHED SILVER, ADDED COPPER\n");
		assertTrue(copperCount + 1, cardCounter(copper, currentPlayer, state));
		printf("TEST: Number of copper cards in hand increased by 1.\n");
		assertTrue(silverCount - 1, cardCounter(silver, currentPlayer, state));
		printf("TEST: Number of silver cards in hand decreased by 1.\n");
		assertTrue(goldCount, cardCounter(gold, currentPlayer, state));
		printf("TEST: Number of gold cards in hand unchanged.\n");
	}
	else if (trashCard == silver && gainCard == silver) {
		printf("TRASHED SILVER, ADDED SILVER\n");
		assertTrue(copperCount, cardCounter(copper, currentPlayer, state));
		printf("TEST: Number of copper cards in hand unchanged.\n");
		assertTrue(silverCount, cardCounter(silver, currentPlayer, state));
		printf("TEST: Number of silver cards in hand unchanged.\n");
		assertTrue(goldCount, cardCounter(gold, currentPlayer, state));
		printf("TEST: Number of gold cards in hand unchanged.\n");
	}
	else if (trashCard == silver && gainCard == gold) {
		printf("TRASHED SILVER, ADDED GOLD\n");
		assertTrue(copperCount, cardCounter(copper, currentPlayer, state));
		printf("TEST: Number of copper cards in hand unchanged.\n");
		assertTrue(silverCount - 1, cardCounter(silver, currentPlayer, state));
		printf("TEST: Number of silver cards in hand decreased by 1.\n");
		assertTrue(goldCount + 1, cardCounter(gold, currentPlayer, state));
		printf("TEST: Number of gold cards in hand increased by 1.\n");
	}
	//Trashing a gold
	if (trashCard == gold && gainCard == copper) {
		printf("TRASHED GOLD, ADDED COPPER\n");
		assertTrue(copperCount + 1, cardCounter(copper, currentPlayer, state));
		printf("TEST: Number of copper cards in hand increased by 1.\n");
		assertTrue(silverCount, cardCounter(silver, currentPlayer, state));
		printf("TEST: Number of silver cards in hand unchanged.\n");
		assertTrue(goldCount - 1, cardCounter(gold, currentPlayer, state));
		printf("TEST: Number of gold cards in hand decreased by 1.\n");
	}
	else if (trashCard == gold && gainCard == silver) {
		printf("TRASHED GOLD, ADDED SILVER\n");
		assertTrue(copperCount, cardCounter(copper, currentPlayer, state));
		printf("TEST: Number of copper cards in hand unchanged.\n");
		assertTrue(silverCount + 1, cardCounter(silver, currentPlayer, state));
		printf("TEST: Number of silver cards in hand increased by 1.\n");
		assertTrue(goldCount - 1, cardCounter(gold, currentPlayer, state));
		printf("TEST: Number of gold cards in hand decreased by 1.\n");
	}
	else if (trashCard == gold && gainCard == gold) {
		printf("TRASHED GOLD, ADDED GOLD\n");
		assertTrue(copperCount, cardCounter(copper, currentPlayer, state));
		printf("TEST: Number of copper cards in hand unchanged.\n");
		assertTrue(silverCount, cardCounter(silver, currentPlayer, state));
		printf("TEST: Number of silver cards in hand unchanged.\n");
		assertTrue(goldCount, cardCounter(gold, currentPlayer, state));
		printf("TEST: Number of gold cards in hand unchanged.\n");
	}
	
	return returnVal;
}

int main() {

	struct gameState G;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };
	srand(time(0));


	printf("\n\n\n\n\nTests for MINE\n");
	//Random test of basic card functionality	
	for (int i = 0; i < 50; i++) {
		int seed = rand() % 1000;
		int choice2 = rand() % 11;


		printf("\nStarting new round of tests.\n");
		initializeGame(2, k, seed, &G);
				for (int j = 0; j < 20; j++) {
			int card = rand() % 3 + 4;
			gainCard(card, &G, 1, 0);
		}
		shuffle(0, &G);

		while (G.handCount[0] > 0)
		{
			discardCard(0, 0, &G, 0);
		}
		for (int j = 0; j < 5; j++) {
			drawCard(0, &G);
		}
		
		int choice1 = rand() % 6;

		testMine(choice1, choice2, 0, 0, &G);
	}




	return 0;
}
