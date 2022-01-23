#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

#include "heap.h"

/*
 * Standard packed heap implementation.
 * Node at x has children at 2*x+1 and 2*x+2, parent at (x-1)/2.
 */
struct heap {
    size_t size;     /* current size of the array */
    size_t n;        /* current number of elements */
    HeapElement *elts;    /* malloc'd block of elements */
};

#define HEAP_MINIMUM_SIZE (16)
#define HEAP_GROW_FACTOR (2)       /* how much to grow or shrink heap by */
#define HEAP_SHRINK_THRESHOLD (3)  /* shrink when n < size / HEAP_SHRINK_THRESHOLD */

static inline size_t 
heapParent(size_t x)
{
    return (x-1)/2;
}

static inline size_t 
heapLeftChild(size_t x)
{
    return 2*x + 1;
}

static inline size_t 
heapRightChild(size_t x)
{
    return 2*x + 2;
}

struct heap *
heapCreate(void)
{
    struct heap *h;

    h = malloc(sizeof(struct heap));
    assert(h);

    h->size = HEAP_MINIMUM_SIZE;
    h->n = 0;
    h->elts = malloc(sizeof(HeapElement) * h->size);

    return h;
}

void
heapDestroy(struct heap *s)
{
    free(s->elts);
    free(s);
}

static inline void
swap(HeapElement *x, HeapElement *y)
{
    HeapElement tmp;

    tmp = *x;
    *x = *y;
    *y = tmp;
}

void
heapInsert(struct heap *h, HeapElement elt)
{
    size_t pos;      /* current position of elt */
    size_t parent;   /* parent of elt at pos */

    if(h->n >= h->size) {
        h->size *= 2;
        h->elts = realloc(h->elts, sizeof(HeapElement) * h->size);
        assert(h->elts);
    }

    /* insert at end */
    pos = h->n++;
    h->elts[pos] = elt;

    /* float up */
    while(pos > 0 && h->elts[pos] < h->elts[parent = heapParent(pos)]) {
        swap(&h->elts[pos], &h->elts[parent]);
        pos = parent;
    }
}

HeapElement
heapDeleteMin(struct heap *h)
{
    HeapElement retval;     /* value to return */
    size_t pos;      /* position of element being floated down */
    size_t left;     /* left child */
    size_t right;    /* right child */
    size_t smaller;  /* smaller child; favors right child on ties */

    assert(h->n > 0);

    retval = h->elts[0];

    /* copy last element to root */
    h->elts[0] = h->elts[--(h->n)];
    pos = 0;

    /* maybe shrink heap */
    if(h->n <= h->size / HEAP_SHRINK_THRESHOLD && h->size / HEAP_GROW_FACTOR >= HEAP_MINIMUM_SIZE) {
        h->size /= HEAP_GROW_FACTOR;
        h->elts = realloc(h->elts, sizeof(HeapElement) * h->size);
    } 

    /* try floating it down */
    for(;;) {

        left = heapLeftChild(pos);
        right = heapRightChild(pos);

        /* which child exists and is smaller? */
        if(right < h->n && h->elts[right] <= h->elts[left]) {
            smaller = right;
        } else if(left < h->n) {
            smaller = left;
        } else {
            /* neither child exists, bail out immediately */
            return retval;
        }
           
        if(h->elts[pos] <= h->elts[smaller]) {
            /* already smaller than smaller child */
            return retval;
        }

        /* do the swap and keep going */
        swap(&h->elts[pos], &h->elts[smaller]);
        pos = smaller;
    }
}

size_t
heapSize(const struct heap *h)
{
    return h->n;
}

#ifdef TEST_MAIN

/* white-box test of heap invariant */
static void
heapCheckInvariant(const struct heap *h)
{
    size_t pos;

    /* check that each child is no less than its parent */
    for(pos = 1; pos < h->n; pos++) {
        assert(h->elts[pos] >= h->elts[heapParent(pos)]);
    }
}

#define N (65537)
#define MULTIPLIER (17)    /* multiplier for out-of-order test, should be prime relative to N */

int
main(int argc, char **argv)
{
    struct heap *h;
    HeapElement i;

    /* run some basic tests */
    h = heapCreate();

    /* insert and remove a whole bunch of elements */
    for(i = 0; i < N; i++) {
        heapInsert(h, i);
        assert(heapSize(h) == i+1);
    }

    heapCheckInvariant(h);

    for(i = 0; i < N; i++) {
        assert(i == heapDeleteMin(h));
        assert(heapSize(h) == N-i-1);
    }

    /* now backwards */
    for(i = 0; i < N; i++) {
        heapInsert(h, N-i-1);
        assert(heapSize(h) == i+1);
    }

    for(i = 0; i < N; i++) {
        assert(i == heapDeleteMin(h));
        assert(heapSize(h) == N-i-1);
    }

    /* now out of order */
    for(i = 0; i < N; i++) {
        heapInsert(h, (MULTIPLIER * i) % N);
        assert(heapSize(h) == i+1);
    }

    heapCheckInvariant(h);

    for(i = 0; i < N; i++) {
        assert(i == heapDeleteMin(h));
        assert(heapSize(h) == N-i-1);
    }

    /* now twice */
    for(i = 0; i < N; i++) {
        heapInsert(h, (MULTIPLIER * i) % N);
        assert(heapSize(h) == i+1);
    }

    heapCheckInvariant(h);

    for(i = 0; i < N; i++) {
        heapInsert(h, (MULTIPLIER * i) % N);
        assert(heapSize(h) == N+i+1);
    }

    heapCheckInvariant(h);

    for(i = 0; i < N; i++) {
        assert(i == heapDeleteMin(h));
        assert(i == heapDeleteMin(h));
        assert(heapSize(h) == 2*(N-i-1));
    }

    return 0;
}
#endif
