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

// Unit test for the kingdomCards function.

int main () {
	
	// allocate memory for array of random numbers
	int* randomArray = malloc(10 * sizeof(int)); 

	int* kingdomCards_result;
	
	int x, y;
	int failure = 0;
	// seed for rand calls
	srand(time(NULL));

	// populate test array with random numbers
	for(x = 0; x < 10; x++)
	{
		randomArray[x] = rand();
	}
	
	printf ("TESTING kingdomCards():\n");
	// call kingdomCards and set to int pointer
	kingdomCards_result = kingdomCards(randomArray[0], randomArray[1], randomArray[2], randomArray[3], randomArray[4], randomArray[5], randomArray[6], randomArray[7], randomArray[8], randomArray[9]);
	
	
	// test original array values versus the return values from kingdomCards
	for(y = 0; y < 10; y++)
	{
		if(randomArray[y] == kingdomCards_result[y])
		{
			printf("Test for position %d Passed \n", y+1);
		}
		else
		{
			printf("Test for position %d FAILED \n", y+1);
			failure = 1;
		}
	}
	
	if(failure == 0)
	{
		printf(GREEN "All tests passed!\n" RESET);
	}
	else
	{
		printf(RED "Test Failure\n" RESET);
	}
	return 0;
}
