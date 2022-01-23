#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "priorityQueue.h"

struct pq {
    size_t n;      /* number of elements */
    size_t size;   /* number of slots in current block */
    elt *values;   /* malloc'd array of actual values */
};

#define INITIAL_SIZE (16)

/* make a new priority queue */
struct pq *pqCreate(void)
{
    struct pq *q;

    q = malloc(sizeof(struct pq));

    q->n = 0;
    q->size = INITIAL_SIZE;
    q->values = malloc(sizeof(elt) * q->size);

    return q;
}

void pqInsert(struct pq *q, elt e)
{
    size_t pos;
    size_t parent;
    elt tmp;

    if(q->n >= q->size) {
        q->size *= 2;
        q->values = realloc(q->values, sizeof(elt) * q->size);
    }

    pos = q->n++;

    /* puts new value in at the end */
    q->values[pos] = e;

    /* float it up */
    while(pos > 0 && q->values[pos] < q->values[parent = (pos - 1) / 2]) {
        /* swap pos and parent */
        tmp = q->values[parent];
        q->values[parent] = q->values[pos];
        q->values[pos] = tmp;
        pos = parent;
    }
}

/* delete and return smallest element */
elt pqDeleteMin(struct pq *q)
{
    elt retval;   /* element I am returning */
    size_t pos;   /* position of element I am floating down */
    size_t left;  /* kids */
    size_t right;
    size_t smaller;  /* smaller kid */
    elt tmp;

    retval = q->values[0];
    q->values[0] = q->values[--(q->n)];

    pos = 0;

    /* restore heap property */
    for(;;) {
        left = 2*pos + 1;
        right = 2*pos + 2;

        if(left >= q->n) {
            /* I have no children! */
            return retval;
        } else if(right >= q->n) {
            /* I have one child! */
            smaller = left;
        } else if(q->values[left] < q->values[right]) {
            /* I have two children, left is smaller */
            smaller = left;
        } else {
            /* right is smaller */
            smaller = right;
        }

        if(q->values[pos] > q->values[smaller]) {
            /* swap */
            tmp = q->values[pos];
            q->values[pos] = q->values[smaller];
            q->values[smaller] = tmp;
            pos = smaller;
        } else {
            return retval;
        }
    }
}

/* destory the priority queue */
void pqDestroy(struct pq *q)
{
    free(q->values);
    free(q);
}

#ifdef TEST_MAIN

#define N (100)

int
main(int argc, char **argv)
{
    struct pq *q;
    elt i;
    elt retval;

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    q = pqCreate();

    assert(q);
    assert(q->n == 0);

    for(i = 0; i < N; i++) {
        pqInsert(q, i);
        assert(q->values[0] == 0);
        assert(q->n == i+1);
    }

    for(i = 0; i < N; i++) {
        retval = pqDeleteMin(q);
        printf("%d ", retval);
        assert(i == retval);
    }

    puts("yes");

    for(i = 0; i < N; i++) {
        pqInsert(q, N-i-1);
        assert(q->values[0] == N-i-1);
        assert(q->n == i+1);
    }

    for(i = 0; i < N; i++) {
        retval = pqDeleteMin(q);
        printf("%d ", retval);
        assert(i == retval);
    }

    puts("yes");

    for(i = 0; i < N; i++) {
        pqInsert(q, (37*i) % N);
        assert(q->n == i+1);
    }

    for(i = 0; i < N; i++) {
        retval = pqDeleteMin(q);
        printf("%d ", retval);
        assert(i == retval);
    }

    puts("yes");

    return 0;
}

#endif
