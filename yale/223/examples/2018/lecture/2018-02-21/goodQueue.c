#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "queue.h"

#define INITIAL_QUEUE_SIZE (4)

struct q {
    int size;   // size of the array
    int head;  // first elt
    int tail;  // first position after end of queue
    elt *a;    // malloc'd block of elts
};

Q *
qCreate(void)
{
    Q * q = malloc(sizeof(struct q));

    q->size = INITIAL_QUEUE_SIZE;
    q->head = q->tail = 0;

    q->a = calloc(INITIAL_QUEUE_SIZE, sizeof(elt));

    return q;
}

void qDestroy(Q * q) { free(q->a); free(q); }

void
enq(Q * q, elt e)
{
    // are we running out of room?
    if((q->tail+1) % q->size == q->head) {
        // yes
        // get a new array
        int newSize = q->size * 2;
        int top = 0;  // tail of new queue
        elt *a2 = calloc(newSize, sizeof(elt));

        while(!qEmpty(q)) {
            a2[top++] = deq(q);
        }

        // toss old array, substitute in new one
        free(q->a);
        q->a = a2;
        q->size = newSize;

        q->head = 0;
        q->tail = top;
    }

    q->a[q->tail] = e;
    q->tail = (q->tail + 1) % q->size;
}

elt
deq(Q * q)
{
    elt e;

    e = q->a[q->head];
    q->head = (q->head + 1) % q->size;

    return e;
}

int
qEmpty(const Q * q)
{
    return q->head == q->tail;
}

