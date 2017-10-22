#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

//testing the Embargo card

int main(int argc, char** argv) {

printf("/*********************** Testing Embargo Card **************************/\n");

//declare variables
struct gameState game;
int seed = rand() % 10;
int players = 2;
int choice1 = 0;
int choice2 = 0;
int choice3 = 0;
int handPosition = 4; 
int k[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int bonus = 0; 

//initialize game

initializeGame(players, k, seed, &game);

//grab numbers before calling the card
int handCount1 = numHandCards(&game);
int coinSupply1 = game.coins;

int embargotoken1 = game.embargoTokens;

if(cardEffect(adventurer, choice1, choice2, choice3, &game, handPosition, bonus) == 0){

int handCount2 = numHandCards(&game);
int coinSupply2 = game.coins;
int embargotoken2 = game.embargoTokens;

if(handCount2 != (handCount1  - 1)){
	
	printf("EMBARGO CARD TEST HAS FAILED\n");
}
if(coinSupply2 != (coinSupply1 + 2)){
	printf("EMBARGO CARD TEST HAS FAILED\n");
}

if(embargotoken2 != (embargotoken1 + 1)){
	printf("EMBARGO CARD TEST HAS FAILED\n");
}
else
{
	printf("EMBARGO CARD TEST HAS PASSED\n"); 
}
}
else {
	printf("EMBARGO CARD TEST HAS FAILED\n");
}

return 0;

}

