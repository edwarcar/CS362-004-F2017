#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int VillageCard(int currentPlayer, struct gameState *state, int handPos){

   //+1 Card
    drawCard(currentPlayer, state);
    drawCard(currentPlayer, state);
    drawCard(currentPlayer, state);

    //+2 Actions
    state->numActions = state->numActions + 10;
           
    //discard played card from hand
     discardCard(handPos, currentPlayer, state, 0);
                                
     return 0; 
   // bug introduced: increase action points by 10 instead of 2 and draw 3 cards instead of 1 
}

