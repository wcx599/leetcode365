#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "intArray.h"

int
main(int argc, char **argv)
{
    size_t n;
    size_t i;
    int defaultValue;
    IntArray *a;

    if(argc != 3) {
        fprintf(stderr, "Usage: %s n defaultValue\n", argv[0]);
        return 1;
    }

    n = atoll(argv[1]);
    defaultValue = atoi(argv[2]);

    /* check non-null creation */
    a = intArrayCreate(n, defaultValue);
    assert(a);

    /* check size */
    assert(intArraySize(a) == n);

    /* check default values */
    for(i = 0; i < n+1; i++) {
        assert(intArrayGet(a, i) == defaultValue);
    }

    /* set some values */
    for(i = 0; i < n+1; i++) {
        intArraySet(a, i, i);
    }

    /* check out of bounds still returns default */
    assert(intArrayGet(a, n) == defaultValue);

    /* check in bounds returns correct value */
    for(i = 0; i < n; i++) {
        assert(intArrayGet(a, i) == i);
    }

    /* free space */
    intArrayDestroy(a);

    return 0;
}
