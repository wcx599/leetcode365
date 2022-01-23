#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <stdint.h>

#include "strategy.h"

#include "heap.h"

struct strategy {
    int numPiles;        /* how many piles */
    struct heap **piles; /* array of piles; note we include an extra so we can count from 1 */
};

struct strategy *
strategyCreate(int numPiles)
{
    struct strategy *s;
    int i;

    s = malloc(sizeof(struct strategy));
    assert(s);

    s->numPiles = numPiles;
    s->piles = malloc(sizeof(struct heap *) * (numPiles + 1));  /* for indexes 0..n */

    for(i = 0; i < numPiles+1; i++) {
        s->piles[i] = heapCreate();
    }

    return s;
}

void
strategyDestroy(struct strategy *s)
{
    int i;

    for(i = 0; i < s->numPiles+1; i++) {
        heapDestroy(s->piles[i]);
    }

    free(s->piles);
    free(s);
}

void
strategyDeal(struct strategy *s, Card c)
{
    heapInsert(s->piles[s->numPiles], c);
}

Card
strategyPlay(struct strategy *s, int pile)
{
    Card c;

    c = heapDeleteMin(s->piles[pile]);
    
    if(pile > 1) {
        heapInsert(s->piles[pile-1], c);
    }

    return c;
}
