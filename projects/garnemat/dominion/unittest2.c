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

// Unit test for the getCost function.

int main () {
	
	int failure = 0;
	int x;
	int getCost_return_value;
	
	// create array with cost of cards
	int* cost_of_cards = malloc(27 * sizeof(int));
	cost_of_cards[0] = 0;  // curse
  cost_of_cards[1] = 2;  // estate
  cost_of_cards[2] = 5;  // duchy
  cost_of_cards[3] = 8;  // province
  cost_of_cards[4] = 0;  // copper
  cost_of_cards[5] = 3;  // silver
  cost_of_cards[6] = 6;  // gold
  cost_of_cards[7] = 6;  // adventurer
  cost_of_cards[8] = 5;  // council room
  cost_of_cards[9] = 4;  // feast
	cost_of_cards[10] = 4; // gardens
  cost_of_cards[11] = 5; // mine
  cost_of_cards[12] = 4; // remodel
  cost_of_cards[13] = 4; // smithy
  cost_of_cards[14] = 3; // village
  cost_of_cards[15] = 4; // baron
  cost_of_cards[16] = 3; // great hall
  cost_of_cards[17] = 5; // minion
  cost_of_cards[18] = 3; // steward
  cost_of_cards[19] = 5; // tribute
	cost_of_cards[20] = 3; // ambassador
  cost_of_cards[21] = 4; // cutpurse
  cost_of_cards[22] = 2; // embargo
  cost_of_cards[23] = 5; // outpost
  cost_of_cards[24] = 4; // salvager
  cost_of_cards[25] = 4; // sea hag
  cost_of_cards[26] = 4; // treasure map
	
	printf ("TESTING getCost():\n");

	for(x = 0; x < 27; x++)
	{
		getCost_return_value = getCost(x);
		
		if(cost_of_cards[x] == getCost_return_value)
		{
			printf(GREEN "Test for card %d Passed\n" RESET, x);
		}
		else
		{
			printf(RED "Test for card %d FAILED\n" RESET, x);
			failure = 1;
		}

	}
	if(failure == 0)
	{
		printf(GREEN"All tests passed!\n"RESET);
	}
	else
	{
		printf(RED"TEST FAILURE\n"RESET);
	}
	return 0;
}
