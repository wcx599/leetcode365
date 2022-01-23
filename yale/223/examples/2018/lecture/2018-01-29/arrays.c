#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "eval.h"

#define N (5)

/* fill an array with a[i] = i */
void
iota(int *a, int n)
{
    for(int i = 0; i < n; i++) {
        a[i] = i;
    }
} 

/* find the max value in an array */
/* const promises I won't modify any ints */
int
max(const int *a, int n)
{
    int max;

    assert(n > 0);

    /* this is a bad idea in many ways */
    // if(a[0] = max) { return 12; }

    max = a[0];

    for(int i = 1; i < n; i++) {
        if(a[i] > max) { max = a[i]; }
    }

    return max;
}

int
main(int argc, char **argv)
{
    int a[N];
    int aa[N];
    int *p;

    a[0] = 1;
    1[a] = 2;

    p = a+2;

    *p = 3;

    for(int i = 0; i < N; i++) {
        printf("a[%d] == %d\n", i, a[i]);
    }

    iota(aa, N);

    for(int i = 0; i < N; i++) {
        printf("aa[%d] == %d\n", i, aa[i]);
    }

    Eval(max(aa, N));

    return 0;
}
