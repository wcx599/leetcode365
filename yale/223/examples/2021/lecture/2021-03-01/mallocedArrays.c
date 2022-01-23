#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

// allocate array of ints and fill with indices
// (named after Python range function)
int *
range(size_t n)
{
    int *a = malloc(sizeof(int) * n);
    assert(a);  // did malloc work?

    for(size_t i = 0; i < n; i++) {
        a[i] = i;
    }

    return a;
}

void
printArray(const int *a, size_t n)
{
    for(size_t i = 0; i < n; i++) {
        printf("%d\n", a[i]);
    }
}

#define ARRAY_SIZE (500)

int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    int *a = range(ARRAY_SIZE);

    printArray(a, ARRAY_SIZE);

    free(a);

    return 0;
}
