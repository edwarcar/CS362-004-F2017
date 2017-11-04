#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define MAX_TESTS 120
//testing the adventurer card

int main(int argc, char** argv) {
printf("/*********************** Randomly Testing Adventurer Card **************************/\n");
//declare variables
struct gameState state;
int seed;
int players;
int handPos; 
int choice1, choice2, choice3 = 0; 
int k[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int player;
int coinBonus; 

srand(time(NULL)); 
int i; 

//initialize game
for(i = 0; i < MAX_TESTS; i++)
{
  	players = rand() % (MAX_PLAYERS - 2) + 2;
        seed = rand();
        coinBonus = 0;
        handPos = rand() % 4;
        player = i % (players);

initializeGame(players, k, seed, &state);

        state.deckCount[player] = rand() % MAX_DECK;   //Pick random deck size out of MAX DECK size
        state.discardCount[player] = rand() % MAX_DECK;
        state.handCount[player] = rand() % MAX_HAND;
        

//grab numbers before calling the card
int handCount1 = numHandCards(&state);

if(cardEffect(adventurer, choice1, choice2, choice3, &state, handPos, coinBonus) == 0){

int handCount2 = numHandCards(&state);

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
}

return 0;

}
