#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "heapsort.h"

// test a sorting routine by filling an array
// with random elements

#define RAND_SEED (1337)

int
main(int argc, char **argv)
{

    if(argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return 1;
    }

    size_t n = strtoull(argv[1], 0, 10);
    int *a = calloc(n, sizeof(int));
    assert(a);

    // for consistency across executions
    srand(RAND_SEED);

    // fill with (pseudo) random data
    for(size_t i = 0; i < n; i++) {
        a[i] = rand();
    }

    // sort
    heapsort(n, a);

    // check results
    // note that this only checks ordering
    // and not whether the array contains the
    // same elements
    for(size_t i = 0; i < n-1; i++) {
        assert(a[i] <= a[i+1]);
    }

    return 0;
}
