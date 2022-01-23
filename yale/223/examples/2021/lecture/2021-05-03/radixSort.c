#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <limits.h>

// Sort n strings in strings 
// using auxiliary space in buffer
// and skipping first skip characters.
static void
radixSortInternal(size_t n, 
        char **strings, 
        char **buffer,
        size_t skip)
{
    size_t count[UCHAR_MAX+1];
    size_t bucket[UCHAR_MAX+1];
    size_t top[UCHAR_MAX+1];

#ifdef DEBUG
    fprintf(stderr, "Sorting at depth %zu:", skip);
    for(size_t i = 0; i < n; i++) {
        fprintf(stderr, " %s", strings[i]);
    } 
    putc('\n', stderr);
#endif

    // initialize counts
    for(int i = 0; i <= UCHAR_MAX; i++) {
        count[i] = 0;
    }

    // count
    for(size_t i = 0; i < n; i++) {
        count[(unsigned char) strings[i][skip]]++;
    }

    // find start of buckets
    top[0] = bucket[0] = 0;
    for(int i = 1; i <= UCHAR_MAX; i++) {
        top[i] = bucket[i] = bucket[i-1] + count[i-1];
    }

    // copy strings into buckets
    for(size_t i = 0; i < n; i++) {
        buffer[top[(unsigned char) strings[i][skip]]++] = strings[i];
    }

    // copy buffer back into strings
    memcpy(strings, buffer, sizeof(char *) * n);

    // recurse on non-'\0' buckets with at least 2 elements
    for(int i = 1; i <= UCHAR_MAX; i++) {
        if(count[i] > 1) {
            radixSortInternal(count[i],
                    strings + bucket[i],
                    buffer,
                    skip + 1);
        }
    }
}

void
radixSort(size_t n, char **strings)
{
    // set up buffer space then call radixSortInternal
    char **buffer = calloc(n, sizeof(char *));

    radixSortInternal(n, strings, buffer, 0);

    free(buffer);
}
