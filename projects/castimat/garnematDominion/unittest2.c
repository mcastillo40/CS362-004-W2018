/* -----------------------------------------------------------------------
 * Test getCost() function
 *
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

// int checkGainCard(int p, struct gameState *post) {
int checkGetCost(int supplyPos, struct gameState *post) {
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));
    
    int r;

    // Validate that each returns the accurate cost
    switch( supplyPos ) 
    {
    case curse:
        r = getCost (supplyPos);
        assert(r == 0);
        break;
    case estate:
        r = getCost (supplyPos);
        assert(r == 2);
        break;    
    case duchy:
        r = getCost (supplyPos);
        assert(r == 5);
        break;
    case province:
        r = getCost (supplyPos);
        assert(r == 8);
        break;
    case copper:
        r = getCost (supplyPos);
        assert(r == 0);
        break;
    case silver:
        r = getCost (supplyPos);
        assert(r == 3);
        break;
    case gold:
        r = getCost (supplyPos);
        assert(r == 6);
        break;
    case adventurer:
        r = getCost (supplyPos);
        assert(r == 6);
        break;
    case council_room:
        r = getCost (supplyPos);
        assert(r == 5);
        break;
    case feast:
        r = getCost (supplyPos);
        assert(r == 4);
        break;
    case gardens:
        r = getCost (supplyPos);
        assert(r == 4);
        break;
    case mine:
        r = getCost (supplyPos);
        assert(r == 5);
        break;
    case remodel:
        r = getCost (supplyPos);
        assert(r == 4);
        break;
    case smithy:
        r = getCost (supplyPos);
        assert(r == 4);
        break;
    case village:
        r = getCost (supplyPos);
        assert(r == 3);
        break;
    case baron:
        r = getCost (supplyPos);
        assert(r == 4);
        break;
    case great_hall:
        r = getCost (supplyPos);
        assert(r == 3);
        break;
    case minion:
        r = getCost (supplyPos);
        assert(r == 5);
        break;
    case steward:
        r = getCost (supplyPos);
        assert(r == 3);
        break;
    case tribute:
        r = getCost (supplyPos);
        assert(r == 5);
        break;
    case ambassador:
        r = getCost (supplyPos);
        assert(r == 3);
        break;
    case cutpurse:
        r = getCost (supplyPos);
        assert(r == 4);
        break;
    case embargo: 
        r = getCost (supplyPos);
        assert(r == 2);
        break;
    case outpost:
        r = getCost (supplyPos);
        assert(r == 5);
        break;
    case salvager:
        r = getCost (supplyPos);
        assert(r == 4);
        break;
    case sea_hag:
        r = getCost (supplyPos);
        assert(r == 4);
        break;
    case treasure_map:
        r = getCost (supplyPos);
        assert(r == 4);
        break;
    case treasure_map + 1: 
        r = getCost (supplyPos);
        assert(r == -1);
        break;
    }

    // Check various states of the game for each player is unchanged
    for (int i = 0; i < 2; i++) {
        assert(post->handCount[i] == pre.handCount[i]);
        assert(post->deckCount[i] == pre.deckCount[i]);
        assert(post->discardCount[i] == pre.discardCount[i]);
    }

    // Assert that none of the card supplies has changed
    for (int i = 0; i < treasure_map + 1; i++) {
        assert(post->supplyCount[i] == pre.supplyCount[i]);
    }

    // Assert that played cards and deck count have not changed
    for (int i = 0; i < MAX_DECK; i++) {
        assert(post->playedCards[i] == pre.playedCards[i]);
    }

    return 0;
}

int main () {

    int i, n;

    int seed = 1000;
    int numPlayers = 2;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

    printf ("Testing getCost.\n");

    for (n = 0; n < 2000; n++) {
        for (i = 0; i < treasure_map + 2; i++) {
            // Initialize the game state and player cards
            initializeGame(numPlayers, k, seed, &G);

            // Check the cost of the specific card
            checkGetCost(i, &G);
        }
    }

    printf ("ALL TESTS OK\n");

  return 0;
}
