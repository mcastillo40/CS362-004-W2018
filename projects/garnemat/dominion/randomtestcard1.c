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

	printf ("RANDOM TESTING Smithy Card\n");

	// seed for rand calls
	srand(time(NULL));	
	
	struct gameState state, test_state;
	int seed = 1000;
  int numPlayers = 2;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int drawnCards = 3;
	int discard = 1;
	int failure = 0;
	int x, y, loop_counter, loop_counter1, currentPlayer, otherPlayer, testDeck, testHand, controlHand, controlDeck;

	// pass fail variables
	int pass1 = 0, pass2 = 0, pass3 = 0, pass4 = 0, pass5 = 0, pass6 = 0;
	int fail1 = 0, fail2 = 0, fail3 = 0, fail4 = 0, fail5 = 0, fail6 = 0;
	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &state);
	
	// make a copy of the state to a test state to run cardEffect on
	memcpy(&test_state, &state, sizeof(struct gameState));

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
	

	/*************** START TESTS *************************/	
	
	for(loop_counter1 = 0; loop_counter1 < 1000; loop_counter1++)
	{
	
		// randomize current player and handpos
		currentPlayer = rand() % 2;
		handPos = rand() % 5;
		
		// make a copy of the state to a test state to run cardEffect on
		memcpy(&test_state, &state, sizeof(struct gameState));;
	
		smithyCard(currentPlayer, &test_state, handPos);
	

	
	
		/**** test how many cards were added to hand and compare with non test state. ****/
/*
	#if (NOISY_TEST == 1)
			printf(YELLOW"Testing player hand for card count - Expecting %d \n"RESET, state.handCount[state.whoseTurn] + drawnCards - discard);
	#endif	
*/			
		int testHand = test_state.handCount[currentPlayer];
		int controlHand = state.handCount[currentPlayer];
		
		if(testHand == controlHand + drawnCards - discard)
		{
			//printf(GREEN"Player Hand Returned %d -- SUCCESS\n"RESET, testHand);
			pass1++;
		}
		else
		{
			//printf(RED"Player Hand Returned %d -- FAILURE\n"RESET, testHand);
			//failure = 1;
			fail1++;
		}
		
		
		
		/**** test that the cards came from the deck ****/
/*
	#if (NOISY_TEST == 1)
			printf(YELLOW"Testing player deck for card count - Expecting %d \n"RESET, state.deckCount[state.whoseTurn] - drawnCards);
	#endif	
*/			
		int testDeck = test_state.deckCount[currentPlayer];
		int controlDeck = state.deckCount[currentPlayer];
		
		if(testDeck == controlDeck - drawnCards)
		{
			//printf(GREEN"Player Deck Returned: %d -- TEST SUCCESS\n"RESET, testDeck);
			pass2++;
		}
		else
		{
			//failure = 1;
			//printf(RED"Player Deck Returned: %d -- TEST FAILURE\n"RESET, testDeck);
			fail2++;
		}


		
		/**** test that player2's state hasn't changed ****/
/*		
	#if (NOISY_TEST == 1)
			printf(YELLOW"Testing next players deck and hand for card count - Expecting no changes \n"RESET);
	#endif		
*/	
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
		
		if(testHand == controlHand)
		{
			//printf(GREEN"Next Player Hand: %d -- Control Hand: %d -- TEST SUCCESS \n"RESET, testHand, controlHand );
			pass3++;
		}
		else
		{
			//failure = 1;
			//printf(RED"Next Player Hand: %d -- Control Hand: %d -- TEST FAILURE \n"RESET, testHand, controlHand );
			fail3++;
		}
		
		
		testDeck = test_state.deckCount[otherPlayer];
		controlDeck = state.deckCount[otherPlayer];
		

		if(testDeck == controlDeck)
		{
			//printf(GREEN"Next Player Deck: %d -- Control Deck: %d -- TEST SUCCESS \n"RESET, testDeck, controlDeck );
			pass4++;
		}
		else
		{
			//failure = 1;
			//printf(RED"Next Player Deck: %d -- Control Deck: %d -- TEST FAILURE \n"RESET, testDeck, controlDeck );
			fail4++;
		}


		
		/**** test that there is no change to kingdom cards ****/
/*		
	#if (NOISY_TEST == 1)
			printf(YELLOW"Testing kingdom cards supply count - Expecting no changes \n"RESET);
	#endif	
*/		

		
		for(x = 0; x < 10; x++)
		{
			y = k[x];
			
			if(test_state.supplyCount[y] == state.supplyCount[y])
			{
				//printf(GREEN"test supply count: %d -- Control supply count: %d -- TEST SUCCESS \n"RESET, test_state.supplyCount[y], state.supplyCount[y] );
				pass5++;
			}
			else
			{
				//failure = 1;
				//printf(RED"test supply count: %d -- Control supply count: %d -- TEST FAILURE \n"RESET, test_state.supplyCount[y], state.supplyCount[y] );
				fail5++;
			}
		
		}
	}
#if (NOISY_TEST == 1)
	printf(YELLOW"Testing smithyCard function when currentPlayer, handpos, the starting hands, and decks are randomized \n\n"RESET);
#endif	

#if (NOISY_TEST == 1)
	printf(YELLOW"Testing that three cards were added to hand \n"RESET);
#endif	
	printf(GREEN"Total test Successes: %d \n"RESET, pass1 );
	printf(RED"Total test Failures: %d \n\n"RESET, fail1 );	

#if (NOISY_TEST == 1)
	printf(YELLOW"Testing that the cards came from the deck \n"RESET);
#endif	
	printf(GREEN"Total test Successes: %d \n"RESET, pass2 );
	printf(RED"Total test Failures: %d \n\n"RESET, fail2 );	
	
#if (NOISY_TEST == 1)
	printf(YELLOW"Testing that other players hand hasn't changed \n"RESET);
#endif	
	printf(GREEN"Total test Successes: %d \n"RESET, pass3 );
	printf(RED"Total test Failures: %d \n\n"RESET, fail3 );	
	
#if (NOISY_TEST == 1)
	printf(YELLOW"Testing that other players deck hasn't changed \n"RESET);
#endif	
	printf(GREEN"Total test Successes: %d \n"RESET, pass4 );
	printf(RED"Total test Failures: %d \n\n"RESET, fail4 );
	
	
#if (NOISY_TEST == 1)
	printf(YELLOW"Testing that there is no change to kingdom cards \n"RESET);
#endif	
	printf(GREEN"Total test Successes: %d \n"RESET, pass5 );
	printf(RED"Total test Failures: %d \n\n"RESET, fail5 );	

	
	return 0;
}