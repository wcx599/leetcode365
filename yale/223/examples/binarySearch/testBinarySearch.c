#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "binarySearch.h"

#define N (1000000)

int
main(int argc, char **argv)
{
    size_t i;
    int a[N];

    for(i = 0; i < N; i++) {
        a[i] = 3*i;
    }

    assert(binarySearch(1777, a, N) == 0);
    assert(binarySearch(1779, a, N) == 1);

    return 0;
}
