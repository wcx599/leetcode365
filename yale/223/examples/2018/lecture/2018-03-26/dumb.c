#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// print numbers from min through max the dumb way
void
reduceAndConquer(int min, int max)
{
    if(min > max) {
        return;
    } else {
        printf("%d\n", min);
        reduceAndConquer(min + 1, max);
    }
}

void
reduceAndConquerIterative(int min, int max)
{
start:
    if(min > max) {
        return;
    } else {
        printf("%d\n", min);
        // reduceAndConquer(min + 1, max);
        min = min + 1;
        // max = max;
        goto start;
    }
}

void
reduceAndConquerIterativeWithLoop(int min, int max)
{
    while(min <= max) {
        printf("%d\n", min);
        min = min + 1;
    }
}

void
splitAndConquer(int min, int max)
{
    printf("splitAndConquer(%d,%d)", min, max);
    if(min > max) {
        return;
    } else if(min == max) {
        printf("%d\n", min);
    } else {
        int mid = (min + max) / 2;
        splitAndConquer(min, mid);
        splitAndConquer(mid+1, max);
    }
}

// print numbers from min through max the dumb way
void
reduceAndConquerReversed(int min, int max)
{
    if(min > max) {
        return;
    } else {
        reduceAndConquer(min, max - 1);
        printf("%d\n", max);
    }
}
int
main(int argc, char **argv)
{
    reduceAndConquer(0, 10);
    // splitAndConquer(0, 10);
    // reduceAndConquerReversed(0, 10);
    reduceAndConquerIterative(0, 10);
    reduceAndConquerIterativeWithLoop(0, 10);

    return 0;
}
