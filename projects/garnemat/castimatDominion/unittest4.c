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

// Unit test for the fullDeckCount function.

int main () {
	
	printf ("TESTING fullDeckCount():\n");
	
	// seed for rand calls
	srand(time(NULL));

	struct gameState testState;
	int x, y, z;
	int local_counter1 = 0;
	int local_counter2 = 0;
	int count_return1 = 0;
	int count_return2 = 0;
	int failure = 0;
	
	// test arrays
	int* player1_cards = malloc(10 * sizeof(int));
	int* player2_cards = malloc(10 * sizeof(int));

	testState.handCount[0] = 0;
	testState.handCount[1] = 0;
	
	for(x = 0; x < 10; x++)
	{
			// get random number for card for player 1
			int card = rand() % 27;
			
			// add card to hand for player 1
			testState.hand[0][x] = card;
			
			// increment hand count for player 1
			testState.handCount[0] = testState.handCount[0] + 1;
			
			// add card value to test array for player 1
			player1_cards[x] = card;
			
			// get random number for card for player 2
			card = rand() % 27;
			
			// add card to hand for player 2
			testState.hand[1][x] = card;
			
			// increment hand count for player 2
			testState.handCount[1] = testState.handCount[1] + 1;
			
			// add card value to test array for player 2
			player2_cards[x] = card;
	}
	
	// loop through number of cards
	for(y = 0; y < 27; y++)
	{
		local_counter1 = 0;
		local_counter2 = 0;
		
		// loop through test arrays and count cards for both players
		for(z = 0; z < 10; z++)
		{
			
			if(player1_cards[z] == y)
			{
				local_counter1++;
			}
			
			if(player2_cards[z] == y)
			{
				local_counter2++;
			}
		}
		
		// get player 1 count for card y
		count_return1 = fullDeckCount(0, y, &testState);
		
		// get player 2 count for card y
		count_return2 = fullDeckCount(1, y, &testState);
		
		// TEST PLAYER 1 card count
		
#if (NOISY_TEST == 1)
		printf(YELLOW"Testing player 1 hand for card %d - Expecting %d \n"RESET, y, local_counter1);
#endif
		
		if(local_counter1 == count_return1)
		{
			printf(GREEN"fullDeckCount returned: %d - SUCCESS \n\n"RESET, count_return1 );
		}
		else
		{
			failure = 1;
			printf(RED"fullDeckCount returned: %d - FAILURE \n\n"RESET, count_return1 );
		}

		
		
		
		// TEST PLAYER 2 card count
		
#if (NOISY_TEST == 1)
		printf(YELLOW"Testing player 2 hand for card %d - Expecting %d \n"RESET, y, local_counter2);
#endif


		if(local_counter2 == count_return2)
		{
			printf(GREEN"fullDeckCount returned: %d - SUCCESS \n\n"RESET, count_return2 );
		}
		else
		{
			failure = 1;
			printf(RED"fullDeckCount returned: %d - FAILURE \n\n"RESET, count_return2 );
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