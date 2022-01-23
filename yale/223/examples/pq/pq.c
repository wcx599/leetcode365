#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "pq.h"

struct pq {
    int elementLength;
    int (*compare)(const void *, const void *);
    int n;      /* number of elements */
    int size;   /* number of slots in data */
    void *swapSpace;   /* elementLength bytes used for swapping */
    void *data;
};

#define PQ_INITIAL_SIZE (128)

PQ
pqCreate(int elementLength, int (*compare)(const void *, const void *))
{
    PQ pq;

    pq = malloc(sizeof(*pq));
    assert(pq);

    pq->elementLength = elementLength;
    pq->compare = compare;
    pq->n = 0;
    pq->size = PQ_INITIAL_SIZE;

    pq->swapSpace = malloc(pq->elementLength);
    assert(pq->swapSpace);

    pq->data = malloc(pq->elementLength * pq->size);
    assert(pq->data);

    return pq;
}

void
pqDestroy(PQ pq)
{
    free(pq->data);
    free(pq->swapSpace);
    free(pq);
}

int
pqIsEmpty(PQ pq)
{
    return pq->n == 0;
}

/* Child(i, 0) and Child(i, 1) are children of i */
/* Parent(i) is parent of i */
#define Child(i, x) (2*(i)+1+(x))
#define Parent(i) (((i)-1)/2)

#define NUM_CHILDREN (2)

/* compute the address of position i in the data field */
#define REF(pq, i) ((void *) (((char *) (pq)->data) + (pq)->elementLength * i))

/* swap elements at indexes i1 and i2 */
static void
pqSwap(PQ pq, int i1, int i2)
{
    memcpy(pq->swapSpace, REF(pq, i1), pq->elementLength);
    memcpy(REF(pq, i1), REF(pq, i2), pq->elementLength);
    memcpy(REF(pq, i2), pq->swapSpace, pq->elementLength);
}

void
pqInsert(PQ pq, const void *elt)
{
    int floater;                /* new element */

    while(pq->n + 1 > pq->size) {
        pq->size *= 2;
        pq->data = realloc(pq->data, pq->elementLength * pq->size);
        assert(pq->data);
    }

    /* copy the new element in */
    floater = pq->n++;
    memcpy(REF(pq, floater), elt, pq->elementLength);

    /* float it up until it is at the top */
    /* or it is no smaller than its parent */
    while(floater > 0 && pq->compare(REF(pq, floater), REF(pq, Parent(floater))) <= 0) {
        /* it's smaller than its parent */
        pqSwap(pq, floater, Parent(floater));
        floater = Parent(floater);
    }
}

void
pqDeleteMin(PQ pq, void *retval)
{
    int floater;        /* previous loser floating down */
    int smallChild;    /* smaller child of floater */
    
    assert(!pqIsEmpty(pq));

    /* first copy out the winner */
    memcpy(retval, REF(pq, 0), pq->elementLength);

    --(pq->n);

    if(pqIsEmpty(pq)) {
        /* pq empty, nothing to do */
        return;
    }

    /* else */
    memcpy(REF(pq, 0), REF(pq, pq->n), pq->elementLength);

    floater = 0;

    for(;;) {
        /* find smaller child of floater */
        if(Child(floater, 0) >= pq->n) {
            return;     /* no children, bail out */
        } else if(Child(floater, 1) >= pq->n) {
            smallChild = Child(floater, 0);
        } else if(pq->compare(REF(pq, Child(floater, 0)), REF(pq, Child(floater, 1))) < 0) {
            smallChild = Child(floater, 0);
        } else {
            smallChild = Child(floater, 1);
        }

        /* is floater <= smallChild? */
        if(pq->compare(REF(pq, floater), REF(pq, smallChild)) <= 0) {
            /* yes, we are done */
            return;
        } else {
            /* no, swap and continue floating down */
            pqSwap(pq, floater, smallChild);
            floater = smallChild;
        }
    }
}

void
pqSanityCheck(PQ pq)
{
    int i;
    int j;

    assert(pq->n >= 0);
    assert(pq->n <= pq->size);

    for(i = 0; i < pq->n; i++) {
        for(j = 0; j < NUM_CHILDREN; j++) {
            if(Child(i, j) < pq->n) {
                assert(pq->compare(REF(pq, i), REF(pq, Child(i, j))) <= 0);
            }
        }
    }
}
