#include <stdio.h>
#include <stdlib.h>

#include "declareSort.h"

/* note: must appear outside of any function, and has no trailing semicolon */
DeclareSort(int, int)

#define N (50)

int
main(int argc, char **argv)
{
    int a[N];
    int i;

    for(i=0; i < N; i++) {
        a[i] = N-i;
    }

    int_sort(a, N);

    for(i=0; i < N; i++) {
        printf("%d ", a[i]);
    }
    putchar('\n');

    return 0;
}
