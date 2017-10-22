#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "dominion.h"
#include "rngs.h"
#include <time.h>

//testing supplyCount function in dominion.c

int main(int argc, char** argv){

printf("/*********************** Testing SupplyCount() **************************/\n");

//initialize variables, create a new game state, and call initializeGame()

struct gameState game;
int k[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

//initialize game
int numPlayers = 2;
int seed = rand() % 10;
initializeGame(numPlayers, k, seed, &game);

//set the supply count for a few cards
game.supplyCount[0] = 1;
game.supplyCount[1] = 2;
game.supplyCount[2] = 3; 

//test to see if the supply counts are right

if(supplyCount(0, &game) == 1 && supplyCount(1, &game) == 2 && supplyCount(2, &game) ==3){

printf("SupplyCount() TEST HAS PASSED\n");

}
else {

printf("SupplyCount() TEST HAS FAILED!\n");

}

return 0; 

}
