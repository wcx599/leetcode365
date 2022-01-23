#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "deque.h"

#define DIRECTIONS (2)

// a deque is a circular double-linked list
// with a dummy head element
//
// invariant:
//
// dummy head always exists,
// e->next[dir]->next[!dir] == e for all e

struct deque {
    struct deque *next[DIRECTIONS];
    int value;
};

// constructor
Deque 
dequeCreate(void)
{
    Deque d = malloc(sizeof(struct deque));

    // make it point to itself
    d->next[LEFT] = d->next[RIGHT] = d;

    return d;
}

// destructor
void 
dequeDestroy(Deque d)
{
    while(!dequeIsEmpty(d)) {
        dequeDeq(d, LEFT);
    }

    // free dummy element
    free(d);
}

// mutators/accessors
void
dequeEnq(Deque d, int direction, int v)
{
    // need a new element
    struct deque *e = malloc(sizeof(struct deque));

    // need to fill it in
    e->value = v;
    e->next[direction] = d->next[direction];
    e->next[!direction] = d;

    // make backpointers consistent
    for(int i = LEFT; i <= RIGHT; i++) {
        e->next[i]->next[!i] = e;
    }

    // unrolled version
    // e->next[LEFT]->next[RIGHT] = e;
    // e->next[RIGHT]->next[LEFT] = e;
}

int
dequeDeq(Deque d, int direction)
{
    assert(d->next[direction] != d);

    struct deque *e = d->next[direction];
    int value = e->value;

    // fix successor to e
    e->next[direction]->next[!direction] = d;

    // fix d's outgoing pointer
    d->next[direction] = e->next[direction];

    free(e);

    return value;
}

// accessor
int
dequeIsEmpty(Deque d)
{
    return d == d->next[LEFT];
}
