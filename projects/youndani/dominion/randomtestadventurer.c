#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int checkAdventurer(int p, struct gameState* post) {
    struct gameState pre;
    int preHandCount = post->handCount[p];
    int preNumTreasure = 0;
    int postNumTreasure = 0;
    
    memcpy (&pre, post, sizeof(struct gameState));
    
    cardEffect(adventurer,0,0,0,post,0,0);
    int cardDrawn = 0;
    int postHandCount = post->handCount[player];
    for (int i = 0; i< preHandCount; i++) {
        cardDrawn = pre.hand[player][i];
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
            preNumTreasure++;
        }
    }
    for (int i = 0; i< postHandCount; i++) {
        cardDrawn = post->hand[player][i];
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
            postNumTreasure++;
        }
    }
    assert(postNumTreasure - preNumTreasure >= 0);
    
    return 0;
}

int main() {
    int i, r,  deckCount, discardCount, handCount;
    int numTests, p;
    
    int kingdom[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
    
    struct gameState state;
    memset(&state,0, sizeof(struct gameState));
    printf( "Testing Adventurer\n");
    printf( "Random Tests\n");
    
    PutSeed(3000000000);
    SelectStream(2);
    
    for (numTests=0; numTests < 2000; numTests++) {
        initializeGame(2, kingdomCards, numTests, &state);
        p = floor(Random() * 2);
        p = 0;
        
        int r1 = (int) (floor(Random() * MAX_HAND));
        int r2 = (int) (floor(Random() * MAX_DECK));
        int r3 = (int) (floor(Random() * MAX_HAND));
        
        state.handCount[p] = r1;
        state.deckCount[p] = r2;
        state.discardCount[p] = r3;
        state.whoseTurn = p;
        
        for (i=0; i< state.deckCount[p]; i++) {
            state.hand[p][i] = floor((Random() *26) + 1);
        }
        checkAdventurer(p, &state);
    }
    printf("Tests Completed\n");
}

