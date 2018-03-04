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

// testing great hall Card
int main () {
	printf ("\n\nTESTING Great Hall Card: \n\n");

	struct gameState state, test_state, test_state2;
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
	
	
	// Altering starting hand give player a great_hall card at hand position 1
	state.hand[currentPlayer][0] = great_hall;

	// make a copy of the state to a test state to run cardEffect on
	memcpy(&test_state, &state, sizeof(struct gameState));
	
	// call card effect
	cardEffect(great_hall, choice1, choice2, choice3, &test_state, handPos, &bonus);
	
/************* START TESTS *************/


/************* TEST that a card is drawn - account for Great Hall being discarded *************/

#if (NOISY_TEST == 1)
		printf(YELLOW"TESTING that a card is properly drawn while accounting for the discarded great hall\n"RESET);
#endif

	int test_handcount = test_state.handCount[currentPlayer];
	int control_handcount = state.handCount[currentPlayer];
	
#if (NOISY_TEST == 1)
		printf(YELLOW"Handcount's should be equal \n"RESET);
#endif

	if(test_handcount == control_handcount)
	{
		printf(GREEN"test handcount: %d   control handcount: %d -- SUCCESS\n"RESET, test_handcount, control_handcount);
	}
	else
	{
		printf(RED"test handcount: %d   control handcount: %d -- FAILURE\n"RESET, test_handcount, control_handcount);
		failure = 1;
	}	
	

	
	
	
	
	
	
	
	
/************* TEST that the drawn card comes from the deck *************/
#if (NOISY_TEST == 1)
		printf(YELLOW"TESTING that drawn card is properly drawn from the deck\n"RESET);
#endif		

	int testDeckCount,controlDeckCount;

	testDeckCount = test_state.deckCount[currentPlayer];
	controlDeckCount = state.deckCount[currentPlayer];

#if (NOISY_TEST == 1)
		printf(YELLOW"Test Deck should be one less than control deck \n"RESET);
#endif
	


	if(testDeckCount == controlDeckCount - 1)
	{
		printf(GREEN"controlDeckCount: %d  testDeckCount: %d  -- SUCCESS\n"RESET, controlDeckCount, testDeckCount);
	}
	else
	{
		printf(RED"controlDeckCount: %d  testDeckCount: %d  -- FAILURE\n"RESET, controlDeckCount, testDeckCount);
		failure = 1;
	}
	











/************* TEST that the Great Hall is sent to played cards *************/
#if (NOISY_TEST == 1)
		printf(YELLOW"TESTING that great hall is properly sent to played cards\n"RESET);
#endif		

	int testPlayed, controlPlayed;
	
	testPlayed = test_state.playedCardCount;
	controlPlayed = state.playedCardCount;

#if (NOISY_TEST == 1)
	printf(YELLOW"Test Played should be one more than control Played \n"RESET);
#endif


	
	if(testPlayed == controlPlayed + 1)
	{
		printf(GREEN"testPlayed: %d  controlPlayed: %d  -- SUCCESS\n"RESET, testPlayed, controlPlayed);
	}
	else
	{
		printf(RED"testPlayed: %d  controlPlayed: %d  -- FAILURE\n"RESET, testPlayed, controlPlayed);
		failure = 1;
	}
	
	
	
	
#if (NOISY_TEST == 1)
	printf(YELLOW"TESTING that card sent to played cards is a great hall\n"RESET);
#endif	
	
	int testPlayedCard = test_state.playedCards[0];
	
#if (NOISY_TEST == 1)
	printf(YELLOW"Great Hall Value and Test played card value should be the same \n"RESET);
#endif	
	
	//assert(testPlayedCard == great_hall);
	
	if(testPlayedCard == great_hall)
	{
		printf(GREEN"Great Hall Value: %d  testPlayedCard value: %d  -- SUCCESS\n"RESET, great_hall, testPlayedCard);
	}
	else
	{
		printf(RED"Great Hall Value: %d  testPlayedCard value: %d  -- FAILURE\n"RESET, great_hall, testPlayedCard);
		failure = 1;
	}
	
	











/************* TEST that an action is added *************/

#if (NOISY_TEST == 1)
		printf("TESTING that great hall properly adds a single action\n"RESET);
#endif		

	int testAction, controlAction;
	
	testAction = test_state.numActions;
	controlAction = state.numActions;

#if (NOISY_TEST == 1)
	printf(YELLOW"Test action should be one greater than controlAction \n"RESET);
#endif	

	//assert(testAction == controlAction + 1);

	if(testAction == controlAction + 1)
	{
		printf(GREEN"testAction: %d  controlAction: %d  -- SUCCESS\n"RESET, testAction, controlAction);
	}
	else
	{
		printf(RED"testAction: %d  controlAction: %d  -- FAILURE\n"RESET, testAction, controlAction);
		failure = 1;
	}
	
	
	









/************* TEST that other player's state is not effected *************/

#if (NOISY_TEST == 1)
		printf(YELLOW"Testing next players deck and hand for card count - Expecting no changes \n"RESET);
#endif		
	
	int testHand, controlHand, testDeck, controlDeck;
	
	testHand = test_state.handCount[state.whoseTurn + 1];
	controlHand = state.handCount[state.whoseTurn + 1];
	
	//assert(testHand == controlHand);
	
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
	
	
	
	testDeck = test_state.deckCount[state.whoseTurn + 1];
	controlDeck = state.deckCount[state.whoseTurn + 1];
	
	//assert(testDeck == controlDeck);

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










/************* TEST that there is no change to kingdom cards *************/

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










/************* TEST that score is affected by Great Hall card *************/
#if (NOISY_TEST == 1)
		printf(YELLOW"TESTING that score is affected by Great Hall card\n"RESET);
#endif
	// reset test state to control state
	memcpy(&test_state, &state, sizeof(struct gameState));
	
	// reset second test state to control state
	memcpy(&test_state2, &state, sizeof(struct gameState));
	
	// change great hall card in second test state to a copper
	test_state2.hand[currentPlayer][0] = copper;
	
	int testScore_withGH = scoreFor (currentPlayer, &test_state);
	int testScore_noGH = scoreFor (currentPlayer, &test_state2);
	
#if (NOISY_TEST == 1)
	printf(YELLOW"Test score with card should be one more than the test score without card \n"RESET);
#endif	

	//assert(testScore_withGH == testScore_noGH + 1);

	if(testScore_withGH == testScore_noGH + 1)
	{
		printf(GREEN"test Score with Great Hall: %d  test Score without Great Hall: %d  -- SUCCESS\n"RESET, testScore_withGH, testScore_noGH);
	}
	else
	{
		printf(RED"test Score with Great Hall: %d  test Score without Great Hall: %d  -- FAILURE\n"RESET, testScore_withGH, testScore_noGH);
		failure = 1;
	}

/************* END TESTS *************/







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