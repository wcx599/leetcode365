#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

// Short but mediocre implementation of quicksort
//
// What this does wrong:
//
// Recursion stops at size 1 instead of switching to faster
// algorithm for small n.
//
// Cheap knock-off of dutch flag algorithm just sorts into two
// regions (<= and >) instead of three (<, =, >), giving
// no guarantee of progress in the worst case.
//
// This is an example of a programmer time vs execution
// time trade-off that probably favors programmer time
// a little too much.
static void
quickSort(size_t n, int a[])
{
    printf("quickSort(%d, %p)\n", n, a);

    if(n > 1) {
        size_t index = random() % n;
        int pivot = a[index];

        // dutch flag algorithm with equal region omitted
        // invariant: everything < lo is <= pivot
        size_t lo = 0;
        // invariant: everything > hi is > pivot
        size_t hi = n-1;
        // first unprocessed element is a[lo]
        while(lo <= hi) {
            if(a[lo] <= pivot) {
                // goes in the low side
                lo++;
            } else {
                // goes in the high side
                int temp = a[hi];
                a[hi] = a[lo];
                a[lo] = temp;
                hi--;
            }
        }

        // now sort pieces
        quickSort(lo, a);
        quickSort(n - lo, a + lo);
    }
}

int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    int a[10] = { 117, 37, 565, 929, 110, 1919, 19, 111, 55, 71 };

    quickSort(10, a);

    for(int i = 0; i < 10; i++) {
        printf("%d\n", a[i]);
    }

    return 0;
}
