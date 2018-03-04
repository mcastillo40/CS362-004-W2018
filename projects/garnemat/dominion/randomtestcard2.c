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
	printf ("\n\nRANDOM TESTING Great Hall Card: \n\n");

	struct gameState state, test_state, test_state2;
	int seed = 1000;
  int numPlayers = 2;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int drawnCards = 2;
	int discard;
	int x, y, loop_counter, loop_counter1, currentPlayer, otherPlayer;
	int failure = 0;
	
	// pass fail variables
	int pass1 = 0, pass2 = 0, pass3 = 0, pass4 = 0, pass5 = 0, pass6 = 0, pass7 = 0, pass8 = 0, pass9 = 0;
	int fail1 = 0, fail2 = 0, fail3 = 0, fail4 = 0, fail5 = 0, fail6 = 0, fail7 = 0, fail8 = 0, fail9 = 0;
	
	
	
	
	// initialize a game state and player cards
			 
	initializeGame(numPlayers, k, seed, &state);	

	

	
	
	

	
	
/************* START TESTS *************/



	for(loop_counter = 0; loop_counter < 1000; loop_counter++)
	{

		for(loop_counter1 = 0; loop_counter1 < 2; loop_counter1++)
		{
		// Altering starting deck for both players
		state.deck[loop_counter1][0] = rand() % 27;
		state.deck[loop_counter1][1] = rand() % 27;
		state.deck[loop_counter1][2] = rand() % 27;
		state.deck[loop_counter1][3] = rand() % 27;
		state.deck[loop_counter1][4] = rand() % 27;
		
		// set deckcount to 5
		state.deckCount[loop_counter1] = 5;
		
		// randomize starting hand for both players
		state.hand[loop_counter1][0] = rand() % 27;
		state.hand[loop_counter1][1] = rand() % 27;
		state.hand[loop_counter1][2] = rand() % 27;
		state.hand[loop_counter1][3] = rand() % 27;
		state.hand[loop_counter1][4] = rand() % 27;
		
		// set handcount to 5
		state.handCount[loop_counter1] = 5;

		}	

		// randomize current player and handpos
		currentPlayer = rand() % 2;
		handPos = rand() % 5;

		// Altering starting hand give player a great_hall card at randomized position
		state.hand[currentPlayer][handPos] = great_hall;

		// make a copy of the state to a test state to run cardEffect on
		memcpy(&test_state, &state, sizeof(struct gameState));
	
		greatHallCard(currentPlayer, &test_state, handPos);
	



	/************* TEST that a card is drawn - account for Great Hall being discarded *************/

	/*#if (NOISY_TEST == 1)
			printf(YELLOW"TESTING that a card is properly drawn while accounting for the discarded great hall\n"RESET);
	#endif	*/

		int test_handcount = test_state.handCount[currentPlayer];
		int control_handcount = state.handCount[currentPlayer];
		
	/*#if (NOISY_TEST == 1)
			printf(YELLOW"Handcount's should be equal \n"RESET);
	#endif	*/

		if(test_handcount == control_handcount)
		{
			//printf(GREEN"test handcount: %d   control handcount: %d -- SUCCESS\n"RESET, test_handcount, control_handcount);
			pass1++;
		}
		else
		{
			//printf(RED"test handcount: %d   control handcount: %d -- FAILURE\n"RESET, test_handcount, control_handcount);
			//failure = 1;
			fail1++;
		}	
		

		
		
		
		
		
		
		
		
	/************* TEST that the drawn card comes from the deck *************/
	/*#if (NOISY_TEST == 1)
			printf(YELLOW"TESTING that drawn card is properly drawn from the deck\n"RESET);
	#endif	*/		

		int testDeckCount,controlDeckCount;

		testDeckCount = test_state.deckCount[currentPlayer];
		controlDeckCount = state.deckCount[currentPlayer];

	/*#if (NOISY_TEST == 1)
			printf(YELLOW"Test Deck should be one less than control deck \n"RESET);
	#endif	*/
		


		if(testDeckCount == controlDeckCount - 1)
		{
			//printf(GREEN"controlDeckCount: %d  testDeckCount: %d  -- SUCCESS\n"RESET, controlDeckCount, testDeckCount);
			pass2++;
		}
		else
		{
			//printf(RED"controlDeckCount: %d  testDeckCount: %d  -- FAILURE\n"RESET, controlDeckCount, testDeckCount);
			//failure = 1;
			fail2++;
		}
		











	/************* TEST that the Great Hall is sent to played cards *************/
	/*#if (NOISY_TEST == 1)
			printf(YELLOW"TESTING that great hall is properly sent to played cards\n"RESET);
	#endif	*/		

		int testPlayed, controlPlayed;
		
		testPlayed = test_state.playedCardCount;
		controlPlayed = state.playedCardCount;

	/*#if (NOISY_TEST == 1)
		printf(YELLOW"Test Played should be one more than control Played \n"RESET);
	#endif	*/


		
		if(testPlayed == controlPlayed + 1)
		{
			//printf(GREEN"testPlayed: %d  controlPlayed: %d  -- SUCCESS\n"RESET, testPlayed, controlPlayed);
			pass3++;
		}
		else
		{
			//printf(RED"testPlayed: %d  controlPlayed: %d  -- FAILURE\n"RESET, testPlayed, controlPlayed);
			//failure = 1;
			fail3++;
		}
		
		
		
		
	/*#if (NOISY_TEST == 1)
		printf(YELLOW"TESTING that card sent to played cards is a great hall\n"RESET);
	#endif	*/	
		
		int testPlayedCard = test_state.playedCards[0];
		
	/*#if (NOISY_TEST == 1)
		printf(YELLOW"Great Hall Value and Test played card value should be the same \n"RESET);
	#endif	*/	
		
		//assert(testPlayedCard == great_hall);
		
		if(testPlayedCard == great_hall)
		{
			//printf(GREEN"Great Hall Value: %d  testPlayedCard value: %d  -- SUCCESS\n"RESET, great_hall, testPlayedCard);
			pass4++;
		}
		else
		{
			//printf(RED"Great Hall Value: %d  testPlayedCard value: %d  -- FAILURE\n"RESET, great_hall, testPlayedCard);
			//failure = 1;
			fail4++;
		}
		
		











	/************* TEST that an action is added *************/

	/*#if (NOISY_TEST == 1)
			printf("TESTING that great hall properly adds a single action\n"RESET);
	#endif			*/

		int testAction, controlAction;
		
		testAction = test_state.numActions;
		controlAction = state.numActions;

	/*#if (NOISY_TEST == 1)
		printf(YELLOW"Test action should be one greater than controlAction \n"RESET);
	#endif		*/

		//assert(testAction == controlAction + 1);

		if(testAction == controlAction + 1)
		{
			//printf(GREEN"testAction: %d  controlAction: %d  -- SUCCESS\n"RESET, testAction, controlAction);
			pass5++;
		}
		else
		{
			//printf(RED"testAction: %d  controlAction: %d  -- FAILURE\n"RESET, testAction, controlAction);
			//failure = 1;
			fail5++;
		}
		
		
		









	/************* TEST that other player's state is not effected *************/

	/*#if (NOISY_TEST == 1)
			printf(YELLOW"Testing next players deck and hand for card count - Expecting no changes \n"RESET);
	#endif		*/	
		
		int testHand, controlHand, testDeck, controlDeck;
		
		if(currentPlayer == 0)
		{
			otherPlayer = 1;
		}
		else
		{
			otherPlayer = 0;
		}
		
		
		testHand = test_state.handCount[otherPlayer];
		controlHand = state.handCount[otherPlayer];
		
		//assert(testHand == controlHand);
		
		//printf(YELLOW"TESTING HAND: \n"RESET);
		
		if(testHand == controlHand)
		{
			//printf(GREEN"EXPECTED: %d  ACTUAL RETURN: %d  -- SUCCESS\n"RESET, controlHand, testHand);
			pass6++;
		}
		else
		{
			//printf(RED"EXPECTED: %d  ACTUAL RETURN: %d  -- FAILURE\n"RESET, controlHand, testHand);
			//failure = 1;
			fail6++;
		}	
		
		
		
		testDeck = test_state.deckCount[otherPlayer];
		controlDeck = state.deckCount[otherPlayer];
		
		//assert(testDeck == controlDeck);

		//printf(YELLOW"TESTING DECK: \n"RESET);
		
		if(testDeck == controlDeck)
		{
			//printf(GREEN"EXPECTED: %d  ACTUAL RETURN: %d  -- SUCCESS\n"RESET, controlDeck, testDeck);
			pass7++;
		}
		else
		{
			//printf(RED"EXPECTED: %d  ACTUAL RETURN: %d  -- FAILURE\n"RESET, controlDeck, testDeck);
			//failure = 1;
			fail7++;
		}










	/************* TEST that there is no change to kingdom cards *************/

	/*#if (NOISY_TEST == 1)
			printf(YELLOW"Testing kingdom cards supply count - Expecting no changes \n"RESET);
	#endif		*/
		

		
		for(x = 0; x < 10; x++)
		{
			y = k[x];
			
			if(test_state.supplyCount[y] == state.supplyCount[y])
			{
				//printf(GREEN"test supply count: %d -- Control supply count: %d -- TEST SUCCESS \n"RESET, test_state.supplyCount[y], state.supplyCount[y] );
				pass8++;
			}
			else
			{
				//failure = 1;
				//printf(RED"test supply count: %d -- Control supply count: %d -- TEST FAILURE \n"RESET, test_state.supplyCount[y], state.supplyCount[y] );
				fail8++;
			}
		
		}










	/************* TEST that score is affected by Great Hall card *************/
	/*#if (NOISY_TEST == 1)
			printf(YELLOW"TESTING that score is affected by Great Hall card\n"RESET);
	#endif	*/
		// reset test state to control state
		memcpy(&test_state, &state, sizeof(struct gameState));
		
		// reset second test state to control state
		memcpy(&test_state2, &state, sizeof(struct gameState));
		
		// change great hall card in second test state to a copper
		test_state2.hand[currentPlayer][0] = copper;
		
		int testScore_withGH = scoreFor (currentPlayer, &test_state);
		int testScore_noGH = scoreFor (currentPlayer, &test_state2);
		
	/*#if (NOISY_TEST == 1)
		printf(YELLOW"Test score with card should be one more than the test score without card \n"RESET);
	#endif	*/

		//assert(testScore_withGH == testScore_noGH + 1);

		if(testScore_withGH == testScore_noGH + 1)
		{
			//printf(GREEN"test Score with Great Hall: %d  test Score without Great Hall: %d  -- SUCCESS\n"RESET, testScore_withGH, testScore_noGH);
			pass9++;
		}
		else
		{
			//printf(RED"test Score with Great Hall: %d  test Score without Great Hall: %d  -- FAILURE\n"RESET, testScore_withGH, testScore_noGH);
			//failure = 1;
			fail9++;
		}

	/************* END TESTS *************/


	}







