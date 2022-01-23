#include <assert.h>
#include <limits.h>
#include <string.h>

#include "radixSort.h"

/* in-place MSB radix sort for null-terminated strings */

/* helper routine for swapping */
static void
swapStrings(const char **a, const char **b)
{
    const char *temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

/* this is the internal routine that assumes all strings are equal for the
 * first k characters */
static void
radixSortInternal(int n, const char **a, int k)
{
    int i;
    int count[UCHAR_MAX+1];  /* number of strings with given character in position k */
    int mode;                /* most common position-k character */
    const char **bucket[UCHAR_MAX+1]; /* position of character block in output */
    const char **top[UCHAR_MAX+1];    /* first unused index in this character block */

    /* loop implements tail recursion on most common character */
    while(n > 1) {

        /* count occurrences of each character */
        memset(count, 0, sizeof(int)*(UCHAR_MAX+1));

        for(i = 0; i < n; i++) {
            count[(unsigned char) a[i][k]]++;
        }

        /* find the most common nonzero character */
        /* we will handle this specially */
        mode = 1;
        for(i = 2; i < UCHAR_MAX+1; i++) {
            if(count[i] > count[mode]) {
                mode = i;
            }
        }

        if(count[mode] < n) {

            /* generate bucket and top fields */
            bucket[0] = top[0] = a;
            for(i = 1; i < UCHAR_MAX+1; i++) {
                top[i] = bucket[i] = bucket[i-1] + count[i-1];
            }

            /* reorder elements by k-th character */
            /* this is similar to dutch flag algorithm */
            /* we start at bottom character and swap values out until everything is in place */
            /* invariant is that for all i, bucket[i] <= j < top[i] implies a[j][k] == i */
            for(i = 0; i < UCHAR_MAX+1; i++) {
                while(top[i] < bucket[i] + count[i]) {
                    if((unsigned char) top[i][0][k] == i) {
                        /* leave it in place, advance bucket */
                        top[i]++;
                    } else {
                        /* swap with top of appropriate block */
                        swapStrings(top[i], top[(unsigned char) top[i][0][k]]++);
                    }
                }
            }

            /* we have now reordered everything */
            /* recurse on all but 0 and mode */
            for(i = 1; i < UCHAR_MAX+1; i++) {
                if(i != mode) {
                    radixSortInternal(count[i], bucket[i], k+1);
                }
            }

            /* tail recurse on mode */
            n = count[mode];
            a = bucket[mode];
            k = k+1;

        } else {

            /* tail recurse on whole pile */
            k = k+1;
        }
    }
}

void
radixSort(int n, const char **a)
{
    radixSortInternal(n, a, 0);
}
