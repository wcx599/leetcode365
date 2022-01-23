/* Implementation of IntArray ADT */

#include <stdlib.h>
#include <assert.h>

#include "intArray.h"

/* This definition is only visible in this file. */
struct intArray {
    size_t n;      /* number of elements */
    int *contents; /* malloc'd pointer contents */
    int defaultValue; /* default value for out-of-range gets */
};


IntArray *
intArrayCreate(size_t n, int defaultValue)
{
    IntArray *a;
    int i;

    a = malloc(sizeof(IntArray));
    if(a == 0) { return 0; }

    a->n = n;
    a->contents = malloc(sizeof(int) * n);

    if(a->contents == 0) {
        free(a);
        return 0;
    }

    a->defaultValue = defaultValue;

    for(i = 0; i < n; i++) {
        a->contents[i] = defaultValue;
    }

    return a;
}

size_t
intArraySize(const IntArray *a)
{
    return a->n;
}

void
intArrayDestroy(IntArray *a)
{
    free(a->contents);
    free(a);
}

int
intArrayGet(const IntArray *a, size_t index)
{
    /* note that size_t is unsigned, so we only have to check upper bound */
    if(index < a->n) {
        return a->contents[index];
    } else {
        return a->defaultValue;
    }
}

void 
intArraySet(IntArray *a, size_t index, int value)
{
    /* note that size_t is unsigned, so we only have to check upper bound */
    if(index < a->n) {
        a->contents[index] = value;
    }
    /* else do nothing */
}
