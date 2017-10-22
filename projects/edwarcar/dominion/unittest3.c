

#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "dominion.h"
#include "rngs.h"
#include <time.h>

//testing getCost function in dominion.c

int main(int argc, char** argv){

printf("/*********************** Testing GetCost() **************************/\n");

//initialize variables, create a new game state, and call initializeGame()

struct gameState game;

//check function as a whole to ensure that it is returning -1 if no card name (or incorrect card name) is passed in, as it should
if(getCost(45) != -1){
	printf("GETCOST TEST FAILED.\n");
}

// assert for each value of cards that getCost function returns proper amount
int cards[27] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};
int values[27] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4};

int x = 0;

//loop through all 27 cards and call assert statement on each
for(x = 0; x < 27; x++) {
	if(getCost(cards[x]) != values[x]){
		printf("GETCOST TEST FAILED\n");
	}
}

printf("GETCOST TEST PASSED\n");

return 0;

}
