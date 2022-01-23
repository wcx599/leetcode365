#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void
recursive(int countDown)
{
    printf("Down: %d\n", countDown);

    if(countDown > 0) {
        recursive(countDown-1);
    }

    printf("Up: %d\n", countDown);
}

/* return max value among n 1st elements of a */
int
maxValue(const int *a, int n)
{
    int maxTail;

    assert(n >= 1);

    if(n == 1) {
        return a[0];
    }
    /* else */
    printf("Calling maxValue on %d elements starting at %p\n", n-1, a+1);
    maxTail = maxValue(a+1, n-1);
    printf("Got %d from maxValue\n", maxTail);

    if(a[0] > maxTail) {
        return a[0];
    } else {
        return maxTail;
    }
}

/* maxValue using accumulator */
/* returns max value in a or accum */
static int
maxValueAccumHelper(int *a, int n, int accum)
{
    for(;;) {
        printf("maxValueAccumHelper(%p, %d, %d)\n", a, n, accum);

        if(n == 0) {
            return accum;
        } else if(a[0] > accum) {
            /* return maxValueAccumHelper(a+1, n-1, a[0]); */
            accum = a[0];
            a = a+1;
            n = n-1;
        } else {
            /* return maxValueAccumHelper(a+1, n-1, accum); */
            a = a+1;
            n = n-1;
        }
    }
}

int
maxValueAccum(int *a, int n)
{
    assert(n >= 1);
    return maxValueAccumHelper(a+1, n-1, a[0]);
}


/* return 1 if target is in first n elements of a */
/* return 0 otherwise */
/* assumes a is sorted */
int
binarySearchRecursive(int target, int *a, int n)
{
    int mid;

    mid = n/2;

    printf("binarySearchRecursive(%d, %p, %d)\n", target, a, n);

    if(n == 0) {
        return 0;
    } else if(a[mid] == target) {
        return 1;
    } else if(a[mid] < target) {
        /* target is in upper half */
        return binarySearchRecursive(target, a+(mid+1), n-(mid+1));
    } else {
        /* target is in lower half */
        return binarySearchRecursive(target, a, mid);
    }
}

/* return 1 if target is in first n elements of a */
/* return 0 otherwise */
/* assumes a is sorted */
int
binarySearchIterative(int target, int *a, int n)
{
    int mid;

    for(;;) {

        mid = n/2;

        printf("binarySearchIterative(%d, %p, %d)\n", target, a, n);

        if(n == 0) {
            return 0;
        } else if(a[mid] == target) {
            return 1;
        } else if(a[mid] < target) {
            /* target is in upper half */
            /* return binarySearchRecursive(target, a+(mid+1), n-(mid+1)); */
            a = a+(mid+1);
            n = n-(mid+1);
        } else {
            /* target is in lower half */
            /* return binarySearchRecursive(target, a, mid); */
            n = mid;
        }
    }
}

#define N (10)

int
main(int argc, char **argv)
{
    int i;
    int a[N];

    for(i = 0; i < N; i++) {
        a[i] = 3*i + 11;
    }

    /* what is max value in a? */
    /* printf("maxValue = %d\n", maxValue(a, N)); */

#if 0
    printf("binarySearchRecursive(10000000, a, N) == %d\n", binarySearchRecursive(1000000, a, N));
    printf("binarySearchRecursive(1000, a, N) == %d\n", binarySearchRecursive(1000, a, N));
    printf("binarySearchRecursive(311, a, N) == %d\n", binarySearchRecursive(311, a, N));

    printf("binarySearchIterative(10000000, a, N) == %d\n", binarySearchIterative(1000000, a, N));
    printf("binarySearchIterative(1000, a, N) == %d\n", binarySearchIterative(1000, a, N));
    printf("binarySearchIterative(311, a, N) == %d\n", binarySearchIterative(311, a, N));
#endif

    printf("maxValueAccum(a, N) == %d\n", maxValueAccum(a, N));

    return 0;
}