#if (NOISY_TEST == 1)
	printf(YELLOW"Testing smithyCard function when currentPlayer, handpos, /n starting hands, and starting decks are randomized \n\n"RESET);
#endif	

#if (NOISY_TEST == 1)
	printf(YELLOW"Testing that a card is drawn - while accounting for discard of Great Hall \n"RESET);
#endif	
	printf(GREEN"Total test Successes: %d \n"RESET, pass1 );
	printf(RED"Total test Failures: %d \n\n"RESET, fail1 );	

#if (NOISY_TEST == 1)
	printf(YELLOW"Testing that the card came from the deck \n"RESET);
#endif	
	printf(GREEN"Total test Successes: %d \n"RESET, pass2 );
	printf(RED"Total test Failures: %d \n\n"RESET, fail2 );	
	
#if (NOISY_TEST == 1)
	printf(YELLOW"Testing that played card is sent to played card pile \n"RESET);
#endif	
	printf(GREEN"Total test Successes: %d \n"RESET, pass3 );
	printf(RED"Total test Failures: %d \n\n"RESET, fail3 );	
	
#if (NOISY_TEST == 1)
	printf(YELLOW"Verify that card sent to played pile is a Great Hall \n"RESET);
#endif	
	printf(GREEN"Total test Successes: %d \n"RESET, pass4 );
	printf(RED"Total test Failures: %d \n\n"RESET, fail4 );
	
