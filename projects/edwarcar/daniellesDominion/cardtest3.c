
#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

//testing the village card

int main(int argc, char** argv) {

printf("/*********************** Testing Village Card **************************/\n");

//declare variables
struct gameState game;
int seed = rand() % 10; 
int players = 2;
int choice1 = 0;
int choice2 = 0; 
int choice3 = 0;

int k[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

//initialize game

initializeGame(players, k, seed, &game);

//grab numbers before calling the card
int handCount1 = numHandCards(&game);
int actionCards1 = game.numActions;

if(cardEffect(village, choice1, choice2, choice3, &game, 0, 0) == 0){

	int handCount2 = numHandCards(&game);
	int actionCards2 = game.numActions; 

	//check if drawn cards has gone up by 1 and one has been discarded
	if((handCount2 == (handCount1 + 1 - 1)) && (actionCards2 == (actionCards1 + 2))){

		printf("VILLAGE CARD TEST HAS PASSED\n");
	}
	else
		printf("VILLAGE CARD TEST HAS FAILED\n");

}
else {

	printf("VILLAGE CARD TEST HAS FAILED\n");
}


return 0;

}
