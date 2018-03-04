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


// testing adventurer Card
int main () {
	printf ("\n\nTESTING Adventurer Card: \n\n");

	struct gameState state, test_state;
	int seed = 1000;
  int numPlayers = 2;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int drawnCards = 2;
	int discard;
	int x, y;
	int failure = 0;
	
	
	// initialize a game state and player cards
			 
	initializeGame(numPlayers, k, seed, &state);	
	int currentPlayer = state.whoseTurn;
	
	// Altering starting deck to force discard when card is played
	state.deck[currentPlayer][0] = copper;
	state.deck[currentPlayer][1] = copper;
	state.deck[currentPlayer][2] = copper;
	state.deck[currentPlayer][3] = estate;
	state.deck[currentPlayer][4] = estate;
	
	
	// make a copy of the state to a test state to run cardEffect on
	memcpy(&test_state, &state, sizeof(struct gameState));
	
	// run card effect for adventurer
	
	cardEffect(adventurer, choice1, choice2, choice3, &test_state, handPos, &bonus);
	
	
	
	
/************* test that two cards added to hand *************/

#if (NOISY_TEST == 1)
		printf(YELLOW"Testing that the handcount is 2 higher in the test state than in the control state \n"RESET);
#endif		

	int test_handcount = test_state.handCount[currentPlayer];
	int control_handcount = state.handCount[currentPlayer] + 2;
	
	assert(test_handcount == control_handcount);
	
	if(test_handcount == control_handcount)
	{
		printf(GREEN"test handcount: %d   control handcount: %d -- SUCCESS\n"RESET, test_handcount, control_handcount);
	}
	else
	{
		printf(RED"test handcount: %d   control handcount: %d -- FAILURE\n"RESET, test_handcount, control_handcount);
		failure = 1;
	}
	
	
	
	
	
	
	
	
/************* test that two cards added to hand are treasure cards *************/

#if (NOISY_TEST == 1)
		printf(YELLOW"Testing that the cards added to the hand in test state are treasure cards\n"RESET);
#endif	
	
	int test1, test2;
	
	int card1 = test_state.hand[currentPlayer][(test_state.handCount[currentPlayer] - 1)];
	int card2 = test_state.hand[currentPlayer][(test_state.handCount[currentPlayer] - 2)];
	
	if(card1 == 4 || card1 == 5 || card1 == 6)
		test1 = 1;
	else
		test1 = -1;
	
	if(card2 == 4 || card2 == 5 || card2 == 6)
		test2 = 1;
	else
		test2 = -1;
	

	
	if(test1 == 1)
	{
		printf(GREEN"Card 1 is a treasure card -- SUCCESS\n"RESET);
	}
	else
	{
		printf(RED"Card 1 is not a treasure card -- FAILURE\n"RESET);
		failure = 1;
	}
	
	

	if(test2 == 1)
	{
		printf(GREEN"Card 2 is a treasure card -- SUCCESS\n"RESET);
	}
	else
	{
		printf(RED"Card 2 is not a treasure card -- FAILURE\n"RESET);
		failure = 1;
	}
	
	
	
	
	
	
/************* test that they came from deck *************/

#if (NOISY_TEST == 1)
	printf(YELLOW"Testing that the test deck count after card played and control deck count differ \n"RESET);
	printf(YELLOW"To ensure drawn cards came from players deck \n"RESET);
#endif		

	int testDeckCount,controlDeckCount;

	testDeckCount = test_state.deckCount[currentPlayer];
	controlDeckCount = state.deckCount[currentPlayer];

	assert(testDeckCount != controlDeckCount);
		
	if(testDeckCount != controlDeckCount)
	{
		printf(GREEN"controlDeckCount: %d  testDeckCount: %d  -- SUCCESS\n"RESET, controlDeckCount, testDeckCount);
	}
	else
	{
		printf(RED"controlDeckCount: %d  testDeckCount: %d  -- FAILURE\n"RESET, controlDeckCount, testDeckCount);
		failure = 1;
	}
		
		








/************* test that cards discarded == cards drawn - 2 *************/

#if (NOISY_TEST == 1)
		printf(YELLOW"Testing that non tresure cards drawn were properly discarded \n" RESET);
#endif		

	int testDiscard, testCurrentDeck, controlDiscard, controlCurrentDeck;
	
	testDiscard = test_state.discardCount[currentPlayer];
	testCurrentDeck = test_state.deckCount[currentPlayer];
	controlDiscard = state.discardCount[currentPlayer];
	controlCurrentDeck = state.deckCount[currentPlayer];

	#if (NOISY_TEST == 1)
		printf(YELLOW"testDiscard: %d \ntestCurrentDeck: %d \ncontrolCurrentDeck: %d \ncontrolDiscard: %d \n"RESET, testDiscard, testCurrentDeck, controlCurrentDeck, controlDiscard);
#endif			
	

#if (NOISY_TEST == 1)
		printf(YELLOW"Control deck should equal the test discard pile plus test deck plus 2 for the treasure cards kept  \n"RESET);
#endif			
	

	if(controlCurrentDeck == testDiscard + testCurrentDeck + 2)
	{
		printf(GREEN"EXPECTED: %d  ACTUAL RETURN: %d  -- SUCCESS\n"RESET, controlCurrentDeck, testDiscard + testCurrentDeck + 2);
	}
	else
	{
		printf(RED"EXPECTED: %d  ACTUAL RETURN: %d  -- FAILURE\n"RESET, controlCurrentDeck, testDiscard + testCurrentDeck + 2);
		failure = 1;
	}
	

	
	
	
	
	
	
/************* test that player2's state hasn't changed *************/
	
#if (NOISY_TEST == 1)
		printf(YELLOW"Testing next players deck and hand for card count - Expecting no changes \n"RESET);
#endif		
	
	int testDeck, testHand, controlDeck, controlHand;
	
	testHand = test_state.handCount[currentPlayer + 1];
	controlHand = state.handCount[currentPlayer + 1];
	
	printf(YELLOW"TESTING HAND: \n"RESET);
	
	if(testHand == controlHand)
	{
		printf(GREEN"EXPECTED: %d  ACTUAL RETURN: %d  -- SUCCESS\n"RESET, controlHand, testHand);
	}
	else
	{
		printf(RED"EXPECTED: %d  ACTUAL RETURN: %d  -- FAILURE\n"RESET, controlHand, testHand);
		failure = 1;
	}
	
	
	
	testDeck = test_state.deckCount[currentPlayer + 1];
	controlDeck = state.deckCount[currentPlayer + 1];
	
	printf(YELLOW"TESTING DECK: \n"RESET);
	
	if(testDeck == controlDeck)
	{
		printf(GREEN"EXPECTED: %d  ACTUAL RETURN: %d  -- SUCCESS\n"RESET, controlDeck, testDeck);
	}
	else
	{
		printf(RED"EXPECTED: %d  ACTUAL RETURN: %d  -- FAILURE\n"RESET, controlDeck, testDeck);
		failure = 1;
	}
	
	
	
	
	
	
	
	
/************* test that there is no change to kingdom cards *************/
	
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