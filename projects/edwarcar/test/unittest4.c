#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "rngs.h"
#include <time.h>

//testing initializeGame function in dominion.c

int main(int argc, char** argv){

printf("/*********************** Testing InitializeGame() **************************/\n");

//initialize variables, create a new game state

struct gameState game;
int numPlayers; 
int k[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int seed = rand() % 10; 

//test out a few scenarios

//test 1 - invalid number of players
numPlayers = 0;
if(initializeGame(numPlayers, k, seed, &game) != -1){ //assert this test does not pass because number of players is 0
	printf("INITIALIZEGAME TEST FAILED\n");
}

//test 2 with valid number of players
numPlayers = 2;
if(initializeGame(numPlayers, k, seed, &game) == -1){
	printf("INITIALIZEGAME TEST FAILED\n");
}

//test 3 - ensure correct number of curse cards set 

numPlayers = 2;
initializeGame(numPlayers, k, seed, &game);
if(game.supplyCount[curse] != 10){
	printf("INITIALIZEGAME TEST FAILED\n");
}

numPlayers = 3;
initializeGame(numPlayers, k, seed, &game);
if(game.supplyCount[curse] != 20){
	printf("INITIALIZEGAME TEST FAILED\n");
}

numPlayers = 4; 
initializeGame(numPlayers, k, seed, &game);
if(game.supplyCount[curse] != 30){
	printf("INITIALIZEGAME TEST FAILED\n");
}

//test 4 - ensure correct number of victory cards set 
numPlayers = 2;
initializeGame(numPlayers, k, seed, &game);
if(game.supplyCount[estate] != 8){
	printf("INITIALIZEGAME TEST FAILED\n");
}
if(game.supplyCount[duchy] != 8){
	printf("INITIALIZEGAME TEST FAILED\n");
}
if(game.supplyCount[province] != 8){
	printf("INITIALIZEGAME TEST FAILED\n");
}


numPlayers = 3;
initializeGame(numPlayers, k, seed, &game);
if(game.supplyCount[estate] != 12){
	printf("INITIALIZEGAME TEST FAILED\n");
}
if(game.supplyCount[duchy] != 12){
	printf("INITIALIZEGAME TEST FAILED\n");
}
if(game.supplyCount[province] != 12){
	printf("INITIALIZEGAME TEST FAILED\n");
}
//test 5 - ensure correct number of treasure cards set 
initializeGame(numPlayers, k, seed, &game);
if(game.supplyCount[copper] != 60 - (7 * numPlayers)){
	printf("INITIALIZEGAME TEST FAILED\n");
}
if(game.supplyCount[silver] != 40){
	printf("INITIALIZEGAME TEST FAILED\n");
}
if(game.supplyCount[gold] != 30){
	printf("INITIALIZEGAME TEST FAILED\n");
}

printf("INITIALIZEGAME TEST PASSED\n");

return 0;
}
