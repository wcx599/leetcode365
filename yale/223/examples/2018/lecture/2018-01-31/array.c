#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* creates an returns an array of n elements with a[i] == i */
int *
iota(size_t n)
{
    int *a;

    a = malloc(sizeof(int) * n);

    assert(a);  /* make sure malloc didn't fail */

    for(size_t i = 0; i < n; i++) {
        a[i] = i;
    }

    return a;
}

void
printArray(int *a, int n)
{
    for(size_t i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }

    putchar('\n');
}

#define N (10)

int
main(int argc, char **argv)
{
    int *b;

    b = iota(N);
    printArray(b, N);

    // in class we showed bad outcomes 
    // of omitting this statement
    // or doing it twice
    free(b);

    return 0;
}
