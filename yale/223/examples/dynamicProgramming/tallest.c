#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* computes the sum of the increasing subsequence with largest sum */
int
maxSumIncreasingSubsequence(int n, int *height)
{
    int *best;     /* best[i] is best sum ending with i */
    int max;       /* max of best[j] for height[j] < height[i] */
    int globalMax; /* max of best[i] over all i */
    int i;
    int j;

    best = malloc(n * sizeof(*best));

    assert(best);

    for(i = 0; i < n; i++) {
        max = 0;
        for(j = 0; j < i; j++) {
            if(height[j] < height[i] && best[j] > max) {
                max = best[j];
            }
        }

        best[i] = max + height[i];
    }

    /* now find max over all best[i] */
    globalMax = 0;
    for(i = 0; i < n; i++) {
        if(best[i] > globalMax) {
            globalMax = best[i];
        }
    }

    return globalMax;
}

#define INITIAL_HEIGHT_SIZE (32)

int
main(int argc, char **argv)
{
    int *height;  /* array of heights */
    int n;        /* number of values in height */
    int size;     /* size of height */
    int nextVal;  /* for reading in next value */

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    size = INITIAL_HEIGHT_SIZE;
    height = malloc(size * sizeof(*height));

    n = 0;

    while(scanf("%d", &nextVal) == 1) {
        if(n >= size) {
            size *= 2;
            height = realloc(height, size * sizeof(*height));
        }

        height[n++] = nextVal;
    }

    printf("%d\n", maxSumIncreasingSubsequence(n, height));

    free(height);

    return 0;
}
