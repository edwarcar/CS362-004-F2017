#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

//testing the smithy card

int main(int argc, char** argv) {

printf("/*********************** Testing Smithy Card **************************/\n");

//declare variables
struct gameState game;

int players = 2; 

int k[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int seed = rand() % 10;  
int bonus = 0;
int handPosition = 4;
int choice1 = 0;
int choice2 = 0; 
int choice3 = 0; 
//initialize game

initializeGame(players, k, seed, &game);

//grab numbers before calling the card
int handCount1 = numHandCards(&game);

if(cardEffect(smithy, choice1, choice2, choice3, &game, handPosition, bonus) == 0){

	int handCount2 = numHandCards(&game); 

	if(handCount2 == (handCount1 + 3 - 1)) {
		printf("SMITHY CARD TEST HAS PASSED\n"); 	
	}
	else {
		printf("SMITHY CARD TEST HAS FAILED \n");
	}
}
else {

	printf("SMITHY CARD TEST HAS FAILED!\n");
}

 return 0; 
}
