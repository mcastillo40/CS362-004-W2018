/* -----------------------------------------------------------------------
 * Test whoseTurn() function
 *
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h> 
#include <assert.h>
#include <math.h>
#include "rngs.h"

// int checkGainCard(int p, struct gameState *post) {
int checkWhoseTurn(struct gameState *post, int p, int o) {

    int r;
    
    for (int turn = 0; turn < 5; turn++){
        r = whoseTurn(post);
        assert(r == p);

        // End turn for the player 1 
        endTurn(post);

        r = whoseTurn(post);
        assert(r == o);

        // End turn for the player 2
        endTurn(post);
    }

    return 0;

}

int main (int argc, char** argv) {
    int n, p, o = 0;

    int seed = 1000;
    int numPlayers = 2;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

    printf ("Testing whoseTurn.\n");

    for (n = 0; n < 2000; n++) {
        p = rand() % 2;

        if (p == 0)
            o = 1;
        else 
            o = 0;

        // Initialize the game state and player cards
        initializeGame(numPlayers, k, seed, &G);

        G.whoseTurn = p; 

        // Test if all province cards have been taken
        checkWhoseTurn(&G, p, o);
    }

    printf ("ALL TESTS OK\n");

	return 0;
} 