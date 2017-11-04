#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define MAX_TESTS 120

// This randomly tests Adventurer

/// Oracle function returns 1 if state is valid after drawing adventure card,
/// 0 if state is inconsistent with expected results (player should have 
/// 2 treasure cards and deckCount should be reduced)
int validateStateAfterAdventurerDraw(struct gameState * state, int player, int prevHandCount, int prevDeckCount) {
    if (state->handCount[player] < prevHandCount) {
        printf("Test failure: handCount should be greater after drawing an adventurer card\n");
        printf("handCount before: %d   ", prevHandCount);
        printf("handCount after: %d\n", state->handCount[player]);
        return 0;
    }
    else if (state->deckCount[player] > prevDeckCount && prevDeckCount != 0) {
        printf("Test failure: deckCount should be smaller than before\n");
        printf("deckCount before: %d   ", prevDeckCount);
        printf("deckCount after: %d\n", state->deckCount[player]);
        return 0;
    }
    return 1;
}

int main() {
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
             sea_hag, tribute, smithy};
    int players, player, handCount, deckCount, seed, handPos, coinBonus;
    struct gameState state;
        
    srand(time(NULL));

    printf("Running Random Adventurer Test\n");

    for (int i = 0; i < MAX_TESTS; i++) {

        players = rand() % (MAX_PLAYERS - 2) + 2;
        seed = rand();
        coinBonus = 0;
        handPos = rand() % 4;
        player = i % (players);

        initializeGame(players, k, seed, &state); //initialize Gamestate

        // Initiate valid state variables
        state.deckCount[player] = rand() % MAX_DECK;   //Pick random deck size out of MAX DECK size
        state.discardCount[player] = rand() % MAX_DECK;
        state.handCount[player] = rand() % MAX_HAND;
        
        // Copy state variables
        handCount = state.handCount[player];
        deckCount = state.deckCount[player];
        
        cardEffect(adventurer, 1, 1, 1, &state, handPos, &coinBonus);
        int result = validateStateAfterAdventurerDraw(&state, player, handCount, deckCount);
        assert(result == 1);
    }

    printf("Tests Complete\n");

    return 0;
}