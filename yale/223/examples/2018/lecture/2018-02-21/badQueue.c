#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "queue.h"

#define MAX_QUEUE_SIZE (4)

struct q {
    int head;  // first elt
    int tail;  // first position after end of queue
    elt a[MAX_QUEUE_SIZE];
};

Q *
qCreate(void)
{
    Q * q = malloc(sizeof(struct q));

    q->head = q->tail = 0;

    return q;
}

void qDestroy(Q * q) { free(q); }

void
enq(Q * q, elt e)
{
    q->a[q->tail] = e;
    q->tail = (q->tail + 1) % MAX_QUEUE_SIZE;
}

elt
deq(Q * q)
{
    elt e;

    e = q->a[q->head];
    q->head = (q->head + 1) % MAX_QUEUE_SIZE;

    return e;
}

int
qEmpty(const Q * q)
{
    return q->head == q->tail;
}

