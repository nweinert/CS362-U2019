/* -----------------------------------------------------------------------
* Unit Test for Initialization function
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


void testInit(int numPlayers, int kingdomCards[10], int randomSeed, struct gameState *state, int dupKing) {

	int returnVal = initializeGame(numPlayers, kingdomCards, randomSeed, state);

	if (numPlayers > MAX_PLAYERS) {
		assertTrue(returnVal, -1);
		printf("TEST: too many players.\n");
	}
	if (numPlayers < 2) {
		assertTrue(returnVal, -1);
		printf("TEST: too few players.\n");
	}
	if (dupKing == 1) {
		assertTrue(returnVal, -1);
		printf("TEST: duplicate kingdom cards.\n");
	}

	if (returnVal != -1) {
		assertTrue(state->numPlayers, numPlayers);
		printf("TEST: Correct number of players allocated.\n");

		for (int i = 0; i < numPlayers; i++) {
			assertTrue(state->handCount[i], 5);
			printf("TEST: Player %d hand contains 5 cards.\n", i);
			assertTrue(state->deckCount[i], 10);
			printf("TEST: Player %d deck contains 10 cards.\n", i);
			assertTrue(fullDeckCount(i, copper, state), 7);
			printf("TEST: Player %d deck contains 7 copper cards.\n", i);
			assertTrue(fullDeckCount(i, estate, state), 3);
			printf("TEST: Player %d deck contains 3 estate cards.\n", i);
		}

		for (int i = 0; i < 10; i++) {
			if (state->numPlayers == 2) {
				assertTrue(supplyCount(kingdomCards[i], state), 8);
				printf("TEST: supply contains proper number of kingdom card %d.\n", i);
			}
			else {
				assertTrue(supplyCount(kingdomCards[i], state), 12);
				printf("TEST: supply contains proper number of kingdom card %d.\n", i);
			}

		}
		assertTrue(supplyCount(copper, state), 60 - (state->numPlayers * 7));
		printf("TEST: supply contains proper number of copper cards.\n");
		assertTrue(supplyCount(silver, state), 40);
		printf("TEST: supply contains proper number of silver cards.\n");
		assertTrue(supplyCount(gold, state), 30);
		printf("TEST: supply contains proper number of gold cards.\n");

		if (state->numPlayers == 2) {
			assertTrue(supplyCount(estate, state), 8);
			printf("TEST: supply contains proper number of estate cards.\n");
			assertTrue(supplyCount(duchy, state), 8);
			printf("TEST: supply contains proper number of duchy cards.\n");
			assertTrue(supplyCount(province, state), 8);
			printf("TEST: supply contains proper number of province cards.\n");
		}
		else {
			assertTrue(supplyCount(estate, state), 12);
			printf("TEST: supply contains proper number of estate cards.\n");
			assertTrue(supplyCount(duchy, state), 12);
			printf("TEST: supply contains proper number of duchy cards.\n");
			assertTrue(supplyCount(province, state), 12);
			printf("TEST: supply contains proper number of province cards.\n");
		}

	}


}

int main() {

	srand(time(0));


	printf("\n\n\nTESTING INITIALIZATION FUNCTION\n\n\n");
	for (int x = 0; x < 50; x++) {
		printf("\nNEW TEST \n\n");


		int k[10];
		struct gameState G;
		int randomTest = rand() % 3;
		int numPeople = 0;
		int seed = rand() % 1000;
		int dupKing = 0;

		//testing without duplicates and with proper number of people
		if (randomTest == 0) {	
			numPeople = rand() % 3 + 2;
			for (int i = 0; i < 10; i++) {
				k[i] = i + 8;
			}
		}
		//testing with duplicates
		else if(randomTest == 1) {
			numPeople = rand() % 3 + 2;
			for (int i = 0; i < 10; i++) {
				int random = rand() % 20 + 8;
				for (int j = 0; j < 10; j++) {
					if (random == k[j]) {
						dupKing = 1;
					}
				}
				k[i] = random;
			}
		}
		//testing without duplicates and with wrong number of people
		else {
			numPeople = rand() % 6;
			for (int i = 0; i < 10; i++) {
				k[i] = i + 8;
			}
		}

		testInit(numPeople, k, seed, &G, dupKing);
	}

	return 0;
}
