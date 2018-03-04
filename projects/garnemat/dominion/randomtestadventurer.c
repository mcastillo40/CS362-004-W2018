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

	printf ("\n\nRANDOM TESTING Adventurer Card: \n\n");

	// seed for rand calls
	srand(time(NULL));
	
	
	struct gameState state, test_state;
	int seed = 1000;
  int numPlayers = 2;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int drawnCards = 2;
	int discard;
	int x, y, loop_counter, loop_counter1, currentPlayer, otherPlayer, testDeck, testHand, controlHand, controlDeck;
	int failure = 0;
	
	// Pass-Fail counters for non-shuffling tests
	int nshuff1 = 0, nshuff2 = 0, nshuff3 = 0, nshuff4 = 0, nshuff5 = 0, nshuff6 = 0;
	int nshufferr1 = 0, nshufferr2 = 0, nshufferr3 = 0, nshufferr4 = 0, nshufferr5 = 0, nshufferr6 = 0;

	// Pass-Fail counters for shuffling tests
	int shuff1 = 0, shuff2 = 0, shuff3 = 0, shuff4 = 0, shuff5 = 0, shuff6 = 0;
	int shufferr1 = 0, shufferr2 = 0, shufferr3 = 0, shufferr4 = 0, shufferr5 = 0, shufferr6 = 0;
	
	
	
	// initialize a game state and player cards	 
	initializeGame(numPlayers, k, seed, &state);


	for(loop_counter1 = 0; loop_counter1 < 2; loop_counter1++)
	{
		// Altering starting deck to force discard when card is played
		state.deck[loop_counter1][0] = copper;
		state.deck[loop_counter1][1] = silver;
		state.deck[loop_counter1][2] = gold;
		state.deck[loop_counter1][3] = estate;
		state.deck[loop_counter1][4] = estate;
		
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
		
	/***************************************************************************************
	*
	*
	*																	NON	SHUFFLE TESTS 
	*
	*
	****************************************************************************************/

		
	for(loop_counter = 0; loop_counter < 500; loop_counter++)
	{
		// randomize current player
		currentPlayer = rand() % 2;
		
		// make a copy of the state to a test state to run cardEffect on
		memcpy(&test_state, &state, sizeof(struct gameState));;
		
		// Call Adventurer card function
		adventurerCard(0, &test_state, currentPlayer);

		
		/*************** START TESTS *************************/
		
		
		/************* test that two cards added to hand *************/
		
		/*
		#if (NOISY_TEST == 1)
				printf(YELLOW"Testing that the handcount is 2 higher in the test state than in the control state \n"RESET);
		#endif
		*/

		int test_handcount = test_state.handCount[currentPlayer];
		int control_handcount = state.handCount[currentPlayer] + 2;
			
		// assert(test_handcount == control_handcount);
			
		if(test_handcount == control_handcount)
		{
			//printf(GREEN"test handcount: %d   control handcount: %d -- SUCCESS\n"RESET, test_handcount, control_handcount);
			nshuff1++;
		}
		else
		{
			//printf(RED"test handcount: %d   control handcount: %d -- FAILURE\n"RESET, test_handcount, control_handcount);
			nshufferr1++;
		}
		
		
		/**** test that the cards came from the deck ****/
	/*
	#if (NOISY_TEST == 1)
			printf(YELLOW"Testing player deck for card count - Expecting %d \n"RESET, state.deckCount[state.whoseTurn] - drawnCards);
	#endif	
	*/	
		
		
		testDeck = test_state.deckCount[currentPlayer];
		controlDeck = state.deckCount[currentPlayer];
		
		if(testDeck == controlDeck - drawnCards)
		{
			// printf(GREEN"Player Deck Returned: %d -- TEST SUCCESS\n"RESET, testDeck);
			nshuff2++;
		}
		else
		{
			//failure = 1;
			//printf(RED"Player Deck Returned: %d -- TEST FAILURE\n"RESET, testDeck);
			nshufferr2++;
		}


		
		/**** test that player2's state hasn't changed ****/
	/*	
	#if (NOISY_TEST == 1)
			printf(YELLOW"Testing next players deck and hand for card count - Expecting no changes \n"RESET);
	#endif		
	*/	
		
		// set otherPlayer to player not chosen by rand call
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
			nshuff3++;
		}
		else
		{
			//failure = 1;
			//printf(RED"Next Player Hand: %d -- Control Hand: %d -- TEST FAILURE \n"RESET, testHand, controlHand );
			nshufferr3++;
		}
		
		
		testDeck = test_state.deckCount[otherPlayer];
		controlDeck = state.deckCount[otherPlayer];
		

		if(testDeck == controlDeck)
		{
			//printf(GREEN"Next Player Deck: %d -- Control Deck: %d -- TEST SUCCESS \n"RESET, testDeck, controlDeck );
			nshuff4++;
		}
		else
		{
			//failure = 1;
			//printf(RED"Next Player Deck: %d -- Control Deck: %d -- TEST FAILURE \n"RESET, testDeck, controlDeck );
			nshufferr4++;
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
				nshuff5++;
			}
			else
			{
				//failure = 1;
				//printf(RED"test supply count: %d -- Control supply count: %d -- TEST FAILURE \n"RESET, test_state.supplyCount[y], state.supplyCount[y] );
				nshufferr5++;
			}
		
		}
	}
		
