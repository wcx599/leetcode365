#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <limits.h>  /* for INT_MIN */

/* compute the maximum of the first n elements of array a */
int
maximum(int n, int *a)
{
    int i;
    int max;

    max = INT_MIN;
    for(i = 0; i < n; i++) {
        if(a[i] > max) {
            max = a[i];
        } 
    }

    return max;
}

#define N (5)

int
main(int argc, char **argv)
{
    int a[N];
    int i;

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    for(i = 0; i < N; i++) {
        a[i] = i*i;
    }

    printf("%d\n", maximum(N-1, a+1));

    return 0;
}
