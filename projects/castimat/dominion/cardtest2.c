/*
 * cardtest2.c
 * Tests Adventurer card
 * Draw cards until reveal 2 treasure cards
 * Put treasure cards in your hand then discard the revealed cards
 * 
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int main() {
	int n;
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int seed = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	
  for (n = 0; n < 4; n++) {

    if (n == 0) { // Test if copper is drawn
      printf("Testing copper\n");
      struct gameState G, testG;
      int temphand[MAX_HAND];
      int cardDrawn;
      int drawntreasure = 0, z = 0;

      // Initialize the game state and player cards
      initializeGame(numPlayers, k, seed, &G);

      for (int i = 0; i < G.deckCount[0]; i++){
        if (G.deck[0][i] == silver || G.deck[0][i] == gold || G.deck[0][i] == adventurer)
          G.deck[0][i] = smithy; 
      }

      for (int i = 0; i < G.handCount[0]; i++) {
        if (i == 0)
          G.hand[0][i] = adventurer;
        else
          G.hand[0][i] = smithy;
      }

      // add Copper to deck
      for (int i = 0; i < 3; i++) 
        gainCard(copper, &G, 1, thisPlayer);

      // Shuffle deck 
      shuffle(0, &G);

      // Copy the game state to a test case
      memcpy(&testG, &G, sizeof(struct gameState));

      while (drawntreasure < 2) {
        
        if (G.deckCount[0] < 1){ //if the deck is empty we need to shuffle discard and add to deck
          shuffle(0, &G);
        }

        drawCard(0, &G); 

        cardDrawn = G.hand[0][G.handCount[0]-1]; //top card of hand is most recently drawn card.
        
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) 
          drawntreasure++;
        else  {
          temphand[z] = cardDrawn;
          G.handCount[0]--; //this should just remove the top card (the most recently drawn one).
          z++;
        }
      }
      while(z - 1 >= 0){
        G.discard[0][G.discardCount[0]++] = temphand[z - 1]; // discard all cards in play that have been drawn
        z=z-1;
      }

      // Play adventurer card for testing
      cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

      int originalTreasureCount = 0, testTreasureCount = 0; 
      int originalcopperCount = 0, testcopperCount = 0;
      int originalsilverCount = 0, testsilverCount = 0;
      int originalgoldCount = 0, testgoldCount = 0;

      for (int i = 0; i < testG.handCount[0]; i++) {
        if (testG.hand[0][i] == copper || testG.hand[0][i] == silver || testG.hand[0][i] == gold )
          testTreasureCount++;
        if (testG.hand[0][i] == copper)
          testcopperCount++;
        if (testG.hand[0][i] == silver)
          testsilverCount++;
        if (testG.hand[0][i] == gold)
          testgoldCount++;
      }

      for (int i = 0; i < G.handCount[0]; i++) {
        if (G.hand[0][i] == copper || G.hand[0][i] == silver || G.hand[0][i] == gold)
          originalTreasureCount++;
        if (G.hand[0][i] == copper)
          originalcopperCount++;
        if (G.hand[0][i] == silver)
          originalsilverCount++;
        if (G.hand[0][i] == gold)
          originalgoldCount++;
      }

      printf("Treasure Count in hand: %d; expected: %d\n", testTreasureCount, originalTreasureCount); 
      printf("Copper Count in hand: %d; expected: %d\n", testcopperCount, originalcopperCount); 
      printf("Silver Count in hand: %d; expected: %d\n", testsilverCount, originalsilverCount); 
      printf("Gold Count in hand: %d; expected: %d\n", testgoldCount, originalgoldCount);
      printf("Hand count: %d; expected: %d\n", testG.handCount[0], G.handCount[0] - 1); 
      printf("Deck count: %d; expected: %d\n\n", testG.deckCount[0], G.deckCount[0]); 
    }
    else if (n == 1) { // Test if silver is drawn
      printf("Testing silver\n");

      struct gameState G, testG;
      int temphand[MAX_HAND];
      int cardDrawn;
      int drawntreasure = 0, z = 0;

      // Initialize the game state and player cards
      initializeGame(numPlayers, k, seed, &G);

      for (int i = 0; i < G.deckCount[0]; i++){
        if (G.deck[0][i] == copper || G.deck[0][i] == gold || G.deck[0][i] == adventurer)
          G.deck[0][i] = smithy; 
      }

      for (int i = 0; i < G.handCount[0]; i++) {
        if (i == 0)
          G.hand[0][i] = adventurer;
        else
          G.hand[0][i] = smithy;
      }

      // add Silver to deck
      for (int i = 0; i < 3; i++) {
        gainCard(silver, &G, 1, thisPlayer);
      }

      // Shuffle deck 
      shuffle(0, &G);

      // Copy the game state to a test case
      memcpy(&testG, &G, sizeof(struct gameState));

      while (drawntreasure < 2) {
        
        if (G.deckCount[0] < 1){ //if the deck is empty we need to shuffle discard and add to deck
          shuffle(0, &G);
        }

        drawCard(0, &G); 

        cardDrawn = G.hand[0][G.handCount[0]-1]; //top card of hand is most recently drawn card.

        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) 
          drawntreasure++;
        else  {
          temphand[z] = cardDrawn;
          G.handCount[0]--; //this should just remove the top card (the most recently drawn one).
          z++;
        }
      }
      while(z - 1 >= 0){
        G.discard[0][G.discardCount[0]++] = temphand[z - 1]; // discard all cards in play that have been drawn
        z=z-1;
      }

      // Play adventurer card for testing
      cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

      int originalTreasureCount = 0, testTreasureCount = 0; 
      int originalcopperCount = 0, testcopperCount = 0;
      int originalsilverCount = 0, testsilverCount = 0;
      int originalgoldCount = 0, testgoldCount = 0;

      for (int i = 0; i < testG.handCount[0]; i++) {
        if (testG.hand[0][i] == copper || testG.hand[0][i] == silver || testG.hand[0][i] == gold )
          testTreasureCount++;
        if (testG.hand[0][i] == copper)
          testcopperCount++;
        if (testG.hand[0][i] == silver)
          testsilverCount++;
        if (testG.hand[0][i] == gold)
          testgoldCount++;
      }

      for (int i = 0; i < G.handCount[0]; i++) {
        if (G.hand[0][i] == copper || G.hand[0][i] == silver || G.hand[0][i] == gold)
          originalTreasureCount++;
        if (G.hand[0][i] == copper)
          originalcopperCount++;
        if (G.hand[0][i] == silver)
          originalsilverCount++;
        if (G.hand[0][i] == gold)
          originalgoldCount++;
      }

      printf("Treasure Count in hand: %d; expected: %d\n", testTreasureCount, originalTreasureCount); 
      printf("Copper Count in hand: %d; expected: %d\n", testcopperCount, originalcopperCount); 
      printf("Silver Count in hand: %d; expected: %d\n", testsilverCount, originalsilverCount); 
      printf("Gold Count in hand: %d; expected: %d\n", testgoldCount, originalgoldCount);
      printf("Hand count: %d; expected: %d\n", testG.handCount[0], G.handCount[0] - 1); 
      printf("Deck count: %d; expected: %d\n\n", testG.deckCount[0], G.deckCount[0]); 
      
    }
    else if (n == 2) { // Test if gold is drawn
      printf("Testing gold\n");

      struct gameState G, testG;
      int temphand[MAX_HAND];
      int cardDrawn;
      int drawntreasure = 0, z = 0;

      // Initialize the game state and player cards
      initializeGame(numPlayers, k, seed, &G);

      for (int i = 0; i < G.deckCount[0]; i++){
        if (G.deck[0][i] == copper || G.deck[0][i] == silver || G.deck[0][i] == adventurer)
          G.deck[0][i] = smithy; 
      }

      for (int i = 0; i < G.handCount[0]; i++) {
        if (i == 0)
          G.hand[0][i] = adventurer;
        else
          G.hand[0][i] = smithy;
      }

      // add Gold to deck
      for (int i = 0; i < 3; i++) {
        gainCard(gold, &G, 1, thisPlayer);
      }

      // Shuffle deck 
      shuffle(0, &G);

      // Copy the game state to a test case
      memcpy(&testG, &G, sizeof(struct gameState));

      while (drawntreasure < 2) {
        
        if (G.deckCount[0] < 1){ //if the deck is empty we need to shuffle discard and add to deck
          shuffle(0, &G);
        }

        drawCard(0, &G); 

        cardDrawn = G.hand[0][G.handCount[0]-1]; //top card of hand is most recently drawn card.
        
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) 
          drawntreasure++;
        else  {
          temphand[z] = cardDrawn;
          G.handCount[0]--; //this should just remove the top card (the most recently drawn one).
          z++;
        }
      }
      while(z - 1 >= 0){
        G.discard[0][G.discardCount[0]++] = temphand[z - 1]; // discard all cards in play that have been drawn
        z=z-1;
      }

      // Play adventurer card for testing
      cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

      int originalTreasureCount = 0, testTreasureCount = 0; 
      int originalcopperCount = 0, testcopperCount = 0;
      int originalsilverCount = 0, testsilverCount = 0;
      int originalgoldCount = 0, testgoldCount = 0;

      for (int i = 0; i < testG.handCount[0]; i++) {
        if (testG.hand[0][i] == copper || testG.hand[0][i] == silver || testG.hand[0][i] == gold )
          testTreasureCount++;
        if (testG.hand[0][i] == copper)
          testcopperCount++;
        if (testG.hand[0][i] == silver)
          testsilverCount++;
        if (testG.hand[0][i] == gold)
          testgoldCount++;
      }

      for (int i = 0; i < G.handCount[0]; i++) {
        if (G.hand[0][i] == copper || G.hand[0][i] == silver || G.hand[0][i] == gold)
          originalTreasureCount++;
        if (G.hand[0][i] == copper)
          originalcopperCount++;
        if (G.hand[0][i] == silver)
          originalsilverCount++;
        if (G.hand[0][i] == gold)
          originalgoldCount++;
      }

      printf("Treasure Count in hand: %d; expected: %d\n", testTreasureCount, originalTreasureCount); 
      printf("Copper Count in hand: %d; expected: %d\n", testcopperCount, originalcopperCount); 
      printf("Silver Count in hand: %d; expected: %d\n", testsilverCount, originalsilverCount); 
      printf("Gold Count in hand: %d; expected: %d\n", testgoldCount, originalgoldCount);
      printf("Hand count: %d; expected: %d\n", testG.handCount[0], G.handCount[0] - 1); 
      printf("Deck count: %d; expected: %d\n\n", testG.deckCount[0], G.deckCount[0]); 
      
    }
    else { // Test if any treasure were drawn
      printf("Testing All\n");

      struct gameState G, testG;
      int temphand[MAX_HAND];
      int cardDrawn;
      int drawntreasure = 0, z = 0;

      // Initialize the game state and player cards
      initializeGame(numPlayers, k, seed, &G);

      // add all treasure to deck
      for (int i = 0; i < 3; i++) {
        gainCard(copper, &G, 1, thisPlayer);
        gainCard(silver, &G, 1, thisPlayer);
        gainCard(gold, &G, 1, thisPlayer);
      }

      // Shuffle deck 
      shuffle(0, &G);

      // Copy the game state to a test case
      memcpy(&testG, &G, sizeof(struct gameState));

      while (drawntreasure < 2) {
        
        if (G.deckCount[0] < 1){ //if the deck is empty we need to shuffle discard and add to deck
          shuffle(0, &G);
        }

        drawCard(0, &G); 

        cardDrawn = G.hand[0][G.handCount[0]-1]; //top card of hand is most recently drawn card.
        
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) 
          drawntreasure++;
        else  {
          temphand[z] = cardDrawn;
          G.handCount[0]--; //this should just remove the top card (the most recently drawn one).
          z++;
        }
      }
      while(z - 1 >= 0){
        G.discard[0][G.discardCount[0]++] = temphand[z - 1]; // discard all cards in play that have been drawn
        z=z-1;
      }

      // Play adventurer card for testing
      cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

      int originalTreasureCount = 0, testTreasureCount = 0; 
      int originalcopperCount = 0, testcopperCount = 0;
      int originalsilverCount = 0, testsilverCount = 0;
      int originalgoldCount = 0, testgoldCount = 0;

      for (int i = 0; i < testG.handCount[0]; i++) {
        if (testG.hand[0][i] == copper || testG.hand[0][i] == silver || testG.hand[0][i] == gold )
          testTreasureCount++;
        if (testG.hand[0][i] == copper)
          testcopperCount++;
        if (testG.hand[0][i] == silver)
          testsilverCount++;
        if (testG.hand[0][i] == gold)
          testgoldCount++;
      }

      for (int i = 0; i < G.handCount[0]; i++) {
        if (G.hand[0][i] == copper || G.hand[0][i] == silver || G.hand[0][i] == gold)
          originalTreasureCount++;
        if (G.hand[0][i] == copper)
          originalcopperCount++;
        if (G.hand[0][i] == silver)
          originalsilverCount++;
        if (G.hand[0][i] == gold)
          originalgoldCount++;
      }

      printf("Treasure Count in hand: %d; expected: %d\n", testTreasureCount, originalTreasureCount); 
      printf("Copper Count in hand: %d; expected: %d\n", testcopperCount, originalcopperCount); 
      printf("Silver Count in hand: %d; expected: %d\n", testsilverCount, originalsilverCount); 
      printf("Gold Count in hand: %d; expected: %d\n", testgoldCount, originalgoldCount); 
      printf("Hand count: %d; expected: %d\n", testG.handCount[0], G.handCount[0] - 1); 
      printf("Deck count: %d; expected: %d\n\n", testG.deckCount[0], G.deckCount[0]); 

    }
  }


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}


