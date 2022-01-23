#include <stdlib.h>
#include <assert.h>
#include <limits.h> // for CHAR_BIT

#include "array.h"

#define LEVELS (sizeof(size_t) * CHAR_BIT)

struct array {
    int (*combine)(int, int);
    size_t n;
    int *data[LEVELS];  // data[level][index] points to element
};

#ifdef SANITY_CHECK
// turning on SANITY_CHECK enables (expensive!)
// sanity-checking in fixEntry.

// return result of combining interval [k1,k2)
static int
arrayCombineIterative(const Array *self, size_t k1, size_t k2)
{
    assert(k1 < k2);
    assert(k2 <= self->n);

    int accumulator = self->data[0][k1];
    for(size_t i = k1+1; i < k2; i++) {
        accumulator = self->combine(accumulator, self->data[0][i]);
    }

    return accumulator;
}
#endif

// fix entry in self->data[level][i]
static void
fixEntry(Array *self, int level, size_t i)
{
    assert(level > 0);
    assert(level < LEVELS);
    assert(i < (self->n >> level));

    self->data[level][i] = self->combine(
            self->data[level-1][2*i],
            self->data[level-1][2*i+1]);

#ifdef SANITY_CHECK
    assert(self->data[level][i] == arrayCombineIterative(self, i << level, (i+1) << level));
#endif
}

Array *
arrayCreate(int (*combine)(int, int), size_t n)
{
    assert(n > 0);

    struct array *self = malloc(sizeof(struct array));
    self->combine = combine;
    self->n = n;

    // level i is combined groups of 2^i elements
    // and has size n >> i
    for(int level = 0; (n >> level) > 0; level++) {
        self->data[level] = calloc(n >> level, sizeof(int));
    }

    // bottom layer is already 0.
    // combine elements for higher levels
    for(int level = 1; (n >> level) > 0; level++) {
        for(size_t i = 0; i < (n >> level); i++) {
            fixEntry(self, level, i);
        }
    }

    return self;
}

size_t
arraySize(const Array *self)
{
    return self->n;
}

int
arrayGet(const Array *self, size_t i)
{
    if(i < self->n) {
        return self->data[0][i];
    } else {
        return 0;
    }
}

void
arraySet(Array *self, size_t i, int v)
{
    if(i < self->n) {
        self->data[0][i] = v;

        // fix summary data
        for(int level = 1; (i >> level) < (self->n >> level); level++) {
            fixEntry(self, level, i >> level);
        }
    }
}

// aggegate the first k elements at given level
static int
combineHelper(const Array *self, int level, size_t k)
{
    assert(k > 0);

    if(k == 1) {
        // return first element
        return self->data[level][0];
    } else if(k % 2 == 0) {
        // move up a level
        return combineHelper(self, level+1, k / 2);
    } else {
        // compute prefix by moving up a level, then add last element
        int prefix = combineHelper(self, level+1, k / 2);
        return self->combine(prefix, self->data[level][k-1]);
    }
}

int
arrayCombine(const Array *self, size_t k)
{
    int result;

    if(k == 0 || k > self->n) {
        k = self->n;
    }

    result = combineHelper(self, 0, k);

    return result;
}

void
arrayDestroy(Array *self)
{
    for(int level = 0; (self->n >> level) > 0; level++) {
        free(self->data[level]);
    }
    free(self);
}
