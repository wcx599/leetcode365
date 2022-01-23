#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "heapsort.h"

static void
swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

static size_t
parent(size_t i)
{
    return (i-1)/2;
}

static void
floatUp(size_t i, int *a)
{
    if(i != 0 && a[parent(i)] < a[i]) {
        swap(&a[parent(i)], &a[i]);
        floatUp(parent(i), a);
    }
}

static size_t
child(size_t i, int side)
{
    return 2*i + 1 + side;
}

static void
floatDown(size_t i, size_t n, int *a)
{
    size_t bigger = child(i,0);

    // need to check if bigger >= n
    if(bigger < n) {
        if(bigger + 1 < n && a[bigger+1] > a[bigger]) {
            // right child exists and is bigger
            bigger = bigger + 1;
        }

        // bigger now is index of the bigger child
        // is that child bigger than me?
        if(a[bigger] > a[i]) {
            swap(&a[bigger], &a[i]);
            floatDown(bigger, n, a);
        }
    }
}

void
heapsort(size_t n, int *a)
{
    // Build a heap in place using the packed array trick.
    //
    // The heap variable tracks the number of elements
    // in the heap, and is also the index of the first
    // array element *not* in the heap.
    size_t heap = 0;

    // insert everything into heap, one element
    // at a time
    while(heap < n) {
        // By incrementing heap, we shift a[heap]
        // from the unsorted region to be a new
        // leaf in the heap.
        // We may then have to float it up to restore
        // the heap property.
        floatUp(heap++, a);
    }

    while(heap > 0) {
        // By swapping a[0] to a[--heap],
        // we are moving the old biggest heap
        // element a[0] into the sorted array region,
        // while moving the old rightmost leaf
        // a[heap-1] to the top of the heap at a[0].
        // We may then have to float it down to restore
        // the heap property.
        swap(&a[0], &a[--heap]);
        floatDown(0, heap, a);  // float new root down
    }
}
