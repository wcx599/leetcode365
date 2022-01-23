// angle brackets means search /usr/include
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

// gets declaration of printFactors
// single-quotes means search current directory
#include "printFactors.h"

// firstFactor returns smallest non-trivial factor of n
// static makes it invisible outside this file
static int
firstFactor(int n)
{
    for(int i = 2;; i++) {
        if(n % i == 0) {
            // i evenly divides n
            return i;
        }
    }

    // shouldn't get here
    assert(0);
    return n;
}

// print prime factors of n to stdout
// in increasing order
void
printFactors(int n)
{
    int factor;

    assert(n > 1);  // doesn't work if n < 2

    for(;;) {
        factor = firstFactor(n);
        if(factor == n) {
            printf("%d\n", n);
            return;
        }  else {
            printf("%d ", factor);
            n /= factor;
        }
    }
}