#if (NOISY_TEST == 1)
	printf(YELLOW"Testing adventurerCard function when currentPlayer is randomized\n and there is no forced shuffle \n\n"RESET);
#endif	

#if (NOISY_TEST == 1)
	printf(YELLOW"Testing that two cards were added to hand \n"RESET);
#endif	
	printf(GREEN"Total test Successes: %d \n"RESET, nshuff1 );
	printf(RED"Total test Failures: %d \n\n"RESET, nshufferr1 );	

#if (NOISY_TEST == 1)
	printf(YELLOW"Testing that the cards came from the deck \n"RESET);
#endif	
	printf(GREEN"Total test Successes: %d \n"RESET, nshuff2 );
	printf(RED"Total test Failures: %d \n\n"RESET, nshufferr2 );	
	
#if (NOISY_TEST == 1)
	printf(YELLOW"Testing that other players hand hasn't changed \n"RESET);
#endif	
	printf(GREEN"Total test Successes: %d \n"RESET, nshuff3 );
	printf(RED"Total test Failures: %d \n\n"RESET, nshufferr3 );	
	
#if (NOISY_TEST == 1)
	printf(YELLOW"Testing that other players deck hasn't changed \n"RESET);
#endif	
	printf(GREEN"Total test Successes: %d \n"RESET, nshuff4 );
	printf(RED"Total test Failures: %d \n\n"RESET, nshufferr4 );
	
	
#if (NOISY_TEST == 1)
	printf(YELLOW"Testing that there is no change to kingdom cards \n"RESET);
