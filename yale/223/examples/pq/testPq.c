#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "pq.h"

static int
intCompare(const void *i1, const void *i2)
{
    return (*((const int *) i1) - *((const int *) i2));
}

int
main(int argc, char **argv)
{
    PQ pq;
    int i;
    int ii;

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    pq = pqCreate(sizeof(int), intCompare);

    for(i = 0; i < 100; i++) {
        ii = (i * 37) % 100;

        pqInsert(pq, &ii);
    }

    for(i = 0; i < 100; i++) {
        pqDeleteMin(pq, &ii);
        assert(ii == i);
    }

    assert(pqIsEmpty(pq));

    pqDestroy(pq);

    return 0;
}
