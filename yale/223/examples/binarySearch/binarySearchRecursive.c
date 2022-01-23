#include <stddef.h>

#include "binarySearch.h"

int
binarySearch(int target, const int *a, size_t length)
{
    size_t index;

    index = length/2;

    if(length == 0) {
        /* nothing left */
        return 0;
    } else if(target == a[index]) {
        /* got it */
        return 1;
    } else if(target < a[index]) {
        /* recurse on bottom half */
        return binarySearch(target, a, index);
    } else {
        /* recurse on top half */
        /* we throw away index+1 elements (including a[index]) */
        return binarySearch(target, a+index+1, length-(index+1));
    }
}
