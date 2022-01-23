#include <stdlib.h>
#include <assert.h>
#include <stddef.h>

#include "deque.h"

#define NUM_DIRECTIONS (2)

struct deque {
    struct deque *next[NUM_DIRECTIONS];  /* pointers to next element */
    int value;
};


/* return a new empty deque */
Deque *
dequeCreate(void)
{
    struct deque *d;

    /* offsetof returns position of value inside a struct deque */
    /* short version of struct deque holds dummy header */
    d = malloc(offsetof(struct deque, value));

    assert(d);

    d->next[DEQUE_FRONT] = d->next[DEQUE_BACK] = d;

    return d;
}


/* push new value onto direction side of deque d */
void
dequePush(Deque *d, int direction, int value)
{
    struct deque *e;  /* new element of the list */

    e = malloc(sizeof(struct deque));
    assert(e);

    e->value = value;
    e->next[direction] = d->next[direction];
    e->next[!direction] = d;

    e->next[direction]->next[!direction] = e;
    d->next[direction] = e;
}

/* pop and return first value on direction side of deque d */
/* returns DEQUE_EMPTY if deque is empty */
int 
dequePop(Deque *d, int direction)
{
    int retval;   /* value we are going to return */
    struct deque *e;  /* element we are removing */

    if(dequeIsEmpty(d)) {
        return DEQUE_EMPTY;
    }

    /* else */
    e = d->next[direction];
    retval = e->value;

    d->next[direction] = e->next[direction];   /* patch out e */
    d->next[direction]->next[!direction] = d;  /* restore the invariant */

    free(e);

    return retval;
}

/* return 1 if deque contains no elements, 0 otherwise */
int 
dequeIsEmpty(const Deque *d)
{
    return d == d->next[DEQUE_FRONT];
}

/* free space used by a deque */
void 
dequeDestroy(Deque *d)
{
    while(!dequeIsEmpty(d)) {
        dequePop(d, DEQUE_FRONT);
    }

    free(d);
}
