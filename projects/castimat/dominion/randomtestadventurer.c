#include "myassert.h"
#include <stdio.h>
#include <string.h> 
#include <unistd.h> 
#include <math.h>
#include <stdlib.h>
#include "dominion.h"
#include "rngs.h"

#define TESTS 5000 

int main(){
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int k[10] = {adventurer, council_room, embargo, village, minion, mine, cutpurse, 
	       sea_hag, tribute, smithy};
	int  i;
	int numPlayers = 2;
	int thisPlayer = 0;
	int opponent = 1; 
	int oppAfterHandCount, oppAfterDeckCount, oppAfterDiscardCount;
	int seed = 1000; 
    int treasure[3] = {silver, gold, copper};
    struct gameState G, testG;
    int temphand[MAX_HAND];
    int cardDrawn;
    int drawntreasure = 0, z = 0;
    int randPick;
    int randCard; 
    
	printf ("\nTESTING ADVENTURER\n");

    // Set default to passed
	int handCountpassed = 1; 
	int actionCountpassed = 1;
	int deckCountPassed = 1; 
	int discardCountPassed = 1;
    int treasurePassed = 1;
    int copperPassed = 1;
    int silverPassed = 1;
    int goldPassed = 1; 
	
	int oppHandCountpassed = 1; 
	int oppDeckCountPassed = 1; 
	int oppDiscardCountPassed = 1;

    for (i = 0; i < TESTS; i++) {

        // Initialize the game state and player cards
        initializeGame(numPlayers, k, seed, &G);

        // Randomize deck 
        for (int i = 0; i < G.deckCount[0]; i++) {
            randPick = rand() % 2; 

            if (randPick == 0) {
                randPick = rand() % 9 + 1;
                G.deck[0][i] = k[randPick];
            }
            else {
                randPick = rand() % 3;
                G.deck[0][i] = treasure[randPick];
            }
        }

        // Randomly set hand
        for (int i = 0; i < G.handCount[0]; i++) {
            if (i == 0)
                G.hand[0][i] = adventurer;
            else {
                randCard = rand() % 9 + 1; 
                G.hand[0][i] = k[randCard];
            }
        }

        // add a treasure card
        for (int i = 0; i < 5; i++) {
            randPick = rand() % 3;
            gainCard(treasure[randPick], &G, 1, thisPlayer);
        }

        // Shuffle deck 
        shuffle(0, &G);

        // Copy the game state to a test case
        memcpy(&testG, &G, sizeof(struct gameState));

        // Recreate Adventure Game
        while (drawntreasure < 2) {
        
            if (G.deckCount[0] < 1){ //if the deck is empty we need to shuffle discard and add to deck
                shuffle(0, &G);
            }

            drawCard(0, &G); 

            cardDrawn = G.hand[0][G.handCount[0]-1]; //top card of hand is most recently drawn card.
            
            if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) 
                drawntreasure++;
            else  {
                temphand[z] = cardDrawn;
                G.handCount[0]--; //this should just remove the top card (the most recently drawn one).
                z++;
            }
        }

        while(z - 1 >= 0) {
            G.discard[0][G.discardCount[0]++] = temphand[z - 1]; // discard all cards in play that have been drawn
            z=z-1;
        }

        // Play adventurer card for testing
        cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

        int originalTreasureCount = 0, testTreasureCount = 0; 
        int originalcopperCount = 0, testcopperCount = 0;
        int originalsilverCount = 0, testsilverCount = 0;
        int originalgoldCount = 0, testgoldCount = 0;

        for (int i = 0; i < testG.handCount[0]; i++) {
            if (testG.hand[0][i] == copper || testG.hand[0][i] == silver || testG.hand[0][i] == gold )
                testTreasureCount++;
            if (testG.hand[0][i] == copper)
                testcopperCount++;
            if (testG.hand[0][i] == silver)
                testsilverCount++;
            if (testG.hand[0][i] == gold)
                testgoldCount++;
        }

        for (int i = 0; i < G.handCount[0]; i++) {
            if (G.hand[0][i] == copper || G.hand[0][i] == silver || G.hand[0][i] == gold)
                originalTreasureCount++;
            if (G.hand[0][i] == copper)
                originalcopperCount++;
            if (G.hand[0][i] == silver)
                originalsilverCount++;
            if (G.hand[0][i] == gold)
                originalgoldCount++;
        }

        // Opponent
		oppAfterHandCount = G.handCount[opponent];
		oppAfterDeckCount = G.deckCount[opponent]; 	
		oppAfterDiscardCount = G.discardCount[opponent];

        myAssert(testTreasureCount, originalTreasureCount, &treasurePassed); 
        myAssert(testcopperCount, originalcopperCount, &copperPassed);
        myAssert(testsilverCount, originalsilverCount, &silverPassed);
        myAssert(testgoldCount, originalgoldCount, &goldPassed);
        myAssert(testG.handCount[0], G.handCount[0] - 1, &handCountpassed);
		myAssert(testG.deckCount[0], G.deckCount[0], &deckCountPassed);
        myAssert(testG.numActions, G.numActions, &actionCountpassed);

        // Opponent assert
		myAssert(testG.handCount[opponent], oppAfterHandCount, &oppHandCountpassed);
		myAssert(testG.deckCount[opponent], oppAfterDeckCount, &oppDeckCountPassed);
		myAssert(testG.discardCount[opponent], oppAfterDiscardCount, &oppDiscardCountPassed);
    }


    // Validate 1st player's results
	printf("1st Player\n");
    printf("Draw until 2 treasures then discard other cards\n");

    printf("Treasure: ");
    if (treasurePassed)
		printf("Passed\n");
	else
		printf("Failed\n");

    printf("Copper: ");
    if (copperPassed)
		printf("Passed\n");
	else
		printf("Failed\n");

    printf("Silver: ");
    if (silverPassed)
		printf("Passed\n");
	else
		printf("Failed\n");

    printf("Gold: ");
    if (goldPassed)
		printf("Passed\n");
	else
		printf("Failed\n");

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
    printf("Nothing\n");
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
  	
	printf("-- RANDOM TEST FOR ADVENTURER COMPLETE -- \n\n");
	
	return 0;
}