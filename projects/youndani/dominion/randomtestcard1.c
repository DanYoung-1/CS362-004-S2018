#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int checkCouncilRoom(int p, struct gameState* post) {
    struct gameState pre;
    int preHandCount = post->handCount[p];

    memcpy (&pre, post, sizeof(struct gameState));
    cardEffect(council_room,0,0,0,post,0,0);

    // Assert player hand count has increased by 4
    assert(post->handCount[p] == pre.handCount[p]+4);
    
    // Assert number of buys has increased by 1
    assert(post->numBuys[p] == pre.numBuys[p]+1)

    // Assert each player card count has increased by 1
    for (i = 0; i < state->numPlayers; i++) {
        assert(post->handCount[p] == pre->handCount[p]+1)
    }
    
    // Assert played card count has increased
    assert(post->playedCardCount == pre->playedCardCount+1)
    return 0;
}

int main() {
    int i, r,  deckCount, discardCount, handCount;
    int numTests, p;

    int kingdom[10] = {
        adventurer, council_room, feast, gardens, mine, 
        remodel, smithy, village, baron, great_hall
    };

    struct gameState state;
    memset(&state,0, sizeof(struct gameState));
    printf( "Testing Council Room.\n");
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
        int r4 = (int) (floor(Random() * MAX_HAND));
        
	    state.handCount[p] = r1;
        state.deckCount[p] = r2;
        state.discardCount[p] = r3;
        state.numBuys[p] = r4;
        state.whoseTurn = p;
        
        for (i=0; i< state.deckCount[p]; i++) {
            state.hand[p][i] = floor((Random() *26) + 1);
        }
        checkCouncilRoom(p, &state);
    }
    printf("Tests Completed\n");
}
