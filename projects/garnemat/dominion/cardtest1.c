#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define RESET   "\x1b[0m"


// testing Smithy Card
int main () {

	printf ("TESTING Smithy Card\n");

	struct gameState state, test_state;
	int seed = 1000;
  int numPlayers = 2;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int drawnCards = 3;
	int discard = 1;
	int failure = 0;
	int x, y;
	// initialize a game state and player cards
			 
	initializeGame(numPlayers, k, seed, &state);
	
	// make a copy of the state to a test state to run cardEffect on
	memcpy(&test_state, &state, sizeof(struct gameState));
	
	// run cardEffect function on test state, with smithy(13) chosen
	cardEffect(13, choice1, choice2, choice3, &test_state, handPos, &bonus);
	
	
	/*************** START TESTS *************************/
	
	
	/**** test how many cards were added to hand and compare with non test state. ****/

#if (NOISY_TEST == 1)
		printf(YELLOW"Testing player hand for card count - Expecting %d \n"RESET, state.handCount[state.whoseTurn] + drawnCards - discard);
#endif	
	
	int testHand = test_state.handCount[state.whoseTurn];
	int controlHand = state.handCount[state.whoseTurn];
	
	if(testHand == controlHand + drawnCards - discard)
	{
		printf(GREEN"Player Hand Returned %d -- SUCCESS\n"RESET, testHand);
	}
	else
	{
		printf(RED"Player Hand Returned %d -- FAILURE\n"RESET, testHand);
		failure = 1;
	}
	
	
	
	/**** test that the cards came from the deck ****/

#if (NOISY_TEST == 1)
		printf(YELLOW"Testing player deck for card count - Expecting %d \n"RESET, state.deckCount[state.whoseTurn] - drawnCards);
#endif	
	
	int testDeck = test_state.deckCount[state.whoseTurn];
	int controlDeck = state.deckCount[state.whoseTurn];
	
	if(testDeck == controlDeck - drawnCards)
	{
		printf(GREEN"Player Deck Returned: %d -- TEST SUCCESS\n"RESET, testDeck);
	}
	else
	{
		failure = 1;
		printf(RED"Player Deck Returned: %d -- TEST FAILURE\n"RESET, testDeck);
	}


	
	/**** test that player2's state hasn't changed ****/
	
#if (NOISY_TEST == 1)
		printf(YELLOW"Testing next players deck and hand for card count - Expecting no changes \n"RESET);
#endif		
	
	testHand = test_state.handCount[state.whoseTurn + 1];
	controlHand = state.handCount[state.whoseTurn + 1];
	
	if(testHand == controlHand)
	{
		printf(GREEN"Next Player Hand: %d -- Control Hand: %d -- TEST SUCCESS \n"RESET, testHand, controlHand );
	}
	else
	{
		failure = 1;
		printf(RED"Next Player Hand: %d -- Control Hand: %d -- TEST FAILURE \n"RESET, testHand, controlHand );
	}
	
	
	testDeck = test_state.deckCount[state.whoseTurn + 1];
	controlDeck = state.deckCount[state.whoseTurn + 1];
	

	if(testDeck == controlDeck)
	{
		printf(GREEN"Next Player Deck: %d -- Control Deck: %d -- TEST SUCCESS \n"RESET, testDeck, controlDeck );
	}
	else
	{
		failure = 1;
		printf(RED"Next Player Deck: %d -- Control Deck: %d -- TEST FAILURE \n"RESET, testDeck, controlDeck );
	}


	
	/**** test that there is no change to kingdom cards ****/
	
#if (NOISY_TEST == 1)
		printf(YELLOW"Testing kingdom cards supply count - Expecting no changes \n"RESET);
#endif	
	

	
	for(x = 0; x < 10; x++)
	{
		y = k[x];
		
		if(test_state.supplyCount[y] == state.supplyCount[y])
		{
			printf(GREEN"test supply count: %d -- Control supply count: %d -- TEST SUCCESS \n"RESET, test_state.supplyCount[y], state.supplyCount[y] );
		}
		else
		{
			failure = 1;
			printf(RED"test supply count: %d -- Control supply count: %d -- TEST FAILURE \n"RESET, test_state.supplyCount[y], state.supplyCount[y] );
		}
	
	}
	
	
	
	if(failure == 0)
	{
		printf(GREEN "All tests passed!\n"RESET);
	}
	else
	{
		printf(RED"TEST FAILURE\n"RESET);
	}	
	
	return 0;
}