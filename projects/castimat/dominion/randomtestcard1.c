#include "myassert.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h> 
#include "dominion.h"
#include "rngs.h"

#define TESTS 5000 

int main(){
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int k[10] = {adventurer, council_room, embargo, village, minion, mine, cutpurse, 
	       sea_hag, tribute, smithy};
	int  i, handCount, deckCount, afterHandCount, afterDeckCount;
	int discardCount, afterDiscardCount, actionCount, afterActionCount; 
	int numPlayers = 2;
	int thisPlayer = 0;
	int opponent = 1; 
	int oppAfterHandCount, oppAfterDeckCount, oppAfterDiscardCount;
	int buyCard, afterBuyCard;
	int seed = 1000; 

	// Create different states
	struct gameState G1;
	struct gameState test1;

	printf ("\nTESTING COUNCIL ROOM\n");
	
	// Set default to passed
	int handCountpassed = 1; 
	int actionCountpassed = 1;
	int deckCountPassed = 1; 
	int discardCountPassed = 1;
	int buyCountPassed = 1;
	
	int oppHandCountpassed = 1; 
	int oppDeckCountPassed = 1; 
	int oppDiscardCountPassed = 1;

	for(i = 0; i < TESTS; i++) {

		initializeGame(numPlayers, k, seed, &G1);
		
		G1.deckCount[thisPlayer] = rand() % MAX_DECK;
		G1.discardCount[thisPlayer] = rand() % MAX_DECK;
		G1.handCount[thisPlayer] = rand() % MAX_HAND;

		G1.deckCount[opponent] = rand() % MAX_DECK;
		G1.discardCount[opponent] = rand() % MAX_DECK;
		G1.handCount[opponent] = rand() % MAX_HAND;

		// Copy the game state to a test case
		memcpy(&test1, &G1, sizeof(struct gameState));
		
		cardEffect(council_room, choice1, choice2, choice3, &G1, handpos, &bonus);

		// Current Player
		afterHandCount = G1.handCount[thisPlayer];
		afterDeckCount = G1.deckCount[thisPlayer]; 	
		afterDiscardCount = G1.discardCount[thisPlayer];
		afterActionCount = G1.numActions; 
		afterBuyCard = G1.numBuys; 

		handCount = test1.handCount[thisPlayer] + 3;
		deckCount = test1.deckCount[thisPlayer] - 4; 
		discardCount = test1.discardCount[thisPlayer] + 1;
		actionCount = test1.numActions; 
		buyCard = test1.numBuys + 1; 

		// Opponent
		oppAfterHandCount = G1.handCount[opponent];
		oppAfterDeckCount = G1.deckCount[opponent]; 	
		oppAfterDiscardCount = G1.discardCount[opponent];

		// Current player assert
       	myAssert(handCount, afterHandCount, &handCountpassed);
		myAssert(deckCount, afterDeckCount, &deckCountPassed);
		myAssert(buyCard, afterBuyCard, &buyCountPassed);
		myAssert(discardCount, afterDiscardCount, &discardCountPassed);
		myAssert(actionCount, afterActionCount, &actionCountpassed);

		// Opponent assert
		myAssert(test1.handCount[opponent] + 1, oppAfterHandCount, &oppHandCountpassed);
		myAssert(test1.deckCount[opponent] - 1, oppAfterDeckCount, &oppDeckCountPassed);
		myAssert(test1.discardCount[opponent], oppAfterDiscardCount, &oppDiscardCountPassed);
		
	}

	// Validate 1st player's results
	printf("1st Player\n");
    printf("+4 draw; +1 buy\n");
	printf("HandCount: ");
	if (handCountpassed)
		printf("Passed\n");
	else
		printf("Failed\n");

	printf("DeckCount: ");
	if (deckCountPassed)
		printf("Passed\n");
	else
		printf("Failed\n");	

	printf("BuyCount: ");
	if (buyCountPassed)
		printf("Passed\n");
	else
		printf("Failed\n");

	printf("DiscardCount: ");
	if (discardCountPassed)
		printf("Passed\n");
	else
		printf("Failed\n");	

	printf("ActionCount: ");
	if (actionCountpassed)
		printf("Passed\n");
	else
		printf("Failed\n");	

	// Validate opponents results
	printf("\nOPPONENT\n");
    printf("+1 draw\n");
	printf("Opponent HandCount: ");
	if (oppHandCountpassed)
		printf("Passed\n");
	else
		printf("Failed\n");

	printf("Opponent DeckCount: ");
	if (oppDeckCountPassed)
		printf("Passed\n");
	else
		printf("Failed\n");	

	printf("Opponent DiscardCount: ");
	if (oppDiscardCountPassed)
		printf("Passed\n");
	else
		printf("Failed\n");	
	
	printf("-- RANDOM TEST FOR COUNCIL ROOM COMPLETE -- \n\n");
	
	return 0;
}