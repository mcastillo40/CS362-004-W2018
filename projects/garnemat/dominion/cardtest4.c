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

// testing council Room card
int main () {

	struct gameState state, test_state0, test_state1, test_state2, test_state3;
	int seed = 1000;
  int numPlayers = 4;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int drawnCards = 4;
	int other_drawnCards = 1;
	int discard;
	int x, y;
	int failure = 0;

		printf ("\n\nTESTING Council Room Card: \n\n");
	
	// initialize game
 	initializeGame(numPlayers, k, seed, &state);
	
	// call draw card 5 times for other players since initializeGame only draws for first player
	for (x = 0; x < 5; x++)
	{
		drawCard(1, &state);
		drawCard(2, &state);
		drawCard(3, &state);
	}
	
	// copy game state to all 4 test states
	// this is to run the card effect for each players turn
	memcpy(&test_state0, &state, sizeof(struct gameState));
	memcpy(&test_state1, &state, sizeof(struct gameState));
	memcpy(&test_state2, &state, sizeof(struct gameState));
	memcpy(&test_state3, &state, sizeof(struct gameState));
	
	// set each test state to a different players turn
	test_state0.whoseTurn = 0;
	test_state1.whoseTurn = 1;
	test_state2.whoseTurn = 2;
	test_state3.whoseTurn = 3;

	/**
	// call draw card 5 times for other players in other states since initializeGame only draws for first player
	for (x = 0; x < 5; x++)
	{
		drawCard(1, &test_state1);
		drawCard(2, &test_state2);
		drawCard(3, &test_state3);
	}
	**/
	
	// give a player a council room card in hand position 0 in each test state
	test_state0.hand[0][0] = council_room;
	test_state1.hand[1][0] = council_room;
	test_state2.hand[2][0] = council_room;
	test_state3.hand[3][0] = council_room;
	
	// call card effect with council room for each test state
	cardEffect(council_room, choice1, choice2, choice3, &test_state0, handPos, &bonus);
	cardEffect(council_room, choice1, choice2, choice3, &test_state1, handPos, &bonus);
	cardEffect(council_room, choice1, choice2, choice3, &test_state2, handPos, &bonus);
	cardEffect(council_room, choice1, choice2, choice3, &test_state3, handPos, &bonus);

	
	
/************* START TESTS *************/	
	
/************* TEST that 4 cards are drawn - account for council Room being sent to played *************/

#if (NOISY_TEST == 1)
		printf(YELLOW"Testing that each test state play has drawn 4 cards - accounting for council room being sent to played\n"RESET);
#endif

	int controlHandCount, testHandCount0, testHandCount1, testHandCount2, testHandCount3;
	
	controlHandCount = state.handCount[0];
	testHandCount0 = test_state0.handCount[0];
	testHandCount1 = test_state1.handCount[1];
	testHandCount2 = test_state2.handCount[2];
	testHandCount3 = test_state3.handCount[3];
	
#if (NOISY_TEST == 1)
		printf(YELLOW"Each test hand count should be equal, and 3 more than the control hand count\n"RESET);
#endif

	
	//assert(testHandCount0 == testHandCount1);
	
	if(testHandCount0 == testHandCount1)
	{
		printf(GREEN"testHandCount0: %d  testHandCount1: %d  -- SUCCESS\n"RESET, testHandCount0, testHandCount1);
	}
	else
	{
		printf(RED"testHandCount0: %d  testHandCount1: %d  -- FAILURE\n"RESET, testHandCount0, testHandCount1);
		failure = 1;
	}
	
	//assert(testHandCount0 == testHandCount2);
	
	if(testHandCount0 == testHandCount2)
	{
		printf(GREEN"testHandCount0: %d  testHandCount2: %d  -- SUCCESS\n"RESET, testHandCount0, testHandCount2);
	}
	else
	{
		printf(RED"testHandCount0: %d  testHandCount2: %d  -- FAILURE\n"RESET, testHandCount0, testHandCount2);
		failure = 1;
	}
	
	//assert(testHandCount0 == testHandCount3);
	
	if(testHandCount0 == testHandCount3)
	{
		printf(GREEN"testHandCount0: %d  testHandCount3: %d  -- SUCCESS\n"RESET, testHandCount0, testHandCount3);
	}
	else
	{
		printf(RED"testHandCount0: %d  testHandCount3: %d  -- FAILURE\n"RESET, testHandCount0, testHandCount3);
		failure = 1;
	}
	
	//assert(testHandCount1 == testHandCount2);
	
	if(testHandCount1 == testHandCount2)
	{
		printf(GREEN"testHandCount1: %d  testHandCount2: %d  -- SUCCESS\n"RESET, testHandCount1, testHandCount2);
	}
	else
	{
		printf(RED"testHandCount1: %d  testHandCount2: %d  -- FAILURE\n"RESET, testHandCount1, testHandCount2);
		failure = 1;
	}
	
	//assert(testHandCount1 == testHandCount3);
	
	if(testHandCount1 == testHandCount3)
	{
		printf(GREEN"testHandCount1: %d  testHandCount3: %d  -- SUCCESS\n"RESET, testHandCount1, testHandCount3);
	}
	else
	{
		printf(RED"testHandCount1: %d  testHandCount3: %d  -- FAILURE\n"RESET, testHandCount1, testHandCount3);
		failure = 1;
	}
	
	
	//assert(testHandCount2 == testHandCount3);
	
	if(testHandCount2 == testHandCount3)
	{
		printf(GREEN"testHandCount2: %d  testHandCount3: %d  -- SUCCESS\n"RESET, testHandCount2, testHandCount3);
	}
	else
	{
		printf(RED"testHandCount2: %d  testHandCount3: %d  -- FAILURE\n"RESET, testHandCount2, testHandCount3);
		failure = 1;
	}
	
	//assert(controlHandCount == testHandCount0 - 3);
	
	if(controlHandCount == testHandCount0 - 3)
	{
		printf(GREEN"controlHandCount: %d  testHandCount0: %d  -- SUCCESS\n"RESET, controlHandCount, testHandCount0);
	}
	else
	{
		printf(RED"controlHandCount: %d  testHandCount0: %d  -- FAILURE\n"RESET, controlHandCount, testHandCount0);
		failure = 1;
	}
	
	//assert(controlHandCount == testHandCount1 - 3);
	
	if(controlHandCount == testHandCount1 - 3)
	{
		printf(GREEN"controlHandCount: %d  testHandCount1: %d  -- SUCCESS\n"RESET, controlHandCount, testHandCount1);
	}
	else
	{
		printf(RED"controlHandCount: %d  testHandCount1: %d  -- FAILURE\n"RESET, controlHandCount, testHandCount1);
		failure = 1;
	}	
	
	//assert(controlHandCount == testHandCount2 - 3);
	
	if(controlHandCount == testHandCount2 - 3)
	{
		printf(GREEN"controlHandCount: %d  testHandCount2: %d  -- SUCCESS\n"RESET, controlHandCount, testHandCount2);
	}
	else
	{
		printf(RED"controlHandCount: %d  testHandCount2: %d  -- FAILURE\n"RESET, controlHandCount, testHandCount2);
		failure = 1;
	}		
	
	//assert(controlHandCount == testHandCount3 - 3);
	
	if(controlHandCount == testHandCount3 - 3)
	{
		printf(GREEN"controlHandCount: %d  testHandCount3: %d  -- SUCCESS\n"RESET, controlHandCount, testHandCount3);
	}
	else
	{
		printf(RED"controlHandCount: %d  testHandCount3: %d  -- FAILURE\n"RESET, controlHandCount, testHandCount3);
		failure = 1;
	}		
	












/************* TEST that cards came from players deck *************/

#if (NOISY_TEST == 1)
		printf(YELLOW"TESTING that each player drew from their own decks\n"RESET);
#endif

	int controlDeckCount, testDeckCount0, testDeckCount1, testDeckCount2, testDeckCount3;

	controlDeckCount = state.deckCount[0];
	testDeckCount0 = test_state0.deckCount[0];
	testDeckCount1 = test_state1.deckCount[1];
	testDeckCount2 = test_state2.deckCount[2];
	testDeckCount3 = test_state3.deckCount[3];
	
#if (NOISY_TEST == 1)
		printf(YELLOW"Each test deck should be decremented by 4, and thus be 4 less than the control deck\n"RESET);
#endif	


	//assert(testDeckCount0 == controlDeckCount - 4);
	
	if(testDeckCount0 == controlDeckCount - 4)
	{
		printf(GREEN"controlDeckCount: %d  testDeckCount0: %d  -- SUCCESS\n"RESET, controlDeckCount, testDeckCount0);
	}
	else
	{
		printf(RED"controlDeckCount: %d  testDeckCount0: %d  -- FAILURE\n"RESET, controlDeckCount, testDeckCount0);
		failure = 1;
	}		
	
	
	//assert(testDeckCount1 == controlDeckCount - 4);
	
	if(testDeckCount1 == controlDeckCount - 4)
	{
		printf(GREEN"controlDeckCount: %d  testDeckCount1: %d  -- SUCCESS\n"RESET, controlDeckCount, testDeckCount1);
	}
	else
	{
		printf(RED"controlDeckCount: %d  testDeckCount1: %d  -- FAILURE\n"RESET, controlDeckCount, testDeckCount1);
		failure = 1;
	}			
	
	//assert(testDeckCount2 == controlDeckCount - 4);
	
	if(testDeckCount2 == controlDeckCount - 4)
	{
		printf(GREEN"controlDeckCount: %d  testDeckCount2: %d  -- SUCCESS\n"RESET, controlDeckCount, testDeckCount2);
	}
	else
	{
		printf(RED"controlDeckCount: %d  testDeckCount2: %d  -- FAILURE\n"RESET, controlDeckCount, testDeckCount2);
		failure = 1;
	}			
	
	//assert(testDeckCount3 == controlDeckCount - 4);

	if(testDeckCount3 == controlDeckCount - 4)
	{
		printf(GREEN"controlDeckCount: %d  testDeckCount3: %d  -- SUCCESS\n"RESET, controlDeckCount, testDeckCount3);
	}
	else
	{
		printf(RED"controlDeckCount: %d  testDeckCount3: %d  -- FAILURE\n"RESET, controlDeckCount, testDeckCount3);
		failure = 1;
	}		











/************* TEST that all other players draw one card regardless of which player plays the card *************/

#if (NOISY_TEST == 1)
	printf(YELLOW"TESTING that all other players draw one card regardless of which player plays Council Room\n"RESET);
#endif

	int drawCount_state0_1, drawCount_state0_2, drawCount_state0_3; // test_state0
	int drawCount_state1_1, drawCount_state1_2, drawCount_state1_3; // test_state1
	int drawCount_state2_1, drawCount_state2_2, drawCount_state2_3; // test_state2
	int drawCount_state3_1, drawCount_state3_2, drawCount_state3_3; // test_state3
	
	int expectedCount = 6;
	
	// test_state0 players draw count
	drawCount_state0_1 = test_state0.handCount[1];
	drawCount_state0_2 = test_state0.handCount[2];
	drawCount_state0_3 = test_state0.handCount[3];
	
	// test_state1 players draw count
	drawCount_state1_1 = test_state1.handCount[0];
	drawCount_state1_2 = test_state1.handCount[2];
	drawCount_state1_3 = test_state1.handCount[3];	

	// test_state2 players draw count
	drawCount_state2_1 = test_state2.handCount[0];
	drawCount_state2_2 = test_state2.handCount[1];
	drawCount_state2_3 = test_state2.handCount[3];
	
	// test_state3 players draw count
	drawCount_state3_1 = test_state3.handCount[0];
	drawCount_state3_2 = test_state3.handCount[1];
	drawCount_state3_3 = test_state3.handCount[2];
	

#if (NOISY_TEST == 1)
	printf(YELLOW"test_state0 TESTS: Player 0 uses Council Room\n"RESET);
#endif


	// test_state0 TESTS
	
	//assert(drawCount_state0_1 == 6);
	
	if(drawCount_state0_1 == expectedCount)
	{
		printf(GREEN"Player 1: %d -- expected: %d  -- SUCCESS\n"RESET, drawCount_state0_1, expectedCount);
	}
	else
	{
		printf(RED"Player 1: %d -- expected: %d  -- FAILURE\n"RESET, drawCount_state0_1, expectedCount);
		failure = 1;
	}		
	
	
	//assert(drawCount_state0_2 == 6);
	
	if(drawCount_state0_2 == expectedCount)
	{
		printf(GREEN"Player 2: %d -- expected: %d  -- SUCCESS\n"RESET, drawCount_state0_2, expectedCount);
	}
	else
	{
		printf(RED"Player 2: %d -- expected: %d  -- FAILURE\n"RESET, drawCount_state0_2, expectedCount);
		failure = 1;
	}		
	
	
	//assert(drawCount_state0_3 == 6);
	
	if(drawCount_state0_3 == expectedCount)
	{
		printf(GREEN"Player 3: %d -- expected: %d  -- SUCCESS\n"RESET, drawCount_state0_3, expectedCount);
	}
	else
	{
		printf(RED"Player 3: %d -- expected: %d  -- FAILURE\n"RESET, drawCount_state0_3, expectedCount);
		failure = 1;
	}		
	
	
	
#if (NOISY_TEST == 1)
	printf(YELLOW"test_state1 TESTS: Player 1 uses Council Room\n"RESET);
#endif
	
	// test_state1 TESTS
	
	//assert(drawCount_state1_1 == 6);
	
	if(drawCount_state1_1 == expectedCount)
	{
		printf(GREEN"Player 0: %d -- expected: %d  -- SUCCESS\n"RESET, drawCount_state1_1, expectedCount);
	}
	else
	{
		printf(RED"Player 0: %d -- expected: %d  -- FAILURE\n"RESET, drawCount_state1_1, expectedCount);
		failure = 1;
	}			
	
	//assert(drawCount_state1_2 == 6);
	
	if(drawCount_state1_2 == expectedCount)
	{
		printf(GREEN"Player 2: %d -- expected: %d  -- SUCCESS\n"RESET, drawCount_state1_2, expectedCount);
	}
	else
	{
		printf(RED"Player 2: %d -- expected: %d  -- FAILURE\n"RESET, drawCount_state1_2, expectedCount);
		failure = 1;
	}				
	
	//assert(drawCount_state1_3 == 6);
	
	if(drawCount_state1_3 == expectedCount)
	{
		printf(GREEN"Player 3: %d -- expected: %d  -- SUCCESS\n"RESET, drawCount_state1_3, expectedCount);
	}
	else
	{
		printf(RED"Player 3: %d -- expected: %d  -- FAILURE\n"RESET, drawCount_state1_3, expectedCount);
		failure = 1;
	}			
	
	
#if (NOISY_TEST == 1)
	printf(YELLOW"test_state2 TESTS: Player 2 uses Council Room\n"RESET);
#endif	
	
	// test_state2 asserts
	
	//assert(drawCount_state2_1 == 6);
	
	if(drawCount_state2_1 == expectedCount)
	{
		printf(GREEN"Player 0: %d -- expected: %d  -- SUCCESS\n"RESET, drawCount_state2_1, expectedCount);
	}
	else
	{
		printf(RED"Player 0: %d -- expected: %d  -- FAILURE\n"RESET, drawCount_state2_1, expectedCount);
		failure = 1;
	}		
	
	//assert(drawCount_state2_2 == 6);
	
	if(drawCount_state2_2 == expectedCount)
	{
		printf(GREEN"Player 1: %d -- expected: %d  -- SUCCESS\n"RESET, drawCount_state2_2, expectedCount);
	}
	else
	{
		printf(RED"Player 1: %d -- expected: %d  -- FAILURE\n"RESET, drawCount_state2_2, expectedCount);
		failure = 1;
	}	
	
	//assert(drawCount_state2_3 == 6);
	
	if(drawCount_state2_3 == expectedCount)
	{
		printf(GREEN"Player 3: %d -- expected: %d  -- SUCCESS\n"RESET, drawCount_state2_3, expectedCount);
	}
	else
	{
		printf(RED"Player 3: %d -- expected: %d  -- FAILURE\n"RESET, drawCount_state2_3, expectedCount);
		failure = 1;
	}		
	
	
#if (NOISY_TEST == 1)
	printf(YELLOW"test_state3 TESTS: Player 3 uses Council Room\n"RESET);
#endif	
	
	// test_state3 asserts
	
	//assert(drawCount_state3_1 == 6);
	
	if(drawCount_state3_1 == expectedCount)
	{
		printf(GREEN"Player 0: %d -- expected: %d  -- SUCCESS\n"RESET, drawCount_state3_1, expectedCount);
	}
	else
	{
		printf(RED"Player 0: %d -- expected: %d  -- FAILURE\n"RESET, drawCount_state3_1, expectedCount);
		failure = 1;
	}		
	
	//assert(drawCount_state3_2 == 6);
	
	if(drawCount_state3_2 == expectedCount)
	{
		printf(GREEN"Player 1: %d -- expected: %d  -- SUCCESS\n"RESET, drawCount_state3_2, expectedCount);
	}
	else
	{
		printf(RED"Player 1: %d -- expected: %d  -- FAILURE\n"RESET, drawCount_state3_2, expectedCount);
		failure = 1;
	}			
	
	//assert(drawCount_state3_3 == 6);
	
	if(drawCount_state3_3 == expectedCount)
	{
		printf(GREEN"Player 2: %d -- expected: %d  -- SUCCESS\n"RESET, drawCount_state3_3, expectedCount);
	}
	else
	{
		printf(RED"Player 2: %d -- expected: %d  -- FAILURE\n"RESET, drawCount_state3_3, expectedCount);
		failure = 1;
	}			
	











/************* TEST council room is sent to played cards *************/

#if (NOISY_TEST == 1)
		printf(YELLOW"TESTING that council room is properly sent to played cards\n"RESET);
#endif		

int controlPlayed, testPlayed0, testPlayed1, testPlayed2, testPlayed3;


	controlPlayed = state.playedCardCount;
	testPlayed0 = test_state0.playedCardCount;
	testPlayed1 = test_state1.playedCardCount;
	testPlayed2 = test_state2.playedCardCount;
	testPlayed3 = test_state3.playedCardCount;

#if (NOISY_TEST == 1)
	printf(YELLOW "All four test state played counts should be one more than the controlPlayed count\n"RESET);
#endif

	//assert(testPlayed0 == controlPlayed + 1);
	
	if(testPlayed0 == controlPlayed + 1)
	{
		printf(GREEN"controlPlayed: %d -- testPlayed0: %d  -- SUCCESS\n"RESET, controlPlayed, testPlayed0);
	}
	else
	{
		printf(RED"controlPlayed: %d -- testPlayed0: %d  -- FAILURE\n"RESET, controlPlayed, testPlayed0);
		failure = 1;
	}				
	
	//assert(testPlayed1 == controlPlayed + 1);
	
	if(testPlayed1 == controlPlayed + 1)
	{
		printf(GREEN"controlPlayed: %d -- testPlayed1: %d  -- SUCCESS\n"RESET, controlPlayed, testPlayed1);
	}
	else
	{
		printf(RED"controlPlayed: %d -- testPlayed1: %d  -- FAILURE\n"RESET, controlPlayed, testPlayed1);
		failure = 1;
	}					
	
	//assert(testPlayed2 == controlPlayed + 1);
	
	if(testPlayed2 == controlPlayed + 1)
	{
		printf(GREEN"controlPlayed: %d -- testPlayed2: %d  -- SUCCESS\n"RESET, controlPlayed, testPlayed2);
	}
	else
	{
		printf(RED"controlPlayed: %d -- testPlayed2: %d  -- FAILURE\n"RESET, controlPlayed, testPlayed2);
		failure = 1;
	}						
	
	//assert(testPlayed3 == controlPlayed + 1);

	if(testPlayed3 == controlPlayed + 1)
	{
		printf(GREEN"controlPlayed: %d -- testPlayed3: %d  -- SUCCESS\n"RESET, controlPlayed, testPlayed3);
	}
	else
	{
		printf(RED"controlPlayed: %d -- testPlayed3: %d  -- FAILURE\n"RESET, controlPlayed, testPlayed3);
		failure = 1;
	}			
	
	
	
	
#if (NOISY_TEST == 1)
	printf(YELLOW"Confirming that card sent to played cards is a council room card\n"RESET);
#endif	

	int testPlayedCard0 = test_state0.playedCards[0];
	int testPlayedCard1 = test_state1.playedCards[0];
	int testPlayedCard2 = test_state2.playedCards[0];
	int testPlayedCard3 = test_state3.playedCards[0];

#if (NOISY_TEST == 1)
	printf(YELLOW"Council Room Value and Test played card value should be the same \n"RESET);
#endif	
	
	//assert(testPlayedCard0 == council_room);
	
	if(testPlayedCard0 == council_room)
	{
		printf(GREEN"Council Room: %d -- testPlayedCard0: %d  -- SUCCESS\n"RESET, council_room, testPlayedCard0);
	}
	else
	{
		printf(RED"Council Room: %d -- testPlayedCard0: %d  -- FAILURE\n"RESET, council_room, testPlayedCard0);
		failure = 1;
	}				
	
	//assert(testPlayedCard1 == council_room);
	
	if(testPlayedCard1 == council_room)
	{
		printf(GREEN"Council Room: %d -- testPlayedCard1: %d  -- SUCCESS\n"RESET, council_room, testPlayedCard1);
	}
	else
	{
		printf(RED"Council Room: %d -- testPlayedCard1: %d  -- FAILURE\n"RESET, council_room, testPlayedCard1);
		failure = 1;
	}					
	
	//assert(testPlayedCard2 == council_room);
	
	if(testPlayedCard2 == council_room)
	{
		printf(GREEN"Council Room: %d -- testPlayedCard2: %d  -- SUCCESS\n"RESET, council_room, testPlayedCard2);
	}
	else
	{
		printf(RED"Council Room: %d -- testPlayedCard2: %d  -- FAILURE\n"RESET, council_room, testPlayedCard2);
		failure = 1;
	}					
	
	//assert(testPlayedCard3 == council_room);
	
	if(testPlayedCard3 == council_room)
	{
		printf(GREEN"Council Room: %d -- testPlayedCard3: %d  -- SUCCESS\n"RESET, council_room, testPlayedCard3);
	}
	else
	{
		printf(RED"Council Room: %d -- testPlayedCard3: %d  -- FAILURE\n"RESET, council_room, testPlayedCard3);
		failure = 1;
	}				
	


	
	







	
/************* TEST that kingdom cards are unaffected *************/


#if (NOISY_TEST == 1)
		printf(YELLOW"Testing That there are no changes to kingdom cards in any of the 4 test states - Expecting no changes \n"RESET);
#endif		


	for(x = 0; x < 10; x++)
	{
		y = k[x];
		
		//assert(test_state0.supplyCount[y] == state.supplyCount[y]);
		
		if(test_state0.supplyCount[y] == state.supplyCount[y])
		{
			printf(GREEN"test state 0 supply count: %d -- Control supply count: %d -- TEST SUCCESS \n"RESET, test_state0.supplyCount[y], state.supplyCount[y] );
		}
		else
		{
			failure = 1;
			printf(RED"test state 0 supply count: %d -- Control supply count: %d -- TEST FAILURE \n"RESET, test_state0.supplyCount[y], state.supplyCount[y] );
		}
		
		//assert(test_state1.supplyCount[y] == state.supplyCount[y]);
		
		if(test_state1.supplyCount[y] == state.supplyCount[y])
		{
			printf(GREEN"test state 1 supply count: %d -- Control supply count: %d -- TEST SUCCESS \n"RESET, test_state1.supplyCount[y], state.supplyCount[y] );
		}
		else
		{
			failure = 1;
			printf(RED"test state 1 supply count: %d -- Control supply count: %d -- TEST FAILURE \n"RESET, test_state1.supplyCount[y], state.supplyCount[y] );
		}		
		
		//assert(test_state2.supplyCount[y] == state.supplyCount[y]);
		
		if(test_state2.supplyCount[y] == state.supplyCount[y])
		{
			printf(GREEN"test state 2 supply count: %d -- Control supply count: %d -- TEST SUCCESS \n"RESET, test_state2.supplyCount[y], state.supplyCount[y] );
		}
		else
		{
			failure = 1;
			printf(RED"test state 2 supply count: %d -- Control supply count: %d -- TEST FAILURE \n"RESET, test_state2.supplyCount[y], state.supplyCount[y] );
		}				
		
		//assert(test_state3.supplyCount[y] == state.supplyCount[y]);
		
		if(test_state3.supplyCount[y] == state.supplyCount[y])
		{
			printf(GREEN"test state 3 supply count: %d -- Control supply count: %d -- TEST SUCCESS \n"RESET, test_state3.supplyCount[y], state.supplyCount[y] );
		}
		else
		{
			failure = 1;
			printf(RED"test state 3 supply count: %d -- Control supply count: %d -- TEST FAILURE \n"RESET, test_state3.supplyCount[y], state.supplyCount[y] );
		}		
		
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