#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define MAX_TESTS 500 

int main() {
    //initialize variables
    int k[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int players, player, seed, handPosition, bonus;
    struct gameState game;
    int choice1 = 0;
    int choice2 = 0; 
    int choice3 = 0;
    int test_failed = 0;
    int test_status = 1; 	
    srand(time(NULL));

   printf("/*********************** Randomly Testing Village Card **************************/\n");

    for (int i = 0; i < MAX_TESTS; i++) {

        //initialize variables randomly
        players = rand() % (MAX_PLAYERS - 2) + 2;
        seed = rand();
        bonus = 0;
        handPosition = rand() % 4;
        player = i % (players);

        initializeGame(players, k, seed, &game); //initialize game 

        //randomly initialize game's state variables
        game.deckCount[player] = rand() % MAX_DECK;   //Pick random deck size out of MAX DECK size
        game.discardCount[player] = rand() % MAX_DECK;
        game.handCount[player] = rand() % MAX_HAND;
        
    	//grab numbers before calling the card
	int handCount1 = numHandCards(&game);
	int actionCards1 = game.numActions;

	//check if card effect works on this card
	if(cardEffect(village, choice1, choice2, choice3, &game, 0, 0) == 0){
	//check if drawn cards has gone up by 1 and one has been discarded

	//grab numbers after calling card	
	 int handCount2 = numHandCards(&game);
        int actionCards2 = game.numActions;

		//check if hand count and number of action points were changed properly	
        	if(handCount2 != (handCount1 + 1 - 1)){
	
			printf("Error: Handcount should not have changed after playing village card\n");
			printf("Hand count before: %d. Hand count after: %d.\n", handCount1, handCount2); 
                        test_failed++; 	
			test_status = 0; //set test state to failed
		}
		if(actionCards2 != (actionCards1 + 2)){									
		 	printf("Error: Number of action points should have increased by 2 after  playing village card\n");
                	printf("Action points before: %d. Action points after: %d.\n", actionCards1, actionCards2); 
			test_failed++;
			test_status = 0; //set test state to failed
        	}
	}
	else {
		printf("Error: card could not be played\n"); 
	}

	if(test_status == 0){
		printf("Iteration %d: test failed\n", i);
	}
	else {
		printf("Iteration %d: test passed \n", i); 
	}
 	
}
	if(test_failed > 0){
		printf("Village card failed %d random tests\n", test_failed); 
	}
	else {
		printf("Village card passed all random tests\n"); 
	}

    return 0;
}
