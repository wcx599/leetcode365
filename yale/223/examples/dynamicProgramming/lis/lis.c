#include <stdlib.h>
#include <assert.h>

#include "lis.h"

unsigned long
longest_increasing_subsequence(const int a[], unsigned long n, int *output)
{
    struct lis_data {
        unsigned long length;             /* length of LIS ending at this point */
        unsigned long prev;               /* previous entry in the LIS ending at this point */
    } *table;

    unsigned long best;      /* best entry in table */
    unsigned long scan;      /* used to generate output */

    unsigned long i;            
    unsigned long j;
    unsigned long best_length;

    /* special case for empty table */
    if(n == 0) return 0;

    table = malloc(sizeof(*table) * n);

    for(i = 0; i < n; i++) {
        /* default best is just this element by itself */
        table[i].length = 1;
        table[i].prev = n;              /* default end-of-list value */

        /* but try all other possibilities */
        for(j = 0; j < i; j++) {
            if(a[j] < a[i] && table[j].length + 1 > table[i].length) {
                /* we have a winner */
                table[i].length = table[j].length + 1;
                table[i].prev = j;
            }
        }
    }

    /* now find the best of the lot */
    best = 0;

    for(i = 1; i < n; i++) {
        if(table[i].length > table[best].length) {
            best = i;
        }
    }

    /* table[best].length is now our return value */
    /* save it so that we don't lose it when we free table */
    best_length = table[best].length;

    /* do we really have to compute the output? */
    if(output) {
        /* yes :-( */
        scan = best;
        for(i = 0; i < best_length; i++) {
            assert(scan >= 0);
            assert(scan < n);

            output[best_length - i - 1] = a[scan];

            scan = table[scan].prev;
        }
    }

    free(table);

    return best_length;
}
