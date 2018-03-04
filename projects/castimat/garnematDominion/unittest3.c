/* -----------------------------------------------------------------------
 * Test isGameOver() function
 *
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// int checkGainCard(int p, struct gameState *post) {
int checkIsGameOver(struct gameState *post, int testFlag, int p) {
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));

    int r;
  
    if (testFlag == 0) { // Test if all province cards have been taken
        for (int i = 0; i < 8; i++){
           assert(gainCard(province, post, 1, p) == 0); 
        }

        assert (supplyCount(province, post) == supplyCount(province, &pre) - 8);
        
        r = isGameOver(post);

        assert(r == 1);
        assert(numHandCards(post) == numHandCards(&pre));

        // Check various states of the game for each player is unchanged
        for (int i = 0; i < 2; i++) {
            assert(post->handCount[i] == pre.handCount[i]);
            
            if (i == 0)
                assert(post->deckCount[i] == pre.deckCount[i] + 8);
            else 
                assert(post->deckCount[i] == pre.deckCount[i]);
            
            assert(post->discardCount[i] == pre.discardCount[i]);
        }

        // Assert that none of the card supplies has changed
        for (int i = 0; i < treasure_map + 1; i++) {
            if (i == province)
                assert(post->supplyCount[i] == pre.supplyCount[i] - 8);
            else
                assert(post->supplyCount[i] == pre.supplyCount[i]);
        }

        // Assert that played cards and deck count have not changed
        for (int i = 0; i < MAX_DECK; i++) {
            assert(post->playedCards[i] == pre.playedCards[i]);
        }
    }
    else if (testFlag == 1) { // Test if three supply pile are at 0
        for (int i = 0; i < 10; i++){
           assert(gainCard(adventurer, post, 1, p) == 0); 
           assert(gainCard(council_room, post, 1, p) == 0);
           assert(gainCard(mine, post, 1, p) == 0);
        }
        
        r = isGameOver(post);

        // assert that game is over
        assert(r == 1);

        // Assert that the selected cards have been emptied
        assert (supplyCount(adventurer, post) == supplyCount(adventurer, &pre) - 10);
        assert (supplyCount(council_room, post) == supplyCount(council_room, &pre) - 10);
        assert (supplyCount(mine, post) == supplyCount(mine, &pre) - 10);

        // Assert that none of the card supplies has changed
        for (int i = 0; i < treasure_map + 1; i++) {
            if (i == adventurer || i == council_room || i == mine)
                assert(post->supplyCount[i] == pre.supplyCount[i] - 10);
            else
                assert(post->supplyCount[i] == pre.supplyCount[i]);
        }

        // Assert that played cards and deck count have not changed
        for (int i = 0; i < MAX_DECK; i++) {
            assert(post->playedCards[i] == pre.playedCards[i]);
        }
    }
    else { // Test if the game is not over
        r = isGameOver(post);

        assert(r == 0);

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
    }

    return 0;

}

int main (int argc, char** argv) {
    int n, p = 0;
    int checkProvinceCards = 0, checkSupplyPile = 1, checkNotOver = 2;

    int seed = 1000;
    int numPlayers = 2;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

    printf ("Testing isGameOver.\n");

    for (n = 0; n < 2000; n++) {
        // Initialize the game state and player cards
        initializeGame(numPlayers, k, seed, &G);

        // Test if all province cards have been taken
        checkIsGameOver(&G, checkProvinceCards, p);
        G.supplyCount[province] = 8;

        // Test if three supply piles are at 0
        checkIsGameOver(&G, checkSupplyPile, p);
        G.supplyCount[adventurer] = 8;
        G.supplyCount[council_room] = 8;
        G.supplyCount[mine] = 8;

        // Test if the game is not over
        checkIsGameOver(&G, checkNotOver, p);
    }

    printf ("ALL TESTS OK\n");

	return 0;
} 