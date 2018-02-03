/*
 * cardtest3.c
 * Tests council room card
 * +4 card, +1 Buy, other player draw 1 card
 * 
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Council Room"

int main() {
	int drawCard = 4;
	int buyCard = 1; 
    int discarded = 1;
	int addAction = 0;
    int xtraCoins = 0;
	int oppDraw = 1; 
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
	printf("     Draws: %d card; Actions: +%d; Discards (self): %d; Opponent Draws: %d card\n\n", drawCard, addAction, discarded, oppDraw);

	// Copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	// Play village card for testing
	cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);
	
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

	// Validate that buy increased by 1
	printf("Buys = %d, expected = %d\n", testG.numBuys, G.numBuys + buyCard);

	// Validate that action count increased by 0
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
	printf("hand count = %d, expected = %d\n", testG.handCount[opponent], G.handCount[opponent] + 1);

	// Check other player's deck count
	printf("Deck count = %d, expected = %d\n", testG.deckCount[opponent], G.deckCount[opponent] - oppDraw);

	// Check other player's discard count
	printf("Discard pile = %d, expected = %d\n", testG.discardCount[opponent], G.discardCount[opponent] + 0);

	// Check other player's coin count
	printf("Coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}


