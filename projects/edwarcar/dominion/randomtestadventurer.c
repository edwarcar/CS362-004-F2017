#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TESTS 500 

int main() {
printf("/*********************** Testing Adventurer Card **************************/\n");

    //initialize variables
    int k[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int players;
    int player;
    int handCount;
    int deckCount;
    int seed;
    int handPosition;
    int bonus;
    struct gameState game;
    int test_state; 
    int test_failed = 0; 
    int handCountAfter;
    int deckCountAfter; 	
    srand(time(NULL));

    // set up loop to run MAX_TESTS number of random tests
    for (int i = 0; i < MAX_TESTS; i++) {

	//initialize variables
        players = rand() % (MAX_PLAYERS - 2) + 2;
        seed = rand();
        bonus = 0;
        handPosition = rand() % 4;
        player = i % (players);
        test_state = 1; 

	// initialize game
        initializeGame(players, k, seed, &game); 

        //randomly initialize variables 
        game.deckCount[player] = rand() % MAX_DECK;   //Pick random deck size out of MAX DECK size
        game.discardCount[player] = rand() % MAX_DECK;
        game.handCount[player] = rand() % MAX_HAND;
        
        // get hand count and deck count before using card 
        handCount = numHandCards(&game);
        deckCount = game.deckCount[player];
        
	//check if cardEffect ran properly
 	if( cardEffect(adventurer, 1, 1, 1, &game, handPosition, bonus) == 0){

		//get hand count and deck count after using card
		handCountAfter = numHandCards(&game); 
		deckCountAfter = game.deckCount[player];
 
		//compare hand count and deck count after using card to see if the the card is working properly
        	if (handCountAfter != (handCount + 2)) {
            		printf("Error: handCount should increase by 2 after drawing an adventurer card\n");
            		printf("Hand count before: %d. Hand count after: %d\n", handCount, handCountAfter); 
			test_state = 0; //set test state to failed
	    		test_failed++; 	
        	}
		if (deckCountAfter > deckCount && deckCount != 0) {
	    		printf("Error: deck count should have decreased!\n"); 
	   		printf("Hand deck before: %d. Deck count after: %d\n", deckCount, deckCountAfter);
			test_failed++; 
			test_state = 0; //set test state to failed
 		}
    	}
	//if cardEffect didn't work, print error
	else {
		printf(" Error: card could not be played\n");
		test_state = 0; //set test state to failed
	}


        if(test_state == 1){
    		printf("Iteration %d: test passed\n" , i); 
    	}
	else{
		printf("Iteration %d: test failed\n" , i); 
	}
     }

    if(test_failed > 0){
	printf("Adventurer card failed %d random tests\n", test_failed);
    }		
    else {
        printf("Adventurer card passed all tests\n");  
    }	
    return 0;
}
