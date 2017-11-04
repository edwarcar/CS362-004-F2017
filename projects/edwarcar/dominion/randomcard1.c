#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#define NUM_TESTS 10
#define CARD_COUNT treasure_map

int main(){
    
    int i,j, player_count, player, seed, deck_treasures, hand_count, pre_count , post_count;
    int k[10] = {curse,estate,duchy,province,copper,baron, smithy, treasure_map, minion, steward};
    srand(time(NULL));   
    struct gameState G;
    
    printf("******Begin Random Test Adventurer*****\n");    
    // Main Loop
    for(i = 0;i < NUM_TESTS; i++){ 
        pre_count = 0; post_count = 0;
        player_count = rand() % 3 + 2;
        seed = rand() % 100;    
        //assume game is initialized
        if(initializeGame(player_count, k, seed, &G) == -1){ 
            printf("Error initializing a random game\n");
            exit(0);
        }
        // generate a random player 
        player = rand() % player_count; 
        G.whoseTurn = player;
        G.numActions = 1;
        G.handCount[player] = 5;
        G.deckCount[player] = rand() % MAX_HAND;
        G.discardCount[player] = 0;
        
        //randomly generate deck
        for(j = 0; j < G.deckCount[player]; j++){
            G.deck[player][j] = rand() % CARD_COUNT;
            if(G.deck[player][j] >= copper && G.deck[player][j] <= gold){ 
                deck_treasures++;
            }
        }
        //randomly generate hand
        for(j = 0; j < G.handCount[player]; j++){   
            G.hand[player][j] = rand() % CARD_COUNT;
            if(G.hand[player][j] >= copper && G.hand[player][j] <= gold){ 
                pre_count++;    }
        }
    
        G.hand[player][0] = adventurer; 
        hand_count = G.handCount[player];
        playCard(0, 0, 0, 0, &G); //play card
        //2 cards should have been placed in users hand
        if(hand_count + 2 != G.handCount[player]){
            printf("Error! Cannot put 2 cards into players hand\n");
            exit(0);    
        }
        
        for(j = 0; j < G.handCount[player]; j++){
            if(G.hand[player][j] >= copper && G.hand[player][j] <= gold)
                    post_count++;
        }
        printf("Pre: %d\n", pre_count);
        printf("Post: %d\n", post_count);
        
        if(pre_count + 2 != post_count){
            printf("Error! Cannot put 2 cards into players hand\n");
            exit(0);    
        }
        printf("Iteration #%d: \n", i);
        
    }
    printf("******Random Test Adventurer Finished******\n");    
    return 0;
}