#if (NOISY_TEST == 1)
	printf(YELLOW"Testing that a single action is added \n"RESET);
#endif	
	printf(GREEN"Total test Successes: %d \n"RESET, pass5 );
	printf(RED"Total test Failures: %d \n\n"RESET, fail5 );	
	
#if (NOISY_TEST == 1)
	printf(YELLOW"Testing that other players hand hasn't changed \n"RESET);
#endif	
	printf(GREEN"Total test Successes: %d \n"RESET, pass6 );
	printf(RED"Total test Failures: %d \n\n"RESET, fail6 );
	
#if (NOISY_TEST == 1)
	printf(YELLOW"Testing that other players deck hasn't changed \n"RESET);
#endif	
	printf(GREEN"Total test Successes: %d \n"RESET, pass7 );
	printf(RED"Total test Failures: %d \n\n"RESET, fail7 );
	
#if (NOISY_TEST == 1)
	printf(YELLOW"Testing that there is no change to kingdom cards \n"RESET);
#endif	
	printf(GREEN"Total test Successes: %d \n"RESET, pass8 );
	printf(RED"Total test Failures: %d \n\n"RESET, fail8 );	
	
#if (NOISY_TEST == 1)
	printf(YELLOW"Testing that the game score is properly affected by great hall \n"RESET);
#endif	
	printf(GREEN"Total test Successes: %d \n"RESET, pass8 );
	printf(RED"Total test Failures: %d \n\n"RESET, fail8 );	

	
	return 0;
}