#endif	
	printf(GREEN"Total test Successes: %d \n"RESET, nshuff5 );
	printf(RED"Total test Failures: %d \n\n"RESET, nshufferr5 );
	
	/***************************************************************************************
	*
	*
	*																		SHUFFLE TESTS 
	*
	*
	****************************************************************************************/
	
	for(loop_counter1 = 0; loop_counter1 < 2; loop_counter1++)
	{
		// Altering starting deck randomize draw pile to possibly force a call to shuffle
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
		
		// one of each coin placed in discard pile for each player
		state.discard[loop_counter1][0] = copper;
		state.discard[loop_counter1][1] = silver;
		state.discard[loop_counter1][2] = gold;
		
		// set discard count to 3
		state.discardCount[loop_counter1] = 3;
	
	}
	
	
	// Run test 500 times
	for(loop_counter = 0; loop_counter < 500; loop_counter++)
	{
		// randomize current player
		currentPlayer = rand() % 2;
		
		// make a copy of the state to a test state to run cardEffect on
		memcpy(&test_state, &state, sizeof(struct gameState));;
		
		// Call Adventurer card function
		adventurerCard(0, &test_state, currentPlayer);

		
		/*************** START TESTS *************************/
		
		
		/************* test that two cards added to hand *************/
		
		/*
		#if (NOISY_TEST == 1)
				printf(YELLOW"Testing that the handcount is 2 higher in the test state than in the control state \n"RESET);
		#endif
		*/

		int test_handcount = test_state.handCount[currentPlayer];
		int control_handcount = state.handCount[currentPlayer] + 2;
			
		// assert(test_handcount == control_handcount);
			
		if(test_handcount == control_handcount)
		{
			//printf(GREEN"test handcount: %d   control handcount: %d -- SUCCESS\n"RESET, test_handcount, control_handcount);
			shuff1++;
		}
		else
		{
			//printf(RED"test handcount: %d   control handcount: %d -- FAILURE\n"RESET, test_handcount, control_handcount);
			shufferr1++;
		}
		
		
		/**** test that all cards are still accounted for****/
	/*
	#if (NOISY_TEST == 1)
			printf(YELLOW"Testing player deck for card count - Expecting %d \n"RESET, state.deckCount[state.whoseTurn] - drawnCards);
	#endif	
	*/	
		
		
		testDeck = test_state.deckCount[currentPlayer] + test_state.handCount[currentPlayer] + test_state.discardCount[currentPlayer];
		controlDeck = state.deckCount[currentPlayer] + state.handCount[currentPlayer] + state.discardCount[currentPlayer];;
		
		if(testDeck == controlDeck)
		{
			// printf(GREEN"Player Deck Returned: %d -- TEST SUCCESS\n"RESET, testDeck);
			shuff2++;
		}
		else
		{
			//failure = 1;
			//printf(RED"Player Deck Returned: %d -- TEST FAILURE\n"RESET, testDeck);
			shufferr2++;
		}


		
		/**** test that player2's state hasn't changed ****/
	/*	
	#if (NOISY_TEST == 1)
			printf(YELLOW"Testing next players deck and hand for card count - Expecting no changes \n"RESET);
	#endif		
	*/	
		
		// set otherPlayer to player not chosen by rand call
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
			shuff3++;
		}
		else
		{
			//failure = 1;
			//printf(RED"Next Player Hand: %d -- Control Hand: %d -- TEST FAILURE \n"RESET, testHand, controlHand );
			shufferr3++;
		}
		
		
		testDeck = test_state.deckCount[otherPlayer];
		controlDeck = state.deckCount[otherPlayer];
		

		if(testDeck == controlDeck)
		{
			//printf(GREEN"Next Player Deck: %d -- Control Deck: %d -- TEST SUCCESS \n"RESET, testDeck, controlDeck );
			shuff4++;
		}
		else
		{
			//failure = 1;
			//printf(RED"Next Player Deck: %d -- Control Deck: %d -- TEST FAILURE \n"RESET, testDeck, controlDeck );
			shufferr4++;
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
				shuff5++;
			}
			else
			{
				//failure = 1;
				//printf(RED"test supply count: %d -- Control supply count: %d -- TEST FAILURE \n"RESET, test_state.supplyCount[y], state.supplyCount[y] );
				shufferr5++;
			}
		
		}		
	}	
		
#if (NOISY_TEST == 1)
	printf(YELLOW"Testing adventurerCard function when currentPlayer is randomized\n and there is a potential shuffle call since the starting hands\nand the starting decks are randomized\n\n"RESET);
#endif	

#if (NOISY_TEST == 1)
	printf(YELLOW"Testing that two cards were added to hand \n"RESET);
#endif	
	printf(GREEN"Total test Successes: %d \n"RESET, shuff1 );
	printf(RED"Total test Failures: %d \n\n"RESET, shufferr1 );	

#if (NOISY_TEST == 1)
	printf(YELLOW"Testing that all cards are still accounted for \n"RESET);
#endif	
	printf(GREEN"Total test Successes: %d \n"RESET, shuff2 );
	printf(RED"Total test Failures: %d \n\n"RESET, shufferr2 );	
	
#if (NOISY_TEST == 1)
	printf(YELLOW"Testing that other players hand hasn't changed \n"RESET);
#endif	
	printf(GREEN"Total test Successes: %d \n"RESET, shuff3 );
	printf(RED"Total test Failures: %d \n\n"RESET, shufferr3 );	
	
#if (NOISY_TEST == 1)
	printf(YELLOW"Testing that other players deck hasn't changed \n"RESET);
#endif	
	printf(GREEN"Total test Successes: %d \n"RESET, shuff4 );
	printf(RED"Total test Failures: %d \n\n"RESET, shufferr4 );
	
#if (NOISY_TEST == 1)
	printf(YELLOW"Testing that there is no change to kingdom cards \n"RESET);
#endif	
	printf(GREEN"Total test Successes: %d \n"RESET, shuff5 );
	printf(RED"Total test Failures: %d \n\n"RESET, shufferr5 );
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		/*
		if(failure == 0)
		{
			printf(GREEN "All tests passed!\n"RESET);
		}
		else
		{
			printf(RED"TEST FAILURE\n"RESET);
		}
		*/
	
	
	return 0;
}