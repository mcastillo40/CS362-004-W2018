/* -----------------------------------------------------------------------
 * Test gainCard() function
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
int checkGainCard(int supplyPos, struct gameState *post, int toFlag, int p, int * handPass, int *handFail, int *deckPass, int *deckFail, int *discardPass, int *discardFail) {
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));

    int r;
  
    // tests flag 1, that card was added to deck of the player
    if (toFlag == 1){
        r = gainCard (supplyPos, post, toFlag, p);

        if (post->deckCount[p] == pre.deckCount[p] + 1) {
            int temp = *deckPass;
            temp++;
            *deckPass = temp;
        }
        else {
            int temp = *deckFail;
            temp++;
            *deckFail = temp;
        }

        // assert that the supply count was reduced
        assert (supplyCount(supplyPos, post) == supplyCount(supplyPos, &pre) - 1); 
        assert (r == 0);
    }
    else if (toFlag == 2){ // tests flag 2, that card was added to hand of the player
        r = gainCard (supplyPos, post, toFlag, p);

        if (post->handCount[p] == pre.handCount[p] + 1) {
            int temp = *handPass;
            temp++;
            *handPass = temp;
        }
        else {      
            int temp = *handFail;
            temp++;
            *handFail = temp;
        }
        // assert that the supply count was reduced
        assert (supplyCount(supplyPos, post) == supplyCount(supplyPos, &pre) - 1); 
        assert (r == 0);
    }
    else if (toFlag == 0) { // tests flag 0, that card was placed in discard pile
        r = gainCard (supplyPos, post, toFlag, p);

        if (post->discardCount[p] == pre.discardCount[p] + 1) {
            int temp = *discardPass;
            temp++;
            *discardPass = temp;
        }
        else {
            int temp = *discardFail;
            temp++;
            *discardFail = temp;
        }
        
        // assert that the supply count was reduced
        assert (supplyCount(supplyPos, post) == supplyCount(supplyPos, &pre) - 1); 
        assert (r == 0);
    }
    else { // Test to see if -1 will be returned when supplyCount is empty
        for (int i = 0; i < 11; i++)
            r = gainCard (supplyPos, post, toFlag, p);

        assert (r == -1);
    }
    return 0; 
}

int main () {
    int handPass = 0, handFail = 0;
    int deckPass = 0, deckFail = 0;
    int discardPass = 0, discardFail = 0;
    
    int n, p = 0;

    int seed = 1000;
    int numPlayers = 2;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

    printf ("Testing gainCard.\n");

    for (n = 0; n < 2000; n++) {
        p = rand() % 2;
        // Initialize the game state and player cards
        initializeGame(numPlayers, k, seed, &G);

        // Check if card was added to discard pile
        checkGainCard(minion, &G, 0, p, &handPass, &handFail, &deckPass, &deckFail, &discardPass, &discardFail);

        // Check if card was added to deck pile
        checkGainCard(minion, &G, 1, p, &handPass, &handFail, &deckPass, &deckFail, &discardPass, &discardFail);

        // Check if card was added to hand pile
        checkGainCard(minion, &G, 2, p, &handPass, &handFail, &deckPass, &deckFail, &discardPass, &discardFail);

        // Check if supply count is depleted for specific card
        checkGainCard(minion, &G, 3, p, &handPass, &handFail, &deckPass, &deckFail, &discardPass, &discardFail);
    }

    printf("Deck Passed: %d\n", deckPass);
    printf("Deck Failed: %d\n", deckFail);
    printf("Hand Passed: %d\n", handPass);
    printf("Hand Failed: %d\n", handFail);
    printf("Discard Passed: %d\n", discardPass);
    printf("Discard Failed: %d\n", discardFail);

    printf ("ALL TESTS OK\n");

  return 0;
}
