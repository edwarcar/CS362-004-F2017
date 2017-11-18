#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

//testing the adventurer card

int main(int argc, char** argv) {
printf("/*********************** Testing Adventurer Card **************************/\n");
//declare variables
struct gameState game;
int seed = rand() % 10;
int players = 2;
int bonus = 0; 
int handPosition = 4; 
int choice1, choice2, choice3 = 0; 
int k[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

//initialize game

initializeGame(players, k, seed, &game);

//grab numbers before calling the card
int handCount1 = numHandCards(&game);

if(cardEffect(adventurer, choice1, choice2, choice3, &game, handPosition, bonus) == 0){

int handCount2 = numHandCards(&game);

	//check if deck has grown by more than 2 (number of treasure cards that can be taken with this card)
	if(handCount2 == (handCount1 + 2)){
		printf("ADVENTURER CARD TEST HAS PASSED\n");
	}
	else {
		 printf("ADVENTURER CARD TEST HAS FAILED\n");
	}
}
else
{
	printf("ADVENTURER CARD TEST HAS FAILED\n");
}

return 0;

}
