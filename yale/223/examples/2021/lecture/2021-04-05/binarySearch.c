#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

// return pointer to location
// containing x, or 0 if not found
int *
binarySearch(size_t n, int a[], int x)
{
    if(n == 0) {
        // it's not there
        return 0;
    } 
    // else

    size_t mid = n/2;

    if(a[mid] == x) {
        return &a[mid];
    } else if(a[mid] > x) {
        // x is in the bottom half
        return binarySearch(mid, a, x);
    } else {
        // x is in the top half
        return binarySearch(n - mid - 1, a + mid + 1, x);
    }
}

// iterative version
// return pointer to location
// containing x, or 0 if not found
int *
binarySearchIterative(size_t n, int *a, int x)
{
    for(;;) {
        if(n == 0) {
            // it's not there
            return 0;
        } 
        // else

        size_t mid = n/2;

        if(a[mid] == x) {
            return &a[mid];
        } else if(a[mid] > x) {
            // x is in the bottom half
            n = mid;
        } else {
            // x is in the top half
            n = n - mid - 1;
            a = a + mid + 1;
        }
    }
}

int
main(int argc, char **argv)
{

    if(argc != 2) {
        fprintf(stderr, "Usage: %s target\n", argv[0]);
        return 1;
    }

    int a[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

    int target = atoi(argv[1]);

    // int *location = binarySearch(10, a, target);
    int *location = binarySearchIterative(10, a, target);

    if(location == 0) {
        puts("not found");
    } else {
        printf("found at index %d\n", location - a);
    }

    return 0;
}
