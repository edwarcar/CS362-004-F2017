#include "dominion.h"
#include <assert.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

//test of isGameOver() function in dominion.c

int main(int argc, char **argv) {

printf("/*********************** Testing IsGameOver() **************************/\n");

//create a gamestate

struct gameState game;
int k[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

//initialize game
int numPlayers = 2;
int seed = rand() % 10; 
initializeGame(numPlayers, k, seed, &game); 

//stack of province cards should be at 0 for game to end

//set province count to 0
game.supplyCount[province] = 0;

if(isGameOver(&game) != 1){
	printf("ISGAMEOVER() TEST HAS FAILED\n");
}

//check if 3 of the supply piles are at 0

//first set supply counts to 0
game.supplyCount[1] = 0;
game.supplyCount[2] = 0;
game.supplyCount[3] = 0; 

if(isGameOver(&game) != 1){
	printf("ISGAMEOVER() TEST HAS FAILED\n");
}

printf("ISGAMEOVER() TEST HAS PASSED\n");
return 0; 

}

