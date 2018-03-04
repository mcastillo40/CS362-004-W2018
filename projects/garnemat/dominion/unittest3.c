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


// Unit test for the whoseTurn function.

int main () {

	struct gameState testState;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int numPlayer = 4;
	int seed = 1234;
	int x;
	int counter = 0;
	int rollover = 0;
	int whoseTurn_value;
	int failure = 0;
	int init_value = initializeGame(numPlayer, k, seed, &testState);
	
	printf ("TESTING whoseTurn():\n");
	
	// run for loop 10 times to account for rollover back to the first player
	for(x = 0; x < 10; x++)
	{
		// Test for player rollover and account for rollover in output.
		if(counter == numPlayer)
		{
			rollover = rollover + numPlayer;
			counter = 0;
#if (NOISY_TEST == 1)		
		printf(YELLOW"All players have had a turn, rolling over to player 1"RESET);
#endif					
			
			
		}
		
		whoseTurn_value = whoseTurn(&testState);
#if (NOISY_TEST == 1)		
		printf(YELLOW"Player Turn expected: %d \n"RESET, x - rollover + 1);
#endif		
		
		if(x - rollover == whoseTurn_value)
		{
			printf(GREEN "whoseTurn() indicates Player Turn: %d - TEST SUCCESS\n\n"RESET, whoseTurn_value + 1);
		}
		else
		{
			printf(RED "whoseTurn() indicates Player Turn: %d - TEST FAILURE\n\n"RESET, whoseTurn_value + 1);
			failure = 1;
		}

		// call endTurn to advance turn.
		int endturn_value = endTurn(&testState);
		
		counter++;
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