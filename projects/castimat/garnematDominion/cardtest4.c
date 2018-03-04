/*
 * cardtest4.c
 * Tests Village card
 * +1 card, +2 action
 * 
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

int main() {
	int drawCard = 1;
    int discarded = 1;
	int addAction = 2;
    int xtraCoins = 0;
    int shuffledCards = 0;
	int estateCard = 0, duchyCard = 0, provinceCard = 0; 
	int copperCard = 0, silverCard = 0, goldCard = 0;

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	int opponent = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	
	// Initialize the game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("     Draws: %d card; Actions: +%d; Discards (self): %d\n\n", drawCard, addAction, discarded);

	// Copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	// Play village card for testing
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	// Get the state of the currrent user
	printf("Current player's state\n");

	// Validate that the hand counts are identical
	printf("Hand count = %d, expected = %d", testG.handCount[thisPlayer], G.handCount[thisPlayer] + drawCard);
	if (testG.handCount[thisPlayer] == G.handCount[thisPlayer] + drawCard)
		printf("  PASSED\n");
	else
		printf("  FAILED\n");

	// Validate that the deck count is identical
	printf("Deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - discarded + shuffledCards);

	// Validate that action count increased by 2
	printf("Actions = %d, expected = %d\n", testG.numActions, G.numActions + addAction);

	// Validate that discard pile increased by 1
	printf("Discard pile = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded);

	// Validate that no coins were added to user
	printf("Coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);

	// Validate victory card pile 
	printf("Estate Card = %d, expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate] - estateCard);
	printf("Duchy Card = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy] - duchyCard);
	printf("Province Card = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province] - provinceCard);

	// Validate treasure card pile 
	printf("Copper Card = %d, expected = %d\n", testG.supplyCount[copper], G.supplyCount[copper] - copperCard);
	printf("Silver Card = %d, expected = %d\n", testG.supplyCount[silver], G.supplyCount[silver] - silverCard);
	printf("Gold Card = %d, expected = %d\n", testG.supplyCount[gold], G.supplyCount[gold] - goldCard);

	/* Validate that the other user's state has not changed */
	// Check other player's hand count
	printf("\nOpponent player's state\n");
	printf("hand count = %d, expected = %d\n", testG.handCount[opponent], G.handCount[opponent]);

	// Check other player's deck count
	printf("Deck count = %d, expected = %d\n", testG.deckCount[opponent], G.deckCount[opponent]);

	// Check other player's discard count
	printf("Discard pile = %d, expected = %d\n", testG.discardCount[opponent], G.discardCount[opponent] + 0);

	// Check other player's coin count
	printf("Coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}


