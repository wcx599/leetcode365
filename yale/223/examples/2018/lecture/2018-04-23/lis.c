#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

// compute longest increasing subsequence of a string
// returns lis as malloc'd string, called should free
char *
lis(const char *s)
{
    // length of s
    size_t n = strlen(s);

    assert(n > 0);

    // length of lis ending at position i
    size_t *length = calloc(n, sizeof(size_t));

    // previous position in sequence
    size_t *prev = calloc(n, sizeof(size_t));

    // dynamic programming, build table
    for(size_t i = 0; i < n; i++) {
        // compute lis ending at s[i]
        length[i] = 1;  // can always do s[i] alone
        prev[i] = i;    // placeholder

        // look at all previous j
        for(size_t j = 0; j < i; j++) {
            if(s[j] < s[i]) {
                if(length[j] + 1 > length[i]) {
                    // pick this sequence instead
                    length[i] = length[j] + 1;
                    prev[i] = j;
                }
            }
        }
    }

    // generate output sequence
    size_t best = 0;  // best starting point

    for(size_t i = 1; i < n; i++) {
        if(length[i] > length[best]) {
            best = i;
        }
    }

    char *output = malloc(length[best]+1);
    output[length[best]] = '\0';

    for(size_t i = best;; i = prev[i]) {
        output[length[i] - 1] = s[i];
        if(length[i] == 1) {
            // done
            break;
        }
    }

    return output;
}


int
main(int argc, char **argv)
{

    if(argc != 2) {
        fprintf(stderr, "Usage: string %s\n", argv[0]);
        return 1;
    }

    char *output = lis(argv[1]);
    puts(output);
    free(output);

    return 0;
}
